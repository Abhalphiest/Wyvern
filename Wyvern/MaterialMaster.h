#ifndef _MATERIALMASTER_H
#define _MATERIALMASTER_H
#include "definitions.h"
class MaterialMaster{

	///<summary> The texture struct contains all the data associated with a single texture </summary>
	struct Texture
	{
		uint m_references;
		GLuint m_textureID;
		String m_path;
		uint m_width;
		uint m_height;
		uint m_imageSize;
		unsigned char* m_data = nullptr; //rgb data
		///<summary> Calls the destructor if there are no more references </summary>
		void DeleteTexture(void){ if (m_references == 0) delete this; }
		///<summary>Private destructor </summary>
		private:~Texture(void){
			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
		}
	};
	///<summary> The texture struct contains all the data associated with a single material</summary>
	struct Material
	{
		float m_specular;
		vec3 m_color = BLACK;
		Texture* m_texture = nullptr;
		uint m_shaderProgram;
		///<summary>Removes the texture from the material, decreases the number of references to that texture, and attempts to 
		///delete the texture (the texture will only be deleted at 0 references)</summary>
		void RemoveTexture(void)
		{
			if (m_texture != nullptr)
			{
				m_texture->m_references--;
				if (m_texture->m_references == 0)
					m_texture->DeleteTexture();
			}
		}
		///<summary>Constructor </summary>
		Material(void)
		{
			//fprintf(stdout, "material constructor called");
			m_specular = 0.0f;
		}
		///<summary>Copy Constructor </summary>
		Material(const Material& other)
		{
			
			m_texture = other.m_texture;
			if (m_texture != nullptr)
				m_texture->m_references++;
			m_specular = other.m_specular;
			m_shaderProgram = other.m_shaderProgram;
			m_color = other.m_color;
		}
		///<summary>Destructor</summary>
		~Material(void){
			RemoveTexture();
		}
		///<summary>Assignment Operator</summary>
		Material& operator=(const Material& other)
		{
			if (m_texture != nullptr)
				RemoveTexture();
			m_texture = other.m_texture;
			if (m_texture != nullptr)
				m_texture->m_references++;
			m_specular = other.m_specular;
			m_shaderProgram = other.m_shaderProgram;
			m_color = other.m_color;
			return *this;
		}

	};
	

public:
	///<summary> </summary>
	///<returns> A pointer to the Material Master instance.</returns>
	static MaterialMaster* GetInstance(void);
	///<summary> </summary>
	static void ReleaseInstance(void);
	///<summary> </summary>
	///<param name="p_filepath"> </param>
	///<param name="p_materialID"> </param>
	///<returns> </returns>
	bool LoadBMP(char* p_filepath, uint p_materialID);
	///<summary> </summary>
	///<param name="p_filepath"> </param>
	///<param name="p_materialID"> </param>
	///<returns> </returns>
	bool LoadTGA(char* p_filepath, uint p_materialID);
	///<summary> </summary>
	///<returns> </returns>
	uint CreateMaterial(void);
	///<summary> </summary>
	///<param name="p_materialID"> </param>
	///<returns> </returns>
	uint CreateMaterial(uint p_materialID);
	//<summary> </summary>
	///<param name="p_materialIndex"> </param>
	void BindMaterial(uint p_materialIndex);
	//<summary> </summary>
	///<param name="p_materialIndex"> </param>
	///<param name="p_color"></param>
	void SetMaterialColor(uint p_materialIndex, vec3 p_color);
	//<summary> </summary>
	///<param name="p_materialIndex"> </param>
	///<returns> </returns>
	vec3 GetMaterialColor(uint p_materialIndex);
	//<summary> </summary>
	///<param name="p_materialIndex"> </param>
	void RemoveTexture(uint p_materialIndex);
	//<summary> </summary>
	///<param name="p_materialID"> </param>
	///<param name="p_specular"> </param>
	void SetSpecular(uint p_materialIndex, float p_specular);
	//<summary> </summary>
	///<param name="p_materialID"> </param>
	///<param name="p_programIndex"> </param>
	void SetProgramIndex(uint p_materialIndex, GLuint p_programIndex);
	//<summary> </summary>
	///<returns> </returns>
	uint GetShaderProgram(void){ return m_materials[m_currentMaterial].m_shaderProgram; }

private:
	///<summary> Private Constructor </summary>
	MaterialMaster(void);
	///<summary> Private Copy Constructor. Does nothing, is just implemented to be private.</summary>
	MaterialMaster(const MaterialMaster& other);
	///<summary> Private Destructor. Does nothing, is just implemented to be private. </summary>
	~MaterialMaster(void);
	///<summary> Private Assignment Operator. Does nothing, is just implemented to be private. </summary>
	MaterialMaster& operator=(const MaterialMaster& other);
	std::map<String, Texture*> m_texturePathMap; //to see if we already loaded this texture
	std::vector<Material> m_materials;
	uint m_currentMaterial;
	static MaterialMaster* m_instance;
};
#endif