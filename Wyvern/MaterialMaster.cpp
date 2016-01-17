#include "MaterialMaster.h"

MaterialMaster* MaterialMaster::GetInstance(void)
{

}
void MaterialMaster::ReleaseInstance(void)
{

}
bool MaterialMaster::LoadBMP(char* p_filepath, uint p_materialID)
{

}
bool MaterialMaster::LoadTGA(char* p_filepath, uint p_materialID)
{

}
uint MaterialMaster::CreateMaterial(void)
{

}
uint MaterialMaster::CreateMaterial(uint m_materialID)
{

}
void MaterialMaster::BindMaterial(uint p_materialIndex)
{

}
void MaterialMaster::SetMaterialColor(uint p_materialIndex, vec3 color)
{

}
void MaterialMaster::RemoveTexture(uint p_materialIndex)
{

}
void MaterialMaster::SetSpecular(uint p_materialIndex, float p_specular)
{

}
void MaterialMaster::SetProgramIndex(GLuint p_programIndex)
{

}
MaterialMaster::MaterialMaster(void)
{

}
MaterialMaster& MaterialMaster::operator=(const MaterialMaster& other)
{

}
MaterialMaster::MaterialMaster(const MaterialMaster& other)
{

}
MaterialMaster::~MaterialMaster(void)
{

}