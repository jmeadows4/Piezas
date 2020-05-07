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
