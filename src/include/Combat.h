// Combat.h
#include "UserInterface.h"
#include "CombatMap.h"
#include "Button.h"
#include "Operator.h"
#include "OperatorIndicator.h"
#include "Enemy.h"

class Combat : public UserInterface
{
private:
	CombatMap map;
	std::vector<std::pair<OperatorIndicator, Operator> > opList;
public:
	Combat() = default;
	Combat(std::shared_ptr<Game>, std::string);
};