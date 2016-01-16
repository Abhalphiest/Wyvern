#include"ShaderMaster.h"
ShaderMaster* ShaderMaster::m_instance = nullptr;

//singleton functions
ShaderMaster* ShaderMaster::GetInstance(void)
{
	if (m_instance == nullptr)
	{
		m_instance = new ShaderMaster();
	}
	return m_instance;
}

void ShaderMaster::ReleaseInstance(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}


//we might not a special constructor, copy constructor,
//assignment overload, and destructor, but in case the implementation changes down the line
//to include heap variables, it's nice to have them stubbed out.
//constructor
ShaderMaster::ShaderMaster(void)
{
	m_programs = std::vector<Program>();
	
}
ShaderMaster::ShaderMaster(ShaderMaster const  &other)
{
	m_programs = other.m_programs;

}

ShaderMaster& ShaderMaster::operator=(ShaderMaster const& other)
{
	if (this != &other)
	{
		m_programs = other.m_programs;
	}

	return *this;
}
//destructor
ShaderMaster::~ShaderMaster(void)
{
	//nothing to free at the moment
}


GLuint ShaderMaster::LoadVertexShader(const char* p_vertexFilePath, Program& p_program)
{

	p_program.m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	String vertexShaderSource;
	std::ifstream vertexShaderStream(p_vertexFilePath, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		String line = "";
		while (std::getline(vertexShaderStream, line))
		{
			vertexShaderSource += "\n" + line; //shouldn't need carriage return, I hope

		}
		vertexShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Check your filepath carefully. \n", p_vertexFilePath);
		getchar(); //hold command prompt
		return -1; //exit failure
	}
	GLint result = GL_FALSE; //using as bool
	int infoLogLength;

	//compile the shader
	printf("Compiling shader: %s \n", p_vertexFilePath);
	char const* vertexSourcePointer = vertexShaderSource.c_str(); //get a c style string for gl
	glShaderSource(p_program.m_vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(p_program.m_vertexShaderID);
	
	//check on our new shader
	glGetShaderiv(p_program.m_vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(p_program.m_vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) //we have errors
	{
		std::vector<char> vertexShaderError(infoLogLength + 1); //leave room for null, let's print out our errors
		glGetShaderInfoLog(p_program.m_vertexShaderID, infoLogLength, NULL, &vertexShaderError[0]);
		printf("%s \n", &vertexShaderError[0]); //send em to standard out
	}

	return p_program.m_vertexShaderID;
	
}
GLuint ShaderMaster::LoadFragmentShader(const char* p_fragmentFilePath, Program& p_program)
{
	p_program.m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	String fragmentShaderSource;
	std::ifstream fragmentShaderStream(p_fragmentFilePath, std::ios::in);
	if (fragmentShaderStream.is_open())
	{
		String line = "";
		while (std::getline(fragmentShaderStream, line))
		{
			fragmentShaderSource += "\n" + line; //shouldn't need carriage return, I hope

		}
		fragmentShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Check your filepath carefully. \n", p_fragmentFilePath);
		getchar(); //hold command prompt
		return -1; //exit failure
	}
	GLint result = GL_FALSE; //using as bool
	int infoLogLength;

	//compile the shader
	printf("Compiling shader: %s \n", p_fragmentFilePath);
	char const* fragmentSourcePointer = fragmentShaderSource.c_str(); //get a c style string for gl
	glShaderSource(p_program.m_fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(p_program.m_fragmentShaderID);

	//check on our new shader
	glGetShaderiv(p_program.m_fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(p_program.m_fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) //we have errors
	{
		std::vector<char> fragmentShaderError(infoLogLength + 1); //leave room for null, let's print out our errors
		glGetShaderInfoLog(p_program.m_fragmentShaderID, infoLogLength, NULL, &fragmentShaderError[0]);
		printf("%s \n", &fragmentShaderError[0]); //send em to standard out
	}

	return p_program.m_fragmentShaderID;
}


uint ShaderMaster::CreateShaderProgram(void)
{
	uint index = m_programs.size();
	m_programs.push_back(Program());
	return index;

}
void ShaderMaster::AddShader(const char* p_filepath, ShaderType p_shader) //add some shaders
{
	switch (p_shader)
	{
		case VERTEX_SHADER:
		{
			if (LoadVertexShader(p_filepath, m_programs[m_currentProgram]) > 0)
				m_programs[m_currentProgram].m_shadersLoaded = m_programs[m_currentProgram].m_shadersLoaded | p_shader;

			break;
		}
		case FRAGMENT_SHADER:
		{
								if (LoadFragmentShader(p_filepath, m_programs[m_currentProgram])>0)
				m_programs[m_currentProgram].m_shadersLoaded = m_programs[m_currentProgram].m_shadersLoaded | p_shader;
			break;
		}
	}
}

void ShaderMaster::CompileProgram(uint p_index)
{
	if (p_index >= m_programs.size() || p_index < 0)
		return;
	printf("Linking program \n");
	m_programs[p_index].m_programID = glCreateProgram();
	if (VERTEX_SHADER&m_programs[p_index].m_shadersLoaded)
	{
		glAttachShader(m_programs[p_index].m_programID, m_programs[p_index].m_vertexShaderID);
	}
	if (FRAGMENT_SHADER&m_programs[p_index].m_shadersLoaded)
	{
		glAttachShader(m_programs[p_index].m_programID, m_programs[p_index].m_fragmentShaderID);
	}

	glLinkProgram(m_programs[p_index].m_programID);

	GLint result = GL_FALSE; //using as bool
	int infoLogLength;
	//check the program
	glGetProgramiv(m_programs[p_index].m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programs[p_index].m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) //we have some errors to print
	{
		std::vector<char> programError(infoLogLength + 1);
		glGetProgramInfoLog(m_programs[p_index].m_programID, infoLogLength, NULL, &programError[0]);
		printf("%s \n", &programError[0]);
	}
	if (VERTEX_SHADER&m_programs[p_index].m_shadersLoaded)
	{
		glDetachShader(m_programs[p_index].m_programID, m_programs[p_index].m_vertexShaderID);
		glDeleteShader(m_programs[p_index].m_vertexShaderID);
	}
	if (FRAGMENT_SHADER&m_programs[p_index].m_shadersLoaded)
	{
		glDetachShader(m_programs[p_index].m_programID, m_programs[p_index].m_fragmentShaderID);
		glDeleteShader(m_programs[p_index].m_fragmentShaderID);
	}
	return;

	
}

void ShaderMaster::BindShaderProgram(uint p_programIndex)
{
	if (p_programIndex >= m_programs.size() || p_programIndex < 0)
		return;

	m_currentProgram = p_programIndex;
	glUseProgram(m_programs[m_currentProgram].m_programID);

}