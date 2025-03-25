#include "GravitySource.h"

GravitySource::GravitySource(float pos_x, float pos_y, float strength, sf::Vector2f vel)
    : pos(pos_x, pos_y), strength(strength), velocity(vel), baseColor(sf::Color::White), radius(10.0f) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
    shape.setFillColor(baseColor);
}

void GravitySource::update(float dt) {
    pos += velocity * dt;
    shape.setPosition(pos);
}

void GravitySource::render(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f GravitySource::getPos() const {
    return pos;
}

float GravitySource::getStrength() const {
    return strength;
}

void GravitySource::setStrength(float newStrength) {
    strength = newStrength;
}

float GravitySource::getRadius() const {
    return radius;
}

void GravitySource::setRadius(float newRadius) {
    radius = newRadius;
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

void GravitySource::setColor(sf::Color col) {
    baseColor = col;
    shape.setFillColor(baseColor);
}
