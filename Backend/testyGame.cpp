// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"
#include "NumberException.h"

#include "Board.h"

using namespace ::testing;

TEST(TestGame, LoseGame) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 0, 0, 0},
    };
    Board gameBoard(pole);
    ASSERT_EQ(false, gameBoard.pick(0, 0));
    ASSERT_EQ(GameStatus::Lose, gameBoard.getStatus());
    ASSERT_EQ(true, gameBoard.inBoard(0, 0));
}

TEST(TestGame, WinGame) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 0, 0, 0},
    };
    Board gameBoard(pole);
    ASSERT_EQ(true, gameBoard.pick(1, 0));
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
    gameBoard.pick(1, 1);
    gameBoard.pick(1, 2);
    gameBoard.pick(1, 3);
    gameBoard.pick(0, 3);
    gameBoard.pick(2, 0);
    gameBoard.pick(2, 2);
    gameBoard.pick(2, 3);
    gameBoard.pick(3, 1);
    gameBoard.pick(3, 2);
    gameBoard.pick(3, 3);

    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());

    gameBoard.markBomb(0, 0);
    gameBoard.markBomb(0, 1);
    gameBoard.markBomb(0, 2);
    gameBoard.markBomb(2, 1);
    gameBoard.markBomb(3, 0);
    ASSERT_EQ(GameStatus::Win, gameBoard.getStatus());
}

TEST(TestGame, BFSTestWhenPickNumber) {
    vector<vector<int>> pole = {
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
    };
    Board gameBoard(pole);
    ASSERT_EQ(true, gameBoard.pick(1, 1));
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
    ASSERT_EQ(false, gameBoard.isVisible(0, 0));
    ASSERT_EQ(false, gameBoard.isVisible(1, 0));
    ASSERT_EQ(false, gameBoard.isVisible(0, 1));
    ASSERT_EQ(true, gameBoard.isVisible(1, 1));
    ASSERT_EQ(false, gameBoard.isVisible(3, 3));
}

TEST(TestGame, TestOpenedCells) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
    };
    Board gameBoard(pole);
    ASSERT_EQ(-1, gameBoard.numberOfBombNear(1, 1));
    ASSERT_EQ(true, gameBoard.pick(1, 1));
    ASSERT_EQ(8, gameBoard.numberOfBombNear(1, 1));
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}

TEST(TestGame, NotFinishedGame) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
    }; /// 1 means mine
    Board gameBoard(pole);
    gameBoard.pick(1, 1);
    gameBoard.markBomb(1, 1);
    ASSERT_EQ(8, gameBoard.numberOfBombNear(1, 1));
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}

TEST(TestGame, WrongPick) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
    }; /// 1 means mine
    Board gameBoard(pole);
    ASSERT_THROW(gameBoard.pick(10, 10), NumberException);
    gameBoard.markBomb(1, 1);
    ASSERT_EQ(-1, gameBoard.numberOfBombNear(1, 1));
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}

TEST(TestGame, PickOpenCell) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
    }; /// 1 means mine
    Board gameBoard(pole);
    gameBoard.pick(1, 1);
    gameBoard.markBomb(1, 1);
    ASSERT_EQ(8, gameBoard.numberOfBombNear(1, 1));
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}

TEST(TestGame, ChcekPotentionalBombs) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
    }; /// 1 means mine
    Board gameBoard(pole);
    gameBoard.markBomb(1, 1);
    ASSERT_EQ(-1, gameBoard.numberOfBombNear(1, 1));
    ASSERT_EQ(false, gameBoard.isVisible(1, 1));
    ASSERT_EQ(true, gameBoard.isFlagInCell(1, 1));
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}

