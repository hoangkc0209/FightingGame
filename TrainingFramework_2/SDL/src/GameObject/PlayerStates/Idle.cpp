#include "Idle.h"

#include "PlayerStateMachine.h"
#include "ResourceManagers.h"
#include "Keystate.h"
#include "Define.h"

Idle::Idle(PlayerStateMachine& state_mech)
	:PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::IDLE;
	SetAnimation("genjuro/idle.png", 1, 13, 1,0.07f);
}

Idle::~Idle()
{
}

void Idle::Init()
{
}

void Idle::Exit()
{
}

void Idle::Reset()
{
	m_animation.get()->Reset();
}

void Idle::HandleEvents()
{
}

void Idle::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
	if (KeyState::IsKeyPressed(m_is_flip ? control[2] : control[0]))
	{
		m_state_machine.ChangeState((int)PlayerState::WALK_FORWARD);//forward
	}
	if (KeyState::IsKeyPressed(!m_is_flip ? control[2] : control[0]))
	{
		m_state_machine.ChangeState((int)PlayerState::WALK_BACKWARD);//back ward
	}
	/*if (KeyState::IsKeyPressed(control[1])) {
		m_state_machine.ChangeState((int)PlayerState::JUMP);
	}*/
	if (KeyState::IsKeyPressed(control[3])) {
		m_state_machine.ChangeState((int)PlayerState::DEFEND);
	}
	if (KeyState::IsKeyPressed(control[5])) {
		if (KeyState::IsKeyPressed(control[1])) {
			m_state_machine.ChangeState((int)PlayerState::DA_CAO);
		}
		if (KeyState::IsKeyPressed(control[3])) {
			m_state_machine.ChangeState((int)PlayerState::DA_THAP);
		}
	}

	if (KeyState::IsKeyPressed(control[4]))
	{
		m_state_machine.ChangeState((int)PlayerState::CHEM_CO_BAN);
		if (KeyState::IsKeyPressed(control[3]))
		{
			m_state_machine.ChangeState((int)PlayerState::CHEM_THAP);
		}
		if (KeyState::IsKeyPressed(control[1])) {
			m_state_machine.ChangeState((int)PlayerState::CHEM_CAO);
		}
		/*if (KeyState::IsKeyPressed(!m_is_flip ? control[2] : control[0]) && KeyState::IsKeyPressed(control[1]))
		{
			m_state_machine.ChangeState((int)PlayerState::NHAY_CHEM);
		}*/
		if (KeyState::IsKeyPressed(!m_is_flip ? control[2] : control[0]) && KeyState::IsKeyPressed(control[3]) && KeyState::IsKeyPressed(control[5]))
		{
			m_state_machine.ChangeState((int)PlayerState::CHEM_TU_DUOI);
		}
	}
}

void Idle::Update(float deltaTime, float& x, float& y)
{
	m_animation.get()->Update(deltaTime);
}

void Idle::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
