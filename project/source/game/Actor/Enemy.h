//#pragma once
//
//#include "source\game\Actor\Actor.h"
//#include "source\game\Actor\Player.h"
//#include "source\game\Actor\Bullet.h"
//#include <list>
//#include <vector>
//#include "source\system\UI\Widget.h"
////#include "source\system\sound\sound.h"
//
//class EnemyManager;
//class Enemy_Zako;
//class E2_YuppiY;
//
//class EnemyBase :public Actor
//{
//public:
//	EnemyBase(Player* p_ref, int mesh_id, float HP_MAX);
//	virtual ~EnemyBase() {}
//protected:
//	Player* player_reference;
//	DirectX::XMFLOAT3 move;
//	float HP_MAX;
//
//	int ai_mode{};
//	int ai_timer{};
//	float speed{};
//public:
//	float hp;
//
//	virtual bool Update() = 0;
//	virtual void ChangeAI(int new_mode)
//	{
//		ai_mode = new_mode;
//		ai_timer = 0;
//		speed = .0f;
//	}
//
//};
//
//
//class EnemyManager
//{
//public:
//	EnemyManager()
//	{}
//	~EnemyManager() {}
//private:
//	static bool is_loaded;
//public:
//	static Player* player_reference;
//
//
//
//	static void Initialize(Player* p_ref)
//	{
//		player_reference = p_ref;
//		enemies_list.clear();
//		if (is_loaded)return;
//		AddEnemyModel("DATA\\3D\\aku.fbx");
//		AddEnemyModel("DATA\\3D\\ecc.fbx");
//		AddEnemyModel("DATA\\3D\\oh.fbx");
//		AddEnemyModel("DATA\\3D\\totsu.fbx");
//		
//		is_loaded = true;
//	}
//
//	static void ResetPlayerReference(Player* p_ref)
//	{
//		player_reference = p_ref;
//	}
//
//	static std::list<std::unique_ptr<EnemyBase>> enemies_list;
//
//	static void SpawnEnemy(std::unique_ptr<EnemyBase> enemy);
//
//	static std::vector<std::shared_ptr<StaticMesh>> enemies_model_list;
//
//	static void AddEnemyModel(const char* filename);
//
//	static std::shared_ptr<StaticMesh> GetMesh(int id);
//
//	static void Update();
//
//	static void Render()
//	{
//		for each(auto& enemy in enemies_list)
//		{
//			enemy->Render();
//		}
//	}
//
//	static bool ShotCollision(Bullet* bullet)
//	{
//		for (auto& it = enemies_list.begin(); it != enemies_list.end();/**/)
//		{
//
//			VECTORIII b_pos(bullet->GetActorLocation().x, bullet->GetActorLocation().y, bullet->GetActorLocation().z);
//			//if(bullet->GetActorLocation()- (*it)->GetActorLocation())
//			VECTORIII e_pos((*it)->GetActorLocation().x, (*it)->GetActorLocation().y, (*it)->GetActorLocation().z);
//
//
//			if (HitCheckSphere(b_pos, 1.5f, e_pos, 1.5f))
//			{
//
//				(*it)->hp -= 1.0f;
//				if ((*it)->hp <= 0)
//				{
//					it = enemies_list.erase(it);
//				}
//				/*else
//				{
//					it++;
//					continue;
//				}*/
//					return true;
//
//			}
//			else
//				it++;
//		}
//		return false;
//	}
//
//
//	static void RandomSpawn()
//	{
//		static int count = 0;
//		count++;
//
//		if (count > 10)
//		{
//			count = 0;
//			enemies_list.emplace_back(std::make_unique<E2_YuppiY>(DirectX::XMFLOAT3(0, 0, 0), player_reference));
//		}
//	}
//
//
//	static void SpawnE2(DirectX::XMFLOAT3 pos)
//	{
//		EnemyManager::enemies_list.emplace_back(std::make_unique<E2_YuppiY>(pos,player_reference ));
//
//	}
//
//};
//
//
//
//class Enemy_Zako :public EnemyBase
//{
//public:
//	Enemy_Zako(DirectX::XMFLOAT3 pos, Player* p_ref) :
//		EnemyBase(p_ref, 0,1.0f)
//	{
//		this->position = pos;
//		move = DirectX::XMFLOAT3(0.2f, 0, 0);
//	}
//private:
//
//public:
//
//	bool Update()
//	{
//		position.x += move.x;
//		position.y += move.y;
//		position.z += move.z;
//
//		if (HitCheckSphere(GetActorLocation(), 1.5f, player_reference->GetActorLocation(), 1.2f))
//		{
//
//			player_reference->life--;
//			return true;
//		}
//		return false;
//
//	}
//};
//
//
//class Enemy_Chaser :public EnemyBase
//{
//public:
//	Enemy_Chaser(DirectX::XMFLOAT3 pos, Player* p_ref) :
//		EnemyBase(p_ref, 2,1.0f)
//	{
//		this->position = pos;
//		move = DirectX::XMFLOAT3(0.2f, 0, 0);
//
//		speed = 0.5f;
//
//	}
//private:
//	//float speed{};
//public:
//
//	bool Update()
//	{
//
//
//		VECTORIII player_pos = player_reference->GetActorLocation();
//
//		VECTORIII pos = GetActorLocation();
//
//		pos += (player_pos - pos).GetNormalize()*speed;
//
//
//
//		position = DirectX::XMFLOAT3(pos.x, pos.y, pos.z);
//
//		if (HitCheckSphere(GetActorLocation(), 1.5f, player_reference->GetActorLocation(), 1.2f))
//		{
//
//			player_reference->life--;
//			return true;
//		}
//		return false;
//
//	}
//};
//
//
//class E2_YuppiY final :public EnemyBase
//{
//public:
//	E2_YuppiY(DirectX::XMFLOAT3 pos, Player* p_ref) :
//		EnemyBase(p_ref,3,1.0f)
//	{
//		position = pos;
//	}
//
//private:
//	enum AI_MODE {
//		CHASE, ATTACK, STOP, WALK
//	};
//	enum CAUTION_STATE {
//		NOTHING, QUESTION, CAUTION
//	}caution_state = NOTHING;
//
//	const float E2_MOVE_SPEED= 0.60f;
//	const float sencetivity = 8.5f;
//	float caution_gauge = 0;
//	const float E_GAUGE_CAUTION_MAX = 300.0f;
//	const float E_GAUGE_ANGRY_MAX = 100.0f;
//public:
//	void AI_Walk()
//	{
//		position.x -= 2;
//	
//	}
//	bool AI_Chase(bool is_move)
//	{
//		float ax, ay, bx, by, crossP;
//		float dotP, L1, L2, cosValue, dAngle;
//		ax = sinf(angle);
//		ay = cosf(angle);
//		bx = player_reference->GetActorLocation().x - position.x;
//		by = player_reference->GetActorLocation().y - position.y;
//		crossP = ay*bx - ax*by;
//		dotP = ax*bx + ay*by;
//		L1 = sqrtf(ax*ax + ay*ay);
//		L2 = sqrtf(bx*bx + by*by);
//		cosValue = .0f;
//		if (L2 > .0f)cosValue = dotP / (L1*L2);
//		if (cosValue > -1.0f)
//		{
//			dAngle = 1.0f - cosValue;
//			if (dAngle > 0.04f)dAngle = 0.04f;
//			if (crossP > .0f)	angle += dAngle;
//			else				angle -= dAngle;
//		}
//
//		if (is_move) {
//			float speed = E2_MOVE_SPEED;
//			if (caution_state == NOTHING)
//			{
//				speed = 0.25f*2.0f;
//			}
//			else if (caution_state == CAUTION)
//			{
//				speed = 0.45f*2.0f;
//			}
//			position.x += sinf(angle)*speed ;
//			position.y += cosf(angle)*speed ;
//
//		}
//		else return false;
//		if (L2 < sencetivity*6.0f)
//		{
//			switch (caution_state)
//			{
//			case NOTHING:
//				if (L2 < sencetivity*2.0f ) {
//					caution_state = CAUTION;
//				}
//				break;
//			case QUESTION:
//
//				
//					if (caution_gauge++ > E_GAUGE_CAUTION_MAX)
//					{
//						caution_gauge = 0;
//						caution_state = CAUTION;
//					}
//
//				
//				break;
//			case CAUTION:
//				
//				{
//					if (caution_gauge++ > E_GAUGE_ANGRY_MAX)
//					{
//						caution_gauge = E_GAUGE_ANGRY_MAX;
//						
//						ChangeAI(ATTACK);
//					}
//
//				}
//				break;
//			default:
//				break;
//			}
//		}
//
//
//		return false;
//
//	}
//	bool AI_Attack()
//	{
//		ai_timer++;
//		if (ai_timer <= 60)
//		{
//			AI_Chase(false);
//			
//		}
//		if ((ai_timer > 60) && (ai_timer <= 75)) {
//
//			position.x += sinf(angle)*E2_MOVE_SPEED*speed ;
//			position.y += cosf(angle)*E2_MOVE_SPEED*speed ;
//			if ((speed += 0.40f) > 5.30f)
//				speed = 5.30f;
//		}
//		else if (ai_timer >75)
//		{
//			position.x += sinf(angle)*E2_MOVE_SPEED*speed;
//			position.y += cosf(angle)*E2_MOVE_SPEED*speed;
//			if ((speed -= .020f) <= .0f) {
//				speed = .0f;
//				caution_gauge = .0f;
//
//				return true;
//			}
//		}
//		return false;
//	}
//
//	inline bool AI_Stop()
//	{
//		if (ai_timer++ > 90)return true;
//		return false;
//	}
//	
//	void AI()
//	{
//		if (YMabsolute(position.x - player_reference->GetActorLocation().x) > 1280*1.5f)return;
//		if (YMabsolute(position.y - player_reference->GetActorLocation().y) > 720*1.5f)return;
//
//	
//		switch (ai_mode)
//		{
//		case WALK:
//
//
//			break;
//		case CHASE:
//			if (AI_Chase(true))
//			{
//
//				ChangeAI(ATTACK);
//			}
//			break;
//		case ATTACK:
//			if (AI_Attack())
//			{
//			
//				ChangeAI(STOP);
//			}
//			break;
//
//		case STOP:
//			if (AI_Stop())
//			{
//				ChangeAI(CHASE);
//			}
//			break;
//		default:
//			break;
//		}
//	}
//
//	
//
//	bool Update()
//	{
//		AI();
//
//		if (HitCheckSphere(GetActorLocation(), 1.5f, player_reference->GetActorLocation(), 1.2f))
//		{
//			
//			player_reference->life--;
//			return true;
//		}
//		return false;
//	}
//	
//};
//
//
//class Enemy_ECC final :public EnemyBase
//{
//public:
//	Enemy_ECC(DirectX::XMFLOAT3 pos, Player* p_ref) :
//		EnemyBase(p_ref, 1,50)
//	{
//		this->position = pos;
//		move = DirectX::XMFLOAT3(0.2f, 0, 0);
//		scale = 3.0f;
//		//angle = PI;
//		ai_method = std::make_unique<AI_Walk>(this, 4*60);
//
//		max_dist = 10.0f;
//
//		hp_gauge_widget = std::make_unique<GaugeWidget>(VECTORII(415, 38), VECTORII(1280 - 415, 0), 0.0f, L"DATA\\2D\\towerHP_bar.png", L"DATA\\2D\\towerHP.png");
//	}
//
//	~Enemy_ECC()
//	{
//		GameBrain::GetInstance()->game_state = GameBrain::WIN;
//	}
//private:
//
//	float max_dist{};
//	std::unique_ptr<GaugeWidget> hp_gauge_widget;
//
//public:
//	std::list<std::unique_ptr<Bullet>> ecc_bullet_list;
//
//
//	class AI_Base			 
//	{
//	public:
//		AI_Base(Enemy_ECC* _ecc_ref) :
//			ecc_ref(_ecc_ref)
//		{}
//		virtual ~AI_Base() {}
//	protected:
//		Enemy_ECC* ecc_ref;
//	public:
//
//		virtual bool Method() = 0;
//	};
//
//	class AI_Shot		final :public AI_Base
//	{
//	public:
//		AI_Shot(Enemy_ECC* _ecc_ref, int num_of_shots) :
//			AI_Base(_ecc_ref),
//			shot_speed(1.5f),
//			shot_span(10),
//			shot_num(num_of_shots)
//		{}
//		~AI_Shot() {}
//	private:
//		float shot_speed;
//		const int shot_span;
//		const int shot_num;
//		int span_count{};
//		int shot_count{};
//	public:
//
//		bool Method();
//	};
//
//	class AI_Walk		final :public AI_Base
//	{
//	public:
//		AI_Walk(Enemy_ECC* _ecc_ref, int walk_time_max) :
//			AI_Base(_ecc_ref),
//			TIME_MAX(walk_time_max)
//		{}
//		~AI_Walk() {}
//	private:
//		int time_count{};
//		int TIME_MAX;
//	public:
//
//		bool Method();
//	};
//
//	class AI_Spawner	final :public AI_Base
//	{
//	public:
//		AI_Spawner(Enemy_ECC* _ecc_ref, int num) :
//			AI_Base(_ecc_ref),
//			NUM(num)
//		{}
//		~AI_Spawner() {}
//	private:
//		
//		const int NUM;
//		int n = 0;
//		int timer = 0;
//		int LAG = 25;
//	public:
//
//		bool Method();
//	};
//
//	bool Update()
//	{
//		ai_method->Method();
//
//		for (auto& it = ecc_bullet_list.begin(); it != ecc_bullet_list.end();/**/)
//		{
//			(*it)->Update();
//
//			if (HitCheckSphere((*it)->GetActorLocation(), 1.5f, player_reference->GetActorLocation(), 1.2f))
//			{
//				it = ecc_bullet_list.erase(it);
//				player_reference->life--;
//			
//			}
//			else it++;
//		}
//
//		hp_gauge_widget->gauge = hp / HP_MAX;
//
//
//
//		return false;
//	}
//
//	void Render()
//	{
//		EnemyBase::Render();
//
//		for each(auto& bullet in ecc_bullet_list)
//		{
//			bullet->Render();
//		}
//
//		hp_gauge_widget->Render();
//	}
//
//	std::unique_ptr<AI_Base> ai_method;
//
//};