TEST(TestGame, CantRestartGame) {
    vector<vector<int>> pole = {
            {1, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
    }; /// 1 means mine
    Board gameBoard(pole);
    gameBoard.pick(0, 1);
    gameBoard.markBomb(0, 1);
    ASSERT_EQ(-1, gameBoard.numberOfBombNear(0, 1));
    ASSERT_EQ(GameStatus::Lose, gameBoard.getStatus());
}

TEST(TestGame, BadGeneration) {
    ASSERT_THROW(Board gameBoard(-1, 1, 1);, NumberException);
}

TEST(TestGame, BadNumberOfMines) {
    ASSERT_THROW(Board gameBoard(10, 10, 100), NumberException);
}

TEST(TestGame, BFSTestWhenPickEmptyCell) {
    vector<vector<int>> pole = {
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
    };
    Board gameBoard(pole);
    gameBoard.pick(3, 3);
    ASSERT_EQ(true, gameBoard.isVisible(1, 1));
    ASSERT_EQ(true, gameBoard.isVisible(1, 0));
    ASSERT_EQ(true, gameBoard.isVisible(0, 1));
    ASSERT_EQ(false, gameBoard.isVisible(0, 0));
    ASSERT_EQ(1, gameBoard.numberOfBombNear(1, 1));
    gameBoard.markBomb(0, 0);
    ASSERT_EQ(GameStatus::Win, gameBoard.getStatus());
}

TEST(TestGame, BFSTestWhenPickFieldAndEmptyCell) {
    vector<vector<int>> pole = {
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
    };
    Board gameBoard(pole);
    gameBoard.pick(1, 1);
    ASSERT_EQ(true, gameBoard.isVisible(1, 1));
    ASSERT_EQ(false, gameBoard.isVisible(1, 0));
    ASSERT_EQ(false, gameBoard.isVisible(0, 1));
    ASSERT_EQ(false, gameBoard.isVisible(0, 0));
    gameBoard.pick(3, 3);
    ASSERT_EQ(true, gameBoard.isVisible(1, 1));
    ASSERT_EQ(true, gameBoard.isVisible(1, 0));
    ASSERT_EQ(true, gameBoard.isVisible(0, 1));
    ASSERT_EQ(false, gameBoard.isVisible(0, 0));
    ASSERT_EQ(1, gameBoard.numberOfBombNear(1, 1));
    gameBoard.markBomb(0, 0);
    ASSERT_EQ(GameStatus::Win, gameBoard.getStatus());
}

TEST(TestGame, BFSInIndependentParts) {
    vector<vector<int>> pole = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
    };
    Board gameBoard(pole);
    gameBoard.pick(0, 3);
    ASSERT_EQ(true, gameBoard.isVisible(1, 2));
    ASSERT_EQ(true, gameBoard.isVisible(0, 2));
    ASSERT_EQ(true, gameBoard.isVisible(1, 3));
    ASSERT_EQ(false, gameBoard.isVisible(2, 1));
    ASSERT_EQ(false, gameBoard.isVisible(1, 0));
    ASSERT_EQ(false, gameBoard.isVisible(3, 2));
    ASSERT_EQ(2, gameBoard.numberOfBombNear(1, 2));
    ASSERT_EQ(-1, gameBoard.numberOfBombNear(2, 1));
    gameBoard.pick(3, 0);
    ASSERT_EQ(true, gameBoard.isVisible(2, 1));
    ASSERT_EQ(true, gameBoard.isVisible(2, 0));
    ASSERT_EQ(true, gameBoard.isVisible(3, 1));
    ASSERT_EQ(2, gameBoard.numberOfBombNear(2, 1));

    gameBoard.markBomb(0, 0);
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}

TEST(TestGame, BFSEmptyBoard) {
    vector<vector<int>> pole = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
    };
    Board gameBoard(pole);
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
    gameBoard.pick(0, 3);
    ASSERT_EQ(GameStatus::Win, gameBoard.getStatus());
}

TEST(TestGame, BFSWrongBombpeack) {
    vector<vector<int>> pole = {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
    };
    Board gameBoard(pole);
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
    gameBoard.pick(0, 3);
    gameBoard.markBomb(1, 1);
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}

TEST(TestGame, ManyPicks) {
    Board gameBoard(4, 4, 6);
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
    for(int i = 0;i<3;i++){
        for(int j = 0;j<4;j++){
            gameBoard.pick(i, j);
        }
    }
    ASSERT_EQ(GameStatus::Lose, gameBoard.getStatus());
}

TEST(TestGame, RegenerateGame) {
    vector<vector<int>> pole = {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
    };
    Board gameBoard(pole);
    gameBoard.pick(1, 1);
    ASSERT_EQ(GameStatus::Lose, gameBoard.getStatus());
    gameBoard.recreate();
    ASSERT_EQ(GameStatus::Going, gameBoard.getStatus());
}