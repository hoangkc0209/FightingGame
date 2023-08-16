#include "Run_forward.h"
#include "Define.h"
#include "PlayerStateMachine.h"

Run_forward::Run_forward(PlayerStateMachine& state_mech)
	: PlayerStateBase(state_mech)
{
	m_player_state = (int)PlayerState::RUN_FORWARD;
	SetAnimation("genjuro/chay truoc 2.png", 1, 6, 1,0.05f);
}

Run_forward::~Run_forward()
{
}

void Run_forward::Init()
{
}

void Run_forward::Exit()
{
}

void Run_forward::Reset()
{
	m_animation.get()->Reset();
	m_current_speed = m_dashspeed;
}

void Run_forward::HandleEvents()
{
}

void Run_forward::HandleKeyEvents(SDL_Scancode control[6], float deltaTime)
{
}

void Run_forward::Update(float deltaTime, float& x, float& y)
{
	x += (1 - 2 * m_is_flip) * m_current_speed * deltaTime;
	m_current_speed -= m_deaccel_rate*deltaTime;

	if (m_current_speed < 0)
		m_current_speed = 0;

	m_animation.get()->Update(deltaTime);

	y = SCREEN_HEIDHT - 150 - 6;
	if (m_animation.get()->GetFinished())
	{
		m_state_machine.ChangeState((int)PlayerState::IDLE);
		y = SCREEN_HEIDHT - 150;
	}
}

void Run_forward::Draw(SDL_Renderer* renderer, float x, float y)
{
	m_animation.get()->Set2DPosition(x, y);
	m_animation.get()->SetFlip(m_is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	m_animation.get()->Draw(renderer);
}

