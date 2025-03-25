#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "GravitySource.h"

#define TRAIL_LENGTH 100

class Particle {
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape shape;
    std::deque<sf::Vector2f> trail;
    sf::Color baseColor; // Dynamic color chosen by the user

public:
    Particle(float pos_x, float pos_y, float vel_x, float vel_y);

    void updatePhysics(const std::vector<GravitySource>& sources, float dt);
    void render(sf::RenderWindow& window, bool showTrail) const;
    void setColor(sf::Color col);
    void setSize(float size); // New setter for particle size
    void updateTrail();
    float getRadius() const;
    sf::Vector2f getPosition() const { return pos; }
};

#endif // PARTICLE_H
