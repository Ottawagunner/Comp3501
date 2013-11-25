#pragma once

#include "mobileentityclass.h"
#include "projectileclass.h"

class CollisionManagerClass
{
public:
	CollisionManagerClass(void);
	~CollisionManagerClass(void);

	bool AreColliding(MobileEntityClass* entityOne, MobileEntityClass* entityTwo);
};

