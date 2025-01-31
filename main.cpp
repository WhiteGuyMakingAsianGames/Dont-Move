#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

class Player {
public:
    Player(b2World& world) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(400.0f, 300.0f);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(10.0f, 10.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
    }

    void draw(sf::RenderWindow& window) {
        sf::RectangleShape shape(sf::Vector2f(20.0f, 20.0f));
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(10.0f, 10.0f);
        shape.setPosition(body->GetPosition().x, body->GetPosition().y);
        window.draw(shape);
    }

private:
    b2Body* body;
};

class Obstacle {
public:
    Obstacle(b2World& world, float x, float y) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(x, y);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape staticBox;
        staticBox.SetAsBox(20.0f, 20.0f);

        body->CreateFixture(&staticBox, 0.0f);
    }

    void draw(sf::RenderWindow& window) {
        sf::RectangleShape shape(sf::Vector2f(40.0f, 40.0f));
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(20.0f, 20.0f);
        shape.setPosition(body->GetPosition().x, body->GetPosition().y);
        window.draw(shape);
    }

private:
    b2Body* body;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Don't Move");
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    Player player(world);
    std::vector<Obstacle> obstacles;
    obstacles.emplace_back(world, 200.0f, 300.0f);
    obstacles.emplace_back(world, 600.0f, 300.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        world.Step(1.0f / 60.0f, 6, 2);

        player.draw(window);
        for (auto& obstacle : obstacles) {
            obstacle.draw(window);
        }

        window.display();
    }

    return 0;
}
