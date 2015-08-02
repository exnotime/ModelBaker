#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
namespace gfx {
struct Mesh {
	unsigned int VertexBufferOffset;
	unsigned int IndexBufferOffset;
    int IndexCount;
    int VertexCount;
	unsigned int Material;
    glm::vec3 Min;
    glm::vec3 Max;
};

struct Model {
    unsigned int IndexHandle;
    unsigned int VertexHandle;
	unsigned int MaterialOffset;
	std::string Name;
	int NumVertices;
	int NumIndices;
	bool Loaded;
	glm::vec3 Min;
	glm::vec3 Max;
    unsigned int MaterialCount;
	std::vector<Mesh> Meshes;
};
}
