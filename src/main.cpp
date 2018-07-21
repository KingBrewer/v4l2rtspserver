/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.cpp
** 
** V4L2 RTSP streamer                                                                 
**                                                                                    
** H264 capture using V4L2                                                            
** RTSP using live555                                                                 
**                                                                                    
** -------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "logger.h"
#include "commonserverruntime.h"


SERVER_CONTEXT CTX;

// -----------------------------------------
//    signal handler
// -----------------------------------------
void sighandler(int n)
{
    stop_server(CTX);
}

// -----------------------------------------
//    entry point
// -----------------------------------------
int main(int argc, char** argv) 
{
    if (CTX.ctl_params.parse_input_params(argc, argv)) {
        signal(SIGINT,sighandler);
        return start_server(CTX);
    }
    return 1;

}



