#ifndef __ObjectLayer__
#define __ObjectLayer__

#include <vector>
#include "Layer.h"
#include "GameObject.h"

class ObjectLayer : public Layer
{
public:
	virtual ~ObjectLayer();

	virtual void update(Level* pLevel);
	virtual void render();

	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:

	std::vector<GameObject*> m_gameObjects;

};

#endif /* defined ( __ObjectLayer__ ) */