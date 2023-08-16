#pragma once

#include "PlayerStateBase.h"

class Run_forward : public PlayerStateBase
{
public:
	Run_forward(PlayerStateMachine& state_mech);
	~Run_forward();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
private:
	static constexpr int m_dashspeed = 1500;
	static constexpr int m_deaccel_rate = 8*m_dashspeed;
	int m_current_speed = m_dashspeed;
};