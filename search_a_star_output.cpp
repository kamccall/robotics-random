#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

// Map object class
class Map {
public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<int>> grid = {{ 0, 1, 0, 0, 0, 0 },
                                { 0, 1, 0, 0, 0, 0 },
                                { 0, 1, 0, 0, 0, 0 },
                                { 0, 1, 0, 0, 0, 0 },
                                { 0, 0, 0, 1, 1, 0 }};
    vector<vector<int>> heuristic = {{ 9, 8, 7, 6, 5, 4 },
                                     { 8, 7, 6, 5, 4, 3 },
                                     { 7, 6, 5, 4, 3, 2 },
                                     { 6, 5, 4, 3, 2, 1 },
                                     { 5, 4, 3, 2, 1, 0 }};
};

// Planner object class
class Planner : Map {
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
    for (int i = 0; i < Vec.size(); ++i) 
    {
        for (int j = 0; j < Vec[0].size(); ++j) 
        {
            cout << Vec[i][j] << ' ';
        }
        cout << endl;
    }
}

// search function to implement a*star using h, g and f functions
void search(Map map, Planner planner)
{
    // create closed 2 array filled with 0s and first element 1
    vector<vector<int>> closed(map.mapHeight, vector<int>(map.mapWidth));
    closed[planner.start[0]][planner.start[1]] = 1;

    // create expand array filled with -1
    vector<vector<int>> expand(map.mapHeight, vector<int>(map.mapWidth, -1));

    // create action array filled with -1
    vector<vector<int>> action(map.mapHeight, vector<int>(map.mapWidth, -1));

    // defined the quadruplet values
    int x = planner.start[0];
    int y = planner.start[1];
    int g = 0;
    int f = g + map.heuristic[x][y];

    // store the expansions
    vector<vector<int>> open;
    open.push_back({ f, g, x, y });

    // flags and counters
    bool found  = false;
    bool resign = false;
    int count   = 0;

    int x2;
    int y2;

    // while I am still searching for the goal and the problem is solvable
    while (!found && !resign) 
    {
        // Resign if no values in the open list and you can't expand anymore
        if (open.size() == 0) 
        {
            resign = true;
            cout << "Failed to reach a goal" << endl;
        }
        // Keep expanding
        else 
        {
            // remove from open list
            sort(open.begin(), open.end());
            reverse(open.begin(), open.end());
            vector<int> next;
            // stored the popped value into next
            next = open.back();
            open.pop_back();

            g = next[1];
            x = next[2];
            y = next[3];

            // fill the expand vectors with count
            expand[x][y] = count;
            count += 1;

            // Check if we reached the goal:
            if (x == planner.goal[0] && y == planner.goal[1]) 
            {
                found = true;
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
                            int f2 = g2 + map.heuristic[x2][y2];
                            open.push_back({ f2, g2, x2, y2 });
                            closed[x2][y2] = 1;
                            action[x2][y2] = i;
                        }
                    }
                }
            }
        }
    }
    // print the expansion List
    print2DVector(expand);

    // find the path with robot orientation
    vector<vector<string>> policy(map.mapHeight, vector<string>(map.mapWidth, "-"));

    // going backward to populate policy matrix
    x = planner.goal[0];
    y = planner.goal[1];
    policy[x][y] = '*';

    while (x != planner.start[0] or y != planner.start[1]) 
    {
        x2 = x - planner.movements[action[x][y]][0];
        y2 = y - planner.movements[action[x][y]][1];
        policy[x2][y2] = planner.movements_arrows[action[x][y]];
        x = x2;
        y = y2;
    }

    // print the path with arrows
    cout << endl;
    print2DVector(policy);
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
