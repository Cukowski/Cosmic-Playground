#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "GravitySource.h"
#include "Particle.h"
#include <vector>

class Renderer {
public:
    static void renderParticles(sf::RenderWindow& window, const std::vector<Particle>& particles, bool showTrail, bool showGlow);
    static void renderGravitySources(sf::RenderWindow& window, const std::vector<GravitySource>& sources);
    static void renderGlow(sf::RenderWindow& window, const Particle& particle);
};

#endif // RENDERER_H
