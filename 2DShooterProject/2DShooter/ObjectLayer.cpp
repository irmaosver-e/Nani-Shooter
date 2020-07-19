#include "ObjectLayer.h"

#include "Game.h"
#include "SDLSystem.h"
#include "GameObject.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		delete (*it);
	}
	m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
    //m_collisionManager.checkCollision(GameObject* obj, std::vector<GameObject*>* objs);
    /*
    //should check colisions in level
	m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
	m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);
	
	if (pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheSDLSystem::Instance().getScreenWidth())
	{
		m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
	}

    */

    // iterate through the objects
    if (!m_gameObjects.empty())
    {
        for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
        {
            TheCollisionManager::Instance().checkCollision(*it);

            if ((*it)->getPosition().getX() <= TheSDLSystem::Instance().getScreenWidth())
            {
                (*it)->setUpdating(true);
                (*it)->update();
            }
            else
            {
                if ((*it)->objType() != std::string("Player"))
                {
                    (*it)->setUpdating(false);
                    (*it)->scroll(TheGame::Instance().getScrollSpeed());
                }
                else
                {
                    (*it)->update();
                }
            }

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
    }
}

void ObjectLayer::render()
{
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        if (m_gameObjects[i]->getPosition().getX() <= TheSDLSystem::Instance().getScreenWidth())
        {
            m_gameObjects[i]->draw();
        }
    }
}
