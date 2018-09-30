//#include "source\game\Actor\Enemy.h"
//#include "source\system\sound\sound.h"
//std::list<std::unique_ptr<EnemyBase>>		EnemyManager::enemies_list;
//std::vector<std::shared_ptr<StaticMesh>>	EnemyManager::enemies_model_list;
//Player*  EnemyManager::player_reference;
//bool EnemyManager::is_loaded;
//
//
//void EnemyManager::SpawnEnemy(std::unique_ptr<EnemyBase> enemy)
//{
//	/*Enemy_Zako* a;
//
//	enemies_list.emplace_back(std::make_unique<Enemy_Zako>());*/
//}
//
//void EnemyManager::AddEnemyModel(const char* filename)
//{
//	enemies_model_list.emplace_back(std::make_shared<StaticMesh>(filename));
//}
//
//std::shared_ptr<StaticMesh> EnemyManager::GetMesh(int id)
//{
//	return enemies_model_list[id];
//}
//
//
//
//EnemyBase::EnemyBase(Player* p_ref, int mesh_id,float HP_MAX) :
//	Actor(EnemyManager::GetMesh(mesh_id)),
//	move({ 0,0,0 }),
//	player_reference(p_ref),
//	HP_MAX(HP_MAX),
//	hp(HP_MAX)
//{}
//
//
//bool Enemy_ECC::AI_Shot::Method()
//{
//	span_count++;
//	if (shot_span < span_count)
//	{
//		VECTORIII ecc_pos(ecc_ref->GetActorLocation());
//		VECTORIII player_pos(ecc_ref->player_reference->GetActorLocation());
//
//		VECTORIII v = player_pos - ecc_pos;
//		v.Normalize();
//		DirectX::XMFLOAT3 vec(v.x, v.y, v.z);
//		ecc_ref->ecc_bullet_list.emplace_back(std::make_unique<Bullet>(ecc_ref->position, vec, EnemyManager::GetMesh(2)));
//
//		span_count = 0;
//		shot_count++;
//		if (shot_count > shot_num)
//		{
//			ecc_ref->ai_method.reset(new AI_Walk(ecc_ref,200));
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool Enemy_ECC::AI_Walk::Method()
//{
//	VECTORIII ecc_pos(ecc_ref->GetActorLocation());
//	VECTORIII player_pos(ecc_ref->player_reference->GetActorLocation());
//
//	VECTORIII target_point= (ecc_pos - player_pos).GetNormalize()*ecc_ref->max_dist+ player_pos;
//
//	ecc_pos +=((target_point - ecc_pos)/50.0f);
//	ecc_ref->position.x = ecc_pos.x;
//	ecc_ref->position.y = ecc_pos.y;
//	ecc_ref->position.z = ecc_pos.z;
//
//
//	time_count++;
//	if (time_count > TIME_MAX)
//	{
//		int a = rand() % 2;
//
//		if (a == 1)
//		{
//
//		
//		ecc_ref->ai_method.reset(new AI_Shot(ecc_ref, 24));
//		
//		}
//		else
//		{
//			ecc_ref->ai_method.reset(new AI_Spawner(ecc_ref, 12));
//		}
//		return true;
//	}
//	return false;
//}
//
//bool Enemy_ECC::AI_Spawner::Method()
//{
//	//EnemyManager::enemies_list.emplace_back(std::make_unique<E2_YuppiY>(DirectX::XMFLOAT3(0, 0, 0), ));
//	timer++;
//	if (timer > LAG)
//	{
//		timer = 0;
//		EnemyManager::SpawnE2(ecc_ref->position);
//		n++;
//	}
//
//	
//	if (n > NUM)
//	{
//		ecc_ref->ai_method.reset(new AI_Walk(ecc_ref, 200));
//		return true;
//	}
//
//	return false;
//}
//
//
//
//void EnemyManager::Update()
//{
//	//RandomSpawn();
//	for (auto& it = enemies_list.begin(); it != enemies_list.end();/**/)
//	{
//		if ((*it)->Update())
//		{
//			it = enemies_list.erase(it);
//			SoundBrain::getInstance()->SE_Play(2);
//		}
//		else it++;
//	}
//}