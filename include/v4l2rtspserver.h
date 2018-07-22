#ifndef V4L2RTSPSERVER_H
#define V4L2RTSPSERVER_H

namespace v4l2rtspserver {

int run_streamer(const char* video_source, const int& width, const int& height, const int& fps);
int stop_streamer();

}

#endif // V4L2RTSPSERVER_H
