#include "pch.h"
#include "Worldmap_Player.h"

#include "CKeyMgr.h"

Worldmap_Player::Worldmap_Player()
{
	m_Rigidbody = AddComponent(new CRigidbody);
	m_Rigidbody->UseGravity(false);

	m_Animator = AddComponent(new CAnimator);

	m_Woldmap_Player_Collider = AddComponent(new CCollider);
	m_Woldmap_Player_Collider->SetScale(Vec2(100, 100));

	CCamera::GetInstance().SetWorldmapPlayerToCamera(this);
}

Worldmap_Player::~Worldmap_Player()
{
}


void Worldmap_Player::begin()
{
	LoadAnimation();
}

void Worldmap_Player::tick()
{
	UpdateState();
	UpdateAnimation();
	MoveAndAction();
}

void Worldmap_Player::UpdateState()
{
	bool up = KEY_PRESSED(KEY::UP);
	bool down = KEY_PRESSED(KEY::DOWN);
	bool right = KEY_PRESSED(KEY::RIGHT);
	bool left = KEY_PRESSED(KEY::LEFT);


	if (!up && !down && !right && !left)
		m_State = STATE::IDLE;

	else if (up && !down && !right && !left)
	{
		m_Dir = DIR::UP;
		m_State = STATE::WALK;
	}
	else if (down && !up && !right && !left)
	{
		m_Dir = DIR::DOWN;
		m_State = STATE::WALK;
	}
	else if (right && !left && !up && !down)
	{
		m_Dir = DIR::RIGHT;
		m_State = STATE::WALK;
	}
	else if (left && !right && !up && !down)
	{
		m_Dir = DIR::LEFT;
		m_State = STATE::WALK;
	}

	else if (up && right && !down && !left)
	{
		m_Dir = DIR::UP_RIGHT;
		m_State = STATE::WALK;
	}
	else if (up && left && !right && !down)
	{
		m_Dir = DIR::UP_LEFT;
		m_State = STATE::WALK;
	}
	else if (down && right && !up && !left)
	{
		m_Dir = DIR::DOWN_RIGHT;
		m_State = STATE::WALK;
	}
	else if (down && left && !up && !right)
	{
		m_Dir = DIR::DOWN_LEFT;
		m_State = STATE::WALK;
	}

}

void Worldmap_Player::UpdateAnimation()
{
	if (m_State == STATE::IDLE)
	{
		switch (m_Dir)
		{
			case Worldmap_Player::DIR::RIGHT:
				m_Animator->Play(L"cuphead_world_map_side_idle", true);
				break;
			case Worldmap_Player::DIR::LEFT:
				m_Animator->Play(L"cuphead_world_map_side_idle_L", true);
				break;
			case Worldmap_Player::DIR::UP:
				m_Animator->Play(L"cuphead_world_map_up_idle", true);
				break;
			case Worldmap_Player::DIR::DOWN:
				m_Animator->Play(L"cuphead_world_map_down_idle", true);
				break;
			case Worldmap_Player::DIR::UP_RIGHT:
				m_Animator->Play(L"cuphead_world_map_diag_up_idle", true);
				break;
			case Worldmap_Player::DIR::UP_LEFT:
				m_Animator->Play(L"cuphead_world_map_diag_up_idle_L", true);
				break;
			case Worldmap_Player::DIR::DOWN_RIGHT:
				m_Animator->Play(L"cuphead_world_map_diag_down_idle", true);
				break;
			case Worldmap_Player::DIR::DOWN_LEFT:
				m_Animator->Play(L"cuphead_world_map_diag_down_idle_L", true);
				break;
		}
	}

	else if (m_State == STATE::WALK)
	{
		switch (m_Dir)
		{
			case Worldmap_Player::DIR::RIGHT:
				m_Animator->Play(L"cuphead_world_map_side_walk", true);
				break;
			case Worldmap_Player::DIR::LEFT:
				m_Animator->Play(L"cuphead_world_map_side_walk_L", true);
				break;
			case Worldmap_Player::DIR::UP:
				m_Animator->Play(L"cuphead_world_map_up_walk", true);
				break;
			case Worldmap_Player::DIR::DOWN:
				m_Animator->Play(L"cuphead_world_map_down_walk", true);
				break;
			case Worldmap_Player::DIR::UP_RIGHT:
				m_Animator->Play(L"cuphead_world_map_diag_up_walk", true);
				break;
			case Worldmap_Player::DIR::UP_LEFT:
				m_Animator->Play(L"cuphead_world_map_diag_up_walk_L", true);
				break;
			case Worldmap_Player::DIR::DOWN_RIGHT:
				m_Animator->Play(L"cuphead_world_map_diag_down_walk", true);
				break;
			case Worldmap_Player::DIR::DOWN_LEFT:
				m_Animator->Play(L"cuphead_world_map_diag_down_walk_L", true);
				break;
		}
	}

	else if (m_State == STATE::WIN)
	{
		m_Animator->Play(L"cuphead_world_map_win", true);
	}
}

