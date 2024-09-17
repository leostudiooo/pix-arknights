#include "Settlement.h"
#include "Game.h"
#include "Terminal.h"

Settlement::Settlement(std::shared_ptr<Game> game, std::string levelName, int rating)
	: UserInterface(game), levelName(levelName), rating(rating)
{
	loadAssets();
	background.setTexture(*game->getTexture("settlement_bg"));
	background.setPosition(0, 0);

	levelNameText.setFont(*game->getFont("font_small"));
	levelNameText.setString("Level " + levelName);
	levelNameText.setCharacterSize(8);
	levelNameText.setFillColor(sf::Color::White);
	levelNameText.setPosition(10, 24);

	title.setFont(*game->getFont("font_small"));
	title.setString(rating > 0 ? "Mission Complete" : "Mission Failed");
	title.setCharacterSize(16);
	title.setFillColor(sf::Color::White);
	title.setPosition(10, 30);

	for (int i = 0; i < 3; i++)
	{
		sf::Sprite star;
		star.setTexture(*game->getTexture(i < rating ? "star" : "star_empty"));
		star.setPosition(10 + i * 16, 50);
		hexagonStars.push_back(star);
	}

    continueButton.setTextures(game->getTexture("continue_normal"), game->getTexture("continue_hover"), game->getTexture("continue_click"));
    continueButton.setGame(game);
    continueButton.setPosition(sf::Vector2f(160, 90));
    continueButton.setOnClick([game]() {auto newGame = game->getGame(); newGame->popState(true); });
}

void Settlement::loadAssets()
{
	game->load(TEXTURE, "settlement_bg", "settlement/bg.png");

	game->load(TEXTURE, "continue_normal", "settlement/continue_normal.png");
	game->load(TEXTURE, "continue_hover", "settlement/continue_hover.png");
	game->load(TEXTURE, "continue_pressed", "settlement/continue_click.png");
	
	game->load(TEXTURE, "star", "settlement/star.png");
	game->load(TEXTURE, "star_empty", "settlement/star_empty.png");
	
	game->load(MUSIC, "settlement_victory", "settlement/victory.mp3");
	game->load(MUSIC, "settlement_defeat", "settlement/defeat.mp3");
}

void Settlement::handleEvent(const sf::Event &event)
{
	continueButton.handleEvent(event);
}

void Settlement::update()
{
	continueButton.update();
}

void Settlement::render(sf::RenderWindow &window)
{
	window.draw(background);
	window.draw(levelNameText);
	window.draw(title);
	for (auto &star : hexagonStars)
		window.draw(star);
	continueButton.render(window);
}

void Settlement::playMusic()
{
    game->bgMusic = game->getMusic(rating > 0 ? "settlement_victory" : "settlement_defeat");
    game->bgMusic->setLoop(true);
    game->bgMusic->play();
}
