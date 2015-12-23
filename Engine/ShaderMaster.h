#ifndef _SHADERMASTER_H
#define _SHADERMASTER_H
#include "definitions.h"

//The shader master will be more completely implemented once I have a better grasp of how
//more complex shaders work and what the architecture should look like
class ShaderMaster{
	
public: 
		enum ShaderType
		{
			VERTEX_SHADER = 1,
			FRAGMENT_SHADER = 2
			// = 4, = 8, etc
		};
		static ShaderMaster* GetInstance(void); //singleton
		static void ReleaseInstance(void); //release the singleton
		void AddShader(const char* filepath, ShaderType shader); //add some shaders
		GLuint LoadProgram(void);
		GLuint GetProgramID(void){ return m_programID; }
private: 
		ShaderMaster(void); //constructor
		ShaderMaster(ShaderMaster const &other); //copy constructor
		ShaderMaster& operator=(ShaderMaster const &other); //copy assignment operator
		~ShaderMaster(void); //destructor

		static ShaderMaster* m_instance; //singleton instance
		GLuint m_shadersLoaded; //for when we're making our program
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
		GLuint m_programID;
		GLuint LoadVertexShader(const char* vertexFilePath);
		GLuint LoadFragmentShader(const char* fragmentFilePath);
		
};

#endif