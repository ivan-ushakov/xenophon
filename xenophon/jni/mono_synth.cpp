#include "mono_synth.h"

#include <cmath>

mono_synth_t::mono_synth_t() : _midi_note(0)
{
	_oscillator.reset(new wt_oscillator_t());

	_note_table.resize(46);
	for (size_t i = 0; i < _note_table.size(); i++)
		_note_table[i] = std::pow(2, ((float) i + 1 - _note_table.size()) / 12.0f) * 440;
}

bool mono_synth_t::prepare_for_play()
{
	_oscillator->set_sample_rate(_sample_rate);
	_oscillator->prepare_for_play();
	return true;
}

bool mono_synth_t::process_audio_frame(const std::vector<float> &input_buffer, std::vector<float> &output_buffer, 
	unsigned int input_channel_count, unsigned int ouput_channel_count)
{
	if (_midi_note != 0)
	{
		_oscillator->process_audio_frame(input_buffer, output_buffer, input_channel_count, ouput_channel_count);
	}	
	return true;
}

bool mono_synth_t::midi_note_on(uint32_t channel, uint32_t midi_note, uint32_t velocity)
{
	if (midi_note >= _note_table.size()) return true;

	_oscillator->set_frequency(_note_table[midi_note]);
	_oscillator->set_note_on(true);
	_midi_note = midi_note;
	return true;
}

bool mono_synth_t::midi_note_off(uint32_t channel, uint32_t midi_note, uint32_t velocity, bool all_notes_off)
{
	_oscillator->set_note_on(false);
	_midi_note = 0;
	return true;
}
