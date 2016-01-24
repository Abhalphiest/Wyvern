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
	///<summary> Returns the instance of the MaterialMaster singleton. If no instance exists yet, creates the instance.</summary>
	///<returns> A pointer to the Material Master instance.</returns>
	static MaterialMaster* GetInstance(void);
	///<summary>Destroys the Material Master singleton instance. </summary>
	static void ReleaseInstance(void);
	///<summary> Loads a texture from a .bmp file to the given material. A material is necessary because textures cannot
	///exist without at least one referencing material by design.</summary>
	///<param name="p_filepath">The file path to the .bmp file starting in the application directory.</param>
	///<param name="p_materialID">The index of the material that the texture should be loaded into.</param>
	///<returns>A boolean indicating success or failure. </returns>
	bool LoadBMP(char* p_filepath, uint p_materialID);
	///<summary>Loads a texture from a .tga file to the given material. A material is necessary because textures cannot
	///exist without at least one referencing material by design. </summary>
	///<param name="p_filepath">The file path to the .tga file starting in the application directory. </param>
	///<param name="p_materialID">The index of the material that the texture should be loaded into. </param>
	///<returns>A boolean indicating success or failure. </returns>
	bool LoadTGA(char* p_filepath, uint p_materialID);
	///<summary>Creates an empty material and provides the index with which to access it to the caller.</summary>
	///<returns>The 0-based index of the created material within the material master's list. </returns>
	uint CreateMaterial(void);
	///<summary>Creates a material identical to the supplied material. However, changes to one will not persist across to the other.
	///This is an easy way to, for example, have many similar values but different textures.</summary>
	///<param name="p_materialID"> The index of the material to be copied.</param>
	///<returns>The 0-based index of the created material within the material master's list.   </returns>
	uint CreateMaterial(uint p_materialID);
	//<summary>Sets the color of the material (under the texture). </summary>
	///<param name="p_materialIndex">The index of the material to change. </param>
	///<param name="p_color">A vector of RGB values ranging [0,1]</param>
	void SetMaterialColor(uint p_materialIndex, vec3 p_color);
	//<summary>Gets the color of the material. </summary>
	///<param name="p_materialIndex">The index of the material to change. </param>
	///<returns>A vector of RGB values ranging [0,1], indicating the material's base color. </returns>
	vec3 GetMaterialColor(uint p_materialIndex);
	///<summary>Removes the texture associated with the material. If this material is the last one with a reference to that texture, the texture
	///will be deleted.</summary>
	///<param name="p_materialIndex"> The index of the material whose texture will be removed.</param>
	void RemoveTexture(uint p_materialIndex);
	//<summary>Specular property</summary>
	///<param name="p_materialID">The index of the material to change. </param>
	///<param name="p_specular">A float value on [0,1] indicating the specularity of the object.</param>
	void SetSpecular(uint p_materialIndex, float p_specular);
	//<summary>Shader program property </summary>
	///<param name="p_materialID">The index of the material to change. </param>
	///<param name="p_programIndex">The new shader program index </param>
	void SetProgramIndex(uint p_materialIndex, GLuint p_programIndex);
	//<summary>Shader program property </summary>
	///<param name="p_materialIndex">The index of the material to change. </param>
	///<returns>The index of the material's shader program. </returns>
	uint GetShaderProgram(uint p_materialIndex){ return m_materials[p_materialIndex].m_shaderProgram; }
	//<summary>Destroys all materials and textures. Recommended for a level switch or similar.</summary>
	void ClearMaterials(void){ m_materials.clear();}

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