#ifndef _SHADERMASTER_H
#define _SHADERMASTER_H
#include "definitions.h"

//The shader master will be more completely implemented once I have a better grasp of how
//more complex shaders work and what the architecture should look like
class ShaderMaster{
	
public: 
		///<summary> Bit field. Options are VERTEX_SHADER, FRAGMENT_SHADER, and GEOMETRY_SHADER </summary>
		enum ShaderType
		{
			VERTEX_SHADER = 1,
			FRAGMENT_SHADER = 2,
			GEOMETRY_SHADER = 4
		};
		///<summary>Returns the instance of the Shader Master, and if none exists yet, creates the instance. </summary>
		///<returns>A pointer to the Shader Master instance </returns>
		static ShaderMaster* GetInstance(void); 
		///<summary>Destroys the Shader Master singleton </summary>
		static void ReleaseInstance(void); 
		///<summary>Adds a shader to the currently bound shader program. </summary>
		///<param name="p_filepath">The filepath of the shader starting from the application directory. </param>
		///<param name="p_shader">The type of shader being loaded.</param>
		void AddShader(const char* p_filepath, ShaderType p_shader); 
		///<summary>Compiles the program with OpenGL after all the shaders are loaded. </summary>
		///<param name="p_programIndex">The index of the program to compile. </param>
		void CompileProgram(uint p_programIndex);
		///<summary>Property for the programID of the currently bound program.</summary>
		///<returns>The GL id of the currently bound program. </returns>
		GLuint GetProgramID(void){ return m_programs[m_currentProgram].m_programID; }
		///<summary>Sets the indicated program as the current shader program.</summary>
		///<param name="p_programIndex">The index of the program to be bound. NOTE: The shader master index, NOT the GL index.</param>
		void BindShaderProgram(uint p_programIndex);
		///<summary>Creates an empty shader program.</summary>
		///<returns>The index value of the newly created program.</returns>
		uint CreateShaderProgram(void);
private: 
		///<summary>Private Constructor </summary>
		ShaderMaster(void); 
		///<summary>Private Copy Constructor </summary>
		ShaderMaster(ShaderMaster const &other); 
		///<summary>Private assignment operator </summary>
		ShaderMaster& operator=(ShaderMaster const &other); 
		///<summary>Private destructor </summary>
		~ShaderMaster(void); 
		///<summary>The Program struct contains all the information associated with the shader program.</summary>
		struct Program
		{
			GLuint m_shadersLoaded; //for when we're making our program
			GLuint m_vertexShaderID;
			GLuint m_fragmentShaderID;
			GLuint m_geometryShaderID;
			GLuint m_programID;
		};
		static ShaderMaster* m_instance; //singleton instance
		std::vector<Program> m_programs;
		uint m_currentProgram;
		///<summary> Loads and binds a vertex shader to the parameter program.</summary>
		///<param name="p_vertexFilePath">The file path of the vertex shader, starting in application directory. </param>
		///<param name="p_program>The program to bind the new shader to. </param>
		///<returns>The GL index of the new shader. </returns>
		GLuint LoadVertexShader(const char* p_vertexFilePath, Program& p_program);
		///<summary>Loads and binds a fragment shader to the parameter program. </summary>
		///<param name="p_fragmentFilePath">The file path of the fragment shader, starting in application directory.  </param>
		///<param name="p_program>The program to bind the new shader to. </param>
		///<returns>The GL index of the new shader. </returns>
		GLuint LoadFragmentShader(const char* p_fragmentFilePath, Program& p_program);
		
};

#endif