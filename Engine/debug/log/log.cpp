#include "log.h"


bool g_create_log = true; //by default, create a log if it doesn't exist
char g_log_path[1024] = { 0 }; //initialize to empty string


stream_field g_logged_streams = debug_stream |
error_stream |
event_stream |
console_stream; //log everything by default

bool g_append_log = false; //overwrite the log by default


						   //some helper functions

void set_log_append() { g_append_log = true; }
void set_log_overwrite() { g_append_log = false; }
void set_logged_streams(stream_field streams) { g_logged_streams = streams; }
void disable_log_creation() { g_create_log = false; }
void enable_log_creation() { g_create_log = true; }
void set_log_path(char path[1028]) { memccpy(&g_log_path, &path, 0, 1028); }