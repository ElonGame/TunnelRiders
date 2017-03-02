#pragma once
#include "Renderer.h"
#include "RenderComponent.h"
#include "Game.h"


Renderer::Renderer()
	:	_clearColour(16.0f / 255.0f, 151.0f / 255.0f, 220.0f / 255.0f, 1.0f)
{
	
}


Renderer::~Renderer()
{
}

void Renderer::Draw(RenderComponent* gob, glm::mat4 MM)
{
	if (gob->ShouldDraw())
	{
		MM = glm::translate(MM, gob->GetPosition());
		MM = glm::rotate(MM, -gob->GetAngle().z, glm::vec3(0, 0, 1)); // Rotates anti-clockwise
		MM = glm::rotate(MM, -gob->GetAngle().y, glm::vec3(0, 1, 0)); // Rotates anti-clockwise
		MM = glm::rotate(MM, -gob->GetAngle().x, glm::vec3(1, 0, 0)); // Rotates anti-clockwise
		MM = glm::scale(MM, gob->GetScale());

		if (gob->GetMesh())
		{
			Draw(gob->GetMesh(), gob->GetTexture(), 
				MM, 
				Game::TheGame->GetSceneManager()->GetCamera()->GetViewMatrix(), 
				Game::TheGame->GetSceneManager()->GetCamera()->GetProjectionMatrix(), 
				gob->GetColour());
		}
	}
}

void Renderer::Draw2D(RenderComponent * gob, glm::mat4 MM)
{
	if (gob->ShouldDraw())
	{
		MM = glm::translate(MM, glm::vec3(-gob->GetPosition().x, gob->GetPosition().y, 1.0f));
		MM = glm::rotate(MM, -gob->GetAngle().z, glm::vec3(0, 0, 1)); // Rotates anti-clockwise
		MM = glm::scale(MM, glm::vec3(gob->GetScale().x, gob->GetScale().y, 1.0f));

		glm::mat4 ortho = Game::TheGame->GetSceneManager()->GetCamera()->GetOrthoMatrix();
		//ortho = glm::transpose(ortho);

		if (gob->GetMesh())
		{
			Draw(gob->GetMesh(), gob->GetTexture(),
				MM, 
				Game::TheGame->GetSceneManager()->GetCamera()->GetViewMatrix(), 
				ortho,
				glm::vec4(gob->GetColour().x, gob->GetColour().y, gob->GetColour().z, 0.0f));
		}
	}
}
