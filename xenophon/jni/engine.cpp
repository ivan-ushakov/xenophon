#include "engine.h"

#include <cmath>

#include "log.h"
#include "common.h"

engine_t::engine_t() : object_t("engine")
{

}

void engine_t::create()
{
    LOGI("creating engine...");
    SLresult result = slCreateEngine(&_object, 0, NULL, 0, NULL, NULL);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to create engine");
        throw sl_exception(result);
    }
    realize();

    result = (*_object)->GetInterface(_object, SL_IID_ENGINE, &_engine);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to get engine interface");
        throw sl_exception(result);
    }

    create_output_mix();
    create_player();
}

void engine_t::add_plugin(std::unique_ptr<plugin_t> &plugin)
{
    plugin->set_sample_rate(44100);
    plugin->prepare_for_play();
    _plugins.push_back(std::move(plugin));
}

std::unique_ptr<player_t> &engine_t::player()
{
    return _player;
}

void engine_t::create_output_mix()
{
    LOGI("creating output mix...");

    SLObjectItf object;
    SLresult result = (*_engine)->CreateOutputMix(_engine, &object, 0, NULL, NULL);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to create output mix");
        throw sl_exception(result);
    }

    _output_mix = std::unique_ptr<output_mix_t>(new output_mix_t(object));
    _output_mix->realize();
}

void engine_t::create_player()
{
    LOGI("creating player...");

    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 4};
    SLDataFormat_PCM format_pcm = {
        SL_DATAFORMAT_PCM, 
        2, 
        SL_SAMPLINGRATE_44_1,
        SL_PCMSAMPLEFORMAT_FIXED_16, 
        SL_PCMSAMPLEFORMAT_FIXED_16,
        SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, 
        SL_BYTEORDER_LITTLEENDIAN
    };
    SLDataSource audio_source = {&loc_bufq, &format_pcm};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, _output_mix->object()};
    SLDataSink audio_sink = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[1] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};
    SLObjectItf object;
    SLresult result = (*_engine)->CreateAudioPlayer(_engine, &object, &audio_source, &audio_sink, 1, ids, req);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to create player");
        throw sl_exception(result);
    }

    _player = std::unique_ptr<player_t>(new player_t(object));
    _player->realize();
    _player->setup();

    std::function<void(std::vector<char> &buffer)> f = [&](std::vector<char> &buffer) { process_plugins(buffer); };
    _player->set_handler(f);
}

void engine_t::process_plugins(std::vector<char> &buffer)
{
    LOGI("process plugins...");

    std::vector<float> input_buffer(2);
    std::vector<float> output_buffer(2);

    size_t frame_size = 2 * 2;
    size_t frame_count = buffer.size() / frame_size;
    for (size_t frame = 0; frame < frame_count; frame++)
    {
        for (size_t i = 0; i < _plugins.size(); i++)
        {
            std::unique_ptr<plugin_t> &p = _plugins[i];
            p->process_audio_frame(input_buffer, output_buffer, 2, 2);
        }

        size_t frame_offset = frame_size * frame;
        size_t channel_offset = output_buffer.size(); 
        for (size_t j = 0; j < output_buffer.size(); j++)
        {
            int sample = floor(32768 * output_buffer[j]);        
            buffer[frame_offset + channel_offset * j] = sample & 0xFF;
            buffer[frame_offset + channel_offset * j + 1] = (sample >> 8) & 0xFF;
        }
    }
}
