#pragma once
#include "ObjImporter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


bool ObjImporter::LoadObjFromFile(const char * fileName, std::vector<glm::vec3> &verticies, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals)
{
	verticies.clear();
	uvs.clear();
	normals.clear();

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;

	std::ifstream file;
	file.open(fileName);
	std::string line;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			
			if (line.substr(0, 2) == "v ")	// Vertex
			{
				std::istringstream v (line.substr(2));
				glm::vec3 vertex;
				v >> vertex.x; v >> vertex.y; v >> vertex.z;
				tempVertices.push_back(vertex);
			}
			else if (line.substr(0, 2) == "vt") // UV
			{
				std::istringstream v (line.substr(2));
				glm::vec2 uv;
				v >> uv.x; v >> uv.y;
				uv.y = 1.0f - uv.y;
				tempUVs.push_back(uv);
			}
			else if (line.substr(0, 2) == "vn") // Normal
			{
				std::istringstream v(line.substr(2));
				glm::vec3 normal;
				v >> normal.x; v >> normal.y; v >> normal.z;
				tempNormals.push_back(normal);
			}
			else if (line.substr(0, 2) == "f ") // Triangles / Faces
			{
				std::string left = line.substr(2);
				
				std::istringstream v(left);
				unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
				char ch;

				v >> vertexIndex[0] >> ch >> uvIndex[0] >> ch >> normalIndex[0];
				v >> vertexIndex[1] >> ch >> uvIndex[1] >> ch >> normalIndex[1];
				v >> vertexIndex[2] >> ch >> uvIndex[2] >> ch >> normalIndex[2];

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				if (v >> vertexIndex[3] >> ch >> uvIndex[3] >> ch >> normalIndex[3])
				{
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
					vertexIndices.push_back(vertexIndex[0]);

					uvIndices.push_back(uvIndex[2]);
					uvIndices.push_back(uvIndex[3]);
					uvIndices.push_back(uvIndex[0]);

					normalIndices.push_back(normalIndex[2]);
					normalIndices.push_back(normalIndex[3]);
					normalIndices.push_back(normalIndex[0]);
				}
			}
		}
		file.close();
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		verticies.push_back(tempVertices[vertexIndices[i] - 1]);
		uvs.push_back(tempUVs[uvIndices[i] - 1]);
		normals.push_back(tempNormals[normalIndices[i] - 1]);
	}
	
	return true;
}
