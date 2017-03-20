#ifndef _LOG_H
#pragma once
#define _LOG_H

#include "wyvern.h"
#include "log_settings.h"

typedef __int8 stream_field;
enum e_streams
{
	debug_stream = 1,
	error_stream = 2,
	event_stream = 4,
	console_stream = 8
};

void set_log_append();
void set_log_overwrite();
void set_logged_streams(stream_field streams);
void disable_log_creation();
void enable_log_creation();
void set_log_path(char path[1028]);


#endif