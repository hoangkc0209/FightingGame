#include "Defend.h"

#include "Keystate.h"
#include "PlayerStateMachine.h"

Defend::Defend(PlayerStateMachine& state_mech)
	:PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::DEFEND;
	SetAnimation("genjuro/defend.png", 1, 6, 1, 0.05f);
}

Defend::~Defend()
{
}

void Defend::Init()
{
}

void Defend::Exit()
{
}

void Defend::Reset()
{
	m_animation.get()->Reset();
}

void Defend::HandleEvents()
{
}

void Defend::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
	if (!(KeyState::IsKeyPressed(control[3])))
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
	}
}

void Defend::Update(float deltaTime, float& x, float& y)
{
	if (!m_animation.get()->GetFinished())
		m_animation.get()->Update(deltaTime);
	if (m_animation.get()->GetFinished())
		m_animation.get()->SetFrame(5);
}

void Defend::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
