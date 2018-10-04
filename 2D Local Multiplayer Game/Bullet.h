#pragma once
#include "Engine\Entity.h"
class Bullet :
	public Entity
{
public:
	Bullet(Utils::Transform _Transform, Utils::EANCHOR _Anchor, std::shared_ptr<class Player> _CurrentPlayer);

	~Bullet();

	void Init(b2World& _world);
	std::shared_ptr<class Player> GetCurrentPlayer() { return CurrentPlayer; };
	virtual void Update() override;

protected:
	bool FiredRight = false;
	bool FiredLeft = false;
	std::shared_ptr<Player> CurrentPlayer;
};

