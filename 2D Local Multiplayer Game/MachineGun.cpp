#include "MachineGun.h"
#include "Bullet.h"
#include "Engine\SceneManager.h"
#include "Engine\Scene.h"
#include "Engine\SoundManager.h"
#include "Player.h"



MachineGun::MachineGun(glm::vec2 Position, Utils::EANCHOR _Anchor)
	: Weapon(Position, _Anchor, MACHINE_GUN)
{
	SoundManager::GetInstance()->AddAudio("Resources/Sounds/BulletWhiz.mp3", false, "MachineGunFire");
}


MachineGun::~MachineGun()
{

}

void MachineGun::Fire()
{
	SoundManager::GetInstance()->PlayAudio("MachineGunFire");
	std::shared_ptr<Bullet> BulletFromAGun = std::make_shared<Bullet>(Bullet({transform}, Utils::CENTER,CurrentPlayer));
	BulletFromAGun->Init(*body->GetWorld());
	SceneManager::GetInstance()->GetCurrentScene()->AddEntity(BulletFromAGun);
}
