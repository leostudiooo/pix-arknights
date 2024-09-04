#include "Game.h"
#include "UserInterface.h"
#include "SplashScreen.h"
#include "MainMenu.h"

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "CombatMap.h"

Game::Game()
{
	window.create(sf::VideoMode(768,432), "Pixnights");
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
    if (!uiStack.empty()) {
        // 创建画面和音频的淡出效果
        float maxVolume = bgMusic ? bgMusic->getVolume() : 100.0f;
        for (int alpha = 0; alpha <=255; alpha += 3) {
            handleEvent();
            // 渲染当前界面并添加淡出效果
            uiStack.top()->render(window); 
            sf::RectangleShape fade(sf::Vector2f(window.getSize()));
            fade.setFillColor(sf::Color(0, 0, 0, alpha));
            window.draw(fade);
            window.display();

            // 如果需要切换音频，同时执行音频的淡出效果
            if (switchMusic && bgMusic && bgMusic->getStatus() == sf::Music::Playing) {
                float vol = maxVolume * (255 - alpha) / 255.0f;
                bgMusic->setVolume(vol);
            }
        }

        if (switchMusic && bgMusic) {
            bgMusic->stop();
        }
    }

    // 推入新状态
    uiStack.push(std::move(ui));
    // 创建画面和音频的淡入效果
    for (int alpha = 0; alpha <= 255; alpha += 3) {
        handleEvent();
        uiStack.top()->render(window); 
        sf::RectangleShape fade(sf::Vector2f(window.getSize()));
        fade.setFillColor(sf::Color(0, 0, 0, 255 - alpha));
        window.draw(fade);
        window.display();

        // 如果需要切换音频，同时执行音频的淡入效果
        if (switchMusic) {
            float vol = 100.0f * alpha / 255.0f;
            bgMusic->setVolume(vol);
		    // std::clog << "Setting volume to " << vol << std::endl;
        }
    }
}

bool Game::popState(bool switchMusic) {
    if (!uiStack.empty()) {
        // 创建画面和音频的淡出效果
		float maxVolume = bgMusic ? bgMusic->getVolume() : 100.0f;
        for (int alpha = 0; alpha <= 255; alpha += 3) {
            handleEvent();
            uiStack.top()->render(window); 
            sf::RectangleShape fade(sf::Vector2f(window.getSize()));
            fade.setFillColor(sf::Color(0, 0, 0, alpha));
            window.draw(fade);
            window.display();

            // 如果需要切换音频，同时执行音频的淡出效果
            if (switchMusic && bgMusic && bgMusic->getStatus() == sf::Music::Playing) {
                float vol = maxVolume * (255 - alpha) / 255.0f;
                bgMusic->setVolume(vol);
            }
        }

        if (switchMusic && bgMusic) {
            bgMusic->stop();
        }

        // 弹出当前状态
        uiStack.pop();
    }

    if (!uiStack.empty()) {
        // 创建画面和音频的淡入效果
        for (int alpha = 0; alpha <= 255; alpha += 3) {
            handleEvent();
            uiStack.top()->render(window); 
            sf::RectangleShape fade(sf::Vector2f(window.getSize()));
            fade.setFillColor(sf::Color(0, 0, 0, 255 - alpha));
            window.draw(fade);
            window.display();

            // 如果需要切换音频，同时执行音频的淡入效果
            if (switchMusic) {
                float vol = 100.0f * (alpha / 255.0f);
                bgMusic->setVolume(vol);
            }
        }
        return true;
    }
    else return false;
}

bool Game::popStateNoTransition() {
    if (!uiStack.empty()) {
        uiStack.pop();
        return true;
    }
    else return false;
}

void Game::init() {
    // 不要在这里就加载地图等资源，在初始化 UI 的时候用 loadAssets() 进行加载
    // 参考 MainMenu.h/cpp
	uiStack.push(std::make_unique<SplashScreen>(getGame()));

    load(FONT, "font_small", "ChillBitmap_7px.ttf");
    getFont("font_small")->setSmooth(false);
    load(FONT, "font_large", "ChillBitmap_16px.ttf");
    getFont("font_large")->setSmooth(false);

    load(TEXTURE, "back_normal", "buttons/back_normal.png");
    load(TEXTURE, "back_hover", "buttons/back_hover.png");
    load(TEXTURE, "back_click", "buttons/back_click.png");

    load(TEXTURE, "home_normal", "buttons/home_normal.png");
    load(TEXTURE, "home_hover", "buttons/home_hover.png");
    load(TEXTURE, "home_click", "buttons/home_click.png");
}

void Game::run()
{
	while (window.isOpen())
	{
		handleEvent();
		window.clear();

		
        if (!uiStack.empty())// 先绘制战斗地图
        if (combatMap) {
            combatMap->draw(window);
        }
)
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