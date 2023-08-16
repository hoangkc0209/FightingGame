#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include <SDL_image.h>
#include "Define.h"

GSPlay::GSPlay()
	:player1(1, false), player2(2, true)
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	player1.SetPosition((SCREEN_WIDTH / 2) - player1.GetSpriteWidth() - 150, SCREEN_HEIDHT -  150);
	player1.SetControl({ SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_T, SDL_SCANCODE_Y });

	player2.SetPosition((SCREEN_WIDTH / 2) + 150, SCREEN_HEIDHT  - 150);
	player2.SetControl({ SDL_SCANCODE_LEFT, SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN, SDL_SCANCODE_KP_1, SDL_SCANCODE_KP_2 });




	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background/bkthuyen.png");
	texture.get()->SetScaleMode(SDL_ScaleModeNearest);
	// background

	m_background = std::make_shared<SpriteAnimation>(texture, 1, 22, 1, 0.2f);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// hp bar base
	texture = ResourceManagers::GetInstance()->GetTexture("BHP_base.png");
	obj1 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	obj1->SetSize(400, 50);
	obj1->Set2DPosition(0, 30);

	texture = ResourceManagers::GetInstance()->GetTexture("BHP_base_2.png");
	obj2 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	obj2->SetSize(400, 50);
	obj2->Set2DPosition(400, 30);

	// hp bar real
	texture = ResourceManagers::GetInstance()->GetTexture("BHP_red.png");
	hp1= std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	hp1->SetSize(327, 18);
	hp1->Set2DPosition(71, 39);

	texture = ResourceManagers::GetInstance()->GetTexture("BHP_red_2.png");
	hp2 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	hp2->SetSize(327, 18);
	hp2->Set2DPosition(729-327, 39);


	//player1 win
	texture = ResourceManagers::GetInstance()->GetTexture("genjuro/player1win.png");
	win1 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	win1->SetSize(430, 70);
	win1->Set2DPosition(185, 200);
	//do you want to 

	//player2 win
	texture = ResourceManagers::GetInstance()->GetTexture("genjuro/player2win.png");
	win2 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	win2->SetSize(430, 70);
	win2->Set2DPosition(185, 200);


	//tie
	texture = ResourceManagers::GetInstance()->GetTexture("genjuro/tie.png");
	tie = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	tie->SetSize(430, 70);
	tie->Set2DPosition(185, 200);

	//button play again
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_play.png");
	buttonPlayAgain = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	buttonPlayAgain->SetSize(240, 90);//dai rong
	buttonPlayAgain->Set2DPosition(SCREEN_WIDTH/2-120, 400);
	buttonPlayAgain->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});



	//btn resume
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_play.png");
	btn_play = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btn_play->SetSize(240, 90);//dai rong
	btn_play->Set2DPosition(SCREEN_WIDTH / 2 - 120, 200);
	btn_play->SetOnClick([this]() {
		isPause = false;
		});
	m_listButton.push_back(btn_play);

	//btn exit
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_exit.png");
	btn_exit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btn_exit->SetSize(240, 90);//dai rong
	btn_exit->Set2DPosition(SCREEN_WIDTH / 2 - 120, 300);
	btn_exit->SetOnClick([this]() {
		isPause = true;
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(btn_exit);


	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("button/btn_pause.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(80, 30);//dai rong
	button->Set2DPosition(SCREEN_WIDTH - button->GetWidth(), 5);
	//button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		isPause = true;
		});
	//m_listButton.push_back(button);
	m_KeyPress = 0;


	//mTimer = std::make_shared<Timer>();


	m_Sound = std::make_shared<Sound>("Data/Sounds/musicplay.mp3");
	m_Sound->PlaySound();


}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{
	m_Sound->StopSound();
}
void GSPlay::Resume()
{
	m_Sound->PlaySound();
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	if (isPause) {
		for (auto button : m_listButton)
		{
			if (button->HandleTouchEvent(&e))
			{
				break;
			}
		}
	}
	else
	{
		if (button->HandleTouchEvent(&e)) {}
	}
	/*for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}*/

	if (buttonPlayAgain->HandleTouchEvent(&e)){}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	/*m_background->Update(deltaTime);*/
	if (isPause) {
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
	}
	else
	{
		m_background->Update(deltaTime);
		button->Update(deltaTime);
		buttonPlayAgain->Update(deltaTime);
		for (auto it : m_listAnimation)
		{
			//if (m_KeyPress == 1)
			//{
			//	
			//	//it->MoveLeft(deltaTime);
			//}
			it->Update(deltaTime);
		}
		player1.HandleKeyEvents(deltaTime);
		player2.HandleKeyEvents(deltaTime);
		player1.Update(deltaTime, player1, player2);
		player2.Update(deltaTime, player1, player2);

		hp1->SetSize(327 * player1.GetCurrentHp() / 100, 18);
		hp2->SetSize(327 * player2.GetCurrentHp() / 100, 18);
		hp2->Set2DPosition(729 - hp2->GetWidth(), 39);
		if (player2.GetCurrentHp() <= 0) {
			checkWinner1 = true;
		}
		if (player1.GetCurrentHp() <= 0) {
			checkWinner2 = true;
		}
		if (player1.GetCurrentHp()<=0 && player2.GetCurrentHp()<=0) {
			checkTie = true;
		}
	}
	//buttonPlayAgain->Update(deltaTime);
	//for (auto it : m_listAnimation)
	//{
	//	//if (m_KeyPress == 1)
	//	//{
	//	//	
	//	//	//it->MoveLeft(deltaTime);
	//	//}
	//	it->Update(deltaTime);
	//}
	//player1.HandleKeyEvents(deltaTime);
	//player2.HandleKeyEvents(deltaTime);
	//player1.Update(deltaTime,player1,player2);
	//player2.Update(deltaTime,player1,player2);

	//hp1->SetSize(327 * player1.GetCurrentHp() / 100,18);
	//hp2->SetSize(327 * player2.GetCurrentHp() / 100, 18);
	//hp2->Set2DPosition(729 - hp2->GetWidth(), 39);
	/*if ((player2.GetCurrentHp() <= 0 || player1.GetCurrentHp()<=0 ||(player1.GetCurrentHp()<=0 && player2.GetCurrentHp()<=0)) && !mTimer->IsStarted()) {
		mTimer->Start();
	}*/

	/*if (player2.GetCurrentHp() <= 0) {
		checkWinner1 = true;
	}
	if (player1.GetCurrentHp() <= 0) {
		checkWinner2 = true;
	}*/

	//if (mTimer->GetTicks() > 3000) {
	//	/*GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);*/
	//	if (player2.GetCurrentHp() <= 0)
	//		checkWinner1 = true;
	//	if (player1.GetCurrentHp() <= 0)
	//		checkWinner2 = true;
	//}
	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	obj1->Draw(renderer);
	obj2->Draw(renderer);
	hp1->Draw(renderer);
	hp2->Draw(renderer);
	//m_score->Draw();



	//ve pause 
	if (isPause) {
		for (auto it : m_listButton)
		{
			it->Draw(renderer);
		}
	}
	else
	{
		button->Draw(renderer);
	}
	player1.Draw(renderer);
	player2.Draw(renderer);

	/*player1.DrawBoundingBox(renderer);
	player2.DrawBoundingBox(renderer);*/
	//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}

	if (checkWinner1 == true) {
		win1->Draw(renderer);
		buttonPlayAgain->Draw(renderer);
	}
	if (checkWinner2 == true) {
		win2->Draw(renderer);
		buttonPlayAgain->Draw(renderer);
	}
	if (checkTie) {
		tie->Draw(renderer);
		buttonPlayAgain->Draw(renderer);
	}
}


//void GSPlay::DrawBoundingBox(SDL_Renderer* render)
//{
//	player1.DrawBoundingBox(render);
//	player2.DrawBoundingBox(render);
//
//}

