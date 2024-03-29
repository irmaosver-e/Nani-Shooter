#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic() : SDLGameObject() {}
	virtual ~AnimatedGraphic() {}

	virtual void load(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_animSpeed;
	int m_frameCount;
};

#endif /* defined ( __AnimatedGraphic__ ) */