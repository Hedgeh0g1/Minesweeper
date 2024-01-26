//
// Created by user on 12/22/2023.
//

#ifndef CVICENIE12_CELL_H
#define CVICENIE12_CELL_H


class Cell {
private:
    bool isMine;
    bool isVisible;
    int adjacentMines;
    bool flag;

public:
    Cell() : isMine(false), isVisible(false), adjacentMines(0), flag(false) {}

    void setMine() { isMine = true;}

    bool hasMine() const { return isMine;}

    bool isCellVisible() const { return isVisible; }

    void makeVisible() { isVisible = true;}

    int getAdjacentMines() const { return adjacentMines;}

    void incrementAdjacentMines() { adjacentMines++; }

    bool isFlag(){return flag;}

    void setFlag(bool f){flag = f;}
};


#endif //CVICENIE12_CELL_H
