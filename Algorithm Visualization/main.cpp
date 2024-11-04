#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BAR_WIDTH = 2;
const int VISUALIZATION_DELAY_MS = .01;//change for speed

void drawArray(sf::RenderWindow& window, const std::vector<int>& array) {
    window.clear();
    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, array[i]));
        bar.setFillColor(sf::Color::Green);
        bar.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - array[i]);
        window.draw(bar);
    }
    window.display();
}

void quickSort(std::vector<int>& array, int low, int high, sf::RenderWindow& window) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (array[j] < pivot) {
                i++;
                std::swap(array[i], array[j]);
                drawArray(window, array);
                sf::sleep(sf::milliseconds(VISUALIZATION_DELAY_MS));
            }
        }
        std::swap(array[i + 1], array[high]);
        drawArray(window, array);
        sf::sleep(sf::milliseconds(VISUALIZATION_DELAY_MS));
        quickSort(array, low, i, window);
        quickSort(array, i + 2, high, window);
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    const int ARRAY_SIZE = WINDOW_WIDTH / BAR_WIDTH;
    std::vector<int> array(ARRAY_SIZE);
    for (int& value : array) {
        value = std::rand() % (WINDOW_HEIGHT - 20);
    }
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sort Visualization");
    drawArray(window, array);
    quickSort(array, 0, ARRAY_SIZE - 1, window);
    sf::sleep(sf::seconds(3));
    return 0;
}
