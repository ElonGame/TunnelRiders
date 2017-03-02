#pragma once
#include "GameObjectComponent.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Texture.h"


class RenderComponent
	: public GameObjectComponent
{
public:
	RenderComponent(GameObject* gob);
	virtual ~RenderComponent();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void OnMessage(Message* msg);
	virtual void End();

	Mesh* GetMesh() const { return _mesh; }
	void SetMesh(Mesh* m) { _mesh = m; }

	Texture* GetTexture() const { return _texture; }
	void SetTexture(Texture* texture) { _texture = texture; }

	glm::vec4 GetColour() const { return _colour; }
	void SetColour(glm::vec4 c) { _colour = c; }

	bool ShouldDraw() const { return _shouldDraw; }
	void ShouldDraw(bool v) { _shouldDraw = v; }

	bool TwoDimensions() const { return _twoDimensions; }
	void TwoDimensions(bool d) { _twoDimensions = d; }

	// Get position/scale/angle etc from parent object
	glm::vec3 GetAngle() const { return _gameObject->GetAngle(); }
	glm::vec3 GetScale() const { return _gameObject->GetScale(); }
	glm::vec3 GetPosition() const { return _gameObject->GetPosition(); }


protected:
	Mesh* _mesh;
	Texture* _texture;
	glm::vec4 _colour;
	bool _shouldDraw;
	bool _twoDimensions;
};

