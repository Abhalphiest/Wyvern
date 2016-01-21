#include "MaterialMaster.h"
MaterialMaster* MaterialMaster::m_instance = nullptr;
MaterialMaster* MaterialMaster::GetInstance(void)
{
	if (m_instance == nullptr)
	{
		m_instance = new MaterialMaster();
	}
	return m_instance;
}
void MaterialMaster::ReleaseInstance(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}
bool MaterialMaster::LoadBMP(char* p_filepath, uint p_materialID)
{
	if (p_materialID < 0 || p_materialID >= m_materials.size())
		return false;

	if (m_texturePathMap.find(p_filepath) != m_texturePathMap.end())
	{
		m_materials[p_materialID].RemoveTexture(); //get rid of the old one
		m_materials[p_materialID].m_texture = m_texturePathMap[p_filepath];
		m_texturePathMap[p_filepath]->m_references++;
		return true;
	}
	Texture* texture = new Texture();
	m_texturePathMap[p_filepath] = texture;
	texture->m_references = 1;
	m_materials[p_materialID].RemoveTexture(); //get rid of the old one
	m_materials[p_materialID].m_texture = texture; //set our new one

	unsigned char header[54]; //bmp files begin with a 54 byte header
	uint dataPos; //position where the actual date begins
	//open the file
	FILE* file = fopen(p_filepath, "rb");
	if (!file){ fprintf(stderr, "Image could not be opened \n"); return false; }
	if (fread(header, 1, 54, file) != 54)
	{
		fprintf(stderr, "Not a correct BMP file \n");
		return false;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		fprintf(stderr, "Not a correct BMP file \n");
		return false;
	}
	dataPos = *(int*)&(header[0x0A]);
	texture->m_imageSize = *(int*)&(header[0x22]);
	texture->m_width = *(int*)&(header[0x12]);
	texture->m_height = *(int*)&(header[0x16]);

	//some bmp files are misformatted, guess missing info
	if (texture->m_imageSize == 0)
	{
		texture->m_imageSize = texture->m_width*texture->m_height * 3;
	}
	if (dataPos = 0)
	{
		dataPos = 54; //start after the bmp header
	}
	texture->m_data = new unsigned char[texture->m_imageSize];
	fread(texture->m_data, 1, texture->m_imageSize, file);
	fclose(file);

	glGenTextures(1, &(texture->m_textureID));
	//bind the newly created texture
	glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
	//give the image to open gl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->m_width, texture->m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->m_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return true;
}
bool MaterialMaster::LoadTGA(char* p_filepath, uint p_materialID)
{
	if (p_materialID < 0 || p_materialID >= m_materials.size())
		return false;

	if (m_texturePathMap.find(p_filepath) != m_texturePathMap.end())
	{
		m_materials[p_materialID].RemoveTexture(); //get rid of the old one
		m_materials[p_materialID].m_texture = m_texturePathMap[p_filepath];
		m_texturePathMap[p_filepath]->m_references++;
		return true;
	}
	Texture* texture = new Texture();
	m_texturePathMap[p_filepath] = texture;
	texture->m_references = 1;
	m_materials[p_materialID].RemoveTexture(); //get rid of the old one
	m_materials[p_materialID].m_texture = texture; //set our new one

	glGenTextures(1, &(texture->m_textureID));
	glBindTexture(1, texture->m_textureID);

	//still needs to be figured out
	return false;
}
uint MaterialMaster::CreateMaterial(void)
{
	Material newMaterial = Material();
	m_materials.push_back(newMaterial);
	return m_materials.size() - 1;
}
uint MaterialMaster::CreateMaterial(uint p_materialID)
{
	if (p_materialID < 0 || p_materialID >= m_materials.size())
		return p_materialID;
	m_materials.push_back(m_materials[p_materialID]);
	return m_materials.size() - 1;

}
void MaterialMaster::BindMaterial(uint p_materialIndex)
{
	if (p_materialIndex < 0 || p_materialIndex >= m_materials.size())
		return;
	m_currentMaterial = p_materialIndex;

}
void MaterialMaster::SetMaterialColor(uint p_materialIndex, vec3 p_color)
{
	if (p_materialIndex < 0 || p_materialIndex >= m_materials.size())
		return;
	m_materials[p_materialIndex].m_color = p_color;
}
vec3 MaterialMaster::GetMaterialColor(uint p_materialIndex){
	if (p_materialIndex < 0 || p_materialIndex >= m_materials.size())
		return vec3(0.0f);
	return m_materials[p_materialIndex].m_color;
}
void MaterialMaster::RemoveTexture(uint p_materialIndex)
{
	if (p_materialIndex < 0 || p_materialIndex >= m_materials.size())
		return;
	m_materials[p_materialIndex].RemoveTexture();
}
void MaterialMaster::SetSpecular(uint p_materialIndex, float p_specular)
{
	if (p_materialIndex < 0 || p_materialIndex >= m_materials.size())
		return;
	m_materials[p_materialIndex].m_specular = p_specular;
}
void MaterialMaster::SetProgramIndex(uint p_materialIndex, GLuint p_programIndex)
{
	if (p_materialIndex < 0 || p_materialIndex >= m_materials.size())
		return;
	m_materials[p_materialIndex].m_shaderProgram = p_programIndex;
}
MaterialMaster::MaterialMaster(void)
{
	m_texturePathMap = std::map<String, Texture*>();
	m_materials = std::vector<Material>();
}
