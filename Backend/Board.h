#include <iostream>
#include <vector>
#include <queue>
#include "Cell.h"

#pragma once

using namespace std;

enum class GameStatus {
    Going,
    Win,
    Lose
};


class Board {
    int rows;
    int cols;
    vector<vector<Cell>> cells;
    GameStatus status;
    vector<int>dx = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    vector<int>dy = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
public:
    Board(int numRows, int numCols, int numMines);
    Board(vector<vector<int>> pole);
    void recreate();
    void plantMines(int numMines);
    void calculateBombNumberNear();
    bool inBoard(int x, int y);
    bool isVisible(int x, int y);
    bool pick(int x, int y);
    int numberOfBombNear(int x, int y);
    bool markBomb(int x, int y);
    bool isFlagInCell(int x, int y);
    GameStatus getStatus(){return status;}
    void setStatus(GameStatus s){status = s;}
    void win();
};
