#include "Cursor.h"

#include "SDLSystem.h"
#include "InputHandler.h"

void Cursor::load(const LoaderParams& rParams)
{
	SDLGameObject::load(rParams);

	//should get from levelmap
	m_moveSpeed = 3;

	m_textureID = m_animations[0];
}

void Cursor::draw()
{
	SDLGameObject::draw();
}

void Cursor::update()
{
	m_velocity.getXRef() = 0;
	m_velocity.getYRef() = 0;
	handleInput();
	SDLGameObject::update();

	//SDLGameObject::handleAnimation();
}

void Cursor::clean()
{
	SDLGameObject::clean();
}

void Cursor::collision()
{
}

void Cursor::handleInput()
{
	// handle keys
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
	{
		m_velocity.getYRef() = (float)-m_moveSpeed;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight() - 10)
	{
		m_velocity.getYRef() = (float)m_moveSpeed;
	}

	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
	{
		m_velocity.getXRef() = (float)-m_moveSpeed;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth())
	{
		m_velocity.getXRef() = (float)m_moveSpeed;
	}

	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		//temporary TEST
		m_animSpeed = 300;
	}
	else
	{
		// temporary TEST
		if (m_animSpeed > 150)
		{
			m_animSpeed--;
		}
	}
	// */

	/* handle joysticks /
	if(TheInputHandler::Instance().joysticksInitialised())
	{
		if(TheInputHandler::Instance().getButtonState(0, 2))
		{
			if(m_bulletCounter == m_bulletFiringSpeed)
			{
				TheSoundManager::Instance().playSound("shoot", 0);
				TheBulletHandler::Instance().addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
				m_bulletCounter = 0;
			}

			m_bulletCounter++;
		}
		else
		{
			m_bulletCounter = m_bulletFiringSpeed;
		}

		if((TheInputHandler::Instance().getAxisX(0, 1) > 0 && (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth()) || (TheInputHandler::Instance().getAxisX(0, 1) < 0 && m_position.getX() > 0))
		{
			m_velocity.setX(m_moveSpeed * TheInputHandler::Instance().getAxisX(0, 1));
		}

		if((TheInputHandler::Instance().getAxisY(0, 1) > 0 && (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight() - 10 ) || (TheInputHandler::Instance().getAxisY(0, 1) < 0 && m_position.getY() > 0))
		{
			m_velocity.setY(m_moveSpeed * TheInputHandler::Instance().getAxisY(0, 1));
		}
	}
	//*/
}
