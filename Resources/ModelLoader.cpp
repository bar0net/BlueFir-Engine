#include "ModelLoader.h"

#include "LogSystem.h"
#include "BaseMacros.h"

#include "Mesh.h"

#include "assimp/cimport.h"
#include "assimp/postprocess.h"

bluefir::graphics::Mesh * bluefir::core::ModelLoader::Load(const char* data, unsigned int size)
{
	ASSERT(data);

	
	const aiScene* scene = aiImportFileFromMemory(data, size, aiProcess_Triangulate, "FBX");

	if (scene == NULL)
	{
		const char* error = aiGetErrorString();
		LOGERROR("Error loading the model: %s", error);
		return nullptr;
	}

	return nullptr;
}
