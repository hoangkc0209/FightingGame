#include "Fighter.h"

#include "GameManager/ResourceManagers.h"
#include "Define.h"
#include <assert.h>

Fighter::Fighter(int id, bool flip)
	:
	m_id(id)
{
	m_current_hp=100;
	m_isFlip = flip;
	m_state_machine.SetFlip(flip);
	//m_previos_hp1 = m_current_hp;
	m_previos_hp = m_current_hp;
}

Fighter::~Fighter()
{
}

void Fighter::Init()
{
} 

void Fighter::SetControl(std::array<SDL_Scancode, 6> control)
{
	for (int i = 0; i < m_numControl; ++i)
		m_control[i] = control[i];
}

void Fighter::Draw(SDL_Renderer* renderer)
{
	m_state_machine.CurrentState().get()->Draw(renderer, m_position.x, m_position.y);
}

void Fighter::DrawBoundingBox(SDL_Renderer* renderer)
{
	// Xác định kích thước hộp xung quanh nhân vật
	int boxWidth = GetSpriteWidth();
	int boxHeight = GetSpriteHeight();

	// Vị trí góc trái trên của hộp xung quanh nhân vật
	int boxLeft = static_cast<int>(m_position.x);
	int boxTop = static_cast<int>(m_position.y);

	// Tạo một hình chữ nhật để vẽ hộp xung quanh nhân vật
	SDL_Rect boundingBox = { boxLeft, boxTop, boxWidth, boxHeight };

	// Đặt màu vẽ cho hộp xung quanh (màu đỏ)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Vẽ hộp xung quanh nhân vật lên màn hình
	SDL_RenderDrawRect(renderer, &boundingBox);
}
void Fighter::PushBackFromCollision(Fighter& other)
{
	// Xác định hướng đẩy lùi dựa trên hướng di chuyển của nhân vật hiện tại và nhân vật khác
	float pushBackDirection = (m_position.x < other.m_position.x) ? -1.0f : 1.0f;
	float pushBackDistance = 10.0f;
	// Tính toán kích thước hộp va chạm cho cả hai nhân vật
	//SDL_Rect currentCollisionRect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), GetSpriteWidth() , GetSpriteHeight() };
	//SDL_Rect otherCollisionRect = { static_cast<int>(other.m_position.x), static_cast<int>(other.m_position.y), other.GetSpriteWidth(), other.GetSpriteHeight() };
	int smallCollisionWidth = static_cast<int>(GetSpriteWidth() * 0.5f);
	int smallCollisionHeight = static_cast<int>(GetSpriteHeight() * 0.5f);

	SDL_Rect currentCollisionRect = {
		static_cast<int>(m_position.x + (GetSpriteWidth() - smallCollisionWidth) * 0.5f),
		static_cast<int>(m_position.y + (GetSpriteHeight() - smallCollisionHeight) * 0.5f),
		smallCollisionWidth,
		smallCollisionHeight
	};

	SDL_Rect otherCollisionRect = {
		static_cast<int>(other.m_position.x + (other.GetSpriteWidth() - smallCollisionWidth) * 0.5f),
		static_cast<int>(other.m_position.y + (other.GetSpriteHeight() - smallCollisionHeight) * 0.5f),
		smallCollisionWidth,
		smallCollisionHeight
	};
	// Kiểm tra va chạm giữa hai nhân vật
	if (SDL_HasIntersection(&currentCollisionRect, &otherCollisionRect))
	{
		// Nếu có va chạm, thực hiện đẩy lùi cho cả hai nhân vật

		// Đẩy lùi nhân vật hiện tại
		m_position.x += pushBackDirection * pushBackDistance;

		// Đẩy lùi nhân vật khác
		other.m_position.x -= pushBackDirection * pushBackDistance;
	}
}

