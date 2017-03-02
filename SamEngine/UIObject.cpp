#include "UIObject.h"


UIObject::UIObject(Mesh* mesh, Texture* texture, glm::vec3 position, glm::vec3 scale) : GameObject("ui")
{
	RenderComponent* rc = new RenderComponent(this);
	rc->TwoDimensions(true);
	rc->ShouldDraw(true);
	rc->SetMesh(mesh);
	rc->SetTexture(texture);

	_position = position;
	_scale = scale;
}


UIObject::~UIObject()
{
}

void UIObject::Start()
{
	GameObject::Start();
}

void UIObject::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void UIObject::End()
{
	GameObject::End();
}

void UIObject::Reset()
{
	GameObject::Reset();
}

