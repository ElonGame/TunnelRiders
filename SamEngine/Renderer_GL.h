#pragma once
#if BUILD_GL
#include "Renderer.h"
#include "Mesh.h"
#include "Texture.h"

class Renderer_GL :
	public Renderer
{
public:
	Renderer_GL();
	virtual ~Renderer_GL();

	virtual void ClearScreen() {}
	virtual void Destroy() {}
	virtual void Draw(const Mesh* mesh, const Texture* texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 PM, glm::vec4 colour) {}
	virtual void Draw2D(const Mesh* mesh, const Texture* texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 OM, glm::vec4 colour) {}
	virtual void Initialise(int width, int height) {}
	virtual void SwapBuffers() {}
	void InitialiseShaders() {}
};

#endif