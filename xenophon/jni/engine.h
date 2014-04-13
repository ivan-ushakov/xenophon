#ifndef _BEATPAD_ENGINE
#define _BEATPAD_ENGINE

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <memory>
#include <vector>

#include "player.h"
#include "plugin.h"

class output_mix_t : public object_t
{
public:
    output_mix_t(SLObjectItf object) : object_t("output mix", object) {};
};

class engine_t : public object_t
{
    SLEngineItf _engine;
    std::unique_ptr<output_mix_t> _output_mix;
    std::unique_ptr<player_t> _player;
    std::vector<std::unique_ptr<plugin_t>> _plugins;

public:
    engine_t();

    void create();
    void add_plugin(std::unique_ptr<plugin_t> &plugin);

    bool midi_note_on(uint32_t channel, uint32_t midi_note, uint32_t velocity);
    bool midi_note_off(uint32_t channel, uint32_t midi_note, uint32_t velocity, bool all_notes_off);

    std::unique_ptr<player_t> &player();

private:
    void create_output_mix();
    void create_player();

    void process_plugins(std::vector<char> &buffer);
};

#endif
