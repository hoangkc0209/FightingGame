#pragma once

#include <string>
#include <array>

#include "CMath.h"
#include "PlayerStates/PlayerStateMachine.h"
#include "SpriteAnimation.h"
#include "SDL_mixer.h"


class Fighter
{
public:
	Fighter(int id, bool flip);
	~Fighter();

	void Init();
	//control [right, up, left, down, attack]
	void SetControl(std::array<SDL_Scancode, 6> control);
	void Draw(SDL_Renderer* renderer);
	void Update(float deltatime,Fighter& p1,Fighter& p2);
	void SetPosition(float x, float y);
	void HandleKeyEvents(float deltaTime);
	void DrawBoundingBox(SDL_Renderer* renderer);
	int CheckCollisionP1HitP2(Fighter p1, Fighter p2);
	int CheckCollisionP2HitP1(Fighter p1, Fighter p2);
	//SDL_Rect GetCollisionRect() const { return m_collisionRect; }
	void PushBackFromCollision(Fighter& other);
	int GetSpriteWidth();
	int GetSpriteHeight();
	int GetCurrentHp();
private:
	bool isPlayer2Dead = false,isPlayer1Dead=false;
	bool isHit1 = false, isHit2 = false;
	//Basic attribute
	int m_id;
	static inline int m_hp_max=100;
	int m_current_hp;
	int m_previos_hp;
	Vector2 m_position;
	//SDL_Rect m_collisionRect;
	//Flip false facing right, true facing left
	bool m_isFlip;
	//Input
	int m_KeyState = 0;
	static constexpr int m_numControl = 6;
	//control [right, up, left, down, attack]
	SDL_Scancode m_control[m_numControl];
	//State machine
	PlayerStateMachine m_state_machine;

	Mix_Chunk* hit = Mix_LoadWAV("Data/Sounds/hit.mp3");
};