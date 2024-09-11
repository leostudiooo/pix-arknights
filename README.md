# Pixnights
## Dependendcy

- SFML 2.6.1

On Windows, the SFML library should be placed at `C:\sfml\2.6.1`. If you have installed SFML in a different directory, you should modify the `CMakeLists.txt` file accordingly.

On GNU/Linux, you can install the library with the package manager. For example, on Ubuntu you can run `sudo apt-get install libsfml-dev` to install the library.

On macOS you can simply run `brew install sfml` to install the library.

## Build (Visual Studio 2022)

1. Build Visual Studio solution file with CMake

```powershell
cmake -G "Visual Studio 17 2022" -A x64 .
```

And you will get a solution file to open with Visual Studio 2022.

2. Configure Visual Studio Project for SFML

Open the solution file with Visual Studio 2022, head to `Solution Explorer`, set `Pixnights` as the startup project, right click on the project, and select `Properties`. In the `Configuration Properties`, set the following:

(a) `C/C++` -> `General` -> `Additional Include Directories`: `C:\sfml\2.6.1\include`
(b) `Linker` -> `General` -> `Additional Library Directories`: `C:\sfml\2.6.1\lib`

Then `F5` to build and run the project. It will fail to run because the `sfml-graphics-2.dll` is missing. You can copy the dll file from `C:\sfml\2.6.1\bin` to the project `Debug` directory, or add the path to the system environment variable `PATH`.

## Open Source Projects in Use

- [SFML](https://www.sfml-dev.org/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [ChillBitmap Font](https://github.com/Warren2060/ChillBitmap)

## LICENSE

*Pixnights* is a fan-made pixel art game inspired by, and based on the settings of [*明日方舟*](https://ak.hypergryph.com/) or [*Arknights*](https://arknights.global/), a mobile tower defense game developed by [Hypergryph](https://www.hypergryph.com/). The project is not affiliated with Hypergryph, and is not intended for commercial use. All rights to the original game and its assets belong to Hypergryph.

The project is developed by Leo Li and Leo Kao, and is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/?ref=chooser-v1).