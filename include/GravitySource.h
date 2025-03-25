#pragma once
#ifndef GRAVITYSOURCE_H
#define GRAVITYSOURCE_H

#include <SFML/Graphics.hpp>

class GravitySource {
private:
    sf::Vector2f pos;
    float strength;
    float radius;
    sf::CircleShape shape;
    sf::Vector2f velocity; // For orbital movement
    sf::Color baseColor;

public:
    GravitySource(float pos_x, float pos_y, float strength, sf::Vector2f vel = { 0, 0 });

    void update(float dt); // Update position for orbital motion
    void render(sf::RenderWindow& window) const;

    sf::Vector2f getPos() const;
    float getStrength() const;
    void setStrength(float newStrength);
    void setRadius(float newRadius);
    float getRadius() const;
    void setColor(sf::Color col);
};

#endif // GRAVITYSOURCE_H
