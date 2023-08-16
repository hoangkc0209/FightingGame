#include "GSMenu.h"
#include "Sound.h"
#include <SDL_mixer.h>


GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("background/basara.png");
	texture.get()->SetScaleMode(SDL_ScaleModeNearest);
	// background

	m_background = std::make_shared<SpriteAnimation>(texture, 1, 20, 1, 0.2f);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);
	 

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_play.png");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	
	btnPlay->SetSize(180,60);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth())/2+160, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2 -50);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);

	// exit button 
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_exit.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnClose->SetSize(120,45);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//sound on button
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_play_sound.png");
	std::shared_ptr<MouseButton> btn_play_sound = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btn_play_sound->SetSize(40, 40);
	btn_play_sound->Set2DPosition(710,550);
	btn_play_sound->SetOnClick([]() {
		Mix_ResumeMusic();
		});
	m_listButton.push_back(btn_play_sound);

	// sound off button
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_mute.png");
	std::shared_ptr<MouseButton> btn_mute = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btn_mute->SetSize(40, 40);
	btn_mute->Set2DPosition(755,550);
	btn_mute->SetOnClick([]() {
		Mix_PauseMusic();
		});
	m_listButton.push_back(btn_mute);
	//help game
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_help.png");
	std::shared_ptr<MouseButton> btnHelp = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnHelp->SetSize(180,60);
	btnHelp->Set2DPosition((SCREEN_WIDTH - btnHelp->GetWidth())/2+160, (SCREEN_HEIDHT - btnHelp->GetHeight()) / 2 + 50);
	btnHelp->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_HELP);
		});
	m_listButton.push_back(btnHelp);

	// game title
	///Set Font
	m_textColor = { 255, 255, 255 };
	m_textGameName = std::make_shared<Text>("Data/font (2).ttf", m_textColor);
	m_textGameName->SetSize(480, 80);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 2 - 250);
	m_textGameName->LoadFromRenderText("Antagonistic Fight");
	m_Sound = std::make_shared<Sound>("Data/Sounds/musicbackground.mp3");
	m_Sound->PlaySound();
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->StopSound();

}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}
static float time = 0.0f;
void GSMenu::Update(float deltaTime)
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

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
}
