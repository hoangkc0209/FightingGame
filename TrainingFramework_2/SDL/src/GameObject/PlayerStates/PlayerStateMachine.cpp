#include "PlayerStateMachine.h"

#include "ResourceManagers.h"
#include "Define.h"

PlayerStateMachine::PlayerStateMachine()
{
	AddState((int)PlayerState::IDLE);
	AddState((int)PlayerState::CHEM_CO_BAN);
	AddState((int)PlayerState::CHEM_CAO);
	AddState((int)PlayerState::CHEM_THAP);
	AddState((int)PlayerState::NHAY_CHEM);
	AddState((int)PlayerState::CHEM_TU_DUOI);
	AddState((int)PlayerState::DA_CAO);
	AddState((int)PlayerState::DA_THAP);
	AddState((int)PlayerState::JUMP);
	AddState((int)PlayerState::DEFEND);
	AddState((int)PlayerState::WALK_FORWARD);
	AddState((int)PlayerState::WALK_BACKWARD);
	AddState((int)PlayerState::RUN_FORWARD);
	AddState((int)PlayerState::RUN_BACKWRAD);
	AddState((int)PlayerState::TRUNG_CHIEU);
	AddState((int)PlayerState::DEAD);

	ChangeState((int)PlayerState::IDLE);
}

PlayerStateMachine::~PlayerStateMachine()
{
	CleanUp();
}

void PlayerStateMachine::CleanUp()
{
	// cleanup the all states
	m_StateMap.clear();
}

void PlayerStateMachine::AddState(int stt)
{
	if (m_StateMap.find(stt) == m_StateMap.end())
	{
		std::shared_ptr<PlayerStateBase> state = PlayerStateBase::CreateState(stt, *this);
		if (state == nullptr)
			return;
		m_StateMap.insert(std::pair<int, std::shared_ptr<PlayerStateBase>>(stt, state));
	}
}

void PlayerStateMachine::SetFlip(bool is_flip)
{
	for (auto state : m_StateMap)
	{
		state.second.get()->SetFlip(is_flip);
	}
}

void PlayerStateMachine::ChangeState(int stt)
{
	if (m_StateMap.find(stt) == m_StateMap.end())
	{
		return;
	}

	m_pActiveState = m_StateMap[stt];
	m_pActiveState.get()->Reset();
}
