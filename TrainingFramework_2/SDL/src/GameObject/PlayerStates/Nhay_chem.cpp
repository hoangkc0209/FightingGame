#include "Nhay_chem.h"
#include "Define.h"
#include "Keystate.h"
#include "PlayerStateMachine.h"

Nhay_chem::Nhay_chem(PlayerStateMachine& state_mech)
	: PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::NHAY_CHEM;
	SetAnimation("genjuro/nhay chem 1.png", 1, 10, 1, 0.05f);
}

Nhay_chem::~Nhay_chem()
{
}

void Nhay_chem::Init()
{
}

void Nhay_chem::Exit()
{
}


void Nhay_chem::Reset()
{
	m_animation.get()->Reset();
}

void Nhay_chem::HandleEvents()
{
}

void Nhay_chem::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{

}

void Nhay_chem::Update(float deltaTime, float& x, float& y)
{
	y = SCREEN_HEIDHT - 150 - 52;
	m_animation.get()->Update(deltaTime);
	if (m_animation.get()->GetFinished()) {
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Nhay_chem::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
