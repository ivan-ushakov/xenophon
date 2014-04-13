#ifndef _BEATPAD_MONO_SYNTH
#define _BEATPAD_MONO_SYNTH

#include <memory>

#include "plugin.h"
#include "wtoscillator.h"

class mono_synth_t : public plugin_t
{
	std::vector<float> _note_table;
	std::unique_ptr<wt_oscillator_t> _oscillator;
	uint32_t _midi_note;

public:
    mono_synth_t();

    bool prepare_for_play();
    bool process_audio_frame(const std::vector<float> &input_buffer, std::vector<float> &output_buffer, 
    	unsigned int input_channel_count, unsigned int ouput_channel_count);

    bool midi_note_on(uint32_t channel, uint32_t midi_note, uint32_t velocity);
    bool midi_note_off(uint32_t channel, uint32_t midi_note, uint32_t velocity, bool all_notes_off);
};

#endif