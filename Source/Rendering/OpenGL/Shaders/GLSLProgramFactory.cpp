#include <Rendering/OpenGL/Shaders/GLSLProgramFactory.h>
#include <Rendering/OpenGL/Shaders/GLSLVisualProgram.h>

std::string Miracle::GLSLProgramFactory::DefaultVersion = "#version 430";
std::string Miracle::GLSLProgramFactory::DefaultVSEntry = "main";
std::string Miracle::GLSLProgramFactory::DefaultPSEntry = "main";
std::string Miracle::GLSLProgramFactory::DefaultGSEntry = "main";


Miracle::GLSLProgramFactory::GLSLProgramFactory()
{
	Version = DefaultVersion;
	VertexShaderEntry = DefaultVSEntry;
	PixelShaderEntry = DefaultPSEntry;
	GeometryShaderEntry = DefaultGSEntry;
}

Miracle::GLSLProgramFactory::~GLSLProgramFactory()
{

}


_U32 Miracle::GLSLProgramFactory::GetShaderLanguage() const
{
	return ProgramFactory::GLSL;
}

std::shared_ptr<Miracle::VisualProgram> Miracle::GLSLProgramFactory::CreateFromNamedSources(
	const std::string& a_vsName, const std::string& a_vsSource,
	const std::string& a_psName, const std::string& a_psSource,
	const std::string& a_gsName, const std::string& a_gsSource)
{
	if (a_vsSource == "" || a_psSource == "")
	{
		MENGINE_ASSERT_MSG(false,"A program must have a vertex shader and a pixel shader.");
		return nullptr;
	}

	GLuint vsHandle = Compile(GL_VERTEX_SHADER, a_vsSource);
	if (vsHandle == 0)
	{
		return nullptr;
	}

	GLuint psHandle = Compile(GL_FRAGMENT_SHADER, a_psSource);
	if (psHandle == 0)
	{
		return nullptr;
	}

	GLuint gsHandle = 0;
	if (a_gsSource != "")
	{
		gsHandle = Compile(GL_GEOMETRY_SHADER, a_gsSource);
		if (gsHandle == 0)
		{
			return nullptr;
		}
	}

	GLuint programHandle = glCreateProgram();
	if (programHandle == 0)
	{
		MENGINE_ASSERT_MSG(false,"Program creation failed.");
		return nullptr;
	}

	glAttachShader(programHandle, vsHandle);
	glAttachShader(programHandle, psHandle);
	if (gsHandle > 0)
	{
		glAttachShader(programHandle, gsHandle);
	}

	if (!Link(programHandle))
	{
		glDetachShader(programHandle, vsHandle);
		glDeleteShader(vsHandle);
		glDetachShader(programHandle, psHandle);
		glDeleteShader(psHandle);
		if (gsHandle)
		{
			glDetachShader(programHandle, gsHandle);
			glDeleteShader(gsHandle);
		}
		glDeleteProgram(programHandle);
		return nullptr;
	}

	std::shared_ptr<GLSLVisualProgram> program = std::make_shared<GLSLVisualProgram>(programHandle, vsHandle, psHandle, gsHandle);
	const GLSLReflection& reflector = program->GetReflector();
	program->SetVertexShader(std::make_shared<VertexShader>(reflector));
	program->SetPixelShader(std::make_shared<PixelShader>(reflector));
	
	return program;
}

GLuint Miracle::GLSLProgramFactory::Compile(GLenum a_shaderType, const std::string& a_source)
{
	GLuint handle = glCreateShader(a_shaderType);
	if (handle > 0)
	{
		const GLchar* code = a_source.c_str();
		glShaderSource(handle, 1, &code, nullptr);
		glCompileShader(handle);
		GLint status;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint logLength;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
			if (logLength > 0)
			{
				std::vector<GLchar> log(logLength);
				GLsizei numWritten;
				glGetShaderInfoLog(handle, static_cast<GLsizei>(logLength), &numWritten, log.data());
				MENGINE_ASSERT_MSG(false,"Compile failed");
			}
			else
			{
				MENGINE_ASSERT_MSG(false,"Invalid info log length.");
			}
			glDeleteShader(handle);
			handle = 0;
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Cannot create shader.");
	}
	return handle;
}

bool Miracle::GLSLProgramFactory::Link(GLuint a_programHandle)
{
	glLinkProgram(a_programHandle);
	int status;
	glGetProgramiv(a_programHandle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		int logLength;
		glGetProgramiv(a_programHandle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			std::vector<GLchar> log(logLength);
			int numWritten;
			glGetProgramInfoLog(a_programHandle, logLength, &numWritten, log.data());
			MENGINE_ASSERT_MSG(false,"Link failed");
		}
		else
		{
			MENGINE_ASSERT_MSG(false,"Invalid info log length.");
		}
		return false;
	}
	else
	{
		return true;
	}
}

