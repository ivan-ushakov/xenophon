#ifndef _BEATPAD_WT_OSCILLATOR
#define _BEATPAD_WT_OSCILLATOR

#include "plugin.h"

class wt_oscillator_t : public plugin_t
{

	const static std::size_t TABLE_SIZE = 1024;

	std::vector<float> _sin_table;
	float _frequency;
	float _read_index;
	float _increment;
	bool _note_on;

public:
    wt_oscillator_t();

    void set_frequency(float frequency);
    void set_note_on(bool note_on);

    bool prepare_for_play();
    bool process_audio_frame(const std::vector<float> &input_buffer, std::vector<float> &output_buffer, 
    	unsigned int input_channel_count, unsigned int ouput_channel_count);

    bool midi_note_on(uint32_t channel, uint32_t midi_note, uint32_t velocity) {};
    bool midi_note_off(uint32_t channel, uint32_t midi_note, uint32_t velocity, bool all_notes_off) {};

private:
	void reset();
	void cook_frequency();
};

#endif