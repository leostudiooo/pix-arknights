#include "Game.h"

int main(int argc, char *argv[])
{
	std::clog << "Starting game at " << argv[0] << std::endl;
	auto path = std::filesystem::current_path();
	if (std::filesystem::current_path().string().find("bin" || "build" || "Debug" || "Release") != std::string::npos)
	{
		path = path.parent_path();
	}
	auto game = std::make_shared<Game>();
	game->setAssetPrefix(path.string() + "/assets/");
	game->init();
	game->run();
}