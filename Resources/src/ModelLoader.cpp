#include "ModelLoader.h"

#include "LogSystem.h"
#include "BaseMacros.h"
#include "FileSystem.h"

#include "Mesh.h"
#include "Material.h"

#include "../Vendor/Assimp/include/assimp/cimport.h"
#include "../Vendor/Assimp/include/assimp/postprocess.h"
#include "../Vendor/Assimp/include/assimp/scene.h"
#include "../Vendor/Assimp/include/assimp/material.h"
#include "../Vendor/Assimp/include/assimp/mesh.h"

#include "ModuleTexture.h"
#include "BufferLayout.h"
#include "ModuleRenderer.h"

// TODO: think how to properly import textures from here!
// maybe return a vector with all the paths

bool bluefir::core::ModelLoader::Load(const char * data, unsigned int size, std::vector<int>& meshes, std::vector<int>& materials)
{
	ASSERT(data);

	/*std::string folder(filename);
	if (folder.find_first_of("\\") == std::string::npos) folder = "";
	else folder = folder.substr(0, folder.find_last_of("\\") + 1);*/

	const aiScene* scene = aiImportFileFromMemory(data, size, aiProcess_Triangulate, "FBX");

	if (scene == NULL)
	{
		const char* error = aiGetErrorString();
		LOGERROR("Error loading the model: %s", error);
		return false;
	}

	meshes.reserve(scene->mNumMeshes);

	LOGINFO("Loading 3D model.");
	ParseNode(scene->mRootNode, aiMatrix4x4(), scene, meshes);
	LOGINFO("Loading 3D model complete.");

	LOGINFO("Loading model textures.");
	materials.reserve(scene->mNumMaterials);
	/*for (unsigned int i = 0U; i < scene->mNumMaterials; ++i)
	{
		aiString path;
		scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path, (aiTextureMapping*)aiTextureMapping_UV, 0);

		unsigned int textureID = bluefir_textures.LoadTexture((folder + path.C_Str()).c_str());
		materials.emplace_back(textureID);
	}*/
	LOGINFO("Loading model textures complete.");

	aiReleaseImport(scene);
	return true;
}

void bluefir::core::ModelLoader::ParseNode(const aiNode* const node, aiMatrix4x4 transform, const aiScene* const scene, std::vector<int>& meshes)
{
	
	ASSERT(scene);

	if (node == nullptr) return;

	transform = transform * node->mTransformation;
	for (unsigned int i = 0U; i < node->mNumChildren; i++)
	{
		ParseNode(node->mChildren[i], transform, scene, meshes);
	}

	for (unsigned int i = 0U; i < node->mNumMeshes; ++i)
	{
		graphics::Mesh* m = nullptr;

		// TODO: Do I want to use a version this?
		switch (scene->mMeshes[i]->mPrimitiveTypes)
		{
		case (aiPrimitiveType_POINT):
			//m.poylygon = 1;
			break;
		case(aiPrimitiveType_LINE):
			//m.poylygon = 2;
			break;
		case(aiPrimitiveType_TRIANGLE):
			//m.poylygon = 3;
			break;

		default:
			LOGWARNING("Mesh %d contains non supported polygons.");
			continue;
			break;
		}

		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.emplace_back(bluefir_renderer.CreateMesh(CreateMesh(mesh, &transform)));
	}
}

bluefir::graphics::Mesh* bluefir::core::ModelLoader::CreateMesh(const aiMesh* const mesh, const aiMatrix4x4* transform)
{
	ASSERT(mesh);

	unsigned int num_uvw_coord = mesh->mNumUVComponents[0];

	std::vector<float>* vertices = new std::vector<float>();
	std::vector<unsigned int>* indices = new std::vector<unsigned int>();
	graphics::BufferLayout* layout = new graphics::BufferLayout();

	layout->Push<float>(3);
	layout->Push<int>(num_uvw_coord);

	for (unsigned int j = 0U; j < mesh->mNumVertices; ++j)
	{
		aiVector3D v = *transform * mesh->mVertices[j];

		float* vertex = (float*)&v;
		for (unsigned int k = 0U; k < 3U; ++k)
			vertices->push_back(vertex[k]);

		float* uvw = (float*)&mesh->mTextureCoords[0][j];
		for (unsigned int k = 0U; k < num_uvw_coord; ++k) 
			vertices->push_back(uvw[k]);
	}

	for (unsigned int i = 0U; i < mesh->mNumFaces; ++i)
	{
		if (mesh->mFaces[i].mNumIndices > 3)
		{
			LOGWARNING("Mesh with more than 3 vertices per element.");
		}

		for (unsigned int j = 0U; j < mesh->mFaces[i].mNumIndices; ++j)
		{
			indices->push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	graphics::Mesh* _m = new graphics::Mesh(vertices, indices, layout);
	_m->Build();
	return _m;
}