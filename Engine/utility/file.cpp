
#include"file.h"

file* open_file(const char* path, bool append) 
{
	file* returnfile = nullptr;
	FILE* basefile = fopen(path, "r+");
	if (basefile != NULL)
	{
		//change once we have a memory allocator
		returnfile = (file*)malloc(sizeof(file));
		returnfile->m_file = basefile;
		returnfile->m_references = 1;
		returnfile->m_path = path;
	}
	return returnfile;
}
void  close_file(file* file)
{
	assert(file != nullptr);
	fclose(file->m_file);
}
void  clear_file(file* file)
{
	assert(file != nullptr);
	
}
void  append_file(file* file, const char* str)
{
	assert(file != nullptr);
}
void  overwrite_file(file* file, const char* str)
{
	assert(file != nullptr);
}
file* create_file(const char* path)
{
	return nullptr;
}