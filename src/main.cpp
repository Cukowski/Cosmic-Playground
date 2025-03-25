#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "GravitySource.h"
#include "Particle.h"
#include "Renderer.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Screen dimensions
#define WIDTH 1600
#define HEIGHT 1000

// Define our game states as if charting new cosmic eras
enum class GameState {
    MAIN_MENU,
    SIMULATION,
    EXIT
};

sf::Color generateRandomColor() {
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity Simulation Game");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    srand(static_cast<unsigned int>(time(nullptr)));

    GameState gameState = GameState::MAIN_MENU;

    // Containers for our celestial entities
    std::vector<GravitySource> gravitySources;
    std::vector<Particle> particles;
    const int numParticles = 2000;

    // Simulation settings—each parameter a note in our gravitational symphony
    bool showGlow = false;
    bool showTrails = true;
    float particleColor[3] = { 173.0f / 255.0f, 216.0f / 255.0f, 230.0f / 255.0f };
    bool randomColor = false;
    float gravityColor[3] = { 1.0f, 1.0f, 1.0f };
    float gravityStrength = 7000.0f;
    float gravityRadius = 10.0f;
    float particleSpeed = 30.0f;  // Initial particle speed
    float particleSize  = 4.0f;   // Particle size (radius)

    // A simple score: count the gravity sources you add—the more, the merrier the cosmos
    int score = 0;

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            // In SIMULATION mode, a left-click births a new gravity source into existence
            if (gameState == GameState::SIMULATION && event.type == sf::Event::MouseButtonPressed) {
                if (!ImGui::GetIO().WantCaptureMouse && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f clickPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    GravitySource newSource(clickPos.x, clickPos.y, gravityStrength);
                    newSource.setRadius(gravityRadius);
                    sf::Color srcColor(
                        static_cast<sf::Uint8>(gravityColor[0] * 255),
                        static_cast<sf::Uint8>(gravityColor[1] * 255),
                        static_cast<sf::Uint8>(gravityColor[2] * 255)
                    );
                    newSource.setColor(srcColor);
                    gravitySources.push_back(newSource);
                    score++; // Each new gravity source adds to your cosmic score
                }
            }
        }

        float dt = deltaClock.restart().asSeconds();
        ImGui::SFML::Update(window, sf::seconds(dt));

        window.clear();

        // --- MAIN MENU STATE ---
        if (gameState == GameState::MAIN_MENU) {
            ImGui::Begin("Main Menu");
            ImGui::Text("Welcome, traveler, to the cosmic dance of gravity.");
            ImGui::Text("Click 'Start Simulation' to craft your universe.");
            if (ImGui::Button("Start Simulation")) {
                // Reset and initialize the simulation: a new universe begins
                gravitySources.clear();
                particles.clear();
                GravitySource central(WIDTH / 2, HEIGHT / 2, gravityStrength);
                central.setRadius(gravityRadius);
                sf::Color centerColor(
                    static_cast<sf::Uint8>(gravityColor[0] * 255),
                    static_cast<sf::Uint8>(gravityColor[1] * 255),
                    static_cast<sf::Uint8>(gravityColor[2] * 255)
                );
                central.setColor(centerColor);
                gravitySources.push_back(central);

                // Spawn particles that will orbit and illuminate the cosmic stage
                for (int i = 0; i < numParticles; i++) {
                    float variation = 0.2f + (0.1f / numParticles) * i;
                    particles.emplace_back(600, 700, particleSpeed, variation);
                    particles.back().setSize(particleSize); // set initial size
                }
                score = 1; // Reset score as the new universe awakens
                gameState = GameState::SIMULATION;
            }
            if (ImGui::Button("Exit")) {
                window.close();
            }
            ImGui::End();
        }
        // --- SIMULATION STATE ---
        else if (gameState == GameState::SIMULATION) {
            ImGui::SetNextWindowSize(ImVec2(500, 350));  // Set a comfortable size
            ImGui::Begin("Simulation Settings");
            ImGui::PushTextWrapPos(400);  // Wrap text at 400 pixels
            ImGui::Text("Adjust the simulation parameters to witness the cosmic dance unfold...");
            ImGui::PopTextWrapPos();
            ImGui::Checkbox("Show Glow", &showGlow);
            ImGui::Checkbox("Show Particle Trails", &showTrails);
            ImGui::ColorEdit3("Particle Color", particleColor);
            ImGui::Checkbox("Random Particle Colors", &randomColor);
            ImGui::ColorEdit3("Gravity Source Color", gravityColor);
            ImGui::SliderFloat("Gravity Strength", &gravityStrength, 1000.0f, 15000.0f);
            ImGui::SliderFloat("Gravity Radius", &gravityRadius, 5.0f, 75.0f);
            ImGui::SliderFloat("Particle Speed", &particleSpeed, 10.0f, 100.0f);
            ImGui::SliderFloat("Particle Size", &particleSize, 2.0f, 20.0f);
            ImGui::Text("Gravity Sources Added: %d", score);
            if (ImGui::Button("Remove Last Gravity Source") && !gravitySources.empty()) {
                gravitySources.pop_back();
                score--;
            }            
            if (ImGui::Button("Back to Main Menu")) {
                gameState = GameState::MAIN_MENU;
            }
            ImGui::End();

            // Update gravity sources with the current settings—each a shimmering note in the score
            sf::Color currentGravityColor(
                static_cast<sf::Uint8>(gravityColor[0] * 255),
                static_cast<sf::Uint8>(gravityColor[1] * 255),
                static_cast<sf::Uint8>(gravityColor[2] * 255)
            );
            for (auto& source : gravitySources) {
                source.setStrength(gravityStrength);
                source.setRadius(gravityRadius);
                source.setColor(currentGravityColor);
                source.update(dt);
            }

            // Update particles so they dance to the tune of gravity and light
            sf::Color currentParticleColor(
                static_cast<sf::Uint8>(particleColor[0] * 255),
                static_cast<sf::Uint8>(particleColor[1] * 255),
                static_cast<sf::Uint8>(particleColor[2] * 255)
            );
            for (auto& particle : particles) {
                // Update the size in case the slider changed it
                particle.setSize(particleSize);
                
                if (randomColor)
                    particle.setColor(generateRandomColor());
                else
                    particle.setColor(currentParticleColor);
                
                particle.updatePhysics(gravitySources, dt);
            }

            // Render the evolving cosmos
            Renderer::renderGravitySources(window, gravitySources);
            Renderer::renderParticles(window, particles, showTrails, showGlow);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