void Worldmap_Player::MoveAndAction()
{
	if (m_State != STATE::WALK)
	{
		m_Rigidbody->SetVelocity(Vec2(0, 0));
		return;
	}

	switch (m_Dir)
	{
		case Worldmap_Player::DIR::RIGHT:
			m_Rigidbody->SetVelocity(Vec2(m_WalkSpeed, 0));
			break;
		case Worldmap_Player::DIR::LEFT:
			m_Rigidbody->SetVelocity(Vec2(-m_WalkSpeed, 0));
			break;
		case Worldmap_Player::DIR::UP:
			m_Rigidbody->SetVelocity(Vec2(0, -m_WalkSpeed));
			break;
		case Worldmap_Player::DIR::DOWN:
			m_Rigidbody->SetVelocity(Vec2(0, m_WalkSpeed));
			break;
		case Worldmap_Player::DIR::UP_RIGHT:
			m_Rigidbody->SetVelocity(Vec2(1, -1).Normalize() * m_WalkSpeed);
			break;
		case Worldmap_Player::DIR::UP_LEFT:
			m_Rigidbody->SetVelocity(Vec2(-1, -1).Normalize() * m_WalkSpeed);
			break;
		case Worldmap_Player::DIR::DOWN_RIGHT:
			m_Rigidbody->SetVelocity(Vec2(1, 1).Normalize() * m_WalkSpeed);
			break;
		case Worldmap_Player::DIR::DOWN_LEFT:
			m_Rigidbody->SetVelocity(Vec2(-1, 1).Normalize() * m_WalkSpeed);
			break;
		default:
			break;
	}
}

void Worldmap_Player::LoadAnimation()
{
	//// Idle
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\down_idle\\cuphead_world_map_down_idle.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\Left\\diag_down_idle_L\\cuphead_world_map_diag_down_idle_L.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\Left\\diag_up_idle_L\\cuphead_world_map_diag_up_idle_L.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\Left\\side_idle_L\\cuphead_world_map_side_idle_L.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\Right\\diag_down_idle_R\\cuphead_world_map_diag_down_idle.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\Right\\diag_up_idle_R\\cuphead_world_map_diag_up_idle.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\Right\\side_idle_R\\cuphead_world_map_side_idle.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Idle\\up_idle\\cuphead_world_map_up_idle.json", 12);

	//// Walk
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\down_walk\\cuphead_world_map_down_walk.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\Left\\diag_down_walk_L\\cuphead_world_map_diag_down_walk_L.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\Left\\diag_up_walk_L\\cuphead_world_map_diag_up_walk_L.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\Left\\side_walk_L\\cuphead_world_map_side_walk_L.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\Right\\diag_down_walk_R\\cuphead_world_map_diag_down_walk.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\Right\\diag_up_walk_R\\cuphead_world_map_diag_up_walk.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\Right\\side_walk_R\\cuphead_world_map_side_walk.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Walk\\up_walk\\cuphead_world_map_up_walk.json", 12);

	//// Win
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead_World_Map\\Win\\cuphead_world_map_win.json", 12);






	// Idle
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\down_idle\\cuphead_world_map_down_idle.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\Left\\diag_down_idle_L\\cuphead_world_map_diag_down_idle_L.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\Left\\diag_up_idle_L\\cuphead_world_map_diag_up_idle_L.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\Left\\side_idle_L\\cuphead_world_map_side_idle_L.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\Right\\diag_down_idle_R\\cuphead_world_map_diag_down_idle.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\Right\\diag_up_idle_R\\cuphead_world_map_diag_up_idle.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\Right\\side_idle_R\\cuphead_world_map_side_idle.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Idle\\up_idle\\cuphead_world_map_up_idle.anim");

	// Walk
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\down_walk\\cuphead_world_map_down_walk.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\Left\\diag_down_walk_L\\cuphead_world_map_diag_down_walk_L.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\Left\\diag_up_walk_L\\cuphead_world_map_diag_up_walk_L.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\Left\\side_walk_L\\cuphead_world_map_side_walk_L.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\Right\\diag_down_walk_R\\cuphead_world_map_diag_down_walk.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\Right\\diag_up_walk_R\\cuphead_world_map_diag_up_walk.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\Right\\side_walk_R\\cuphead_world_map_side_walk.anim");
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Walk\\up_walk\\cuphead_world_map_up_walk.anim");

	// Win
	m_Animator->LoadAnimation(L"animation\\Cuphead_World_Map\\Win\\cuphead_world_map_win.anim");
}

void Worldmap_Player::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}

void Worldmap_Player::OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}

void Worldmap_Player::OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}


