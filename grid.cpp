#include "grid.h"
#include <vector>
#include <queue>

using namespace std;

static const int CELL_SIZE = 8;

Grid::Grid(int w, int h) {
    width = w;
    height =h;
    cells = new Particle[width * height];
    for (int i = 0; i < width * height; i++) {
        cells[i] = Particle(); 
    }
}

Grid::~Grid() {
    delete[] cells;
}

void Grid::updatePhysics() {
    for (int y = height - 2; y >= 0; y--) {

        bool leftPriority = (y % 2 == 0);

        for (int x = 0; x < width; x++) {
            int idx = y * width + x;
            if (cells[idx].id == 0) 
                continue;

            int below = (y + 1) * width + x;
            int bLeft = (y + 1) * width + (x - 1);
            int bRight = (y + 1) * width + (x + 1);

            if (cells[below].id == 0) {
                swap(cells[idx], cells[below]);
            }
            else if (leftPriority) {
                if (x > 0 && cells[bLeft].id == 0) 
                    swap(cells[idx], cells[bLeft]);
                else if (x < width - 1 && cells[bRight].id == 0)
                    swap(cells[idx], cells[bRight]);
            }
            else {
                if (x < width - 1 && cells[bRight].id == 0) 
                    swap(cells[idx], cells[bRight]);
                else if (x > 0 && cells[bLeft].id == 0)
                    swap(cells[idx], cells[bLeft]);
            }
        }
    }
}

int Grid::clearLines() {
    int linesCleared = 0;
    for (int y = height - 1; y >= 0; y--) {
        bool isFull = true;
        for (int x = 0; x < width; x++) {
            if (cells[y * width + x].id == 0) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            linesCleared++;
            queue<pair<int, int>> q;
            vector<bool> visited(width * height, false);

            for (int x = 0; x < width; x++) {
                q.push({x, y});
                visited[y * width + x] = true;
            }

            while (!q.empty()) {
                pair<int, int> curr = q.front();
                q.pop();

                int cx = curr.first;
                int cy = curr.second;
                int currentID = cells[cy * width + cx].id;
                
                cells[cy * width + cx] = Particle();

                int dx[] = {0, 0, 1, -1};
                int dy[] = {1, -1, 0, 0};

                for (int i = 0; i < 4; i++) {
                    int nx = cx + dx[i];
                    int ny = cy + dy[i];

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        int nIdx = ny * width + nx;
                        if (!visited[nIdx] && cells[nIdx].id != 0 && cells[nIdx].id == currentID) {
                            visited[nIdx] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }
    return linesCleared;
}

void Grid::setParticle(int x, int y, int id, sf::Color color, sf::Color baseColor) {
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    int idx = y * width + x;
    cells[idx].id = id;
    cells[idx].color = color;
    cells[idx].baseColor = baseColor;
}

Particle Grid::getParticle(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return Particle();
    return cells[y * width + x];
}

void Grid::draw(sf::RenderWindow& window) {
    sf::RectangleShape rect(sf::Vector2f(CELL_SIZE - 1.f, CELL_SIZE - 1.f));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = y * width + x;
            if (cells[idx].id != 0) {
                rect.setFillColor(cells[idx].color);
                rect.setPosition({(float)x * CELL_SIZE, (float)y * CELL_SIZE});
                window.draw(rect);
            }
        }
    }
}