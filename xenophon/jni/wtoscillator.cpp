#include "wtoscillator.h"

#include <cmath>

wt_oscillator_t::wt_oscillator_t() : _frequency(440), _read_index(0), _increment(0), _is_note_on(true)
{
	_sin_table.resize(TABLE_SIZE);
	for (size_t i = 0; i < TABLE_SIZE; i++)
		_sin_table[i] = sin((float)i / TABLE_SIZE * (2 * M_PI));
	cook_frequency();
}

bool wt_oscillator_t::prepare_for_play()
{
	reset();
	cook_frequency();
	return true;
}

bool wt_oscillator_t::process_audio_frame(const std::vector<float> &input_buffer, std::vector<float> &output_buffer, 
	unsigned int input_channel_count, unsigned int ouput_channel_count)
{
	if (!_is_note_on)
	{
		output_buffer[0] = 0;
		if (input_channel_count == 1 && ouput_channel_count == 2)
			output_buffer[1] = 0;
		if (input_channel_count == 2 && ouput_channel_count == 2)
			output_buffer[1] = 0;
		return true;
	}
	
	int read_index = (int) _read_index;
	float fraction = _read_index - read_index;
	int read_index_next = read_index + 1 > TABLE_SIZE - 1 ? 0 : read_index + 1;

	float out_sample = dLinTerp(0, 1, _sin_table[read_index], _sin_table[read_index_next], fraction);

	_read_index += _increment;
	if (_read_index > TABLE_SIZE) _read_index = _read_index - 1024;

	output_buffer[0] = out_sample;
	if (input_channel_count == 1 && ouput_channel_count == 2)
		output_buffer[1] = out_sample;
	if (input_channel_count == 2 && ouput_channel_count == 2)
		output_buffer[1] = out_sample;

	return true;
}

bool wt_oscillator_t::user_interface_change(int control_index)
{
	return true;
}

void wt_oscillator_t::reset()
{
	_read_index = 0;
}

void wt_oscillator_t::cook_frequency()
{
	_increment = TABLE_SIZE * _frequency / _sample_rate;
}
