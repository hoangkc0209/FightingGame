#pragma once

#include "PlayerStateBase.h"

class Jump : public PlayerStateBase
{
public:
	Jump(PlayerStateMachine& state_mech);
	~Jump();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
private:
	const float giatoc = 10.0f;
	const float giatoc_xuong = 1 /5.0f;
	const float vantoc = -250.0f;
	int vantoc_nhanvat = 0;
};