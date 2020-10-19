#include "ObjectLayer.h"

#include "Game.h"
#include "SDLSystem.h"
#include "CollisionManager.h"
#include "ObjectSpawner.h"
#include "GameObject.h"
#include "Level.h"


ObjectLayer::~ObjectLayer()
{
    for (GameObject* pGameObj : m_gameObjects)
    {
        delete pGameObj;
    }
    m_gameObjects.clear();
}

void ObjectLayer::update()
{
     for (ObjectMarker& objMarker : m_objectMarkers)
    {
        //scroll marker
        objMarker.objPositionMarker.getXRef() -= m_scrollSpeed;
        
        TheObjectSpawner::Instance().spawnObject(*this, objMarker);

    }
    
    // iterate through the objects
    if (!m_gameObjects.empty())
    {
        for (GameObject* pGameObj : m_gameObjects)
        {
            pGameObj->update();

            if (pGameObj->isOn())
            {
                pGameObj->scroll(m_scrollSpeed);
                pGameObj->inViewCheck();

                if (pGameObj->isInView())
                {
                    pGameObj->inView();
                    TheCollisionManager::Instance().checkCollision(pGameObj);
                }
                else
                {
                    pGameObj->outOfView();
                }
            }
        }
        /*
        for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
        {
            // check if dead or off screen
            if ((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheSDLSystem::Instance().getScreenHeight()) || ((*it)->dead()))
            {
                delete* it;
                it = m_gameObjects.erase(it); // erase from vector and get new iterator
            }
            else
            {
                ++it; // increment if all ok
            }

        }
        */
    }
}

void ObjectLayer::render()
{
    for (GameObject* pGameObj : m_gameObjects)
    {
        if (pGameObj->isOn() && pGameObj->isInView())
        {
            pGameObj->draw();
        }
    }
}

