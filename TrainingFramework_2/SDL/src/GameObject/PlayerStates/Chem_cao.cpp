#include "Chem_cao.h"
#include "Define.h"
#include "Keystate.h"
#include "PlayerStateMachine.h"

Chem_cao::Chem_cao(PlayerStateMachine& state_mech)
	: PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::CHEM_CAO;
	SetAnimation("genjuro/chem cao.png", 1, 13, 1,0.05f);
}

Chem_cao::~Chem_cao()
{
}

void Chem_cao::Init()
{
}

void Chem_cao::Exit()
{
}


void Chem_cao::Reset()
{
	m_animation.get()->Reset();
}

void Chem_cao::HandleEvents()
{
}

void Chem_cao::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{

}

void Chem_cao::Update(float deltaTime, float& x, float& y)
{
	m_animation.get()->Update(deltaTime);
	y = SCREEN_HEIDHT - 150 - 42;
	if (m_animation.get()->GetFinished())
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Chem_cao::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
