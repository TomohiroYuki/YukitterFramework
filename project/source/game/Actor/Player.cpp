//#include "source\game\Actor\Player.h"
//#include "source\game\Actor\Enemy.h"
//#include "source\system\Effect\Effect.h"
//#include "source\game\GameBrain.h"
//#include "source\system\sound\sound.h"
//void Player::Update()
//{
//	MainCharacter::Update();
//	angle +=0.04f;
//	shot_method->Shot();
//
//	for (auto it = bullet_list.begin(); it != bullet_list.end();/**/)
//	{
//		if ((*it)->is_end)
//		{
//			it = bullet_list.erase(it);
//		}
//		else
//		{
//			(*it)->Update();
//
//			if (EnemyManager::ShotCollision((*it).get()))
//			{
//				
//				EffectManager::AddEffect((*it)->GetActorLocation(), 10.0f);
//				it = bullet_list.erase(it);
//				SoundBrain::getInstance()->SE_Play(2);
//			}
//			else it++;
//		}
//	}
//
//	if (life <= 0)
//	{
//		GameBrain::GetInstance()->game_state = GameBrain::LOSE;
//	}
//
//}