#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WIDTH = 800;
const int HEIGHT = 600;

class Player {
public:
    Player(int x, int y) : x(x), y(y) {}

    void draw() const {
        std::cout << "Player at (" << x << ", " << y << ")\n";
    }

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
};

class Obstacle {
public:
    Obstacle(int x, int y) : x(x), y(y) {}

    void draw() const {
        std::cout << "Obstacle at (" << x << ", " << y << ")\n";
    }

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
};

void draw(const Player& player, const std::vector<Obstacle>& obstacles) {
    player.draw();
    for (const auto& obstacle : obstacles) {
        obstacle.draw();
    }
}

int main() {
    std::srand(std::time(nullptr));

    Player player(WIDTH / 2, HEIGHT / 2);
    std::vector<Obstacle> obstacles;
    for (int i = 0; i < 5; ++i) {
        obstacles.emplace_back(std::rand() % WIDTH, std::rand() % HEIGHT);
    }

    bool running = true;
    while (running) {
        // Game logic and rendering
        draw(player, obstacles);

        // Simulate game loop delay
        std::cout << "Press Enter to continue or 'q' to quit: ";
        char input;
        std::cin.get(input);
        if (input == 'q') {
            running = false;
        }
    }

    return 0;
}
