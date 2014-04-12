#ifndef _BEATPAD_PLUGIN
#define _BEATPAD_PLUGIN

#include <vector>

inline float dLinTerp(float x1, float x2, float y1, float y2, float x)
{
	float denom = x2 - x1;
	if (denom == 0)
		return y1; // should not ever happen

	// calculate decimal position of x
	float dx = (x - x1) / (x2 - x1);

	// use weighted sum method of interpolating
	float result = dx * y2 + (1 - dx) * y1;

	return result;
}

class plugin_t
{
protected:
	unsigned int _sample_rate;

public:
    plugin_t() {};
    virtual ~plugin_t() {};

    virtual bool prepare_for_play() = 0;
    virtual bool process_audio_frame(const std::vector<float> &input_buffer, std::vector<float> &output_buffer, 
    	unsigned int input_channel_count, unsigned int ouput_channel_count) = 0;
    virtual bool user_interface_change(int control_index) = 0;

    void set_sample_rate(unsigned int sample_rate)
    {
    	_sample_rate = sample_rate;
    }
};

#endif
