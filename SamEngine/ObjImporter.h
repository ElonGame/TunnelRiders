#pragma once
#include <vector>
// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class ObjImporter
{
public:
	static bool LoadObjFromFile(const char * fileName, std::vector<glm::vec3> &verticies, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals);

private:
	ObjImporter() {}
};

