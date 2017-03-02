#pragma once
#if BUILD_GL
#include "Texture.h"
class Texture_GL :
	public Texture
{
public:
	Texture_GL();
	virtual ~Texture_GL();
};

#endif