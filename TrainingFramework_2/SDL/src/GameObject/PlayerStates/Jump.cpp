#include "Jump.h"
#include "Define.h"
#include "Keystate.h"
#include "PlayerStateMachine.h"

Jump::Jump(PlayerStateMachine& state_mech)
	:PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::JUMP;
	SetAnimation("genjuro/jump.png", 1, 15, 1, 0.05f);
}

Jump::~Jump()
{
}

void Jump::Init()
{
}

void Jump::Exit()
{
}

void Jump::Reset()
{
	m_animation.get()->Reset();
	vantoc_nhanvat = vantoc;
}

void Jump::HandleEvents()
{
}

void Jump::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
}

void Jump::Update(float deltaTime, float& x, float& y)
{
	y = SCREEN_HEIDHT - 150 - 97;
	m_animation.get()->Update(deltaTime);
	if (m_animation.get()->GetFinished()) {
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Jump::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
