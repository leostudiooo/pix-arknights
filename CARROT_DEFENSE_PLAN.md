# Carrot Defense: Procedural Tower Defense Implementation Plan

## Project Overview
Transform the Pixnights tower defense engine into "Carrot Defense" - a fully procedural game using only code-generated graphics and synthesized audio, eliminating external asset dependencies.

## Technical Feasibility: ✅ HIGHLY FEASIBLE

### Core Infrastructure Reusability: 90%
- **Game Engine**: Fully reusable state management, window handling, input processing
- **Combat System**: Reusable with data modifications for carrot-themed units
- **JSON Data System**: Perfect for procedural generation parameters
- **Build System**: CMake + SFML remains identical

## Procedural Graphics Strategy

### SFML Shape-Based Rendering
SFML provides excellent shape primitives perfect for procedural generation:

```cpp
// Carrot Tower (Guardian Unit)
sf::CircleShape carrot_body(20.f, 6);  // Hexagon base
carrot_body.setFillColor(sf::Color(255, 140, 0));  // Orange
carrot_body.setOutlineColor(sf::Color(200, 100, 0)); // Darker orange outline

// Carrot Top (Leaves)
sf::CircleShape leaf1(8.f, 3);  // Triangle
leaf1.setFillColor(sf::Color(34, 139, 34));  // Forest green
leaf1.setPosition(-5, -15);
```

### Visual Element Breakdown

#### Towers (Carrot Variants)
- **Basic Carrot**: Orange hexagon + 2-3 green triangles (leaves)
- **Advanced Carrot**: Larger hexagon, more leaves, color variations
- **Elite Carrot**: Golden color, particle effects, glowing outline
- **Special Carrots**: Purple (ranged), white (support), red (explosive)

#### Enemies (Pest Variants)
- **Aphids**: Small green circles (basic enemies)
- **Caterpillars**: Green rectangles with segmentation
- **Beetles**: Dark circles with visible legs (lines)
- **Boss Pest**: Large purple circle with complex patterns

#### Projectiles
- **Seeds**: Small brown circles
- **Juice**: Orange droplet shapes (teardrop)
- **Spores**: Green particles with fade effects
- **Explosions**: Expanding orange circles with particles

#### Environment
- **Map Tiles**: Colored rectangles with borders
- **Paths**: Brown rectangles connecting tiles
- **Background**: Gradient fills with simple patterns
- **UI Elements**: Rounded rectangles with text

### Procedural Animation
```cpp
// Simple growth animation for carrot deployment
void animateCarrotGrowth(sf::Shape& carrot, float progress) {
    float scale = 0.5f + progress * 0.5f;
    carrot.setScale(scale, scale);
    // Add slight rotation for organic feel
    carrot.setRotation(std::sin(progress * 3.14159f) * 5.f);
}
```

## Synthesized Audio Strategy

### SFML Audio Capabilities Assessment
- **sf::Sound**: Perfect for short effects (shooting, hits)
- **sf::Music**: Suitable for background tracks
- **Buffer Generation**: Can create waveforms programmatically

### Sound Generation Implementation

#### Basic Waveform Generator
```cpp
class ToneGenerator {
public:
    static std::vector<sf::Int16> generateTone(float frequency, float duration, 
                                               WaveType type = WaveType::SINE) {
        std::vector<sf::Int16> samples;
        int sampleCount = static_cast<int>(44100 * duration);  // 44.1kHz
        
        for (int i = 0; i < sampleCount; ++i) {
            float time = static_cast<float>(i) / 44100.f;
            float value = 0.f;
            
            switch(type) {
                case WaveType::SINE:
                    value = std::sin(2 * M_PI * frequency * time);
                    break;
                case WaveType::SQUARE:
                    value = (std::sin(2 * M_PI * frequency * time) > 0) ? 1.f : -1.f;
                    break;
                case WaveType::TRIANGLE:
                    value = 2.f * std::asin(std::sin(2 * M_PI * frequency * time)) / M_PI;
                    break;
            }
            
            // Convert to 16-bit PCM
            samples.push_back(static_cast<sf::Int16>(value * 30000));
        }
        
        return samples;
    }
};
```

### Audio Library
- **Shoot**: Quick square wave burst (high frequency)
- **Hit**: Short sine wave with quick decay (medium frequency)
- **Enemy Spawn**: Descending tone sequence
- **Victory**: Ascending major chord arpeggio
- **Defeat**: Descending minor chord
- **Background**: Simple 4-note repeating melody

## Minimal Resource Requirements (Unavoidable)

