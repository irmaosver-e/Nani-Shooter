#include "Eskeletor.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include "Game.h"

Eskeletor::Eskeletor() : Enemy()
{
    m_dyingTime = 50;
    m_health = 2;
    m_moveSpeed = 1;
    m_bulletFiringSpeed = 60;
}

void Eskeletor::collision()
{
    m_health -= 1;

    if (m_health == 0)
    {
        if (!m_bPlayedDeathSound)
        {
            //TheSoundManager::Instance().playSound("explode", 0);

           // m_textureID = "largeexplosion";
            m_currentFrame = 0;
            m_numFrames = 2;
            m_width = 60;
            m_height = 60;
            m_bDying = true;
            m_textureID = m_animations[DEAD];
        }

    }
}

void Eskeletor::collisionWithLayer()
{
    collision();
}

void Eskeletor::update()
{
    SDLGameObject::update();

    if (!m_bDying)
    {        
        m_velocity.getYRef() = (float)m_moveSpeed;

        if (m_bulletCounter == m_bulletFiringSpeed)
        {
           TheSoundManager::Instance().playSound("shoot", 0);
           TheBulletHandler::Instance().fireBullet(m_subTypeID, m_textureID, m_position, Vector2Df(-10, 0));

            m_bulletCounter = 0;
        }
        m_bulletCounter++;

    }
    else
    {
        m_velocity.getYRef() = 0;
        handleDying();
    }
}

void Eskeletor::reset(const LoaderParams& rParams, Vector2Df* position)
{
    m_textureID = m_animations[ALIVE];
    SDLGameObject::reset(rParams, position);

    m_health = 2;   
}
