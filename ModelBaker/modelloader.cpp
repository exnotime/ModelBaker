#include "modelloader.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "fileutility.h"

ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

bool ModelLoader::LoadModel(const std::string &filename)
{
    if(m_Models.find(filename) != m_Models.end()){
        return false;
    }
    Assimp::Importer loader;
    gfx::Model model;
    const aiScene* scene = loader.ReadFile( filename.c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace );
    if(scene && scene->HasMeshes()){
        model.VertexHandle = (int)m_Vertices.size();
        LoadMeshes(model, scene);
        LoadMaterials(model, filename.c_str(),scene);
        model.Name = filename;
        m_Models[filename] = model;
    }
    return true;
}

gfx::Model &ModelLoader::GetModel(const std::string& name)
{
    return m_Models[name];
}


void ModelLoader::Serialize(const char* filename)
{
    //serialize models
}

void ModelLoader::LoadMeshes(gfx::Model &model, const aiScene *scene)
{
    int size = 0;
    int indices = 0;
    gfx::Mesh modelMesh;
    glm::vec4 modelMax , meshMax, modelMin, meshMin;
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        modelMesh.VertexBufferOffset = size;
        unsigned int numVertices = 0;
        unsigned int numIndices = 0;
        //foreach vertice
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            gfx::VertexPosNormalTexTangent vertex;
            vertex.Position.x = mesh->mVertices[i].x;
            vertex.Position.y = mesh->mVertices[i].y;
            vertex.Position.z = mesh->mVertices[i].z;
            vertex.Position.w = 1;

            meshMax = glm::max(meshMax, vertex.Position);
            meshMin = glm::min(meshMin, vertex.Position);
            if (mesh->HasNormals()) {
                vertex.Normal.x = mesh->mNormals[i].x;
                vertex.Normal.y = mesh->mNormals[i].y;
                vertex.Normal.z = mesh->mNormals[i].z;
            }
            if (mesh->HasTangentsAndBitangents()) {
                vertex.Tangent.x = mesh->mTangents[i].x;
                vertex.Tangent.y = mesh->mTangents[i].y;
                vertex.Tangent.z = mesh->mTangents[i].z;
            }
            if (mesh->mTextureCoords[0] != NULL) {
                vertex.TexCoord.x = mesh->mTextureCoords[0][i].x;
                vertex.TexCoord.y = mesh->mTextureCoords[0][i].y;
            }
            numVertices++;
            m_Vertices.push_back(vertex);
        }//end foreach vertice
        //Indices
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            //index = (Num vertices from the already loaded models) + (Size of all the already loaded meshes + mesh->faceindices)
            m_Indices.push_back(model.VertexHandle + size + mesh->mFaces[i].mIndices[0]);
            m_Indices.push_back(model.VertexHandle + size + mesh->mFaces[i].mIndices[1]);
            m_Indices.push_back(model.VertexHandle + size + mesh->mFaces[i].mIndices[2]);
            numIndices += 3;
        }
        modelMax = glm::max(meshMax, modelMax);
        modelMin = glm::min(meshMin, modelMin);
        modelMesh.Max = glm::vec3(meshMax.x,meshMax.y,meshMax.z);
        modelMesh.Min = glm::vec3(meshMin.x,meshMin.y,meshMin.z);

        modelMesh.Material = mesh->mMaterialIndex;
        modelMesh.IndexBufferOffset = indices;
        size += numVertices;
        indices += numIndices;
        modelMesh.VertexCount = numVertices;
        modelMesh.IndexCount = numIndices;
        model.Meshes.push_back(modelMesh);
    }//end foreach mesh
    model.NumVertices = size;
    model.NumIndices = indices;
    model.Max = glm::vec3(modelMax.x,modelMax.y,modelMax.z);
    model.Min = glm::vec3(modelMin.x,modelMin.y,modelMin.z);
}

void ModelLoader::LoadMaterials(gfx::Model &model,const char* filename, const aiScene *scene)
{
    model.MaterialOffset = (int)m_Materials.size();
    model.MaterialCount = scene->mNumMaterials;
    for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            gfx::Material modelMat;
            const aiMaterial* mat = scene->mMaterials[i];
            //get name
            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            modelMat.SetName(std::string(name.C_Str()));
            //albedo
            if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                aiString path;
                if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    std::string fullpath = path.data;
                    modelMat.SetAlbedoTexture(path.data);
                }
            } else {
                modelMat.SetAlbedoTexture("DefaultAlbedo");
            }
            //normal map
            if (mat->GetTextureCount(aiTextureType_HEIGHT) > 0) {
                aiString path;
                if (mat->GetTexture(aiTextureType_HEIGHT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    std::string fullpath = path.data;
                    modelMat.SetNormalTexture(fullpath.c_str());
                }
            } else {
                modelMat.SetNormalTexture("DefaultNormal");
            }
            //roughness map
            if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0) {
                aiString path;
                if (mat->GetTexture(aiTextureType_SPECULAR, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    std::string fullpath = path.data;
                    modelMat.SetRoughnessTexture(fullpath.c_str());
                }
            } else {
                modelMat.SetRoughnessTexture("DefaultRoughness");
            }
            //Metal map
            if (mat->GetTextureCount(aiTextureType_AMBIENT) > 0) { //use ambient texture as metal map for now
                aiString path;
                if (mat->GetTexture(aiTextureType_AMBIENT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    std::string fullpath = path.data;
                    modelMat.SetMetalTexture(fullpath.c_str());
                }
            } else {
                modelMat.SetMetalTexture("DefaultMetal");
            }
            m_Materials.push_back(modelMat);
        }
}
