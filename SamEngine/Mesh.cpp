#pragma once
#include "Mesh.h"
#if BUILD_DIRECTX
#include "VBO_DX.h"
#endif
#if BUILD_GL
#include "VBO_GL.h"
#endif


Mesh::Mesh()
	:	_locked(false),
		_vbo(NULL)
	
{
}


Mesh::~Mesh()
{
	delete _vbo;
	_vbo = NULL;
}

bool Mesh::AddVertex(Vertex v)
{
	if (!_locked)
	{
		_vertices.push_back(v);
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::DeleteVertex(int i)
{
	if (!_locked)
	{
		_vertices.erase(_vertices.begin() + i);
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::ImportFromObj(const char * fileName)
{
	if (!_locked)
	{
		_vertices.clear();

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;

		ObjImporter::LoadObjFromFile(fileName, vertices, uvs, normals);

		for (int i = vertices.size() - 1; i >= 0; i--)
		{
			Vertex v;
			v.x = vertices[i].x;
			v.y = vertices[i].y;
			v.z = vertices[i].z;
			v.u = uvs[i].x;
			v.v = uvs[i].y;
			v.nx = normals[i].x;
			v.ny = normals[i].y;
			v.nz = normals[i].z;

			_vertices.push_back(v);
		}

		//for (int i = 0; i < vertices.size(); i++)
		//{
		//	Vertex v;
		//	v.x = vertices[i].x;
		//	v.y = vertices[i].y;
		//	v.z = vertices[i].z;
		//	v.u = uvs[i].x;
		//	v.v = uvs[i].y;
		//	v.nx = normals[i].x;
		//	v.ny = normals[i].y;
		//	v.nz = normals[i].z;

		//	_vertices.push_back(v);
		//}

		return true;
	}
	return false;
}

bool Mesh::Clear()
{
	if (!_locked)
	{
		_vertices.clear();
		return true;
	}
	return false;
}

void Mesh::Reset()
{
	delete _vbo;
	_vbo = NULL;
	_locked = false;
}

VBO* Mesh::CreateVBO(Renderer* renderer)
{
	_locked = true;

#if BUILD_DIRECTX
	_vbo = new VBO_DX();
#endif

#if BUILD_GL
	_vbo = new VBO_GL();
#endif

	_vbo->Create(renderer, _vertices.data(), NumVertices());
	return _vbo;
}
