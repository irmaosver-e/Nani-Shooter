#include "Level1Boss.h"
#include "Game.h"
#include "SDLSystem.h"
#include "SoundManager.h"
#include "BulletHandler.h"


Level1Boss::Level1Boss() : Enemy()
{
    m_health = 20;
    m_bulletFiringSpeed = 100;

    m_moveSpeed = 2;

    m_entered = false;

    //possibly redundant
    m_dyingTime = 100;
}

void Level1Boss::load(const LoaderParams& rParams)
{
    SDLGameObject::load(rParams);
    m_velocity.getYRef() = (float)-m_moveSpeed;
}

void Level1Boss::collision()
{
    if (m_entered)
    {
        m_health -= 1;

        if (m_health == 0)
        {
            if (!m_bPlayedDeathSound)
            {
               // m_position.getXRef() += 30;
               // m_position.getYRef() += 70;
                TheSoundManager::Instance().playSound("explode", 0);

               m_bDying = true;

                //not yet implemented
                //m_textureID = m_animations[DEAD];
            }

        }
    }
}

void Level1Boss::update()
{
    if(m_entered)
    {
        if (!m_bDying)
        {
            if (m_position.getY() + m_height >= TheSDLSystem::Instance().getScreenHeight())
            {
                m_velocity.getYRef() = (float)-m_moveSpeed;
            }
            else if (m_position.getY() <= 0)
            {
                m_velocity.getYRef() = (float)m_moveSpeed;
            }

            if (m_bulletCounter == m_bulletFiringSpeed)
            {
                /*
                TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY() + 15, 16, 16, "bullet2", 1, Vector2D(-10, 0));
                TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY() + 25, 16, 16, "bullet2", 1, Vector2D(-10, 0));

                TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY() + 200, 16, 16, "bullet2", 1, Vector2D(-10, 0));
                TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY() + 215, 16, 16, "bullet2", 1, Vector2D(-10, 0));
                */

                TheBulletHandler::Instance().fireBullet(m_subTypeID, m_position, Vector2Df(-10, 0));

                m_bulletCounter = 0;
            }

            m_bulletCounter++;

            SDLGameObject::update();
        }
        else
        {
          
            m_velocity.getYRef() = 0;
            doDyingAnimation();

            /* old code
            //scroll(TheGame::Instance().getScrollSpeed());
           // m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));

            if (m_dyingCounter >= m_dyingTime)
            {
                m_bDead = true;
                //TheGame::Instance().setLevelComplete(true);
            }
            m_dyingCounter++;
            */
        }
    }
}

void Level1Boss::scroll(float scrollSpeed)
{
    if(!(m_position.getX() < (TheSDLSystem::Instance().getScreenWidth() - (m_width + 20))))
    {
        GameObject::scroll(scrollSpeed);
    }
    else
    {
        m_entered = true;
    }
}

//needs to make it boss
void Level1Boss::reset(const LoaderParams& rParams)
{
    SDLGameObject::reset(rParams);
    m_entered = false;

    m_health = 20;
    m_dyingCounter = 0;

}

