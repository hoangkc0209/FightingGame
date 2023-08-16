#include "Da_cao.h"
#include "Define.h"
#include "Keystate.h"
#include "PlayerStateMachine.h"

Da_cao::Da_cao(PlayerStateMachine& state_mech)
	: PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::DA_CAO;
	SetAnimation("genjuro/da cao.png", 1, 11, 1, 0.07f);
}

Da_cao::~Da_cao()
{
}

void Da_cao::Init()
{
}

void Da_cao::Exit()
{
}


void Da_cao::Reset()
{
	m_animation.get()->Reset();
}

void Da_cao::HandleEvents()
{
}

void Da_cao::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{

}

void Da_cao::Update(float deltaTime, float& x, float& y)
{
	m_animation.get()->Update(deltaTime);
	y = SCREEN_HEIDHT - 150 - 34;
	if (m_animation.get()->GetFinished())
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Da_cao::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
