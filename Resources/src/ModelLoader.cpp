#include "ModelLoader.h"

#include "LogSystem.h"
#include "BaseMacros.h"

#include "Mesh.h"
#include "Material.h"

#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/material.h"
#include "assimp/mesh.h"

#include "assimp/config.h"

bool bluefir::core::ModelLoader::Load(const char * data, unsigned int size, std::vector<graphics::Mesh*>& meshes, std::vector<graphics::Material*> materials)
{
	ASSERT(data);

	const aiScene* scene = aiImportFileFromMemory(data, size, aiProcess_Triangulate, "FBX");

	if (scene == NULL)
	{
		const char* error = aiGetErrorString();
		LOGERROR("Error loading the model: %s", error);
		return false;
	}

	graphics::Material* material = new graphics::Material();
	material->atributes_["texture"] = new graphics::MaterialAttribData<void, 1>();

	int x = 1;
	material->atributes_["texture"]->SetData(&x);

	int i = material->atributes_["texture"]->GetValue<int>();

	aiReleaseImport(scene);
	return true;
}
