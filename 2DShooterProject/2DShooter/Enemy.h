#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:

	virtual std::string objType() { return "Enemy"; }
	
	virtual void outOfView() { turnObjOff(); }

protected:
	int m_health;

	Enemy() : SDLGameObject() {}
	virtual ~Enemy() {}
};

#endif /*defined(__Enemy__)*/