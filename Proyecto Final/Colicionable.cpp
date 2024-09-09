#include "Colicionable.h"

bool Colicionable::isCollision(Colicionable &obj) const
{
	return getBounds().intersects(obj.getBounds());
}
