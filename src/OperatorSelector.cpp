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
		auto block = std::make_shared<OperatorSelectorBlock>(preview, sf::Vector2f(posX, 92), opInfoStr, game->getFont("font_small"));
		selectorBlocks.push_back(block);
		std::clog << "Created selector block for " << opName << " at " << posX << std::endl;
		posX -= 20;
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
}

void OperatorSelector::update()
{
	for (auto &block : selectorBlocks)
	{
		block->update();
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

void OperatorSelector::handleCombatEvent(const CombatEvent &event)
{
}