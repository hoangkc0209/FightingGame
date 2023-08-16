#pragma once

#include "PlayerStateBase.h"

class Nhay_chem : public PlayerStateBase
{
public:
	Nhay_chem(PlayerStateMachine& state_mech);
	~Nhay_chem();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
};