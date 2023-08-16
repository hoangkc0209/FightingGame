#pragma once

#include "PlayerStateBase.h"

class Chem_tu_duoi : public PlayerStateBase
{
public:
	Chem_tu_duoi(PlayerStateMachine& state_mech);
	~Chem_tu_duoi();

	void Init();
	void Exit();

	void Reset();

	void HandleEvents();
	void HandleKeyEvents(SDL_Scancode control[6], float deltaTime);
	void Update(float deltaTime, float& x, float& y);
	void Draw(SDL_Renderer* renderer, float x, float y);
private:
	static constexpr int speed = 250;
};
