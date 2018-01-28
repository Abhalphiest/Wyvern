#ifndef __WINDOW_H__
#define __WINDOW_H__
#pragma once

#ifndef window_id
#define window_id uint
#endif

namespace Window
{
	//constants
	const uint k_max_windows_registered = 2; // the maximum number of windows that can exist

	struct s_window_params
	{
		const char* m_title;
		uint m_xpos, m_ypos, m_width, m_height;
		bool fullscreen;
		window_id m_parent;
	};

	enum e_window_option
	{
		window_filler_option,
	};

	enum e_dialog_option
	{
		dialog_filler_option,
	};

	//function declarations
	void window_system_init(s_platform_data platform_data);
	uint make_window(s_window_params* parameters, e_window_option options, s_platform_data platform_data);
	uint make_dialog_window(const char* title, const char* text, e_dialog_option options);
	window_id get_platform_window_id(uint index);
	uint get_window_width(uint index);
	uint get_window_height(uint index);
	void close_window(uint index);
	bool make_window_fullscreen(uint index, int width, int height, int colourBits, int refreshRate);
	bool make_window_windowed(uint index);


}


#endif
