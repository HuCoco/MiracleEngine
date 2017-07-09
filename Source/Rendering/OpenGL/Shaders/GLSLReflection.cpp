#include "GLSLReflection.h"



Miracle::GLSLReflection::GLSLReflection(GLuint a_Handle)
	: m_Handle(a_Handle)
{
	if (m_Handle > 0)
	{
		ReflectUniforms();
		ReflectDataBlocks(GL_UNIFORM_BLOCK, m_UniformBlocks);
	}
}


Miracle::GLSLReflection::~GLSLReflection()
{
}

void Miracle::GLSLReflection::ReflectUniforms()
{
	_I32 numResources = 0;
	glGetProgramInterfaceiv(m_Handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numResources);

	if (numResources > 0)
	{
		m_Uniforms.clear();

		GLenum properties[] =
		{
			GL_NAME_LENGTH,
			GL_TYPE,
			GL_LOCATION,
			GL_ARRAY_SIZE,
			GL_OFFSET,
			GL_BLOCK_INDEX,
			GL_ARRAY_STRIDE,
			GL_MATRIX_STRIDE,
			GL_IS_ROW_MAJOR,
			GL_ATOMIC_COUNTER_BUFFER_INDEX,
			GL_REFERENCED_BY_VERTEX_SHADER,
			GL_REFERENCED_BY_GEOMETRY_SHADER,
			GL_REFERENCED_BY_FRAGMENT_SHADER,
			GL_REFERENCED_BY_COMPUTE_SHADER,
		};
		int const numProperties = sizeof(properties) / sizeof(_I32);
		GLint results[numProperties] = { NULL };
		for (int i = 0; i < numResources; ++i)
		{
			Uniform Info;
			glGetProgramResourceiv(m_Handle, GL_UNIFORM, i, numProperties, properties, numProperties, nullptr, results);
			GLint numBytes = results[0] + 1;
			std::vector<GLchar> name(numBytes);
			glGetProgramResourceName(m_Handle, GL_UNIFORM, i, numBytes, nullptr, name.data());
			Info.Name = std::string(name.data());
			GLint* current = &results[1];
			Info.Type = *current++;
			Info.Location = *current++;
			Info.ArraySize = *current++;
			Info.Offset = *current++;
			Info.BlockIndex = *current++;
			Info.ArrayStride = *current++;
			Info.MatrixStride = *current++;
			Info.IsRowMajor = *current++;
			Info.AtomicCounterBufferIndex = *current++;
			Info.referencedBy[VERTEX] = *current++;
			Info.referencedBy[GEOMETRY] = *current++;
			Info.referencedBy[PIXEL] = *current++;
			Info.referencedBy[COMPUTE] = *current++;

			if (GL_INVALID_INDEX == Info.BlockIndex)
			{
				Info.Location = glGetUniformLocation(m_Handle, Info.Name.c_str());
			}

			Info.FullName = Info.Name;
			if (Info.ArraySize > 1)
			{
				auto index = Info.Name.find('[');
				if (index != std::string::npos)
				{
					// Make sure array is not more than single dimensional.
					auto index2 = Info.Name.find('[', index + 1);
					if (index2 != std::string::npos)
					{
						// TODO: Should this cause compile of shader to fail?
						MENGINE_ASSERT_MSG(false,"Only single dimensional arrays supported in GLSL uniforms.");
					}

					Info.Name = Info.Name.substr(0, index);
				}
				else
				{
					// TODO: For now, trap any occurrence of an array member
					// whose name is not of the form "someName[0]".
					MENGINE_ASSERT_MSG(false,"Unexpected condition.");
				}
			}

			m_Uniforms.push_back(Info);
		}
	}
}

void Miracle::GLSLReflection::ReflectDataBlocks(GLenum a_programInterface, std::vector<DataBlock>& a_blocks)
{
	GLint numResources = 0;
	glGetProgramInterfaceiv(m_Handle, a_programInterface, GL_ACTIVE_RESOURCES,
		&numResources);


	if (numResources > 0)
	{
		a_blocks.resize(numResources);

		GLenum properties[] =
		{
			GL_NAME_LENGTH,
			GL_BUFFER_BINDING,
			GL_BUFFER_DATA_SIZE,
			GL_REFERENCED_BY_VERTEX_SHADER,
			GL_REFERENCED_BY_GEOMETRY_SHADER,
			GL_REFERENCED_BY_FRAGMENT_SHADER,
			GL_REFERENCED_BY_COMPUTE_SHADER,
			GL_REFERENCED_BY_TESS_CONTROL_SHADER,
			GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
			GL_NUM_ACTIVE_VARIABLES
		};
		int const numProperties = sizeof(properties) / sizeof(int);
		GLint results[numProperties] = { 0 };
		for (int i = 0; i < numResources; ++i)
		{
			DataBlock& info = a_blocks[i];
			glGetProgramResourceiv(m_Handle, a_programInterface, i,
				numProperties, properties, numProperties, nullptr, results);

			GLint numBytes = results[0] + 1;
			std::vector<GLchar> name(numBytes);
			glGetProgramResourceName(m_Handle, a_programInterface, i, numBytes, nullptr, name.data());
			info.name = std::string(name.data());


			GLint* current = &results[1];
			info.bufferBinding = *current++;
			info.bufferDataSize = *current++;
			info.referencedBy[VERTEX] = *current++;
			info.referencedBy[GEOMETRY] = *current++;
			info.referencedBy[PIXEL] = *current++;
			info.referencedBy[COMPUTE] = *current++;

			// To be sure the bufferBinding field is set correctly, use this approach.
			info.bufferBinding = glGetProgramResourceIndex(m_Handle, a_programInterface, info.name.c_str());

			GLint numActiveVariables = *current++;
			if (numActiveVariables > 0)
			{
				info.activeVariables.resize(numActiveVariables);
				std::fill(info.activeVariables.begin(),
					info.activeVariables.end(), 0);
				GLenum varProperty = GL_ACTIVE_VARIABLES;
				glGetProgramResourceiv(m_Handle, a_programInterface, i, 1,
					&varProperty, numActiveVariables, nullptr,
					&info.activeVariables[0]);
			}
		}
	}
}
