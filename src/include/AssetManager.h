// AssetManager.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdlib>
#include <iostream>

enum AssetType
{
	TEXTURE,
	MUSIC,
	FONT
};

class AssetManager
{
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture> > textures;
	std::unordered_map<std::string, std::shared_ptr<sf::Music> > music;
	std::unordered_map<std::string, std::shared_ptr<sf::Font> > fonts;

public:
	AssetManager();
	~AssetManager();

	void loadTexture(const std::string& name, const std::string& filename);
	std::shared_ptr<sf::Texture> getTexture(const std::string& name);

	void loadMusic(const std::string& name, const std::string& filename);
	std::shared_ptr<sf::Music> getMusic(const std::string& name);

	void loadFont(const std::string& name, const std::string& filename);
	std::shared_ptr<sf::Font> getFont(const std::string& name);
};