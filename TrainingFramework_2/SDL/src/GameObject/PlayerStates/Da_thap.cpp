#include "Da_thap.h"
#include "Define.h"
#include "Keystate.h"
#include "PlayerStateMachine.h"

Da_thap::Da_thap(PlayerStateMachine& state_mech)
	: PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::DA_THAP;
	SetAnimation("genjuro/da thap.png", 1, 8, 1, 0.05f);
}

Da_thap::~Da_thap()
{
}

void Da_thap::Init()
{
}

void Da_thap::Exit()
{
}


void Da_thap::Reset()
{
	m_animation.get()->Reset();
}

void Da_thap::HandleEvents()
{
}

void Da_thap::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{

}

void Da_thap::Update(float deltaTime, float& x, float& y)
{
	m_animation.get()->Update(deltaTime);
	y = SCREEN_HEIDHT - 150 + 10;
	if (m_animation.get()->GetFinished())
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Da_thap::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
