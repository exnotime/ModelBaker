#ifndef MODELLOADER_H
#define MODELLOADER_H
#include "Model.h"
#include "Vertex.h"
#include "Material.h"
#include <map>
#include <assimp/scene.h>
class ModelLoader
{
public:
    ModelLoader();
    ~ModelLoader();

    bool LoadModel(const std::string& filename);
    gfx::Model& GetModel(const std::string& name);
    void Serialize(const char* filename);
public:
    int GetVertexCount(){
        return m_Vertices.size();
    };
    int GetIndexCount(){
        return m_Indices.size();
    }
    gfx::Material& GetMaterial(int index){
        return m_Materials.at(index);
    }

    size_t CalcModelSize(const gfx::Model& model);

private:
    void LoadMeshes(gfx::Model& model, const aiScene* scene);
    void LoadMaterials(gfx::Model& model,const char* filename, const aiScene* scene);

    std::map<std::string, gfx::Model> m_Models;
    std::vector<gfx::VertexPosNormalTexTangent> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<gfx::Material> m_Materials;
};

#endif // MODELLOADER_H
