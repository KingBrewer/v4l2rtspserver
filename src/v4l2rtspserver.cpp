#include "v4l2rtspserver.h"

#include <syslog.h>

#include "commonserverruntime.h"

using namespace v4l2rtspserver;

SERVER_CONTEXT CTX;

int run_streamer(const char* video_source, const int& width, const int& height, const int& fps)
{
    CTX.ctl_params.dev_name = video_source;
    CTX.ctl_params.width = width;
    CTX.ctl_params.height = height;
    CTX.ctl_params.fps = fps;
    CTX.ctl_params.devList.push_back(video_source);

    return start_server(CTX);
}

int stop_streamer()
{
    stop_server(CTX);
    return 0;
}

