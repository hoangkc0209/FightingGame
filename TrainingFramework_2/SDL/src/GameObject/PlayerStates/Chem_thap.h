#pragma once

#include "PlayerStateBase.h"

class Chem_thap : public PlayerStateBase
{
public:
	Chem_thap(PlayerStateMachine& state_mech);
	~Chem_thap();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
};