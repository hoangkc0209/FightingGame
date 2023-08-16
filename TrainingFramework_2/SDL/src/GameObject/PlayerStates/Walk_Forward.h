#pragma once

#include "PlayerStateBase.h"
#include "Define.h"

class WalkForward : public PlayerStateBase
{
public:
	WalkForward(PlayerStateMachine& state_mech);
	~WalkForward();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
private:
	static constexpr int walk_speed = 125;
	static constexpr float m_walk_inertia = 2.0f / ANIMATION_FPS;
	float m_inertia_counter = m_walk_inertia;
};