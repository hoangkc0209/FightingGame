#pragma once

#include "PlayerStateBase.h"

class Da_thap : public PlayerStateBase
{
public:
	Da_thap(PlayerStateMachine& state_mech);
	~Da_thap();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
};