#pragma once

#include "PlayerStateBase.h"

class Chem_cao : public PlayerStateBase
{
public:
	Chem_cao(PlayerStateMachine& state_mech);
	~Chem_cao();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
};