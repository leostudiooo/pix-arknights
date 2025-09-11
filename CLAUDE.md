# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Pixnights is a C++ tower defense game inspired by Arknights, built with SFML 2.6.1. The game uses a state-based architecture with JSON-driven data for levels, operators, and enemies.

## Build Commands

### Windows (Visual Studio 2022)
```powershell
# Generate Visual Studio solution
cmake -G "Visual Studio 17 2022" -A x64 .

# Or use the helper script
./build_solution_file.bat
```

### Linux/macOS
```bash
# Generate build files
cmake .

# Build
make
```

### Run the Game
After building, copy SFML DLLs from `C:\sfml\2.6.1\bin` to the executable directory, or add `C:\sfml\2.6.1\bin` to PATH.

## Build Commands

### Windows (Visual Studio 2022)
```powershell
# Generate Visual Studio solution
cmake -G "Visual Studio 17 2022" -A x64 .

# Or use the helper script
./build_solution_file.bat
```

### Linux/macOS
```bash
# Generate build files
cmake .

# Build
make
```

### Run the Game
After building, copy SFML DLLs from `C:\sfml\2.6.1\bin` to the executable directory, or add `C:\sfml\2.6.1\bin` to PATH.

## Architecture

### Core Components
- **Game Engine** (`src/include/Game.h`): Central manager for window, assets, state stack, and music
- **State System**: Stack-based UI navigation through `UserInterface` base class
- **Asset Manager** (`src/include/AssetManager.h`): Handles texture, font, and JSON loading
- **Combat System** (`src/include/Combat.h`): Main gameplay logic for tower defense mechanics

### State Flow
```
SPLASH_SCREEN → MAIN_MENU → TERMINAL → COMBAT → SETTLEMENT
```

### Key Data Structures
- **Operators** (`src/include/Operator.h`): Player units with stats, ranges, costs
- **Enemies** (`src/include/Enemy.h`): AI units with routes and spawn patterns
- **Levels** (`assets/levels/*.json`): Map layouts, enemy waves, objectives

### Asset Organization
```
assets/
├── levels/       # JSON level definitions
├── operators/    # Character sprites and data
├── enemies/      # Enemy sprites and stats
├── tiles/        # Map tile sprites
└── *.ttf        # ChillBitmap fonts
```

## Development Notes

- **C++ Standard**: C++17
- **Dependencies**: SFML 2.6.1, nlohmann/json (auto-downloaded if missing)
- **Platform Paths**: SFML expected at `C:\sfml\2.6.1` (Windows), system packages (Linux/macOS)
- **Code Style**: 4-space indentation, UTF-8, LF endings (see `.editorconfig`)
- **No Test Framework**: Project has no automated tests
- **No Linting**: No configured code quality tools

### Common Tasks
- **Add New Level**: Create JSON file in `assets/levels/` following existing format
- **Add Operator**: Add sprite to `assets/operators/`, stats to operator JSON files
- **Modify Combat**: Edit `src/Combat.cpp` and related headers
- **UI Changes**: Modify appropriate `UserInterface` implementation in `src/`

## Carrot Defense: Procedural Implementation Guide

### Project Structure for Procedural Variant
```
src/
├── procedural/
│   ├── ProceduralAssetGenerator.h/cpp  # Replaces AssetManager
│   ├── ShapeFactory.h/cpp              # Generates all visual elements
│   ├── ToneGenerator.h/cpp             # Audio synthesis
│   └── CarrotTypes.h                   # Carrot/enemy definitions
├── include/
│   └── [existing headers]
└── [existing source files]
```

### Key Implementation Classes

#### ProceduralAssetGenerator
```cpp
class ProceduralAssetGenerator {
public:
    sf::Texture generateCarrotTower(const CarrotType& type);
    sf::Texture generateEnemyPest(const PestType& type);
    sf::SoundBuffer generateShootSound();
    sf::SoundBuffer generateHitSound();
    sf::Font getSystemFont();  // Minimal font requirement
};
```

#### ShapeFactory
```cpp
class ShapeFactory {
public:
    static sf::Shape createCarrotBody(float size, sf::Color color);
    static sf::Shape createCarrotLeaves(float size, int count = 3);
    static sf::Shape createPestBody(PestType type);
    static sf::Shape createProjectile(ProjectileType type);
    static std::vector<sf::Shape> createExplosionParticles();
};
```

#### ToneGenerator
```cpp
class ToneGenerator {
public:
    enum WaveType { SINE, SQUARE, TRIANGLE, SAWTOOTH };

    static std::vector<sf::Int16> generateTone(float frequency, float duration,
                                               WaveType type = SINE);
    static std::vector<sf::Int16> generateChord(const std::vector<float>& frequencies,
                                                float duration);
    static void applyEnvelope(std::vector<sf::Int16>& samples,
                             float attack, float decay, float sustain, float release);
};
```

### Procedural Generation Patterns

#### Carrot Tower Generation
```cpp
sf::Texture ProceduralAssetGenerator::generateCarrotTower(const CarrotType& type) {
    sf::RenderTexture texture;
    texture.create(64, 64);

    // Create carrot body (hexagon)
    auto body = ShapeFactory::createCarrotBody(type.size, type.color);
    body.setPosition(32, 40);

    // Create leaves (triangles)
    auto leaves = ShapeFactory::createCarrotLeaves(type.size, 3);
    for (auto& leaf : leaves) {
        leaf.setPosition(32, 25);
        texture.draw(leaf);
    }

    texture.draw(body);
    texture.display();
    return texture.getTexture();
}
```

