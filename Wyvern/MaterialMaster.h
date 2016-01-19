#ifndef _MATERIALMASTER_H
#define _MATERIALMASTER_H
#include "definitions.h"
class MaterialMaster{

	
	struct Texture
	{
		uint m_references;
		GLuint m_textureID;
		String m_path;
		uint m_width;
		uint m_height;
		uint m_imageSize;
		unsigned char* m_data = nullptr; //rgb data
		void DeleteTexture(void){ if (m_references == 0) delete this; }
		private:~Texture(void){
			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
		}
	};
	struct Material
	{
		float m_specular;
		vec3 m_color = BLACK;
		Texture* m_texture = nullptr;
		uint m_shaderProgram;
		void RemoveTexture(void)
		{
			if (m_texture != nullptr)
			{
				m_texture->m_references--;
				if (m_texture->m_references == 0)
					m_texture->DeleteTexture();
			}
		}
		Material()
		{
			m_specular = 0;
		}
		Material(const Material& other)
		{
			if (m_texture != nullptr)
				m_texture->m_references++;

		}
		~Material(void){
			RemoveTexture();
		}
		Material& operator=(const Material& other)
		{
			if (m_texture != nullptr)
				m_texture->m_references++;
			return *this;
		}

	};
	

public:
	static MaterialMaster* GetInstance(void);
	static void ReleaseInstance(void);
	bool LoadBMP(char* p_filepath, uint p_materialID);
	bool LoadTGA(char* p_filepath, uint p_materialID);
	uint CreateMaterial(void);
	uint CreateMaterial(uint p_materialID);
	void BindMaterial(uint p_materialIndex);
	void SetMaterialColor(uint p_materialIndex, vec3 p_color);
	void RemoveTexture(uint p_materialIndex);
	void SetSpecular(uint p_materialIndex, float p_specular);
	void SetProgramIndex(uint p_materialIndex, GLuint p_programIndex);

private:
	MaterialMaster(void);
	MaterialMaster& operator=(const MaterialMaster& other);
	MaterialMaster(const MaterialMaster& other);
	~MaterialMaster(void);
	std::map<String, Texture*> m_texturePathMap; //to see if we already loaded this texture
	std::vector<Material> m_materials;
	uint m_currentMaterial;
	static MaterialMaster* m_instance;
};
#endif