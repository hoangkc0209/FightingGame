#include "Chem_thap.h"
#include "Define.h"
#include "PlayerStateMachine.h"

Chem_thap::Chem_thap(PlayerStateMachine& state_mech)
	:PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::CHEM_THAP;
	SetAnimation("genjuro/chem thap.png", 1, 17, 1,0.05f);
}

Chem_thap::~Chem_thap()
{
}

void Chem_thap::Init()
{
}

void Chem_thap::Exit()
{
}

void Chem_thap::Reset()
{
	m_animation.get()->Reset();
}

void Chem_thap::HandleEvents()
{
}

void Chem_thap::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
}

void Chem_thap::Update(float deltaTime, float& x, float& y)
{
	m_animation.get()->Update(deltaTime);
	y = SCREEN_HEIDHT - 150 - 67;
	if (m_animation.get()->GetFinished())
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Chem_thap::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
