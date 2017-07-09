#pragma once

#ifndef _FILE_H
#define _FILE_H

#include"definitions.h"

struct file
{
	FILE* m_file;
	const char* m_path;
	uint m_references;
};

file* open_file(const char* path, bool append);
void  close_file(file* file);
void  clear_file(file* file);
void  append_file(file* file, const char* str);
void  overwrite_file(file* file, const char* str);
file* create_file(const char* path);

#endif