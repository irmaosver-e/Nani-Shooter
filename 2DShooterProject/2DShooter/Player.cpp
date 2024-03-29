#include "Player.h"

#include <SDL.h>

#include "Game.h"
#include "SDLSystem.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "SoundManager.h"
 
Player::Player() : SDLGameObject()
{
	m_bFlyingInOutScreen = NOWHERE;
	m_invulnerable = false;
	m_invulnerableTime = 200;
	m_invulnerableCounter = 0;
	m_lives = 1;
	m_playerHUD = nullptr;
	m_currentForm = SHIP;
	
	m_requestedInputs.direction_hat.H_direction = TB_H_REST;
	m_requestedInputs.direction_hat.V_direction = TB_V_REST;
	m_requestedInputs.action = NO_ACT;
	m_requestedDirectAction = NO_ACT;

	m_desiredAction = NO_ACT;
	//m_lastAction = NO_ACT;
	m_desiredAnimation = NO_ANIM;

	m_desiredAnimation_direction.H_direction = TB_H_REST;
	m_desiredAnimation_direction.V_direction = TB_V_REST;
	m_desired_move_animation_finished = true;
}

Player::~Player()
{
	delete m_playerHUD;
}

void Player::load(const LoaderParams& rParams)
{
	// inherited load function
	SDLGameObject::load(rParams);
	refreshTextureVariables();
	resetAnimation();
	m_currentFrame = m_middleFrame;

	// can set up the players inherited values here
	m_lives = rParams.getLives();

	// set up bullets
	m_bulletFiringSpeed = 7;
	m_moveSpeed = 4;

	// we want to be able to fire instantly
	m_bulletCounter = m_bulletFiringSpeed;

	// time it takes for death explosion
	m_dyingTime = 100;
}

void Player::reset(const LoaderParams& rParams, Vector2Df* position)
{
	actions currentAction = m_desiredAction;	
	ressurectAction(); //sets m_desiredAction to NO_ACT
	
	//it hasnt finished the last stage stage, it must be restarting the game
	if (currentAction != FLY_OFF_ACT)
	{
		m_lives = rParams.getLives();

		if (position)
		{
			m_position = *position;
		}
	}
	
	m_dyingCounter = m_dyingTime;
	m_invulnerable = false;

	m_requestedDirectAction = NO_ACT;	
}

void Player::draw()
{
	SDLGameObject::draw();
	m_playerHUD->draw();
}

void Player::update()
{
	if (m_bUpdating)
	{
		//set invulnerable when resurrected
		if (m_invulnerable)
		{
			m_dyingCounter++;
			if (m_dyingCounter > m_dyingTime)
			{
				m_invulnerable = false;
			}
		}

		m_velocity.getXRef() = 0;
		m_velocity.getYRef() = 0;

		handleInput();

		trackFrameTime();

		handleRequests();
		handleActions(); //has to be b4 animations
		handleAnimation();

		m_position += m_velocity;
	}
}

void Player::collision()
{	
	/*
	  //godmode for debuging
	std::cout << "GOD MODE ON in Player::collision() \n";
	m_invulnerable = true;
	//*/
	  
	//-----------------------
		
	if (!m_invulnerable)
	{
		TheSoundManager::Instance().playSound("shipExplode", 0);
		m_requestedDirectAction = DEATH_ACT;
	}
}

void Player::collisionWithLayer()
{
	collision();
}

void Player::outOfView()
{
	//it is somewhere to the right of the screen
	if (m_position.getX() > 0)
	{
		m_bUpdating = false;
	}
	else
	{
		//player is to the left of the screen
		m_requestedDirectAction = FLY_IN_ACT;
	}

}

void Player::flyOffScreen()
{
	m_requestedDirectAction = FLY_OFF_ACT;
}

