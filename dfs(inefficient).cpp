#include <bits/stdc++.h>
using namespace std;

class Maze{
private:
    int dimX, dimY, endX, endY;
    int **maze;
    int minSteps;
    string minPath;
    queue<int> xQueue;
    queue<int> yQueue;
public:
    static int searchSteps;
    Maze(int startX, int startY, int ex, int ey){
        endX = ex;
        endY = ey;
        minSteps = INT_MAX;
        minPath = "";
        xQueue.push(startX);
        yQueue.push(startY);
    }

    // set up maze
    void set_maze(int x, int y){
        // set maze dimensions
        dimX = x;
        dimY = y;
        maze = new int*[dimY];
        for (int i = 0; i < dimY; i++){
            maze[i] = new int[dimX];
        }
    }

    // add walls
    void set_walls(int x, int y){
        maze[y][x] = 1;
    }

    // print maze
    void print_maze(){
        for (int i = 0; i < dimY; i++){
            for (int j = 0; j < dimX; j++){
                if (j == (dimX-1)){
                    cout << maze[i][j] << endl;
                } else {
                    cout << maze[i][j] << " ";
                }
            }
        }
    }

    void print_solution(){
        if (minSteps == INT_MAX){
            cout << searchSteps << " " << 0 << endl;
            cout << "X" << endl;
        } else {
            cout << searchSteps << " " << minSteps << endl;
            for (int i = 0; i < minPath.length(); i++){
                if (i == minPath.length()-1){
                    cout << minPath[i];
                } else {
                    cout << minPath[i] << " ";
                }
            }
        }
    }

    void solve_maze(string path, int steps){
        if (!xQueue.empty()){
            int x = xQueue.front();
            int y = yQueue.front();

            xQueue.pop();
			yQueue.pop();

            // if reach goal
            if (x == endX && y == endY){
                // cout << "Goal reached. Path: " << path << endl;
                if (steps < minSteps){
                    minSteps = steps;
                    minPath = path;  
                }
            } else if (steps < minSteps){
                // search next step
                if (y < dimY-1){
                    if (maze[y+1][x] == 0){
                        xQueue.push(x);
                        yQueue.push(y+1);
                        searchSteps++;
                        maze[y][x] = 1;
                        solve_maze(path + 'D', steps+1);
                        maze[y][x] = 0;
                    }
                }
                if (y > 0){
                    if (maze[y-1][x] == 0){
                        xQueue.push(x);
                        yQueue.push(y-1);
                        searchSteps++;
                        maze[y][x] = 1;
                        solve_maze(path + 'U', steps+1);
                        maze[y][x] = 0;
                    }
                }

                if (x < dimX-1){
                    if (maze[y][x+1] == 0){
                        xQueue.push(x+1);
                        yQueue.push(y);
                        searchSteps++;
                        maze[y][x] = 1;
                        solve_maze(path + 'R', steps+1);
                        maze[y][x] = 0;
                    }
                }
                if (x > 0){
                    if (maze[y][x-1] == 0){
                        xQueue.push(x-1);
                        yQueue.push(y);
                        searchSteps++;
                        maze[y][x] = 1;
                        solve_maze(path + 'L', steps+1);
                        maze[y][x] = 0;
                    }
                }
            }
        }
    }
    

    // destructor goes here
    ~Maze(){
    }
};

int Maze::searchSteps = 0;

int main(int argc, char* argv[]){
    // set start and goal positions
    Maze maze(stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));

    // set maze dimensions
    int count;
    int dims[2];
    ifstream infile(argv[1]);
    string num = "";
    if (infile.is_open() && infile.good()){
        while (infile >> num && count < 2){
            dims[count] = stoi(num);
            count++;
        }
    }
    maze.set_maze(dims[0], dims[1]);
    
    // search for walls
    count = 0;
    infile.clear();
    infile.seekg(0, ios::beg);
    string dummyLine;
    getline(infile, dummyLine);
    while (infile >> num){
        if (num == "1"){
            int tempX = count % dims[0];
            int tempY = count / dims[0];
            maze.set_walls(tempX, tempY);
        }
        count++;
    }
    
    maze.solve_maze("", 0);
    maze.print_solution();
    return 0;
}