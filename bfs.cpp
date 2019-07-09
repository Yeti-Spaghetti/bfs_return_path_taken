#include <bits/stdc++.h>
using namespace std;

class Maze{
private:
    bool found, begIsWall;
    int dimX, dimY, endX, endY;
    int **maze;
    string path;
    queue<int> xQueue, yQueue;
    queue<string> pQueue;
public:
    static int searchSteps;
    Maze(int startX, int startY, int ex, int ey){
        found = false;
        begIsWall = false;
        endX = ex;
        endY = ey;
        xQueue.push(startX);
        yQueue.push(startY);
        pQueue.push("");
    }

    // set maze dimensions && init to zero
    void set_maze(int x, int y){
        dimX = x;
        dimY = y;
        maze = new int*[dimY];
        for (int i = 0; i < dimY; i++){
            maze[i] = new int[dimX];
            for (int j = 0; j < dimX; j++){
                maze[i][j] = 0;
            }
        }
    }

    // set walls
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

    void solve_maze(){
        // check if start point is a wall
        if (maze[yQueue.front()][xQueue.front()] == 1){
            cout << searchSteps << " " << 0 << endl;
            cout << 'X' << endl;
            return;
        }

        // iterative BFS
        while (!xQueue.empty()){
            int x = xQueue.front();
            int y = yQueue.front();
            path = pQueue.front();

            xQueue.pop();
			yQueue.pop();
            pQueue.pop();

            // if reach goal, print result and terminate function
            if (x == endX && y == endY){
                cout << searchSteps << " " << path.length() << endl;
                for (int i = 0; i < path.length(); i++){
                    if (i == path.length()-1){
                        cout << path[i] << endl;
                    } else {
                        cout << path[i] << " ";
                    }
                }
                found = true;
                return;

            // search for unexplored paths and add to queue
            } else {
                if (y < dimY-1){
                    if (maze[y+1][x] == 0){
                        searchSteps++;
                        xQueue.push(x);
                        yQueue.push(y+1);
                        pQueue.push(path+'D');
                        maze[y+1][x] = 1;
                    }
                }
                if (y > 0){
                    if (maze[y-1][x] == 0){
                        searchSteps++;
                        xQueue.push(x);
                        yQueue.push(y-1);
                        pQueue.push(path+'U');
                        maze[y-1][x] = 1;
                    }
                }
                
                if (x < dimX-1){
                    if (maze[y][x+1] == 0){
                        searchSteps++;
                        xQueue.push(x+1);
                        yQueue.push(y);
                        pQueue.push(path+'R');
                        maze[y][x+1] = 1;
                    }
                }
                if (x > 0){
                    if (maze[y][x-1] == 0){
                        searchSteps++;
                        xQueue.push(x-1);
                        yQueue.push(y);
                        pQueue.push(path+'L');
                        maze[y][x-1] = 1;
                    }
                }
            }
        }

        // if no valid path found
        if (!found){
            cout << searchSteps << " " << 0 << endl;
            cout << 'X' << endl;
        }
    }
};

// keep count of total number of steps taken
int Maze::searchSteps = 0;

int main(int argc, char* argv[]){
    // set start and goal positions
    Maze maze(stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));

    // set maze dimensions
    int dims[2];
    ifstream infile(argv[1]);
    string num = "";
    infile >> dims[0] >> dims[1];
    maze.set_maze(dims[0], dims[1]);
    
    // search and set walls
    int count = 0;
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
    
    maze.solve_maze();
    return 0;
}