// CombatEvent.h
#pragma once

enum CombatEventType
{
	OPERATOR_PREDEPLOY,
	OPERATOR_DEPLOY,
	OPERATOR_ATTACK,
	OPERATOR_RETREAT,
	OPERATOR_DEATH,
	ENEMY_SPAWN,
	ENEMY_ATTACK,
	ENEMY_DEATH,
	ENEMY_REACH_GOAL,
};

class CombatEvent
{
protected:
	CombatEventType type;
	std::shared_ptr<Operator> operatorInvolved;
	std::shared_ptr<Enemy> enemyInvolved;
public:
	CombatEvent() = default;
	~CombatEvent() = default;

	void setInvolvedOperator(std::shared_ptr<Operator> opIv) { operatorInvolved = opIv; }
	void setInvolvedEnemy(std::shared_ptr<Enemy> enIv) { enemyInvolved = enIv; }
};