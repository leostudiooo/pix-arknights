#include "OperatorSelector.h"

#include "Combat.h"
#include "CombatComponent.h"
#include "CombatEvent.h"
#include "OperatorSelectorBlock.h"

#include "json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

OperatorSelector::OperatorSelector(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game)
{
	loadAssets();

	bgBar.setPosition(0, 92);
	bgBar.setFillColor(sf::Color(0x22222299));
	bgBar.setSize(sf::Vector2f(192, 16));
	
	int posX = 192 - 18;
	for(auto &op : operatorData)
	{
		std::string opName = op["name"];
		int opBranch = op["branch"];
		unsigned int opCost = op["cost"];
		std::string opInfoStr = opBranchStr[opBranch] + " " + std::to_string(opCost);
		std::shared_ptr<sf::Texture> preview = game->getTexture(opName + "_preview");
		auto block = std::make_shared<OperatorSelectorBlock>(opName, opCost, preview, sf::Vector2f(posX, 92), opInfoStr, game->getFont("font_small"));
		selectorBlocks.push_back(block);
		std::clog << "Created selector block for " << opName << " at " << posX << std::endl;
		posX -= 17;
	}
}

void OperatorSelector::loadAssets()
{
	std::ifstream file(game->getAssetPrefix() + "operators/operators.json");
	try
	{
		operatorData = json::parse(file);
		std::clog << operatorData << std::endl;
	}
	catch (const std::exception &)
	{
		std::cerr << "Error loading operators" << std::endl;
	}
	file.close();

	operatorData = operatorData["operators"];
	std::stable_sort(operatorData.begin(), operatorData.end(), [](const json &a, const json &b) {
		return a["cost"] > b["cost"];
	});

	for (auto &op : operatorData)
	{
		std::string opName = op["name"];
		game->load(TEXTURE, opName + "_preview", "operators/" + opName + "/preview.png");
	}
}

void OperatorSelector::handleEvent(const sf::Event &event)
{
	for (auto &block : selectorBlocks)
	{
		block->setMousePosition(game->getMousePosition());
		block->handleEvent(event);
	}
}

void OperatorSelector::update()
{
    bool wasSelected = selecting;  // 记录之前的选中状态
    bool anySelected = false;  // 用于标记是否有干员块被选中
    std::string newSelectedOperatorName;  // 用于记录新选中的干员名称

    // 遍历所有干员块
    for (auto &block : selectorBlocks)
    {
        // 更新是否可部署状态
        if (combat->getCurrCost() < block->getOpCost())
            block->setUndeployable(true);
        else
            block->setUndeployable(false);

        bool isCurrentlySelected = block->getSelected();

        if (isCurrentlySelected)
        {
            // 记录新选中的干员名称
            newSelectedOperatorName = block->getOpName();
            anySelected = true;

            // 取消其他干员块的选中状态
            for (auto &otherBlock : selectorBlocks)
            {
                if (otherBlock != block && otherBlock->getSelected())
                {
                    otherBlock->setSelected(false);
                }
            }

            // 设置当前选中状态
            selecting = true;
        }
        else
        {
            // 设置当前选中状态
            if (selecting && !anySelected)
            {
                selecting = false;
            }
        }

        block->update();
    }

    // 发送状态变化的消息
    if (selecting != wasSelected)
    {
        if (selecting)
        {
            std::clog << "Operator " << newSelectedOperatorName << " selected" << std::endl;
            json selectedOp = *findOperator(newSelectedOperatorName);
            std::clog << selectedOp << std::endl;
            combat->createEvent(std::make_shared<CombatEvent>(OPERATOR_PREDEPLOY, selectedOp));
        }
        else
        {
            std::clog << "Operator deselected" << std::endl;
            combat->createEvent(std::make_shared<CombatEvent>(OPERATOR_CANCEL_PREDEPLOY));
        }
    }
}

void OperatorSelector::render(sf::RenderWindow &window)
{
	window.draw(bgBar);
	for (auto &block : selectorBlocks)
	{
		block->render(window);
	}
}

void OperatorSelector::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
    switch (event->getType())
    {
    case OPERATOR_DEPLOY:
    {
        std::clog << "Operator deployed" << std::endl;
        // remove the operator from the list
        std::string opName = event->getData()["name"];
        auto it = std::find_if(selectorBlocks.begin(), selectorBlocks.end(), [&opName](const std::shared_ptr<OperatorSelectorBlock> &block) {
            return block->getOpName() == opName;
        });
        if (it != selectorBlocks.end())
        {
            selectorBlocks.erase(it);
        }
        break;
    }
    default:
        break;
    }
}