void Fighter::Update(float deltatime,Fighter& p1, Fighter& p2)
{
	m_state_machine.CurrentState().get()->Update(deltatime, m_position.x, m_position.y);
	
	/*p1.SetPosition(p1.m_position.x, p1.m_position.y);
	p2.SetPosition(p2.m_position.x, p2.m_position.y);*/

	// Ve Bound cho nhan vat
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIDHT;

	int spriteWidth = GetSpriteWidth();
	int spriteHeight = GetSpriteHeight();

	int leftBoundary = 0;
	int rightBoundary = screenWidth - spriteWidth;

	int m_topBoundary = 0;
	int m_bottomBoundary = screenHeight - spriteHeight;


	// Kiểm tra và giới hạn vị trí của nhân vật theo trục X
	if (m_position.x < leftBoundary)
	{
		m_position.x = leftBoundary;
	}
	else if (m_position.x > rightBoundary)
	{
		m_position.x = rightBoundary;
	}
	/*if (p1.m_position.x + p1.m_state_machine.CurrentState()->GetSpriteWidth() / 1.5 > p2.m_position.x) {
		p1.m_position.x = p2.m_position.x - p1.m_state_machine.CurrentState()->GetSpriteWidth() / 1.5;
		p2.m_position.x =p2.m_position.x-5;
	}*/

	// Kiểm tra và giới hạn vị trí của nhân vật theo trục Y 
	/*if (m_position.y < m_topBoundary)
	{
		m_position.y = m_topBoundary;
	}
	else if (m_position.y > m_bottomBoundary)
	{
		m_position.y = m_bottomBoundary;
	}*/
	// Tính toán hình chữ nhật va chạm cho nhân vật hiện tại và nhân vật khác (p2)
	SDL_Rect currentCollisionRect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), GetSpriteWidth(), GetSpriteHeight() };
	SDL_Rect p2CollisionRect = { static_cast<int>(p2.m_position.x), static_cast<int>(p2.m_position.y), p2.GetSpriteWidth(), p2.GetSpriteHeight() };

	// Kiểm tra va chạm giữa nhân vật hiện tại và nhân vật khác (p2)
	if (SDL_HasIntersection(&currentCollisionRect, &p2CollisionRect))
	{
		// Nếu có va chạm, thực hiện đẩy lùi cho cả hai nhân vật
		PushBackFromCollision(p2);
		p2.PushBackFromCollision(*this);
	}
	

	if (p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::IDLE) {
		p2.m_previos_hp = p2.m_current_hp;
	}
	if (p2.m_previos_hp > p2.m_current_hp ) {
		return;
	}

	//check collision o day
	//play1 hit play2
	switch (CheckCollisionP1HitP2(p1,p2))
	{
	case 1:printf("p1 danh thuong p2\n");
		p2.m_current_hp -= 10;
		p2.isHit2 = true;
		if (p2.isHit2)
		{
			p2.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
			
		printf("%d,%d\n", p2.m_current_hp, p1.m_current_hp);
		break;
	case 2: printf("p1 chem cao p2\n");
		p2.m_current_hp -= 15;
		p2.isHit2 = true;
		if (p2.isHit2) {
			p2.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		printf("%d,%d\n", p2.m_current_hp, p1.m_current_hp);
		break;
	case 3: printf("p1 chem thap p2\n");
		p2.m_current_hp -= 12;
		p2.isHit2 = true;
		if (p2.isHit2) {
			p2.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	case 4: printf("p1 da cao p2\n");
		p2.m_current_hp -= 12;
		p2.isHit2 = true;
		if (p2.isHit2) {
			p2.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	case 5: printf("p1 da thap p2\n");
		p2.m_current_hp -= 10;
		p2.isHit2 = true;
		if (p2.isHit2) {
			p2.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	case 6: printf("p1 da thap p2\n");
		p2.m_current_hp -= 25;
		p2.isHit2 = true;
		if (p2.isHit2) {
			p2.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	default:
		break;
	}

	//mat mau cua p1
	if (p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::IDLE) {
		p1.m_previos_hp = p1.m_current_hp;
	}
	if (p1.m_previos_hp > p1.m_current_hp) {
		return;
	}
	switch (CheckCollisionP2HitP1(p1, p2))
	{
	case 1:printf("p2 danh thuong p1\n");
		p1.m_current_hp -= 10;
		p1.isHit1 = true;
		if (p1.isHit1) {
			p1.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		printf("%d,%d\n",p1.m_current_hp,p2.m_current_hp);
		/*if () {
			m_score1 += 1;
		}*/
		break;
	case 2: printf("p2 chem cao p1\n");
		p1.m_current_hp -= 15;
		p1.isHit1 = true;
		if (p1.isHit1) {
			p1.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	case 3: printf("p2 chem thap p1\n");
		p1.m_current_hp -= 12;
		p1.isHit1 = true;
		if (p1.isHit1) {
			p1.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	case 4: printf("p2 da cao p1\n");
		p1.m_current_hp -= 12;
		p1.isHit1 = true;
		if (p1.isHit1) {
			p1.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	case 5: printf("p2 da thap p1\n");
		p1.m_current_hp -= 10;
		p1.isHit1 = true;
		if (p1.isHit1) {
			p1.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	case 6: printf("p2 da thap p1\n");
		p1.m_current_hp -= 25;
		p1.isHit1 = true;
		if (p1.isHit1) {
			p1.m_state_machine.ChangeState((int)PlayerState::TRUNG_CHIEU);
			Mix_PlayChannel(-1, hit, 0);
		}
		break;
	default:
		break;
	}
	//neu p2 het mau
	if (p2.m_current_hp <= 0 && !p2.isPlayer2Dead) {
		p2.m_state_machine.ChangeState((int)PlayerState::DEAD);
		p2.isPlayer2Dead = true;
		p2.isHit2 = false;
	}

	//neu p1 het mau
	if (p1.m_current_hp <= 0 && !p1.isPlayer1Dead) {
		p1.m_state_machine.ChangeState((int)PlayerState::DEAD);
		p1.isPlayer1Dead = true;
		p1.isHit1 = false;
	}
	/*if (m_score1 >= 40.0f) {
		p2.m_state_machine.ChangeState((int)PlayerState::DEAD);
	}
	if (m_score2 >= 15.0f) {
		p1.m_state_machine.ChangeState((int)PlayerState::DEAD);
	}*/
} 

void Fighter::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}


//function check tai day, check dc 2 doi tuong p1 p2
int Fighter::CheckCollisionP1HitP2(Fighter p1, Fighter p2) {
	float x1 = p1.m_position.x;
	float y1 = p1.m_position.y;
	float x2 = p2.m_position.x;
	float y2 = p2.m_position.y;
	int w1 = p1.GetSpriteWidth();
	int h1 = p1.GetSpriteHeight();
	int w2 = p2.GetSpriteWidth();
	int h2 = p2.GetSpriteHeight();
	bool check_defend_or_dead = false;
	if (p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DEFEND || p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DEAD) {
		check_defend_or_dead = true;
	}
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_CO_BAN && check_defend_or_dead==false)
		return 1;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_CAO && check_defend_or_dead==false)
		return 2;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_THAP && check_defend_or_dead==false)
		return 3;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DA_CAO && check_defend_or_dead==false)
		return 4;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DA_THAP && check_defend_or_dead==false)
		return 5;
	if (x1<x2 + w2 / 1.25 && x1 + w1 / 1.25>x2 && p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_TU_DUOI && check_defend_or_dead == false) {
		return 6;
	}
}

int Fighter::CheckCollisionP2HitP1(Fighter p1, Fighter p2) {
	float x1 = p1.m_position.x;
	float y1 = p1.m_position.y;
	float x2 = p2.m_position.x;
	float y2 = p2.m_position.y;
	int w1 = p1.GetSpriteWidth();
	int h1 = p1.GetSpriteHeight();
	int w2 = p2.GetSpriteWidth();
	int h2 = p2.GetSpriteHeight();
	bool check_defend_or_dead = false;
	if (p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DEFEND || p1.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DEAD) {
		check_defend_or_dead = true;
	}
	if (x1<x2 + w2/0.75 && x1 + w1/0.75>x2 && p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_CO_BAN && check_defend_or_dead == false)
		return 1;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_CAO && check_defend_or_dead == false)
		return 2;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_THAP && check_defend_or_dead == false)
		return 3;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DA_CAO && check_defend_or_dead == false)
		return 4;
	if (x1<x2 + w2/1.5 && x1 + w1/1.5>x2 && p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::DA_THAP && check_defend_or_dead == false)
		return 5;
	if (x1<x2 + w2/1.25 && x1 + w1/1.25>x2 && p2.m_state_machine.CurrentState()->GetPlayerState() == (int)PlayerState::CHEM_TU_DUOI && check_defend_or_dead == false)
		return 6;
}

void Fighter::HandleKeyEvents(float deltaTime)
{
	m_state_machine.CurrentState().get()->HandleKeyEvents(m_control, deltaTime);
}

int Fighter::GetSpriteWidth()
{
	return m_state_machine.CurrentState().get()->GetSpriteWidth();
}
int Fighter::GetSpriteHeight() {
	return m_state_machine.CurrentState().get()->GetSpireHeigth();
}


int Fighter::GetCurrentHp() {
	return m_current_hp;
}