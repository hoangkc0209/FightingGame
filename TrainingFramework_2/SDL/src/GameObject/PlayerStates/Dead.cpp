#include "Dead.h"
#include "Define.h"
#include "Keystate.h"
#include "PlayerStateMachine.h"

Dead::Dead(PlayerStateMachine& state_mech)
	: PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::DEAD;
	SetAnimation("genjuro/bi hat.png", 1, 6, 1, 0.1f);
}

Dead::~Dead()
{
}

void Dead::Init()
{
}

void Dead::Exit()
{
}


void Dead::Reset()
{
	m_animation.get()->Reset();
}

void Dead::HandleEvents()
{
}

void Dead::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{

}

void Dead::Update(float deltaTime, float& x, float& y)
{
	y = SCREEN_HEIDHT - 150 + 5;
	if (!m_animation->GetFinished()) {
		m_animation->Update(deltaTime);
	}
		
	if (m_animation->GetFinished())
		m_animation->SetFrame(5);
	else if (m_animation.get()->GetCurrentFrame() < 3)
	{
		x -= (1 - 2 * m_is_flip) * speed * deltaTime;
	}
}

void Dead::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation->Set2DPosition(x, y);
	m_animation->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation->Draw(renderer);
}
