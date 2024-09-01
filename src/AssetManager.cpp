#include "AssetManager.h"

AssetManager::AssetManager()
{
}

void AssetManager::loadTexture(const std::string& name, const std::string& filename)
{
	auto texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(filename))
	{
		std::cerr << "Failed to load texture: " << filename << std::endl;
		exit(1);
	}
	textures[name] = texture;
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(const std::string& name)
{
	return textures[name];
}

void AssetManager::loadMusic(const std::string& name, const std::string& filename)
{
	auto music = std::make_shared<sf::Music>();
	if (!music->openFromFile(filename))
	{
		std::cerr << "Failed to load music: " << filename << std::endl;
		exit(1);
	}
	this->music[name] = music;
}

std::shared_ptr<sf::Music> AssetManager::getMusic(const std::string& name)
{
	return music[name];
}

void AssetManager::loadFont(const std::string& name, const std::string& filename)
{
	auto font = std::make_shared<sf::Font>();
	if (!font->loadFromFile(filename))
	{
		std::cerr << "Failed to load font: " << filename << std::endl;
		exit(1);
	}
	fonts[name] = font;
}

std::shared_ptr<sf::Font> AssetManager::getFont(const std::string& name)
{
	return fonts[name];
}