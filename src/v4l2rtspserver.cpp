#include "v4l2rtspserver.h"

#include <stdio.h>
#include <string.h>

#include "commonserverruntime.h"

namespace v4l2rtspserver {

SERVER_CONTEXT CTX;

int run_streamer(const char* video_source, const unsigned short& rtspPort, const int& width, const int& height, const int& fps, bool vflip, bool hflip, const int& rotation)
{
    (void)vflip;
    (void)hflip;
    (void)rotation;
    std::string vsrc = std::string(video_source, strnlen(video_source, 255));
    CTX.ctl_params.dev_name = video_source;
    CTX.ctl_params.width = width;
    CTX.ctl_params.height = height;
    CTX.ctl_params.fps = fps;
    CTX.ctl_params.devList.push_back(vsrc);
    CTX.ctl_params.rtspPort = rtspPort;

    return start_server(CTX);
}

int stop_streamer()
{
    stop_server(CTX);
    return wait_for_server(CTX);
}

}