### 1. Font File (1 Required, ~50KB)
**Why SFML Requires This**: `sf::Text` objects need external font files
**Solutions**:
- Use system font (Arial/Helvetica) - platform dependent
- Include tiny bitmap font (50KB max)
- Generate font texture atlas programmatically (complex)

**Recommendation**: Include a single small bitmap font like `ChillBitmap_7px.ttf` (78KB)

### 2. JSON Configuration Files (Keep These)
```json
// towers.json - Carrot types and stats
{
    "carrots": [
        {
            "name": "Basic Carrot",
            "damage": 25,
            "range": 3,
            "cost": 10,
            "color": "#FF8C00",
            "size": 1.0
        },
        {
            "name": "Golden Carrot", 
            "damage": 50,
            "range": 4,
            "cost": 25,
            "color": "#FFD700",
            "size": 1.2
        }
    ]
}
```

### 3. Build Dependencies (Identical to Pixnights)
- **SFML 2.6.1**: Graphics, audio, window management
- **nlohmann/json**: JSON parsing (already auto-downloads)
- **CMake**: Build system
- **C++17**: Language standard

## Implementation Roadmap

### Week 1: Core Infrastructure
- [ ] Create `ProceduralAssetGenerator` to replace `AssetManager`
- [ ] Implement `ShapeFactory` for all visual elements
- [ ] Create `ToneGenerator` for audio synthesis
- [ ] Modify `Combat.cpp` to use generated assets
- [ ] Test basic rendering with shapes

### Week 2: Game Elements
- [ ] Generate carrot tower variants (basic, advanced, elite)
- [ ] Create enemy pest shapes (aphids, caterpillars, beetles)
- [ ] Implement projectile visuals (seeds, juice, spores)
- [ ] Generate map tiles and environment
- [ ] Add basic animations (growth, movement, destruction)

### Week 3: Audio System
- [ ] Implement waveform generator
- [ ] Create shooting sound effects
- [ ] Add enemy spawn and hit sounds
- [ ] Generate background music loops
- [ ] Implement dynamic audio mixing

### Week 4: Polish & Balance
- [ ] Add particle effects for explosions
- [ ] Implement screen shake and visual feedback
- [ ] Create dynamic difficulty scaling
- [ ] Add save/load for high scores
- [ ] Optimize performance and memory usage

## Technical Challenges & Solutions

### Challenge 1: Visual Variety
**Problem**: Procedural graphics may look repetitive
**Solution**: 
- Color variation using HSL color space
- Size scaling based on game stats
- Simple pattern overlays using mathematical functions
- Rotation and positioning randomization

### Challenge 2: Audio Quality
**Problem**: Simple waveforms sound artificial
**Solution**:
- Layer multiple waveforms (e.g., sine + square for richness)
- Apply ADSR envelopes (Attack, Decay, Sustain, Release)
- Use harmonic frequencies for more natural sounds
- Implement basic reverb using delay

### Challenge 3: Performance
**Problem**: Real-time generation may cause frame drops
**Solution**:
- Cache generated assets in memory
- Use object pooling for frequently created/destroyed items
- Implement level-of-detail for distant objects
- Pre-generate common variations at startup

### Challenge 4: File Size Optimization
**Problem**: Executable size might increase with generation code
**Solution**:
- Use compile-time optimization for simple shapes
- Implement efficient waveform caching
- Minimize template instantiations
- Use procedural compression for similar assets

## Resource Size Comparison
- **Pixnights Current**: ~14MB (65 image files + 6 JSON files)
- **Carrot Defense Target**: ~200KB (1 font + 3-4 JSON files + code)
- **Reduction**: 98.5% smaller footprint
- **Executable Size**: Likely 2-3MB (vs 500KB for Pixnights)

## Success Metrics
1. **Zero External Image Files**: All visuals generated by code
2. **Zero External Audio Files**: All sounds synthesized programmatically  
3. **Gameplay Parity**: Same tower defense mechanics as Pixnights
4. **Performance**: 60 FPS maintained on target hardware
5. **File Size**: Under 500KB total assets, under 5MB executable

## Risk Assessment
- **Low Risk**: Core gameplay mechanics, basic shape rendering
- **Medium Risk**: Audio synthesis quality, complex animations
- **High Risk**: Visual appeal compared to pixel art, audio variety

## Conclusion
This project is **highly feasible** and would be an excellent demonstration of procedural generation capabilities. The Pixnights codebase provides a solid foundation, and SFML's capabilities are well-suited for this approach. The main trade-off is visual/audio sophistication vs. file size and technical demonstration value.

**Recommendation**: Proceed with implementation, focusing on creating visually distinct and appealing procedural assets through clever use of color, animation, and particle effects.