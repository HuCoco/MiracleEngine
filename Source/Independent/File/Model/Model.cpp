#include "Model.h"
#include <Independent/File/FileSystem.h>
#include <Independent/File/Image/TexImage.h>
#include <ResourceManager/GameResourceSystem.h>
#include <Core/Foundation/HName.h>


Miracle::Model::~Model()
{
}


void Miracle::Model::AddMesh(Mesh* a_Mesh)
{
	m_Meshs.emplace_back(a_Mesh);
}
