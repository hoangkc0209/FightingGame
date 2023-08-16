#pragma once

#include "PlayerStateBase.h"

class Idle : public PlayerStateBase
{
public:
	Idle(PlayerStateMachine& state_mech);
	~Idle();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
private:
};