#include "Shotgun.h"
#include "Bullet.h"
#include "Engine\SceneManager.h"
#include "Engine\Scene.h"
#include "Engine\SoundManager.h"
#include "Player.h"
Shotgun::Shotgun(glm::vec2 Position, Utils::EANCHOR _Anchor)
	: Weapon(Position, _Anchor, SHOTGUN)
{
	SoundManager::GetInstance()->AddAudio("Resources/Sounds/BulletWhiz.mp3", false, "MachineGunFire");
}



Shotgun::~Shotgun()
{
}

void Shotgun::Fire()
{
	SoundManager::GetInstance()->PlayAudio("MachineGunFire");
	std::shared_ptr<Bullet> BulletFromAGun = std::make_shared<Bullet>(Bullet({ CurrentPlayer->transform.Position,glm::vec3{0,0,0},CurrentPlayer->transform.Scale }, Utils::CENTER, CurrentPlayer));
	BulletFromAGun->Init(*body->GetWorld());
	SceneManager::GetInstance()->GetCurrentScene()->AddEntity(BulletFromAGun);

	std::shared_ptr<Bullet> BulletFromAGun1 = std::make_shared<Bullet>(Bullet({CurrentPlayer->transform.Position,glm::vec3(CurrentPlayer->transform.Rotation.x,CurrentPlayer->transform.Rotation.y,CurrentPlayer->transform.Rotation.z + 20),CurrentPlayer->transform.Scale }, Utils::CENTER, CurrentPlayer));
	BulletFromAGun1->Init(*body->GetWorld());
	SceneManager::GetInstance()->GetCurrentScene()->AddEntity(BulletFromAGun1);

	std::shared_ptr<Bullet> BulletFromAGun2 = std::make_shared<Bullet>(Bullet({ CurrentPlayer->transform.Position,glm::vec3(CurrentPlayer->transform.Rotation.x,CurrentPlayer->transform.Rotation.y,CurrentPlayer->transform.Rotation.z - 20),CurrentPlayer->transform.Scale }, Utils::CENTER, CurrentPlayer));
	BulletFromAGun2->Init(*body->GetWorld());
	SceneManager::GetInstance()->GetCurrentScene()->AddEntity(BulletFromAGun2);

	
}
