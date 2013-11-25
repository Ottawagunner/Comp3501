#include "collisionmanagerclass.h"


CollisionManagerClass::CollisionManagerClass(void)
{
}


CollisionManagerClass::~CollisionManagerClass(void)
{
}

bool CollisionManagerClass::AreColliding(MobileEntityClass* entityOne, MobileEntityClass* entityTwo)
{
	float entityOneRadius, entityTwoRadius, a, b, c, d, vx, vy, vz, px, py, pz;

	entityOneRadius = entityOne->GetWidth()/2;
	entityTwoRadius = entityTwo->GetWidth()/2;

	entityOne->GetPosition(vx, vy, vz);
	entityTwo->GetPosition(px, py, pz);

	a = vx - px;
	b = vy - py;
	c = vz - pz;

	d = sqrt(a*a + b*b + c*c);

	return entityOneRadius + entityTwoRadius > d;
}
