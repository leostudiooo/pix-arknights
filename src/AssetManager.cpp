#include "AssetManager.h"

AssetManager::AssetManager()
{
}

void AssetManager::loadTexture(const std::string &name, const std::string &filename)
{
    if (textures.find(name) != textures.end())
    {
        // remove and reload texture
        textures.erase(name);
    }

    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filename))
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        exit(1);
    }
    texture->setSmooth(false); // disable texture smoothing for pixel art
    textures[name] = texture;
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(const std::string &name)
{
    return textures[name];
}

void AssetManager::loadMusic(const std::string &name, const std::string &filename)
{
    if (music.find(name) != music.end())
    {
        // remove and reload music
        music.erase(name);
    }

    auto music = std::make_shared<sf::Music>();
    if (!music->openFromFile(filename))
    {
        std::cerr << "Failed to load music: " << filename << std::endl;
        exit(1);
    }
    this->music[name] = music;
}

std::shared_ptr<sf::Music> AssetManager::getMusic(const std::string &name)
{
    return music[name];
}

void AssetManager::loadFont(const std::string &name, const std::string &filename)
{
    if (fonts.find(name) != fonts.end())
    {
        // remove and reload font
        fonts.erase(name);
    }

    auto font = std::make_shared<sf::Font>();
    if (!font->loadFromFile(filename))
    {
        std::cerr << "Failed to load font: " << filename << std::endl;
        exit(1);
    }
    fonts[name] = font;
}

std::shared_ptr<sf::Font> AssetManager::getFont(const std::string &name)
{
    return fonts[name];
}

void AssetManager::cleanUnused()
{
    for (auto it = textures.begin(); it != textures.end();)
    {
        if (it->second.use_count() == 1)
        {
            it = textures.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = music.begin(); it != music.end();)
    {
        if (it->second.use_count() == 1)
        {
            it = music.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = fonts.begin(); it != fonts.end();)
    {
        if (it->second.use_count() == 1)
        {
            it = fonts.erase(it);
        }
        else
        {
            ++it;
        }
    }
}