#include "player.h"

#include <exception>

#include "log.h"
#include "jni_common.h"
#include "common.h"

void player_callback(SLAndroidSimpleBufferQueueItf queue, void *context)
{
    player_t *player = (player_t *)context;
    if (player == NULL)
    {
        LOGE("player object not found");
    }
    else player->process();
}

void player_t::setup()
{
    LOGI("setup player...");

    SLresult result = (*_object)->GetInterface(_object, SL_IID_PLAY, &_player);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to get player interface");
        throw sl_exception(result);
    }

    result = (*_object)->GetInterface(_object, SL_IID_BUFFERQUEUE, &_queue);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to get queue interface");
        throw sl_exception(result);
    }

    result = (*_queue)->RegisterCallback(_queue, (slAndroidSimpleBufferQueueCallback)&player_callback, this);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to register callback");
        throw sl_exception(result);
    }

    _queue_buffer.resize(8000);
}

void player_t::start()
{
    SLresult result = (*_player)->SetPlayState(_player, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to play");
        throw sl_exception(result);
    }

    result = (*_queue)->Enqueue(_queue, _queue_buffer.data(), _queue_buffer.size());
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to enqueue data");
        throw sl_exception(result);
    }
}

void player_t::stop()
{
    SLresult result = (*_player)->SetPlayState(_player, SL_PLAYSTATE_STOPPED);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to stop");
        throw sl_exception(result);
    }
}

void player_t::process()
{
    _handler(_queue_buffer);
    SLresult result = (*_queue)->Enqueue(_queue, _queue_buffer.data(), _queue_buffer.size());
    if (result != SL_RESULT_SUCCESS)
        LOGE("fail to enqueue data: %x", result);
}
