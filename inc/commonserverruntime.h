#ifndef COMMONSERVERRUNTIME_H
#define COMMONSERVERRUNTIME_H

#include <list>
#include <string>
#include "V4l2Access.h"


struct SERVER_CONTROL_PARAMETERS {
    // default parameters
    const char *dev_name;
    unsigned int format;
    std::list<unsigned int> videoformatList;
    int width;
    int height;
    int queueSize;
    int fps;
    unsigned short rtspPort;
    unsigned short rtspOverHTTPPort;
    bool multicast;
    int verbose;
    std::string outputFile;
    V4l2Access::IoType ioTypeIn;
    V4l2Access::IoType ioTypeOut;
    std::string url;
    std::string murl;
    bool useThread;
    std::string maddr;
    bool repeatConfig;
    int timeout;
    bool muxTS;
    int defaultHlsSegment;
    unsigned int hlsSegment;
    const char* realm;
    std::list<std::string> userPasswordList;
#ifdef HAVE_ALSA
    int audioFreq;
    int audioNbChannels;
    std::list<snd_pcm_format_t> audioFmtList;
    snd_pcm_format_t audioFmt;
#endif
    std::list<std::string> devList;

    SERVER_CONTROL_PARAMETERS();
    bool parse_input_params(int argc, char** argv);
    void display_help();
};

struct SERVER_CONTEXT {
    pthread_t thr;
    char quit;
    SERVER_CONTROL_PARAMETERS ctl_params;

    SERVER_CONTEXT() { quit = 0; }
};

int start_server(SERVER_CONTEXT& server_params);
int wait_for_server(SERVER_CONTEXT& server_params);
void stop_server(SERVER_CONTEXT& server_params);

void display_help(const SERVER_CONTROL_PARAMETERS& params);

#endif // COMMONSERVERRUNTIME_H
