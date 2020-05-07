/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

#include<iostream>
using namespace std;


class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}
TEST(PiezasTest, checkConstructor)
{
  Piezas obj;
  bool all_blanks = true;
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j < BOARD_COLS; j++){
      if(obj.pieceAt(i, j) != Blank){
        all_blanks = false;
        break;
      }
    }
  }
  ASSERT_TRUE(all_blanks);
}
TEST(PiezasTest, resetWithPrevVals)
{
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(1);
  obj.reset();
  bool all_blanks = true;
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j < BOARD_COLS; j++){
      if(obj.pieceAt(i, j) != Blank){
        all_blanks = false;
        break;
      }
    }
  }
  ASSERT_TRUE(all_blanks);
}
TEST(PiezasTest, dropSingle){
  Piezas obj;
  obj.dropPiece(0);
  ASSERT_TRUE(obj.pieceAt(0,0) == X);
}
TEST(PiezasTest, dropSameCol){
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  ASSERT_TRUE(obj.pieceAt(0,0) == X
           && obj.pieceAt(1, 0) == O
           && obj.pieceAt(2, 0) == X );
}
TEST(PiezasTest, dropOutOfBoundsNeg){
  Piezas obj;
  Piece p = obj.dropPiece(-1);
  ASSERT_TRUE(p == Invalid);
}
TEST(PiezasTest, dropOutOfBoundsPos){
  Piezas obj;
  Piece p = obj.dropPiece(BOARD_COLS);
  ASSERT_TRUE(p == Invalid);
}
TEST(PiezasTest, OverflowCol){
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  Piece p = obj.dropPiece(0);
  ASSERT_TRUE(p == Blank);
}
TEST(PiezasTest, GameStateInvalid){
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(1);
  obj.dropPiece(2);
  obj.dropPiece(3);
  Piece p = obj.gameState();
  ASSERT_TRUE(p == Invalid);
}
TEST(PiezasTest, pieceAtOutOfBoundsNeg){
  Piezas obj;
  Piece p = obj.pieceAt(0, -1);
  ASSERT_TRUE(p == Invalid);
}

//makes a board of:
// X O X O
// X O X O
// X O X O
TEST(PiezasTest, GameStateTieVertical){
  Piezas obj;
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j < BOARD_COLS; j++){
      obj.dropPiece(j);
    }
  }
  Piece p = obj.gameState();
  ASSERT_TRUE(p == Blank);
}
//makes a board of:
// X X X X
// O O O O
// X X X X
TEST(PiezasTest, GameStateTieHorizontal){
  Piezas obj;
  for(int i = 0; i < BOARD_COLS; i++){
    for(int j = 0; j < BOARD_ROWS; j++){
      obj.dropPiece(i);
    }
  }
  Piece p = obj.gameState();
  ASSERT_TRUE(p == Blank);
}
//makes a board of:
// O O X O
// O O X O
// X X X X
TEST(PiezasTest, XWins){
  Piezas obj;
  obj.dropPiece(0);//X
  obj.dropPiece(0);//O
  obj.dropPiece(1);//X
  obj.dropPiece(1);//O
  obj.dropPiece(2);//X
  obj.dropPiece(0);//O
  obj.dropPiece(3);//X
  obj.dropPiece(1);//O
  obj.dropPiece(2);//X
  obj.dropPiece(3);//O
  obj.dropPiece(2);//X
  obj.dropPiece(3);//O


  Piece p = obj.gameState();
  ASSERT_TRUE(p == X);
}
// X X X O
// O O O O
// X X X O
TEST(PiezasTest, OWins){
  Piezas obj;
  obj.dropPiece(0);//X
  obj.dropPiece(0);//O
  obj.dropPiece(1);//X
  obj.dropPiece(1);//O
  obj.dropPiece(2);//X
  obj.dropPiece(2);//O
  obj.dropPiece(0);//X
  obj.dropPiece(3);//O
  obj.dropPiece(1);//X
  obj.dropPiece(3);//O
  obj.dropPiece(2);//X
  obj.dropPiece(3);//O


  Piece p = obj.gameState();
  ASSERT_TRUE(p == O);
}
// X X O O
// X O O X
// X O X O
TEST(PiezasTest, VerticalWin){
  Piezas obj;
  obj.dropPiece(0);//X
  obj.dropPiece(1);//O
  obj.dropPiece(2);//X
  obj.dropPiece(3);//O
  obj.dropPiece(0);//X
  obj.dropPiece(1);//O
  obj.dropPiece(3);//X
  obj.dropPiece(2);//O
  obj.dropPiece(0);//X
  obj.dropPiece(3);//O
  obj.dropPiece(1);//X
  obj.dropPiece(2);//O

  Piece p = obj.gameState();
  ASSERT_TRUE(p == X);
}
TEST(PiezasTest, BadMoveWin){
  Piezas obj;
  obj.dropPiece(0);//X
  obj.dropPiece(1);//O
  obj.dropPiece(2);//X
  obj.dropPiece(3);//O
  obj.dropPiece(0);//X
  obj.dropPiece(1);//O
  obj.dropPiece(3);//X
  obj.dropPiece(2);//O
  obj.dropPiece(0);//X
  obj.dropPiece(0);//O, bad move
  obj.dropPiece(1);//X
  obj.dropPiece(2);//O
  obj.dropPiece(3);//X

  Piece p = obj.gameState();
  ASSERT_TRUE(p == X);
}
