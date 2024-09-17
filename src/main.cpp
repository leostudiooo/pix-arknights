#include "Game.h"

int main(int argc, char *argv[])
{
	std::clog << "Starting game at " << argv[0] << std::endl;
	auto path = std::filesystem::path(argv[0]).parent_path();
	std::clog << "Path: " << path.string() << std::endl;
	// find "build", "bin", "Debug", "Release" in path, if exist then parent_path();
	while (path.filename() == "build" || path.filename() == "bin" || path.filename() == "Debug" || path.filename() == "Release")
	{
		path = path.parent_path();
		std::clog << "Path: " << path.string() << std::endl;
	}
	auto game = std::make_shared<Game>();
	game->setAssetPrefix(path.string() + "/assets/");
	game->init();
	game->run();
}
