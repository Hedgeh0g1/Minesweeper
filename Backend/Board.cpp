#include <limits>
#include <utility>
#include "Board.h"
#include "NumberException.h"


Board::Board(int numRows, int numCols, int numMines) {
    if(numRows < 0 || numCols < 0 || numRows * numCols <= numMines){
        throw NumberException("Wrong input data");
    }
    this->rows = numRows;
    this->cols = numCols;
    this->cells.resize(numRows, vector<Cell>(numCols));
    status = GameStatus::Going;
    plantMines(numMines);
    calculateBombNumberNear();
}

Board::Board(vector<vector<int>> pole) {
    this->cells.resize(0);
    for(int i = 0;i<pole.size();i++){
        vector <Cell> mines;
        for(int j = 0;j<pole[0].size();j++){
            Cell c;
            if(pole[i][j] == 1){
                c.setMine();
            }
            mines.push_back(c);
        }
        this->cells.push_back(mines);
    }
    status = GameStatus::Going;
    this->rows = pole.size();
    this->cols = pole[0].size();
    calculateBombNumberNear();
}

void Board::recreate(){
    int mines = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j] = Cell();
            if(cells[i][j].hasMine())
                mines++;
        }
    }
    status = GameStatus::Going;
    plantMines(mines);
    calculateBombNumberNear();
}

void Board::plantMines(int numMines) {
    for (int i = 0; i < numMines; i++) {
        bool flag = true;
        while (flag) {
            int x = rand() % this->rows;
            int y = rand() % this->cols;
            if(!cells[x][y].hasMine()){
                flag = false;
                cells[x][y].setMine();
            }
        }
    }
}

void Board::calculateBombNumberNear() {
    for(int i = 0;i<this->rows;i++){
        for(int j = 0;j<this->cols;j++){
            if(!cells[i][j].hasMine()){
                for(int k = 0;k<dx.size();k++){
                    int x = dx[k] + i;
                    int y = dy[k] + j;
                    if(inBoard(x, y) && cells[x][y].hasMine()){
                        cells[i][j].incrementAdjacentMines();
                    }
                }
            }
        }
    }
}

bool Board::inBoard(int x, int y) const {
    if(x < 0 || y < 0)
        return false;
    if(x >= this->rows || y >= this->cols)
        return false;
    return true;
}

bool Board::isVisible(int x, int y) {
    if(!inBoard(x, y))
        return false;
    return cells[x][y].isCellVisible();
}

bool Board::pick(int x, int y) {
    if(!inBoard(x, y)) {
        throw NumberException("Wrong coordinates of point on board");
    }

    if(cells[x][y].hasMine()){
        setStatus(GameStatus::Lose);
        return false;
    }

    if(cells[x][y].isFlag()){
        return false;
    }
    if(cells[x][y].getAdjacentMines() == 0) {
        queue<pair<int, int >> sequence;
        sequence.push({x, y});
        while (!sequence.empty()) {
            pair<int, int> coordinates = sequence.front();
            int x = coordinates.first;
            int y = coordinates.second;
            sequence.pop();
            cells[x][y].makeVisible();
            for (int j = 0; j < 9; j++) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (nx >= 0 && nx < this->cols && ny >= 0 && ny < this->rows && !cells[nx][ny].isCellVisible()) {
                    if (!cells[nx][ny].hasMine() && cells[nx][ny].getAdjacentMines() == 0 && !cells[nx][ny].isFlag()) {
                        sequence.push({nx, ny});
                    } else {
                        if (!cells[nx][ny].hasMine() && !cells[nx][ny].isFlag()) {
                            cells[nx][ny].makeVisible();
                        }
                    }
                }
            }
        }
    }
    else{
        cells[x][y].makeVisible();
    }
    win();
    return true;
}

int Board::numberOfBombNear(int x, int y) {
    if(!inBoard(x, y)){
        throw NumberException("Wrong coordinates of point on board");
    }
    if(cells[x][y].isCellVisible())
        return cells[x][y].getAdjacentMines();
    return -1;
}

bool Board::markBomb(int x, int y) {
    if(!inBoard(x, y)){
        throw NumberException("Wrong coordinates of point on board");
    }

    if(cells[x][y].isCellVisible())
        return false;

    if(!cells[x][y].isFlag()){
        cells[x][y].setFlag(true);
    }
    else{
        cells[x][y].setFlag(false);
    }
    win();
    return true;
}

void Board::win(){
    if(status == GameStatus::Lose)
        return;
    for(int i = 0;i<this->rows;i++){
        for(int j = 0;j<this->cols;j++){
            if(cells[i][j].hasMine()){
                if(!cells[i][j].isFlag()){
                    return;
                }
            }
            else{
                if(!cells[i][j].isCellVisible())
                    return;
            }
        }
    }
    status = GameStatus::Win;
}

bool Board::isFlagInCell(int x, int y) {
    if(!inBoard(x, y)){
        throw NumberException("Wrong coordinates of point on board");
    }
    return cells[x][y].isFlag();
}

void Board::saveToFile(const string& filename){
    ofstream outFile(filename, ios::trunc);
    if(!outFile.is_open()){
        cerr << "Error of opening file\n";
        return;
    }
    outFile << this->rows << " " << this->cols << " " << 3 << "\n";
    for(int i = 0;i<this->rows;i++){
        for(int j = 0;j<this->cols;j++){
            if(cells[i][j].hasMine())
                outFile << '@';
            else
                outFile << '.';
        }
        outFile << "\n";
    }
    outFile.close();
}

Board::Board(string fileName) {
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        return;
    }
    if (!(inFile.is_open())) {
        cerr << "Impossible to open file with this name!" << endl;
        return;
    }
    int rows, cols, mines;
    if (!(inFile >> rows >> cols >> mines)) {
        cerr << "Error reading rows and cols from file!" << endl;
        inFile.close();
        return;
    }
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    int linesNumber = 0;
    vector<vector<Cell>> board;
    while (getline(inFile, line)) {
        if(line.size() != cols){
            throw NumberException("Wrong size of board");
        }
        vector <Cell> mines;
        for(int j = 0;j<line.size();j++){
            Cell c;
            if(line[j] == '@'){
                c.setMine();
            }
            mines.push_back(c);
        }
        board.push_back(mines);
        linesNumber++;
    }
    if(linesNumber != rows){
        throw NumberException("Wrong size of board");
    }
    this->rows = rows;
    this->cols = cols;
    this->cells = board;
    this->status = GameStatus::Going;
    calculateBombNumberNear();
}

void Board::recreate(string fileName) {
    Board board(std::move(fileName));
    this->cols = board.cols;
    this->rows = board.rows;
    this->cells = board.cells;
    this->status = GameStatus::Going;
    calculateBombNumberNear();
}
