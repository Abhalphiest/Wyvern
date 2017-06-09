#include "print.h"
#include "../renderer/text_renderer.h"

void print(stream_field streams, const char* msg)
{
	bool use_console = is_console_active();
	if (use_console)
	{
		if (streams & console_stream)
		{
			fprintf(stdout, msg);
		}
		if (streams & error_stream)
		{
			fprintf(stderr, msg);
		}
		if (streams & debug_stream)
		{
//			write_to_log(msg);
		}
		if (streams & event_stream)
		{
			// TODO: fix this
			//render_string(msg, 0, 0);
		}
	}
}
void print_va(stream_field streams, const char* msg, int argc, ...)
{

}