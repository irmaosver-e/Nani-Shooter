#include "RoofTurret.h"

#include "SDLSystem.h"
#include "Game.h"
#include "TextureManager.h"
#include "BulletHandler.h"

void RoofTurret::draw()
{
	//TextureManager::Instance().drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		//                                    m_width, m_height, m_currentRow, m_currentFrame, TheSDLSystem::Instance().getRenderer(), m_angle, m_alpha, SDL_FLIP_VERTICAL);
}

void RoofTurret::update()
{
    if (!m_bDying)
    {
        // we want to scroll this object with the rest
        //scroll(TheGame::Instance().getScrollSpeed());

        if (m_bulletCounter == m_bulletFiringSpeed)
        {
           // TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-3, 3));
           // TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX() + 20, (int)m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(0, 3));
           // TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX() + 40, (int)m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(3, 3));
            m_bulletCounter = 0;
        }

        m_bulletCounter++;
    }
    else
    {
        //scroll(TheGame::Instance().getScrollSpeed());
        handleDying();
    }
}
