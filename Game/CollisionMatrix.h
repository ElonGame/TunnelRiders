#pragma once

// Need to be powers of 2, for bit mask to work
enum CollisionID
{
	Ship_ID = 1,
	Tunnel_ID = 2,
	Obstacle_ID = 4,
	Power_Up = 8
};
