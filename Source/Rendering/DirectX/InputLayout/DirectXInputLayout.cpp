#include <Rendering/DirectX/InputLayout/DirectXInputLayout.h>


const char* Miracle::DirectXInputLayout::m_Semantic[16] =
{
	"",
	"POSITION",
	"BLENDWEIGHT",
	"BLENDINDICES",
	"NORMAL",
	"PSIZE",
	"TEXCOORD",
	"TANGENT",
	"BINORMAL",
	"TESSFACTOR",
	"POSITIONT",
	"COLOR",
	"FOG",
	"DEPTH",
	"SAMPLE"
};


Miracle::DirectXInputLayout::DirectXInputLayout(ID3D11Device* a_Device, VertexBuffer* a_VertexBuffer, Shader* a_Shader)
	: m_Layout(nullptr)
	, m_NumElements(0)
{
	memset(&mElements[0], 0, 16 * sizeof(mElements[0]));
	if (a_VertexBuffer && a_Shader)
	{
		VertexFormat VFormat = a_VertexBuffer->GetVertexFormat();
		m_NumElements = VFormat.GetNumAttributes();
		for (_U32 i = 0; i < m_NumElements; i++)
		{
			VertexSemantic Semantic = VFormat.GetSemantic(i);
			DataFormat Format = VFormat.GetDataFormat(i);
			_U32 unit = VFormat.GetUnit(i);
			_U32 offset = VFormat.GetOffset(i);

			D3D11_INPUT_ELEMENT_DESC& element = mElements[i];
			element.SemanticName = m_Semantic[Semantic];
			element.SemanticIndex = unit;
			element.Format = static_cast<DXGI_FORMAT>(Format);
			element.InputSlot = 0;  // TODO
			element.AlignedByteOffset = offset;
			element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			element.InstanceDataStepRate = 0;
		}
		std::vector<unsigned char> const& compiledCode =
			a_Shader->GetCompiledCode();
		HRESULT hr = a_Device->CreateInputLayout(mElements, (UINT)m_NumElements,
			&compiledCode[0], compiledCode.size(), &m_Layout);
		CHECK_HR_RETURN_NONE("Failed to create input layout");
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Invalid inputs to DX11InputLayout constructor.");
	}
}

Miracle::DirectXInputLayout::~DirectXInputLayout()
{
	FinalRelease(m_Layout);
}

void Miracle::DirectXInputLayout::Enable(ID3D11DeviceContext* context)
{
	if (m_Layout)
	{
		context->IASetInputLayout(m_Layout);
	}
}

void Miracle::DirectXInputLayout::Disable(ID3D11DeviceContext* context)
{
	if (m_Layout)
	{
		context->IASetInputLayout(nullptr);
	}
}
