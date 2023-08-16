#include "Walk_backward.h"

#include "Keystate.h"
#include "PlayerStateMachine.h"

Walk_backward::Walk_backward(PlayerStateMachine& state_mech)
	:PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::WALK_BACKWARD;
	SetAnimation("genjuro/walk_bwd2.png", 1, 7, 1,0.05f);
}

Walk_backward::~Walk_backward()
{
}

void Walk_backward::Init()
{
}

void Walk_backward::Exit()
{
}

void Walk_backward::Reset()
{
	m_animation.get()->Reset();
	m_inertia_counter = m_walk_inertia;
}

void Walk_backward::HandleEvents()
{
}

void Walk_backward::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
	if (KeyState::IsKeyPressed(control[3]))
	{
		m_state_machine.ChangeState((int)PlayerState::DEFEND);
	}
	if (!KeyState::IsKeyPressed(m_is_flip ? control[2] : control[0]))
	{
		if (m_inertia_counter > 0)
			m_inertia_counter -= deltaTime;
		else
		{
			m_state_machine.ChangeState((int)PlayerState::IDLE);
			m_inertia_counter = 0;
		}
	}
	if (KeyState::IsKeyPressed(m_is_flip ? control[2] : control[0]) && m_inertia_counter < m_walk_inertia)
	{
		m_state_machine.ChangeState((int)PlayerState::RUN_BACKWRAD);
	}
	if (KeyState::IsKeyPressed(!m_is_flip ? control[2] : control[0]))
	{
		m_state_machine.ChangeState((int)PlayerState::WALK_FORWARD);
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
		/*if (KeyState::IsKeyPressed(m_is_flip ? control[2] : control[0]) && KeyState::IsKeyPressed(control[1]))
		{
			m_state_machine.ChangeState((int)PlayerState::NHAY_CHEM);
		}*/
		if (KeyState::IsKeyPressed(m_is_flip ? control[0] : control[2]) && KeyState::IsKeyPressed(control[3])) {
			m_state_machine.ChangeState((int)PlayerState::CHEM_TU_DUOI);
		}
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

void Walk_backward::Update(float deltaTime, float& x, float& y)
{
	x -= (1 - 2 * m_is_flip) * m_walk_speed * deltaTime;

	m_animation.get()->Update(deltaTime);
}

void Walk_backward::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
