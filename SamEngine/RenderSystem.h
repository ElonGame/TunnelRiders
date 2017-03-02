#pragma once
#include "System.h"
#include "Renderer.h"
#include <vector>
// GLM
#include "GL\GLM\GLM.hpp"
#include "GL\GLM\GTC\matrix_transform.hpp"
#include "GL\GLM\GTC\type_ptr.hpp"


// Forward declarations
class RenderComponent;

class RenderSystem :
	public System
{
public:
	RenderSystem();
	virtual ~RenderSystem();

	virtual void Process(std::vector<GameObject*>& list, double deltaTime);

	Renderer* GetRenderer()	const { return _renderer; }
	void SetRenderer(Renderer* r) { _renderer = r; }
	glm::mat4 GetMVM() const { return _MVM; }
	void SetMVM(glm::mat4 m) { _MVM = m; }

protected:
	Renderer* _renderer;
	glm::mat4 _MVM;

};

