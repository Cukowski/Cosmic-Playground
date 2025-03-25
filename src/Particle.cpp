#include "Particle.h"
#include <cmath>

Particle::Particle(float pos_x, float pos_y, float vel_x, float vel_y)
    : pos(pos_x, pos_y), vel(vel_x, vel_y), baseColor(sf::Color::Blue) {
    shape.setRadius(4.0f);
    shape.setOrigin(4.0f, 4.0f);
    shape.setPosition(pos);
    shape.setFillColor(baseColor);
}

void Particle::updatePhysics(const std::vector<GravitySource>& sources, float dt) {
    for (const auto& source : sources) {
        sf::Vector2f diff = source.getPos() - pos;
        float distanceSquared = diff.x * diff.x + diff.y * diff.y;
        if (distanceSquared < 50.0f) continue; // Avoid singularity

        float distance = std::sqrt(distanceSquared);
        sf::Vector2f normalizedDiff = diff / distance;
        float force = source.getStrength() / distanceSquared;
        sf::Vector2f acceleration = force * normalizedDiff;
        vel += acceleration * dt;
    }
    pos += vel * dt;
    updateTrail();
}

void Particle::updateTrail() {
    trail.push_front(pos);
    if (trail.size() > TRAIL_LENGTH) {
        trail.pop_back();
    }
}

void Particle::render(sf::RenderWindow& window, bool showTrail) const {
    if (showTrail && trail.size() > 1) {
        sf::VertexArray trailLines(sf::LinesStrip, trail.size());
        for (size_t i = 0; i < trail.size(); i++) {
            float alpha = 255 * (static_cast<float>(i) / trail.size());
            trailLines[i].position = trail[i];
            trailLines[i].color = sf::Color(baseColor.r, baseColor.g, baseColor.b, static_cast<sf::Uint8>(alpha));
        }
        window.draw(trailLines);
    }
    sf::CircleShape shapeCopy = shape;
    shapeCopy.setPosition(pos);
    shapeCopy.setFillColor(baseColor);
    window.draw(shapeCopy);
}

void Particle::setColor(sf::Color col) {
    baseColor = col;
}

void Particle::setSize(float size) {
    shape.setRadius(size);
    shape.setOrigin(size, size); // Keep the circle centered
}


float Particle::getRadius() const {
    return shape.getRadius();
}
