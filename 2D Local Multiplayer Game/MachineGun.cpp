#include "MachineGun.h"
#include "Bullet.h"
#include "Engine\SceneManager.h"
#include "Engine\Scene.h"
#include "Engine\SoundManager.h"
#include "Player.h"



MachineGun::MachineGun(glm::vec2 Position, Utils::EANCHOR _Anchor)
	: Weapon(Position, _Anchor, MACHINE_GUN)
{
	SoundManager::GetInstance()->AddChannel("CGunfire");
	SoundManager::GetInstance()->AddAudio("Resources/Sounds/BulletWhiz.mp3", false, "Shooting");
}


MachineGun::~MachineGun()
{

}

void MachineGun::Fire()
{
	SoundManager::GetInstance()->PlayAudio("Shooting", "CGunfire");
	std::shared_ptr<Bullet> BulletFromAGun = std::make_shared<Bullet>(Bullet({CurrentPlayer->transform}, Utils::CENTER,CurrentPlayer));
	BulletFromAGun->Init(*body->GetWorld());
	SceneManager::GetInstance()->GetCurrentScene()->AddEntity(BulletFromAGun);
}
