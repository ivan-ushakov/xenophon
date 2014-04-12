#ifndef _BEATPAD_PLAYER
#define _BEATPAD_PLAYER

#include <memory>
#include <vector>
#include <functional>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "object.h"

class player_t : public object_t
{
    SLPlayItf _player;
    SLAndroidSimpleBufferQueueItf _queue;
    
    std::vector<char> _queue_buffer;
    unsigned int _output_frame_count;

    std::function<void(std::vector<char> &buffer)> _handler;

public:
    player_t(SLObjectItf object) : object_t("player", object) {};

    void setup();
    
    void set_handler(std::function<void(std::vector<char> &buffer)> &handler)
    {
        _handler = handler;
    }
    
    void start();
    void stop();

    void process();
};

#endif
