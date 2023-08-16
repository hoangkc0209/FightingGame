#pragma once
#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include "PlayerStateBase.h"

enum class PlayerState
{
	INVALID_STATE = 0,
	IDLE,
	CHEM_CO_BAN,
	CHEM_CAO,
	CHEM_THAP,
	NHAY_CHEM,
	CHEM_TU_DUOI,
	DA_CAO,
	DA_THAP,
	DEFEND,
	JUMP,
	WALK_BACKWARD,
	WALK_FORWARD,
	RUN_FORWARD,
	RUN_BACKWRAD,
	TRUNG_CHIEU,
	DEAD,
};

class PlayerStateMachine
{
public:
	PlayerStateMachine();
	~PlayerStateMachine();

	void CleanUp();
	void ChangeState(int stt);

	void SetFlip(bool is_flip);
	// Hàm trả về true nếu nhân vật đang di chuyển sang phải
	bool IsMovingRight() const { return m_isMovingRight; }

	// Hàm trả về true nếu nhân vật đang di chuyển sang trái
	bool IsMovingLeft() const { return m_isMovingLeft; }

	inline std::shared_ptr<PlayerStateBase> CurrentState()const
	{
		return m_pActiveState;
	}
private:
	void AddState(int stt);
	bool m_isMovingRight = false;
	bool m_isMovingLeft = false;
private:
	std::unordered_map<int, std::shared_ptr<PlayerStateBase>> m_StateMap;
	std::shared_ptr<PlayerStateBase> m_pActiveState;
};