void Player::handleInput()
{
	//---------------------------handle Vertical move requests-------------------------------
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_UP) && m_requestedInputs.direction_hat.V_direction != TB_DOWN) //stops UP having priority
	{
		m_requestedInputs.direction_hat.V_direction = TB_UP;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_requestedInputs.direction_hat.V_direction = TB_DOWN;
	}
	else
	{
		m_requestedInputs.direction_hat.V_direction = TB_V_REST;
	}
	
	//-----------------------------handle Horizontal move requests-------------------------------
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_LEFT) && m_requestedInputs.direction_hat.H_direction != TB_RIGHT) //stops LEFT having priority
	{
		m_requestedInputs.direction_hat.H_direction = TB_LEFT;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_requestedInputs.direction_hat.H_direction = TB_RIGHT;
	}
	else
	{
		m_requestedInputs.direction_hat.H_direction = TB_H_REST;
	}

	//------------------------------handle action request----------------------------------------
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_S)) // transform requests prioritised
	{
		m_requestedInputs.action = TRANSFORM_ACT;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_requestedInputs.action = ATTACK_ACT;
	}
	else
	{
		m_requestedInputs.action = NO_ACT;
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

	//}
}

void Player::handleRequests()
{
	//----- handle requests
	if (m_desiredAction == NO_ACT) //no action pending, animations should be finished
	{
		static actions lastAction = NO_ACT;
		if (m_requestedDirectAction != NO_ACT) //direct actions have priority over input actions
		{
			switch (m_requestedDirectAction)
			{
			case FLY_OFF_ACT:
				if (m_currentForm == MECHA) //fly off stage as a ship
				{
					m_desiredAction = TRANSFORM_ACT;
					m_desiredAnimation = TRANSFORM_ANIM;
				}
				else
				{
					m_desiredAction = FLY_OFF_ACT;
				}
				lastAction = m_desiredAction;
				break;

			case FLY_IN_ACT:
				m_desiredAction = FLY_IN_ACT;
				lastAction = m_desiredAction;
				break;

			case DEATH_ACT:
				if (lastAction != DEATH_ACT) //prevents death spamming
				{
					m_desiredAction = DEATH_ACT;
					m_desiredAnimation = DEATH_ANIM;
					lastAction = m_desiredAction;
				}
				break;

			case RESSURECT_ACT:
				m_desiredAction = RESSURECT_ACT;
				lastAction = m_desiredAction;
				break;
			}

			m_requestedDirectAction = NO_ACT;
		}
		else
		{
			switch (m_requestedInputs.action)
			{
			case TRANSFORM_ACT:
				if (lastAction != TRANSFORM_ACT) //prevents actions from spamming if button down
				{
					m_desiredAction = TRANSFORM_ACT;
					m_desiredAnimation = TRANSFORM_ANIM;
					lastAction = m_desiredAction;
				}
				break;
			case ATTACK_ACT:
				m_desiredAction = ATTACK_ACT;
				m_desiredAnimation = ATTACK_ANIM;
				lastAction = m_desiredAction;
				break;

			default:
				if (lastAction != ATTACK_ACT && m_currentForm == MECHA)
				{
					// handles returning to mecha idle anim when fire button released
					m_desiredAnimation = MECHA_IDLE;
				}
				m_bulletCounter = m_bulletFiringSpeed;
				lastAction = m_desiredAction;
			}
		}
	}
}

void Player::handleActions()
{
	actions desiredAct = m_desiredAction;
	//direct actions
	if ((m_desiredAction == FLY_OFF_ACT || m_desiredAction == FLY_IN_ACT) && m_desiredAnimation == NO_ANIM)
	{
		flyInOffAction(m_desiredAction);
	}

	if (m_desiredAction == DEATH_ACT && m_desiredAnimation == NO_ANIM)
	{
		deathAction();
	}
	else if (m_desiredAction == RESSURECT_ACT && m_desiredAnimation == NO_ANIM)
	{
		ressurectAction();
	}

	// input actions only if no direct actions are on
	if (desiredAct != DEATH_ACT
		&& desiredAct != FLY_OFF_ACT
		&& desiredAct != FLY_IN_ACT)
	{
		if (m_desiredAction == TRANSFORM_ACT && m_desiredAnimation == NO_ANIM)
		{
			transformAction();
		}

		//only move or attack if tranform action is off
		if (m_desiredAction != TRANSFORM_ACT)
		{
			moveAction();

			if (m_desiredAction == ATTACK_ACT && m_desiredAnimation == NO_ANIM)
			{
				attackAction();
			}

		}
	}
}

void Player::attackAction()
{
	if (m_bulletCounter >= m_bulletFiringSpeed)
	{
		TheSoundManager::Instance().playSound("shoot", 0);

		TheBulletHandler::Instance().fireBullet(m_subTypeID, m_textureID, m_position, Vector2Df(10, 0));
		m_bulletCounter = 0;
	}
	else
	{
		m_bulletCounter++;
	}

	m_desiredAction = NO_ACT;
}

