#ifndef __Eskeletor__
#define __Eskeletor__


#include "Enemy.h"

class Eskeletor : public Enemy
{
public:

    Eskeletor();
    virtual ~Eskeletor() {}

    virtual void collision();
    virtual void collisionWithLayer();

    virtual void update();

    virtual void reset(const LoaderParams& rParams);

    virtual std::string objType() { return "Eskeletor"; }

};

#endif /* defined ( __Eskeletor__ ) */

