#include "Chem_tu_duoi.h"
#include "Define.h"
#include "PlayerStateMachine.h"

Chem_tu_duoi::Chem_tu_duoi(PlayerStateMachine& state_mech)
	:PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::CHEM_TU_DUOI;
	SetAnimation("genjuro/chem tu duoi len.png", 1, 19, 1, 0.05f);
}

Chem_tu_duoi::~Chem_tu_duoi()
{
}

void Chem_tu_duoi::Init()
{
}

void Chem_tu_duoi::Exit()
{
}

void Chem_tu_duoi::Reset()
{
	m_animation.get()->Reset();
}

void Chem_tu_duoi::HandleEvents()
{
}

void Chem_tu_duoi::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
}

void Chem_tu_duoi::Update(float deltaTime, float& x, float& y)
{
	m_animation.get()->Update(deltaTime);
	y = SCREEN_HEIDHT - 150 - 97;
	x += (1 - 2 * m_is_flip) * speed * deltaTime;
	if (m_animation.get()->GetFinished())
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Chem_tu_duoi::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
