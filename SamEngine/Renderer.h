#pragma once

// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"

class Game;
class RenderComponent;
class Mesh;
class Texture;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual void ClearScreen() = 0;
	virtual void Draw(const Mesh* mesh, const Texture* texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 PM, const glm::vec4 colour) = 0;
	virtual void Draw2D(const Mesh* mesh, const Texture* texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 OM, glm::vec4 colour) = 0;
	virtual void Draw(RenderComponent* gob, glm::mat4 MM);
	virtual void Draw2D(RenderComponent* gob, glm::mat4 MM);
	virtual void Destroy() = 0;
	virtual void Initialise(int width, int height) = 0;
	virtual void SwapBuffers() = 0;

	glm::vec4 _clearColour;

	glm::vec4 GetClearColour() const { return _clearColour; }
	void SetClearColour(glm::vec4 c) { _clearColour = c; }
};

