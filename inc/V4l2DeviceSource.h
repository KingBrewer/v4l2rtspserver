/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** v4l2DeviceSource.h
** 
** V4L2 source 
**
** -------------------------------------------------------------------------*/


#ifndef V4L2_DEVICE_SOURCE
#define V4L2_DEVICE_SOURCE

#include <string>
#include <list> 
#include <iostream>

// live555
#include <liveMedia.hh>

// ---------------------------------
// V4L2 FramedSource
// ---------------------------------
const char marker[] = {0,0,0,1};
class V4L2DeviceSource: public FramedSource 
{
	public:
		// ---------------------------------
		// V4L2 Capture parameters
		// ---------------------------------
		struct V4L2DeviceParameters 
		{
			V4L2DeviceParameters(const char* devname, int format, int queueSize, int width, int height, int fps, bool verbose,const std::string & outputFile) : 
				m_devName(devname), m_format(format), m_queueSize(queueSize), m_width(width), m_height(height), m_fps(fps), m_verbose(verbose), m_outputFIle(outputFile) {};
				
			std::string m_devName;
			int m_width;
			int m_height;
			int m_format;
			int m_queueSize;
			int m_fps;			
			bool m_verbose;
			std::string m_outputFIle;
		};

		// ---------------------------------
		// Captured frame
		// ---------------------------------
		struct Frame
		{
			Frame(char* buffer, int size, timeval timestamp) : m_buffer(buffer), m_size(size), m_timestamp(timestamp) {};
			~Frame()  { delete m_buffer; };
			
			char* m_buffer;
			int m_size;
			timeval m_timestamp;
		};
		
		// ---------------------------------
		// Compute simple stats
		// ---------------------------------
		class Stats
		{
			public:
				Stats(const std::string & msg) : m_fps(0), m_fps_sec(0), m_size(0), m_msg(msg) {};
				
			public:
				int notify(int tv_sec, int framesize);
			
			protected:
				int m_fps;
				int m_fps_sec;
				int m_size;
				const std::string m_msg;
		};
		
	public:
		int getBufferSize() { return m_bufferSize; };
		std::string getAuxLine() { return m_auxLine; };

	protected:
		V4L2DeviceSource(UsageEnvironment& env, V4L2DeviceParameters params);
		virtual ~V4L2DeviceSource();

	protected:
		bool init(unsigned int mandatoryCapabilities);
		int initdevice(const char *dev_name, unsigned int mandatoryCapabilities);
		int checkCapabilities(int fd, unsigned int mandatoryCapabilities);
		int configureFormat(int fd);
		int configureParam(int fd);		
		int xioctl(int fd, int request, void *arg);
	
		static void deliverFrameStub(void* clientData) {((V4L2DeviceSource*) clientData)->deliverFrame();};
		void deliverFrame();
		static void incomingPacketHandlerStub(void* clientData, int mask) { ((V4L2DeviceSource*) clientData)->getNextFrame(); };
		void getNextFrame();
		bool processConfigrationFrame(char * frame, int frameSize);
		void processFrame(char * frame, int &frameSize, const timeval &ref);
		void queueFrame(char * frame, int frameSize, const timeval &tv);

		// overide FramedSource
		virtual void doGetNextFrame();	
		virtual void doStopGettingFrames();
			
	protected:
		virtual bool captureStart() = 0;
		virtual size_t read(char* buffer, size_t bufferSize) = 0;
		virtual bool captureStop() = 0;
		
	protected:
		V4L2DeviceParameters m_params;
		int m_fd;
		int m_bufferSize;
		std::list<Frame*> m_captureQueue;
		Stats m_in;
		Stats m_out;
		EventTriggerId m_eventTriggerId;
		FILE* m_outfile;
		std::string m_auxLine;
};

#endif