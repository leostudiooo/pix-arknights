#include "Game.h"
#include "UserInterface.h"
#include "SplashScreen.h"
#include "MainMenu.h"

#include <iostream>

Game::Game()
{
	window.create(sf::VideoMode(1280, 720), "Pixnights");
	window.setFramerateLimit(60);

	view.setSize(192, 108);
	view.setCenter(192 / 2, 108 / 2);
}

Game::~Game()
{
	while (!uiStack.empty())
	{
		uiStack.pop();
	}
}

void Game::updateView()
{
    sf::Vector2f windowSize(window.getSize());
    sf::Vector2f targetSize(192, 108);

    // 计算窗口和目标的宽高比
    float windowRatio = windowSize.x / windowSize.y;
    float targetRatio = targetSize.x / targetSize.y;
    sf::FloatRect viewport;

    if (windowRatio > targetRatio)
    {
        // 窗口宽于目标宽高比
        float scale = windowSize.y / targetSize.y;
        float width = targetSize.x * scale;
        float left = (windowSize.x - width) / 2.0f / windowSize.x;
        viewport = sf::FloatRect(left, 0.0f, width / windowSize.x, 1.0f);
    }
    else
    {
        // 窗口高于目标宽高比
        float scale = windowSize.x / targetSize.x;
        float height = targetSize.y * scale;
        float top = (windowSize.y - height) / 2.0f / windowSize.y;
        viewport = sf::FloatRect(0.0f, top, 1.0f, height / windowSize.y);
    }

    view.setSize(targetSize);
    view.setCenter(targetSize.x / 2, targetSize.y / 2);
    view.setViewport(viewport);

    window.setView(view);
}


sf::Vector2f Game::getMousePosition()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(mousePosition);
}

void Game::pushState(std::unique_ptr<UserInterface> ui, bool switchMusic) {
	if(!uiStack.empty()) {
    // 创建画面淡出效果
    for (int alpha = 255; alpha >= 0; alpha -= 5) {
        uiStack.top()->render(window); 
        sf::RectangleShape fade(sf::Vector2f(window.getSize()));
        fade.setFillColor(sf::Color(0, 0, 0, alpha));
        window.draw(fade);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }

    // 如果需要切换音频，渐弱当前音乐
    if (switchMusic && bgMusic && bgMusic->getStatus() == sf::Music::Playing) {
        for (float vol = bgMusic->getVolume(); vol >= 0; vol -= 2) {
            bgMusic->setVolume(vol);
            sf::sleep(sf::milliseconds(10));
        }
        bgMusic->stop();
    }
	}
    // 推入新状态
    uiStack.push(std::move(ui));

    // 创建画面淡入效果
    for (int alpha = 0; alpha <= 255; alpha += 5) {
        uiStack.top()->render(window); 
        sf::RectangleShape fade(sf::Vector2f(window.getSize()));
        fade.setFillColor(sf::Color(0, 0, 0, 255 - alpha));
        window.draw(fade);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }

    // 如果需要切换音频，渐强新状态的音乐
    if (switchMusic) {
        bgMusic->play();
        for (float vol = 0; vol <= 100; vol += 2) {
            bgMusic->setVolume(vol);
            sf::sleep(sf::milliseconds(10));
        }
    }
}

void Game::popState(bool switchMusic) {
    // 创建画面淡出效果
    for (int alpha = 255; alpha >= 0; alpha -= 5) {
        uiStack.top()->render(window); 
        sf::RectangleShape fade(sf::Vector2f(window.getSize()));
        fade.setFillColor(sf::Color(0, 0, 0, alpha));
        window.draw(fade);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }

    // 弹出当前状态
    uiStack.pop();

    // 如果还有其他状态，创建画面淡入效果
    if (!uiStack.empty()) {
        for (int alpha = 0; alpha <= 255; alpha += 5) {
            uiStack.top()->render(window); 
            sf::RectangleShape fade(sf::Vector2f(window.getSize()));
            fade.setFillColor(sf::Color(0, 0, 0, 255 - alpha));
            window.draw(fade);
            window.display();
            sf::sleep(sf::milliseconds(10));
        }

        // 如果需要切换音频，渐强上一个状态的音乐
        if (switchMusic) {
            bgMusic->play();
            for (float vol = 0; vol <= 100; vol += 2) {
                bgMusic->setVolume(vol);
                sf::sleep(sf::milliseconds(10));
            }
        }
    }
}

void Game::replaceState(std::unique_ptr<UserInterface> ui, bool switchMusic)
{
	// 弹出当前状态
    if (!uiStack.empty()) {
        // 创建当前状态的淡出效果
        for (int alpha = 255; alpha >= 0; alpha -= 5) {
            uiStack.top()->render(window);
            sf::RectangleShape fade(sf::Vector2f(window.getSize()));
            fade.setFillColor(sf::Color(0, 0, 0, alpha));
            window.draw(fade);
            window.display();
            sf::sleep(sf::milliseconds(10));
        }

        // 如果需要切换音频，渐弱当前音乐
        if (switchMusic && bgMusic && bgMusic->getStatus() == sf::Music::Playing) {
            for (float vol = bgMusic->getVolume(); vol >= 0; vol -= 2) {
                bgMusic->setVolume(vol);
                sf::sleep(sf::milliseconds(10));
            }
            bgMusic->stop();
        }

        // 弹出当前状态
        uiStack.pop();
    }

    // 推入新状态
    pushState(std::move(ui), switchMusic);
}

void Game::init()
{
	uiStack.push(std::make_unique<SplashScreen>(getGame()));
	for (int alpha = 255; alpha >= 0; alpha -= 5) {
		uiStack.top()->render(window);
		sf::RectangleShape fade(sf::Vector2f(window.getSize()));
		fade.setFillColor(sf::Color(0, 0, 0, alpha));
		window.draw(fade);
		window.display();
		sf::sleep(sf::milliseconds(10));
	}
}

void Game::run()
{
	while (window.isOpen())
	{
		handleEvent();
		window.clear();
		if (!uiStack.empty())
		{
			window.setView(view);
			uiStack.top()->update();
			uiStack.top()->render(window);
		}
		else
		{
			window.close();
		}
		window.display();
	}
}

void Game::handleEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			updateView();
		}
		if (!uiStack.empty())
		{
			uiStack.top()->handleEvent(event);
		}
	}
}

void Game::loadSingleAsset(const AssetType assetType, const std::string &name, const std::string &filename)
{
	switch (assetType)
	{
	case TEXTURE:
		assetManager.loadTexture(name, filename);
		break;

	case MUSIC:
		assetManager.loadMusic(name, filename);
		break;

	case FONT:
		assetManager.loadFont(name, filename);

	default:
		break;
	}
}