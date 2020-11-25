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
	enum player_form { MECHA, MORPHING, SHIP };
	enum player_move { BACK, IDLE, FORWARD };
	enum player_stance { STAND, ATTACK, DAMAGE };

	void ressurect();
	void handleInput();
	virtual void handleAnimation();



	HUD* m_playerHUD;
	//ObjectLayer* m_pPlayFieldObjLayer;
	//ObjectMarker* m_pPlayerMarker;

	bool m_bIsShip;
	bool m_bMorphing;

	int m_currentForm;
	int m_previousForm;
	int m_lives;

	bool m_invulnerable;
	bool m_bFlyingOffScreen;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

#endif /*defined(__Player__)*/