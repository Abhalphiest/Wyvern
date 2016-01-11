#ifndef _MATERIALMASTER_H
#define _MATERIALMASTER_H
#include "definitions.h"
class MaterialMaster{

	
	struct Material
	{
		GLuint m_shaderID;
		GLuint m_textureID;

	};
	struct Texture
	{
		uint m_width;
		uint m_height;
		uint m_imageSize;
		std::vector<char> m_data;
	};

public:
	bool LoadBMP(char* p_filepath, uint p_materialID);
	bool LoadTGA(char* p_filepath, uint p_materialID);
	uint CreateMaterial(void);

private:
	std::map<GLuint, Texture> m_textureIDmap;
};
#endif