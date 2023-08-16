#pragma once
#include "BaseObject.h"
#include <SDL_render.h>
class TextureManager;
class SpriteAnimation : public BaseObject {
protected:
	Vector2			m_Vec2DPos;
	int			m_iHeight;
	int			m_iWidth;
	float			m_numFrames;
	int			m_currentFrame;
	float		m_frameTime;
	float		m_currentTime;
	int			m_spriteRow; //start 0,1,2
	int		m_frameCount; // start from 1,2,3...
	float  m_currentTicks;
	Uint32 m_lastUpdate;
	int			m_animSpeed;
	bool		m_is_finished = false;
	int m_numAction; //start from 1,2,3...
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;
public:
	SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;
	void		Reset();

	void		Set2DPosition(float x, float y);
	void		SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);

	Vector2		Get2DPosition();
	void		SetSize(int width, int height);
	void		SetSize(int scale);
	void		SetRow(int row);
	int			GetWidth();
	int			GetHeight();
	void SetFrame(int frame);
	int			GetCurrentFrame();
	int			GetFrameCount();
	bool		GetFinished();
};