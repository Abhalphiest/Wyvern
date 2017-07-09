#ifndef _LOG_H
#pragma once
#define _LOG_H

#include "definitions.h"
#include "debug/log/log_settings.h"
#include "debug/debug_definitions.h"
#include "utility/file.h"


struct s_log_data
{
	bool m_create_log = true; //by default, create a log if it doesn't exist
	char m_log_path[1024] = { 0 }; //initialize to empty string
	stream_field m_logged_streams = debug_stream |
		error_stream |
		event_stream |
		console_stream; //log everything by default

	bool m_append_log = false; //overwrite the log by default
	file* m_log;
};


class c_debug_log
{
public:
	void set_log_append();
	void set_log_overwrite();
	void set_logged_streams(stream_field streams);
	void disable_log_creation();
	void enable_log_creation();
	void set_log_path(char path[1028]);
	void write_to_log(const char* msg);
	~c_debug_log();
	c_debug_log();
private:
	struct s_log_data log_data;
};

#endif