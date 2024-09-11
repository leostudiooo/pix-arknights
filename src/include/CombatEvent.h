// CombatEvent.h
#pragma once

#include "json.hpp"

using json = nlohmann::json;

// Forward declarations
class Operator;
class Enemy;

enum CombatEventType
{
	OPERATOR_PREDEPLOY,
	OPERATOR_CANCEL_PREDEPLOY,
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
	json data;
public:
	CombatEvent() = default;
	~CombatEvent() = default;

	CombatEvent(CombatEventType type) : type(type) {}
	CombatEvent(CombatEventType type, json data) : type(type), data(data) {}
	CombatEvent(CombatEventType type, std::shared_ptr<Operator> opIv) : type(type), operatorInvolved(opIv) {}
	CombatEvent(CombatEventType type, std::shared_ptr<Enemy> enIv) : type(type), enemyInvolved(enIv) {}
	CombatEvent(CombatEventType type, std::shared_ptr<Operator> opIv, std::shared_ptr<Enemy> enIv) : type(type), operatorInvolved(opIv), enemyInvolved(enIv) {}

	CombatEventType getType() const { return type; }
	
	void setInvolvedOperator(std::shared_ptr<Operator> opIv) { operatorInvolved = opIv; }
	void setInvolvedEnemy(std::shared_ptr<Enemy> enIv) { enemyInvolved = enIv; }

	std::shared_ptr<Operator> getOperator() const { return operatorInvolved; }
	std::shared_ptr<Enemy> getEnemy() const { return enemyInvolved; }
};
