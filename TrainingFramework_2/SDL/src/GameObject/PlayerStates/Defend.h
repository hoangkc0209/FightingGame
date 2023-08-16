#pragma once

#include "PlayerStateBase.h"

class Defend : public PlayerStateBase
{
public:
	Defend(PlayerStateMachine& state_mech);
	~Defend();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
};