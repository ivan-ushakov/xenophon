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
	bool _is_note_on;

public:
    wt_oscillator_t();

    bool prepare_for_play();
    bool process_audio_frame(const std::vector<float> &input_buffer, std::vector<float> &output_buffer, 
    	unsigned int input_channel_count, unsigned int ouput_channel_count);
    bool user_interface_change(int control_index);

private:
	void reset();
	void cook_frequency();
};

#endif