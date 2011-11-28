#include "GameOfLife.h"

GameOfLife::GameOfLife(const int w, const int h): width(w), height(h) {
    grid = new bool*[width];
    tempGrid = new bool*[width];
    
    for (size_t i = 0; i < width; ++i) {
        grid[i] = new bool[height];
        tempGrid[i] = new bool[height];
    }
    
    xdomain = new int [3];
    ydomain = new int [3];
    
    srand((unsigned)time(NULL));
};

GameOfLife::~GameOfLife() {
    for (size_t i = 0; i < width; ++i) {
        delete [] grid[i];
        delete [] tempGrid[i];
    }
    
    delete [] grid;
    delete [] tempGrid;
    
    delete [] xdomain;
    delete [] ydomain;
}

void GameOfLife::randomInit(const double probability) {      
	for(size_t i = 0; i < width; ++i) {
		for(size_t j = 0; j < height; ++j) {
            double r = (double)rand() / RAND_MAX;
			grid[i][j] = (r < probability);
		}
	}
}

void GameOfLife::iterate() {
    for (size_t i = 0; i < width; ++i) {
		for(size_t j = 0; j < height; ++j) {
            int neighbors = countNeighbors(i, j);
			
			if (grid[i][j] == true) {
				if (neighbors == 2 || neighbors == 3) {
					// organism survives 
					tempGrid[i][j] = true;
				}
				else {
					// organism dies
					tempGrid[i][j] = false;
				}
			} 
			else {
				if (neighbors == 3) {
					// organism is born
					tempGrid[i][j] = true;
				} 
				else {
					// continues empty
					tempGrid[i][j] = false;
				}
			}
        }
    }
    
    bool** t = grid;
    grid = tempGrid;
    tempGrid = t;
}

int GameOfLife::countNeighbors(const int x, const int y) {
	int neighbors = 0;

	xdomain[0] = (x == 0 ? width - 1: x - 1);
	xdomain[1] = x;
	xdomain[2] = (x == width - 1 ? 0 : x + 1);
	
	ydomain[0] = (y == 0 ? height - 1: y - 1);
	ydomain[1] = y;
	ydomain[2] = (y == height - 1 ? 0 : y + 1);
	
	for(size_t i = 0; i < 3; ++i) {
		for(size_t j = 0; j < 3; ++j) {
            if (!(xdomain[i] == x && ydomain[j] == y)) {
                if (grid[xdomain[i]][ydomain[j]]) {
                    ++neighbors;
                }
            }
		}
	}
	
	return neighbors;
}

bool GameOfLife::organismAt(const int x, const int y) {
    return grid[x][y];
}
