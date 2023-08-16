#pragma once

#include <memory>
#include <string>
#include <SDL.h>

#include "SpriteAnimation.h"

class PlayerStateMachine;

class PlayerStateBase
{
public:
	PlayerStateBase(PlayerStateMachine& state_mech);
	virtual ~PlayerStateBase() {}

	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Reset() = 0;

	virtual void HandleEvents() = 0;
	virtual void HandleKeyEvents(SDL_Scancode control[6], float deltaTime) = 0;
	virtual void Update(float deltaTime, float& x, float& y) = 0;
	virtual void Draw(SDL_Renderer* renderer, float x, float y) = 0;

	static std::shared_ptr<PlayerStateBase> CreateState(int stt, PlayerStateMachine& state_mech);
	int GetPlayerState();
	int GetSpriteWidth();
	int GetSpireHeigth();
	void SetFlip(bool is_flip);
protected:
	void SetAnimation(std::string filepath, int spriteRow, int frameCount, int numAction, float frameTime);
protected:
	int m_player_state;
	std::shared_ptr<SpriteAnimation> m_animation;
	bool m_is_flip;
	PlayerStateMachine& m_state_machine;
};