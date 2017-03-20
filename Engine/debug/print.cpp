#include "print.h"

void print(stream_field streams, const char* msg)
{
	if (is_console_active() && (streams & console_stream))
	{
		fprintf(stdout, msg);
	}
	if (is_console_active() && (streams & error_stream))
	{
		fprintf(stderr, msg);
	}
	if (is_console_active() && (streams & debug_stream))
	{

	}
	if (is_console_active() && (streams & event_stream))
	{

	}
}
void print_va(stream_field streams, const char* msg, int argc, ...)
{

}