#include "GSRestart.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include <SDL_image.h>
#include <SDL_rect.h>

GSRestart::GSRestart()
{
}

GSRestart::~GSRestart()
{
}



void GSRestart::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("bk_help.jpg");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);
	//control player
	texture = ResourceManagers::GetInstance()->GetTexture("control (2).png");
	control1_object = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	control1_object->SetSize(600, 500);
	control1_object->Set2DPosition(50, 100);


	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_exit.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnClose->SetSize(80, 30);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);


	// game title


	///Set Font
	m_textColor = { 255, 255, 255 };
	m_textGameName = std::make_shared<Text>("Data/font (2).ttf", m_textColor);
	m_textGameName->SetSize(480, 80);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 300);
	m_textGameName->LoadFromRenderText("HOW TO PLAY ?");
	m_Sound = std::make_shared<Sound>("Data/Sounds/background.mp3");
	m_Sound->PlaySound();
}

void GSRestart::Exit()
{
	ResourceManagers::FreeInstance();
}

void GSRestart::Pause()
{
	m_Sound->StopSound();

}

void GSRestart::Resume()
{
	m_Sound->PlaySound();
}


void GSRestart::HandleEvents()
{
}

void GSRestart::HandleKeyEvents(SDL_Event& e)
{
}

void GSRestart::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSRestart::HandleMouseMoveEvents(int x, int y)
{
}
//float time = 0.0f;
void GSRestart::Update(float deltaTime)
{
	time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSRestart::Draw(SDL_Renderer* renderer)
{

	m_background->Draw(renderer);
	control1_object->Draw(renderer);

	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
}
