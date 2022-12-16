#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

// Map object class
class Map 
{
public:
    const static int mapWidth  = 6;
    const static int mapHeight = 5;
    vector<vector<int>> grid   = {{ 0, 1, 0, 0, 0, 0 },
                                  { 0, 1, 0, 0, 0, 0 },
                                  { 0, 1, 0, 0, 0, 0 },
                                  { 0, 1, 0, 0, 0, 0 },
                                  { 0, 0, 0, 1, 1, 0 }};
};

// Planner object class
class Planner : Map 
{
public:
    int start[2] = { 0, 0 };
    int goal[2]  = { mapHeight - 1, mapWidth - 1 };
    int cost     = 1;

    string movements_arrows[4] = { "^", "<", "v", ">" };

    vector<vector<int>> movements{{ -1, 0 },
                                  { 0, -1 },
                                  { 1, 0 },
                                  { 0, 1 }};
};

// template function to print 2D vectors of any type
template <typename T>
void print2DVector(T Vec)
{
    for (int i = 0; i < Vec.size(); ++i) {
        for (int j = 0; j < Vec[0].size(); ++j) {
            cout << Vec[i][j] << ' ';
        }
        cout << endl;
    }
}

// search function that outputs final triplet value
void search(Map map, Planner planner)
{
    // location and status variables
    int g = 0;
    int x = planner.start[0];
    int y = planner.start[1];
    int x2;
    int y2;
    bool found;
    bool resign;
    
    // open and closed lists
    vector<vector<int>> closed(map.mapHeight, vector<int>(map.mapWidth));
    closed[planner.start[0]][planner.start[1]] = 1;
    
    vector<vector<int>>  open;
    open.push_back({g, x, y});
    
    while(!found && !resign)
    {
        if(open.size() == 0)
        {
            resign = true;
            cout << "we are done now...\n";
        }
        else
        {
            sort(open.begin(), open.end());
            reverse(open.begin(), open.end());
            vector<int> next;
            
            next = open.back();  // store popped value into next 
            open.pop_back();

            g = next[0];
            x = next[1];
            y = next[2];
            
            // check if we reached the goal
            if (x == planner.goal[0] && y == planner.goal[1]) 
            {
                found = true;
                cout << "[" << g << ", " << x << ", " << y << "]" << endl;
            }

            //else expand new elements
            else 
            {
                for (int i = 0; i < planner.movements.size(); i++) 
                {
                    x2 = x + planner.movements[i][0];
                    y2 = y + planner.movements[i][1];
                    if (x2 >= 0 && x2 < map.grid.size() && y2 >= 0 && y2 < map.grid[0].size()) 
                    {
                        if (closed[x2][y2] == 0 and map.grid[x2][y2] == 0) 
                        {
                            int g2 = g + planner.cost;
                            open.push_back({ g2, x2, y2 });
                            closed[x2][y2] = 1;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Search for the expansions
    search(map, planner);

    return 0;
}
