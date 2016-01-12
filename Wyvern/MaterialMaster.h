#ifndef _MATERIALMASTER_H
#define _MATERIALMASTER_H
#include "definitions.h"
class MaterialMaster{

	
	struct Texture
	{
		uint m_references;
		String m_path;
		uint m_width;
		uint m_height;
		uint m_imageSize;
		std::vector<char> m_data;
	};
	struct Material
	{
		GLuint m_shaderID;
		GLuint m_textureID;
		float m_specular;
		vec3 m_color = BLACK;
		Texture* m_texture;
	};
	

public:
	MaterialMaster* GetInstance(void);
	void ReleaseInstance(void);
	bool LoadBMP(char* p_filepath, uint p_materialID);
	bool LoadTGA(char* p_filepath, uint p_materialID);
	uint CreateMaterial(void);
	uint CreateMaterial(uint m_materialID);
	void BindMaterial(uint p_materialIndex);
	void SetMaterialColor(uint p_materialIndex, vec3 color);
	void RemoveTexture(uint p_materialIndex);
	void SetSpecular(uint p_materialIndex, float p_specular);

private:
	MaterialMaster(void);
	MaterialMaster& operator=(const MaterialMaster& other);
	MaterialMaster(const MaterialMaster& other);
	~MaterialMaster(void);
	std::map<String, Texture*> m_texturePathMap; //to see if we already loaded this texture
	std::vector<Material> m_materials;
	uint m_currentMaterial;
};
#endif