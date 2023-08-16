#pragma once

#include "PlayerStateBase.h"

class Dead : public PlayerStateBase
{
public:
	Dead(PlayerStateMachine& state_mech);
	~Dead();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
private:
	static constexpr int speed = 500;
};