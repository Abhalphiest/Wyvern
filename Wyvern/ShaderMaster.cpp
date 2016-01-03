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
	m_shadersLoaded = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;
	m_programID = 0;
	//just to be sure what we have in there to start out with. only the m_shadersLoaded is 100% necessary
}
ShaderMaster::ShaderMaster(ShaderMaster const  &other)
{
	m_shadersLoaded = other.m_shadersLoaded;
	m_vertexShaderID = other.m_vertexShaderID;
	m_fragmentShaderID = other.m_fragmentShaderID;
	m_programID = other.m_programID;

}

ShaderMaster& ShaderMaster::operator=(ShaderMaster const& other)
{
	if (this != &other)
	{
		m_shadersLoaded = other.m_shadersLoaded;
		m_vertexShaderID = other.m_vertexShaderID;
		m_fragmentShaderID = other.m_fragmentShaderID;
		m_programID = other.m_programID;
	}

	return *this;
}
//destructor
ShaderMaster::~ShaderMaster(void)
{
	//nothing to free at the moment
}


GLuint ShaderMaster::LoadVertexShader(const char* p_vertexFilePath)
{
	
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
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
	glShaderSource(m_vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(m_vertexShaderID);
	
	//check on our new shader
	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) //we have errors
	{
		std::vector<char> vertexShaderError(infoLogLength + 1); //leave room for null, let's print out our errors
		glGetShaderInfoLog(m_vertexShaderID, infoLogLength, NULL, &vertexShaderError[0]);
		printf("%s \n", &vertexShaderError[0]); //send em to standard out
	}

	return m_vertexShaderID;
	
}
GLuint ShaderMaster::LoadFragmentShader(const char* p_fragmentFilePath)
{
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
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
	glShaderSource(m_fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(m_fragmentShaderID);

	//check on our new shader
	glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) //we have errors
	{
		std::vector<char> fragmentShaderError(infoLogLength + 1); //leave room for null, let's print out our errors
		glGetShaderInfoLog(m_fragmentShaderID, infoLogLength, NULL, &fragmentShaderError[0]);
		printf("%s \n", &fragmentShaderError[0]); //send em to standard out
	}

	return m_fragmentShaderID;
}


//this function seems slightly pointless now, but it might be useful in the future depending on implementation
//I'm kind of flying blind here
void ShaderMaster::AddShader(const char* p_filepath, ShaderType p_shader) //add some shaders
{
	switch (p_shader)
	{
		case VERTEX_SHADER:
		{
			if (LoadVertexShader(p_filepath) > 0)
				m_shadersLoaded = m_shadersLoaded | p_shader;

			break;
		}
		case FRAGMENT_SHADER:
		{
			if(LoadFragmentShader(p_filepath)>0)
				m_shadersLoaded = m_shadersLoaded | p_shader;
			break;
		}
	}
}

GLuint ShaderMaster::LoadProgram(void)
{
	printf("Linking program \n");
	m_programID = glCreateProgram();
	if (VERTEX_SHADER&m_shadersLoaded)
	{
		glAttachShader(m_programID, m_vertexShaderID);
	}
	if (FRAGMENT_SHADER&m_shadersLoaded)
	{
		glAttachShader(m_programID, m_fragmentShaderID);
	}

	glLinkProgram(m_programID);

	GLint result = GL_FALSE; //using as bool
	int infoLogLength;
	//check the program
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) //we have some errors to print
	{
		std::vector<char> programError(infoLogLength + 1);
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, &programError[0]);
		printf("%s \n", &programError[0]);
	}
	if (VERTEX_SHADER&m_shadersLoaded)
	{
		glDetachShader(m_programID, m_vertexShaderID);
		glDeleteShader(m_vertexShaderID);
	}
	if (FRAGMENT_SHADER&m_shadersLoaded)
	{
		glDetachShader(m_programID, m_fragmentShaderID);
		glDeleteShader(m_fragmentShaderID);
	}
	return m_programID;

	
}