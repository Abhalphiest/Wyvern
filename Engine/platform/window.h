#ifndef __WINDOW_H__
#define __WINDOW_H__
#pragma once
//includes

#include"platform.h"

#ifndef window_id
#define window_id uint
#endif

namespace Window
{
	//constants
	const uint k_max_windows_registered = 10;

	struct s_window_params
	{
		const char* m_title;
		uint m_xpos, m_ypos, m_width, m_height;
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
	void InitializeWindowSystem();
	uint MakeWindow(s_window_params* parameters, e_window_option options);
	uint MakeDialogWindow(const char* title, const char* text, e_dialog_option options);



}


#endif
