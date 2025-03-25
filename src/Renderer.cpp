#include "Renderer.h"

void Renderer::renderParticles(sf::RenderWindow& window, const std::vector<Particle>& particles, bool showTrail, bool showGlow) {
    for (const auto& particle : particles) {
        particle.render(window, showTrail);
        if (showGlow) {
            renderGlow(window, particle);
        }
    }
}

void Renderer::renderGravitySources(sf::RenderWindow& window, const std::vector<GravitySource>& sources) {
    for (const auto& source : sources) {
        source.render(window);
    }
}

void Renderer::renderGlow(sf::RenderWindow& window, const Particle& particle) {
    // A gentle glow: concentric circles to evoke a cosmic radiance
    sf::CircleShape glow;
    glow.setFillColor(sf::Color(255, 255, 255, 128));
    glow.setRadius(particle.getRadius() * 2);
    glow.setOrigin(glow.getRadius(), glow.getRadius());
    glow.setPosition(particle.getPosition());
    window.draw(glow);

    for (int i = 1; i < 5; i++) {
        glow.setRadius(particle.getRadius() * (2 + i * 0.5f));
        glow.setFillColor(sf::Color(255, 255, 255, 128 - i * 32));
        window.draw(glow);
    }
}
