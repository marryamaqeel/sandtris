#include "grid.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Particle.hpp"
#include <vector>
#include <queue>

grid::grid(int w, int h) : GameObject(100,50)
{
    width = w;
    height = h;
    cell = new Particle[width * height];
    for (int i = 0; i < width*height; i++)
    {
        cell[i].id = 0;
    }
    

}

void grid::setParticle(int x , int y , int id , sf::Color color,sf::Color baseColor)
{
    if ((x>= 0 && x < width) && (y>=0 && y < height))
    {
        int index = (y * width) + x;
        cell[index].color = color;
        cell[index].id = id;
        cell[index].baseColor = baseColor;
    }
    else
    {
        return;
    }
}

int grid::getParticleID(int x, int y)const
{
    if( x>=0 && x <width && y>= 0 && y < height)
    {
        int index = (y * width) + x;
        return cell[index].id;
    }
    else
    {
        return 2;
    }
}
grid::~grid()
{
    delete[] cell;
}

void  grid:: draw(sf::RenderWindow& window)
{
    sf::RectangleShape rectangle;
    float cellsize = 4.0f;
    rectangle.setSize(sf::Vector2f{cellsize, cellsize}); // making sand 4x4 

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width) + x;
            if (cell[index].id == 1 || cell[index].id == 3)
            {
                rectangle.setFillColor(cell[index].color);
                float x_cood = (x*cellsize) + getX();
                float y_cood = (y*cellsize) + getY();
                rectangle.setPosition({x_cood, y_cood});
                window.draw(rectangle);
            }
            // if (cell[index].id==3)
            // {

            // }
        }
        
    }
}

void grid::updatePhysics() // falling sand simulator cellular automata
{
    
    for (int y = height - 2; y >= 0 ; y--) // h - 2 bcz h - 1 is already floor cant go any further
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y*width) + x;
            if (cell[index].id == 1)
            {
                // use random rand() % 2 to decide left or right
                if (getParticleID(x,y+1) == 0) // down (gravity)
                {
                    setParticle(x,y+1,cell[index].id , cell[index].color,cell[index].baseColor);
                    cell[index].id = 0;
                }
                else if(getParticleID(x - 1, y + 1) == 0) // slide left (if space)
                {
                    setParticle(x-1,y+1,cell[index].id , cell[index].color,cell[index].baseColor);
                    cell[index].id = 0;
                }
                else if (getParticleID(x + 1, y + 1) == 0) // right slide (if space)
                {
                    setParticle(x+1,y+1,cell[index].id , cell[index].color,cell[index].baseColor);
                    cell[index].id = 0;
                }

            }
        }
        
    }
    
}

int grid::clearLines()
{
    int totalCleared = 0;

    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false)); // every pixel on grid is false

    // Directions for checking neighbors (Up, Down, Left, Right)
    int dirX[] = {0, 0, -1, 1}; 
    int dirY[] = {-1, 1, 0, 0};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width) + x;
            
            // Skip if not sand, or if we already checked it
            if (cell[index].id != 1 || visited[x][y]) continue;

            sf::Color targetColor = cell[index].baseColor;
            std::vector<sf::Vector2i> currentGroup; // store all we need to remove
            std::queue<sf::Vector2i> q; // will check if same color it will pop it in current group

            // NEW: Track if this specific blob touches the walls
            bool touchesLeftWall = false;
            bool touchesRightWall = false;

            // Start Flood Fill
            q.push({x, y});
            visited[x][y] = true;

            while (!q.empty())
            {
                sf::Vector2i curr = q.front();
                q.pop();
                currentGroup.push_back(curr);

                // If this particle is on the left edge, mark true
                if (curr.x == 0) touchesLeftWall = true;
                
                // If this particle is on the right edge, mark true
                if (curr.x == width - 1) touchesRightWall = true;

                for (int i = 0; i < 4; i++)
                {
                    int nx = curr.x + dirX[i];
                    int ny = curr.y + dirY[i];

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        int nIndex = (ny * width) + nx;
                        
                        // If unvisited, is sand, and has the exact SAME BASE COLOR
                        if (!visited[nx][ny] && 
                            cell[nIndex].id == 1 && 
                            cell[nIndex].baseColor == targetColor)
                        {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }

            // NEW CONDITION: Does this single blob of color touch BOTH walls?
            if (touchesLeftWall && touchesRightWall)
            {
                for (const auto& p : currentGroup)
                {
                    int pIndex = (p.y * width) + p.x;
                    cell[pIndex].id = 3; // Turn back into empty space
                    cell[pIndex].color = sf::Color::White;
                    cell[pIndex].timer = 0.2;
                }
                totalCleared += currentGroup.size();
            }
        }
    }
    
    // Returns how many sand particles were cleared for your score
    return totalCleared;
}
void grid::updateTimers(float dt)
{
    for (int i = 0; i < width * height; i++)
    {
        if (cell[i].id == 3) // If it is in the "dying" white state
        {
            cell[i].timer -= dt; // Count down
            
            if (cell[i].timer <= 0.0f)
            {
                cell[i].id = 0; // Timer finished, make it disappear
            }
        }
    }
}

bool grid::checkGameOver() const
{
    // Check every cell in row 5 (near the top)
    for (int x = 0; x < width; x++) 
    {
        if (getParticleID(x, 5) == 1) 
        {
            return true; // Sand touched the danger zone!
        }
    }
    return false; // We are safe
}