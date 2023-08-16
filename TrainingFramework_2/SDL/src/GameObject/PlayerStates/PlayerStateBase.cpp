#include "PlayerStateBase.h"

#include "ResourceManagers.h"
#include "Define.h"
#include "PlayerStateMachine.h"
#include "Idle.h"
#include "Chem_co_ban.h"
#include "Chem_cao.h"
#include "Chem_thap.h"
#include "Chem_tu_duoi.h"
#include "Da_cao.h"
#include "Da_thap.h"
#include "Jump.h"
#include "Nhay_chem.h"
#include "Run_forward.h"
#include "Run_backward.h"
#include "Walk_Forward.h"
#include "Walk_backward.h"
#include "Dead.h"
#include "Defend.h"
#include "TrungChieu.h"



std::shared_ptr<PlayerStateBase> PlayerStateBase::CreateState(int stt, PlayerStateMachine& state_mech)
{
	std::shared_ptr<PlayerStateBase> ps = nullptr;
	switch (stt)
	{
	case (int)PlayerState::INVALID_STATE:
		break;
	case (int)PlayerState::IDLE:
		ps = std::make_shared<Idle>(state_mech);
		break;
	case (int)PlayerState::CHEM_CO_BAN:
		ps = std::make_shared<Chem_co_ban>(state_mech);
		break;
	case (int)PlayerState::CHEM_CAO:
		ps = std::make_shared<Chem_cao>(state_mech);
		break;
	case (int)PlayerState::CHEM_THAP:
		ps = std::make_shared<Chem_thap>(state_mech);
		break;
	case (int)PlayerState::NHAY_CHEM:
		ps = std::make_shared<Nhay_chem>(state_mech);
		break;
	case (int)PlayerState::CHEM_TU_DUOI:
		ps = std::make_shared<Chem_tu_duoi>(state_mech);
		break;
	case (int)PlayerState::DA_CAO:
		ps = std::make_shared<Da_cao>(state_mech);
		break;
	case (int)PlayerState::DA_THAP:
		ps = std::make_shared<Da_thap>(state_mech);
		break;
	case (int)PlayerState::DEFEND:
		ps = std::make_shared<Defend>(state_mech);
		break;
	case (int)PlayerState::JUMP:
		ps = std::make_shared<Jump>(state_mech);
		break;
	case (int)PlayerState::RUN_FORWARD:
		ps = std::make_shared<Run_forward>(state_mech);
		break;
	case (int)PlayerState::RUN_BACKWRAD:
		ps = std::make_shared<Run_backward>(state_mech);
		break;
	case (int)PlayerState::WALK_FORWARD:
		ps = std::make_shared<WalkForward>(state_mech);
		break;
	case (int)PlayerState::WALK_BACKWARD:
		ps = std::make_shared<Walk_backward>(state_mech);
		break;
	case (int)PlayerState::TRUNG_CHIEU:
		ps = std::make_shared<Trung_chieu>(state_mech);
		break;
	case (int)PlayerState::DEAD:
		ps = std::make_shared<Dead>(state_mech);
		break;
	}
	return ps;
}

int PlayerStateBase::GetPlayerState()
{
	return m_player_state;
}

int PlayerStateBase::GetSpriteWidth()
{
	return m_animation.get()->GetWidth();
}
int PlayerStateBase::GetSpireHeigth() {
	return m_animation.get()->GetHeight();
}

void PlayerStateBase::SetFlip(bool is_flip)
{
	m_is_flip = is_flip;
}

void PlayerStateBase::SetAnimation(std::string filepath, int spriteRow, int frameCount, int numAction, float frameTime)
{
	auto texture = ResourceManagers::GetInstance().get()->GetTexture(filepath);
	texture.get()->SetScaleMode(SDL_ScaleModeNearest);
	std::shared_ptr<SpriteAnimation> ani = std::make_shared<SpriteAnimation>(texture, spriteRow, frameCount, numAction, frameTime);
	ani.get()->SetSize(SPRITE_SCALE_UP);
	m_animation = ani;
}

PlayerStateBase::PlayerStateBase(PlayerStateMachine& state_mech)
	:
	m_state_machine(state_mech)
{
}
