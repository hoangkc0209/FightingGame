#include "Run_backward.h"
#include "Define.h"
#include "PlayerStateMachine.h"

Run_backward::Run_backward(PlayerStateMachine& state_mech)
	: PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::RUN_BACKWRAD;
	SetAnimation("genjuro/chay sau.png", 1, 10, 1,0.05f);
	bool update = true;
}

Run_backward::~Run_backward()
{
}

void Run_backward::Init()
{
}

void Run_backward::Exit()
{
}

void Run_backward::Reset()
{
	m_animation.get()->Reset();
	m_current_speed = m_dashspeed;
}

void Run_backward::HandleEvents()
{
}

void Run_backward::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
}

void Run_backward::Update(float deltaTime, float& x, float& y)
{
	x -= (1 - 2 * m_is_flip) * m_current_speed * deltaTime;
	if (m_is_flip && update) {
		x -= 99;
		update = false;
	}
	m_current_speed -= m_deaccel_rate * deltaTime;

	if (m_current_speed < 0)
		m_current_speed = 0;

	m_animation.get()->Update(deltaTime);
	y = SCREEN_HEIDHT - 150 - 14;

	if (m_animation.get()->GetFinished())
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
		if (m_is_flip) {
			x += 99;
			update = true;
		}
	}
}

void Run_backward::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}