void Player::moveAction()
{
	//----- deals W vertical move request
	bool addVel = true;
	switch (m_requestedInputs.direction_hat.V_direction)
	{
	case TB_UP:
		addVel = (m_position.getY() > 0);
		break;

	case TB_DOWN:
		addVel = (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight();
		break;
	}

	if (addVel)
	{
		m_velocity.getYRef() = (float)m_moveSpeed * m_requestedInputs.direction_hat.V_direction;
	}

	//----- deals W horizontal move request
	addVel = true;
	switch (m_requestedInputs.direction_hat.H_direction)
	{
	case TB_LEFT:
		addVel = (m_position.getX() > 0);
		break;

	case TB_RIGHT:
		addVel = (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth();
		break;
	}

	if (addVel)
	{
		m_velocity.getXRef() = (float)m_moveSpeed * m_requestedInputs.direction_hat.H_direction;
	}
}

void Player::transformAction()
{
	m_currentForm = (stances)(m_currentForm * -1); //inverts form

	switch (m_currentForm)
	{
	case MECHA:
		m_bulletFiringSpeed = 4;
		m_moveSpeed = 2;
		break;
	case SHIP:
		m_bulletFiringSpeed = 7;
		m_moveSpeed = 4;
		break;
	}
	m_desiredAction = NO_ACT;
}

void Player::flyInOffAction(actions inOutAction)
{
	m_invulnerable = true;
	m_velocity.getYRef() = 0;
	m_velocity.getXRef() = (float)m_moveSpeed * 2;

	if(m_desiredAction == FLY_IN_ACT && m_position.getX() >= (TheSDLSystem::Instance().getScreenWidth() / 4))
	{
		//can start counting the invulnerable frames 
		m_dyingCounter = 0; //should be renamed to invulnerable frames
		
		m_desiredAction = NO_ACT;
	}

	//m_bFlyingInOutScreen = inOut;
}

void Player::deathAction()
{
	m_lives -= 1;

	//m_invulnerable = true;

	m_desiredAction = NO_ACT;
	m_requestedDirectAction = RESSURECT_ACT;
}

void Player::ressurectAction()
{
	// ----------- ressurect action

	//needs to get reset pos from params
	m_position.getXRef() = 0 - (m_width + 10);
	m_position.getYRef() = (TheSDLSystem::Instance().getScreenHeight() / 2) - (m_height / 2); //middle of the screen

	m_currentForm = SHIP;
	switchAnimation(SHIP_IDLE);
	m_currentFrame = m_middleFrame;

	m_bulletFiringSpeed = 7;
	m_moveSpeed = 4;

	m_invulnerable = true;

	m_desiredAction = NO_ACT;
}

void Player::handleAnimation()
{
	switch (m_desiredAnimation)
	{
	case TRANSFORM_ANIM:
		transformAnim();
		break;

	case DEATH_ANIM:
		deathAnim();
		break;
	
	default:
		//m_desiredAction = IDLE;
		break;
	}

	//handles move and attack anim
	if (m_desiredAnimation != TRANSFORM_ANIM && m_desiredAnimation != DEATH_ANIM)
	{
		switch (m_currentForm)
		{
		case MECHA:
			handleMechaAnim();
			break;

		case SHIP:
			handleShipAnim();
			break;
		}
	}

	//quick and dirty way offlash when invulnerable
	if (m_invulnerable && (m_dyingCounter > 0 && m_dyingCounter < m_dyingTime))
	{
		if (m_alpha == 255)
		{
			m_alpha = 0;
		}
		else
		{
			m_alpha = 255;
		}
	}
	else
	{
		m_alpha = 255;
	}
}

void Player::handleMechaAnim()
{
	//-------------------------------handles action animations--------------------

	//handles attack transition animations
	if (m_desiredAnimation == ATTACK_ANIM || m_desiredAnimation == MECHA_IDLE)
	{
		animations nextAnim = m_desiredAnimation;

		//checks if the anim is not the desired already nor transition
		if (m_textureID != m_animations[MECHA_ATTACK_TRANSITION] && m_textureID != m_animations[m_desiredAnimation])
		{
			//must be either ATTACK_ANIM or MECHA_IDLE
			nextAnim = MECHA_ATTACK_TRANSITION;
		}

		//waits for the frame to pass the switch animation, but dont reset the frame count
		if (m_bNextFrameOK)
		{
			switchAnimation(nextAnim, false);
		}

		//reached the desired animation 
		if (m_textureID == m_animations[m_desiredAnimation])
		{
			m_desiredAnimation = NO_ANIM;
		}

	}

	//--------------------------handles move animations-----------------------

	static int startFrame, endFrame;
	//sets the desired animation direction
	if (m_desired_move_animation_finished &&
		m_desiredAnimation_direction.H_direction != m_requestedInputs.direction_hat.H_direction)
	{
		if (m_desiredAnimation_direction.H_direction == -m_requestedInputs.direction_hat.H_direction)
		{
			//if the past desired anim is the inverse of the request needs to first go to rest position
			m_desiredAnimation_direction.H_direction = TB_H_REST;
		}
		else
		{
			m_desiredAnimation_direction.H_direction = m_requestedInputs.direction_hat.H_direction;
		}

		switch (m_desiredAnimation_direction.H_direction)
		{
		case TB_RIGHT:
			startFrame = m_middleFrame;
			endFrame = m_numFrames - 1;
			break;
		case TB_LEFT:
			startFrame = m_middleFrame;
			endFrame = 0;
			break;
		default: // TB_V_REST
			int frameHolder = startFrame;
			startFrame = endFrame;
			endFrame = frameHolder;

		}

		m_desired_move_animation_finished = false;

		resetAnimation();
	}

	//deals with the desired animation direction
	//checks if there is a animation to perform
	if (!m_desired_move_animation_finished)
	{
		m_desired_move_animation_finished = playAnimation(startFrame, endFrame);
	}	
}

void Player::handleShipAnim()
{
	static int startFrame, endFrame;

	//sets the desired animation direction
	if (m_desired_move_animation_finished && 
		m_desiredAnimation_direction.V_direction != m_requestedInputs.direction_hat.V_direction)
	{
		if (m_desiredAnimation_direction.V_direction == -m_requestedInputs.direction_hat.V_direction)
		{
			//if the past desired anim is the inverse of the request needs to first go to rest position
			m_desiredAnimation_direction.V_direction = TB_V_REST;
		}
		else
		{
			m_desiredAnimation_direction.V_direction = m_requestedInputs.direction_hat.V_direction;
		}

		//sets start and end frames
		switch (m_desiredAnimation_direction.V_direction)
		{
		case TB_UP:
			startFrame = m_middleFrame;
			endFrame = m_numFrames - 1;
			break;
		case TB_DOWN:
			startFrame = m_middleFrame;
			endFrame = 0;
			break;
		default: // TB_V_REST
			int frameHolder = startFrame;
			startFrame = endFrame;
			endFrame = frameHolder;

		}

		m_desired_move_animation_finished = false;

		resetAnimation();
	}

	//deals with the desired animation direction
	//checks if there is a animation to perform
	if (!m_desired_move_animation_finished)
	{
		m_desired_move_animation_finished = playAnimation(startFrame, endFrame);
	}

	//no attack animation for ship
	if (m_desiredAnimation == ATTACK_ANIM)
	{
		m_desiredAnimation = NO_ANIM;
	}
}

void Player::transformAnim()
{
	switchAnimation(TRANSFORM_ANIM);

	int startFrame = 0, endFrame = 0;
	animations nextAnim;

	switch (m_currentForm)
	{
	case SHIP:
		startFrame = m_numFrames - 1;
		nextAnim = MECHA_IDLE;
		break;
	case MECHA:
		endFrame = m_numFrames - 1;
		nextAnim = SHIP_IDLE;
		break;
	}
	
	if (playAnimation(startFrame, endFrame))
	{
		switchAnimation(nextAnim);

		m_currentFrame = m_middleFrame;
		m_desiredAnimation = NO_ANIM;

		m_desired_move_animation_finished = true;
		m_desiredAnimation_direction.V_direction = TB_V_REST;
		m_desiredAnimation_direction.H_direction = TB_H_REST;
	}
}

void Player::deathAnim()
{
	switchAnimation(DEATH_ANIM);

	if (playAnimation(0, m_numFrames - 1))//play full anim
	{
		m_desiredAnimation = NO_ANIM;
	}	
}