#### Enemy Pest Generation
```cpp
sf::Texture ProceduralAssetGenerator::generateEnemyPest(const PestType& type) {
    sf::RenderTexture texture;
    texture.create(32, 32);

    auto body = ShapeFactory::createPestBody(type);
    body.setPosition(16, 16);

    // Add simple details (eyes, legs) using small shapes
    if (type.hasLegs) {
        for (int i = 0; i < 6; ++i) {
            sf::RectangleShape leg(sf::Vector2f(2, 4));
            // Position legs around body
            texture.draw(leg);
        }
    }

    texture.draw(body);
    texture.display();
    return texture.getTexture();
}
```

### Audio Synthesis Examples

#### Shooting Sound
```cpp
sf::SoundBuffer ProceduralAssetGenerator::generateShootSound() {
    // High-frequency square wave burst
    auto samples = ToneGenerator::generateTone(800.f, 0.1f, WaveType::SQUARE);
    ToneGenerator::applyEnvelope(samples, 0.01f, 0.02f, 0.1f, 0.05f);

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), samples.size(), 1, 44100);
    return buffer;
}
```

#### Background Music Generation
```cpp
std::vector<sf::Int16> generateBackgroundLoop() {
    std::vector<sf::Int16> loop;
    std::vector<float> melody = {261.63f, 293.66f, 329.63f, 349.23f}; // C major

    for (float note : melody) {
        auto tone = ToneGenerator::generateTone(note, 0.5f, WaveType::TRIANGLE);
        loop.insert(loop.end(), tone.begin(), tone.end());
    }

    return loop;
}
```

### Migration Strategy from Pixnights

#### Step 1: Asset Manager Replacement
```cpp
// Replace AssetManager with ProceduralAssetGenerator
class Game {
private:
    // AssetManager assetManager;  // OLD
    ProceduralAssetGenerator assetGenerator;  // NEW
};
```

#### Step 2: Texture Loading Changes
```cpp
// OLD: Load from file
// assetManager.loadTexture("thorns", "assets/operators/thorns.png");

// NEW: Generate procedurally
auto carrotTexture = assetGenerator.generateCarrotTower(basicCarrotType);
```

#### Step 3: Audio Loading Changes
```cpp
// OLD: Load from file
// assetManager.loadMusic("combat", "assets/music/combat.ogg");

// NEW: Generate procedurally
auto combatMusic = assetGenerator.generateCombatMusic();
```

### Testing Strategy

#### Visual Testing
```cpp
// Create test scene to verify all procedural assets
void testProceduralAssets() {
    std::vector<sf::Texture> carrotTextures;
    for (const auto& type : carrotTypes) {
        carrotTextures.push_back(generator.generateCarrotTower(type));
    }

    // Display in grid pattern for visual verification
    displayAssetGrid(carrotTextures, "Carrot Towers");
}
```

#### Audio Testing
```cpp
void testAudioSynthesis() {
    std::vector<sf::Sound> sounds;
    sounds.emplace_back(generator.generateShootSound());
    sounds.emplace_back(generator.generateHitSound());

    // Play sequence to verify audio quality
    for (auto& sound : sounds) {
        sound.play();
        sf::sleep(sf::seconds(0.2f));
    }
}
```

### Performance Considerations

#### Caching Strategy
```cpp
class ProceduralAssetGenerator {
private:
    std::unordered_map<std::string, sf::Texture> textureCache;
    std::unordered_map<std::string, sf::SoundBuffer> soundCache;

public:
    sf::Texture& getCarrotTexture(const CarrotType& type) {
        std::string key = "carrot_" + type.name;
        if (textureCache.find(key) == textureCache.end()) {
            textureCache[key] = generateCarrotTower(type);
        }
        return textureCache[key];
    }
};
```

#### Generation Time Budgets
- **Texture Generation**: <5ms per texture (cached)
- **Sound Generation**: <1ms per sound (cached)
- **Startup Time**: <2 seconds for all assets
- **Runtime Generation**: <16ms per frame (60 FPS budget)

### Code Style Guidelines for Procedural Code

#### Shape Generation
- Use descriptive parameter names (size, color, position)
- Return `sf::Shape` objects for flexibility
- Keep generation functions pure when possible
- Document visual intent with comments

#### Audio Generation
- Use constants for frequency definitions
- Implement ADSR envelopes consistently
- Cache frequently used sounds
- Document musical intent (chord progressions, scales)

#### Error Handling
- Graceful fallbacks for generation failures
- Logging for debugging procedural parameters
- Validation for generated asset quality
- Performance monitoring for generation time

## Development Workflow for Carrot Defense

### Quick Iteration Cycle
1. Modify generation parameters in code
2. Rebuild (fast - no asset processing)
3. Test immediately (no asset loading delays)
4. Fine-tune parameters based on visual/audio feedback

### Asset Debugging
- Use SFML's built-in shape debugging (outlines, colors)
- Implement visual parameter inspectors
- Add audio spectrum visualization for tuning
- Create test scenes for rapid iteration

This procedural approach enables rapid iteration and eliminates asset pipeline bottlenecks, making development significantly faster than traditional asset-based approaches.
