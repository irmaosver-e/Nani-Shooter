#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"
#include "HUD.h"
#include "ObjectLayer.h"

class Player : public SDLGameObject
{
public:
	Player();
	virtual ~Player();

	virtual void load(const LoaderParams& rParams);
	virtual void reset(const LoaderParams& rParams);

	virtual void draw();
	virtual void update();
	
	virtual void collision();
	virtual void collisionWithLayer();

	void flyOffScreen();
	void flyIntoScreen();

	//player does not scroll empty function
	virtual void scroll(float scrollSpeed) {}
	
	int* getLivesPtr() { return &m_lives; }
	int checkLives() const { return m_lives; }
	bool outOfLives() { return (m_lives > 0) ? false : true; }

	void setHUDPtr(HUD* pHUD) { m_playerHUD = pHUD; }

	virtual std::string objType() { return "Player"; }

private:
	enum desires {NONE = -1};
	enum player_form { MECHA, SHIP };
	enum player_stance { IDLE, ATTACK, DEAD, TRANSFORM, SHIP_IDLE, SHIP_MOVE_TRANSITION, MECHA_ATTACK_TRANSITION };

	enum player_x_direction { HORIZ_REST, BACK, FORWARD };
	enum player_y_direction { VERT_REST, UP, DOWN };

	void ressurect();
	void handleInput();
	virtual void handleAnimation();
	void handleMechaAnim();
	void handleShipAnim();

	void handleActions();
	void handleBulletFiring();



	HUD* m_playerHUD;
	//ObjectLayer* m_pPlayFieldObjLayer;
	//ObjectMarker* m_pPlayerMarker;

	bool m_bFiringBullet;

	int m_requestedStance;
	int m_desiredAction;
	int m_currentStance;
	int m_currentForm;

	int m_requested_H_direct;
	int m_requested_V_direct;
	int m_horiz_direct;
	int m_vert_direct;

	int m_lives;

	bool m_invulnerable;
	bool m_bFlyingOffScreen;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

#endif /*defined(__Player__)*/