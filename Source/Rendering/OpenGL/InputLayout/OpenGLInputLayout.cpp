#include <Rendering/OpenGL/InputLayout/OpenGLInputLayout.h>


Miracle::OpenGLInputLayout::OpenGLInputLayout(GLuint a_ProgramHandle, GLuint a_VertexBufferHandle, VertexBuffer* a_Buffer)
	: m_ProgramHandle(a_ProgramHandle)
	, m_VertexBufferHandle(a_VertexBufferHandle)
	, m_NumAttributes(0)
	, m_Attributes(nullptr)
{
	glGenVertexArrays(1, &m_VertexArrayHandle);
	glBindVertexArray(m_VertexArrayHandle);
	glBindBuffer(GL_ARRAY_BUFFER, a_VertexBufferHandle);
	if (a_Buffer)
	{
		const VertexFormat VFormat = a_Buffer->GetVertexFormat();
		m_NumAttributes = VFormat.GetNumAttributes();
		m_Attributes = new Attribute[m_NumAttributes];
		for (_U32 i = 0; i < m_NumAttributes; ++i)
		{
			Attribute& attribute = m_Attributes[i];
			attribute.semantic = VFormat.GetSemantic(i);
			attribute.location = i;
			attribute.numChannels = DataFormatUtils::GetDataFormatChannles(VFormat.GetDataFormat(i));
			attribute.channelType = DataFormatUtils::GetOpenGLChannelType(VFormat.GetDataFormat(i));
			attribute.offset = VFormat.GetOffset(i);
			attribute.stride = VFormat.GetByteSize();
			glEnableVertexAttribArray(attribute.location);
			glBindVertexBuffer(i, a_VertexBufferHandle, attribute.offset, attribute.stride);
			glVertexAttribFormat(attribute.location, attribute.numChannels, attribute.channelType, GL_FALSE, 0);
			glVertexAttribBinding(attribute.location, i);
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Invalid inputs to GL4InputLayout constructor.");
	}
	glBindVertexArray(0);
}

Miracle::OpenGLInputLayout::~OpenGLInputLayout()
{
	delete[] m_Attributes;
	glDeleteVertexArrays(1, &m_VertexArrayHandle);
}

void Miracle::OpenGLInputLayout::Enable()
{
	glBindVertexArray(m_VertexArrayHandle);
}

void Miracle::OpenGLInputLayout::Disable()
{
	glBindVertexArray(0);
}
