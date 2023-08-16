#include "Walk_Forward.h"

#include "Keystate.h"
#include "PlayerStateMachine.h"

WalkForward::WalkForward(PlayerStateMachine& state_mech)
	:PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::WALK_FORWARD;
	SetAnimation("genjuro/walk_fwd2.png", 1, 8, 1,0.05f);
}

WalkForward::~WalkForward()
{
}

void WalkForward::Init()
{
}

void WalkForward::Exit()
{
}

void WalkForward::Reset()
{
	m_animation.get()->Reset();
	m_inertia_counter = m_walk_inertia;
}

void WalkForward::HandleEvents()
{
}

void WalkForward::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
	if (!KeyState::IsKeyPressed(m_is_flip ? control[0] : control[2]))
	{
		if (m_inertia_counter > 0)
			m_inertia_counter -= deltaTime;
		else
		{
			m_state_machine.ChangeState((int)PlayerState::IDLE);
			m_inertia_counter = 0;
		}
	}
	if (KeyState::IsKeyPressed(m_is_flip ? control[0] : control[2]) && m_inertia_counter < m_walk_inertia)
	{
		m_state_machine.ChangeState((int)PlayerState::RUN_FORWARD);
	}
	if (KeyState::IsKeyPressed(!m_is_flip ? control[0] : control[2]))
	{
		m_state_machine.ChangeState((int)PlayerState::WALK_BACKWARD);
	}
	if (KeyState::IsKeyPressed(control[3])) {
		m_state_machine.ChangeState((int)PlayerState::DEFEND);
	}
	/*if (KeyState::IsKeyPressed(control[1])) {
		m_state_machine.ChangeState((int)PlayerState::JUMP);
	}*/
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
		if (KeyState::IsKeyPressed(control[1])) {
			m_state_machine.ChangeState((int)PlayerState::CHEM_CAO);
		}
		if (KeyState::IsKeyPressed(control[3]))
			m_state_machine.ChangeState((int)PlayerState::CHEM_THAP);
	}
	/*if (KeyState::IsKeyPressed(control[5])) {
		if (KeyState::IsKeyPressed(control[1])) {
			m_state_machine.ChangeState((int)PlayerState::DA_CAO);
		}
		if (KeyState::IsKeyPressed(control[3])) {
			m_state_machine.ChangeState((int)PlayerState::DA_THAP);
		}
	}*/

}

void WalkForward::Update(float deltaTime, float& x, float& y)
{
	x += (1 - 2 * m_is_flip) * walk_speed * deltaTime;

	m_animation.get()->Update(deltaTime);
}

void WalkForward::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
