#include "SpriteAnimation.h"
#include "TextureManager.h"
SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_iWidth = texture.get()->originWidth / frameCount;
	m_iHeight = texture.get()->originHeight / numAction;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	//m_flip = flip;
	m_is_finished = false;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}
SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::Init()
{

}

void SpriteAnimation::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void SpriteAnimation::Update(float deltatime)
{
	m_is_finished = false;
	m_currentTicks += deltatime;
	if (m_currentTicks >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
			m_is_finished = true;
		}
		m_currentTicks -= m_frameTime;
	}
}

void SpriteAnimation::Reset()
{
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
}

void SpriteAnimation::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void SpriteAnimation::SetRotation(double angle)
{
	m_angle = angle;
}

void SpriteAnimation::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 SpriteAnimation::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void SpriteAnimation::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}
void SpriteAnimation::SetFrame(int frame)
{
	m_currentFrame = frame;
}

void SpriteAnimation::SetSize(int scale)
{
	m_iWidth = m_iWidth * scale;
	m_iHeight = m_iHeight * scale;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

void SpriteAnimation::SetRow(int row)
{
	m_spriteRow = row;
}

int SpriteAnimation::GetWidth()
{
	return m_iWidth;
}

int SpriteAnimation::GetHeight()
{
	return m_iHeight;
}

int SpriteAnimation::GetCurrentFrame()
{
	return m_currentFrame;
}

int SpriteAnimation::GetFrameCount()
{
	return m_frameCount;
}

bool SpriteAnimation::GetFinished()
{
	return m_is_finished;
}

