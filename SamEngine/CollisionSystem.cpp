#include "stdafx.h"
#include "CollisionSystem.h"
#include "GameObject.h"	
#include "CollisionComponent.h"
#include "CollisionMessage.h"
#include "BoxColliderComponent.h"
#include <iostream>


CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::Process(std::vector<GameObject*>& list, double deltaTime)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		GameObject* collidee = list[i];

		if (!collidee->IsAlive()) continue;
		if (CollisionComponent* cc1 = (CollisionComponent*)(collidee->GetComponent("collision")))
		{
			if (cc1->GetCollisionID() == 0) continue;
			if (cc1->Enabled() == false) continue;
			bool collision = false;
			for (size_t j = i+1; j < list.size(); j++)
			{
				GameObject* collider = list[j];

				if (collidee == collider) continue;
				if (!collider->IsAlive()) continue;

				if (CollisionComponent* cc2 = (CollisionComponent*)(collider->GetComponent("collision")))
				{
					if (cc2->GetCollisionID() == 0) continue;
					if (cc2->Enabled() == false) continue;
					if (cc1->CheckCollisionMatrixFlag(cc2->GetCollisionID()))
					{	
						switch (cc2->GetColliderType())
						{
							case ColliderType::Box:
								collision = cc1->CollideWith((BoxColliderComponent*)cc2);
								break;
							case ColliderType::Circle:
								collision = cc1->CollideWith((CircleColliderComponent*)cc2);
								break;
							case ColliderType::InverseCircle:
								collision = cc1->CollideWith((InverseCircleColliderComponent*)cc2);
								break;
						}

						if (collision)
						{
							// Send a collision message to both objects
							CollisionMessage msg(collidee, collider);
							collidee->OnMessage(&msg);
							collider->OnMessage(&msg);
							break;
						}
					}
				}
			}
		}
	}
}