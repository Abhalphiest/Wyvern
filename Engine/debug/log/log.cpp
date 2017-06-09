#include "log.h"
#ifdef PLATFORM_WINDOWS_64

void c_debug_log::set_log_append() { log_data.m_append_log = true; }
void c_debug_log::set_log_overwrite() { log_data.m_append_log = false; }
void c_debug_log::set_logged_streams(stream_field streams) { log_data.m_logged_streams = streams; }
void c_debug_log::disable_log_creation() { log_data.m_create_log = false; }
void c_debug_log::enable_log_creation() { log_data.m_create_log = true; }
void c_debug_log::set_log_path(char path[1028]) { _memccpy(&log_data.m_log_path, &path, 0, 1028); }
void c_debug_log::write_to_log(const char* msg){}
c_debug_log::c_debug_log(){}
c_debug_log::~c_debug_log(){}

#endif