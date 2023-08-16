#pragma once

#include "PlayerStateBase.h"

class Trung_chieu : public PlayerStateBase
{
public:
	Trung_chieu(PlayerStateMachine& state_mech);
	~Trung_chieu();

	void Init();
	void Exit();

	void Reset();
	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
};