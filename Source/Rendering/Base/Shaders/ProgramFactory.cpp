#include <Rendering/Base/Shaders/ProgramFactory.h>


Miracle::ProgramFactory::ProgramFactory()
{
}


Miracle::ProgramFactory::~ProgramFactory()
{
}

std::shared_ptr<Miracle::VisualProgram> Miracle::ProgramFactory::CreateFromFiles(std::string const& a_vsFile, std::string const& a_psFile, std::string const& a_gsFile)
{
	if (a_vsFile == "" || a_psFile == "")
	{
		MENGINE_ASSERT_MSG(false, "A program must have a vertex shader and a pixel shader.");
		return nullptr;
	}

	std::string vsSource = ReadFromFile(a_vsFile);
	if (vsSource == "")
	{
		MENGINE_ASSERT_MSG(false, "vertex shader is null.");
		return nullptr;
	}

	std::string psSource = ReadFromFile(a_psFile);
	if (psSource == "")
	{
		MENGINE_ASSERT_MSG(false, "pixel shader is null.");
		return nullptr;
	}

	std::string gsSource = "";
	if (a_gsFile != "")
	{
		gsSource = ReadFromFile(a_gsFile);
		if (gsSource == "")
		{
			MENGINE_ASSERT_MSG(false, "geometry shader is null.");
			return nullptr;
		}
	}

	return CreateFromNamedSources(a_vsFile, vsSource, a_psFile, psSource, a_gsFile, gsSource);
}

std::shared_ptr<Miracle::VisualProgram> Miracle::ProgramFactory::CreateFromSources(std::string const& a_vsSource, std::string const& a_psSource, std::string const& a_gsSource /*= ""*/)
{
	return CreateFromNamedSources("vs", a_vsSource, "ps", a_psSource, "gs", a_gsSource);
}


std::string Miracle::ProgramFactory::ReadFromFile(const std::string& a_filename)
{
	std::string source = "";
	std::ifstream input(a_filename);
	if (input)
	{
		while (!input.eof())
		{
			std::string line;
			getline(input, line);
			source += line + "\n";
		}
		input.close();
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Cannot open file.");
	}
	return source;
}

