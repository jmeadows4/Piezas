#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  for(int i = 0; i < BOARD_ROWS; i++){
     std::vector<Piece> row(BOARD_COLS, Blank);
    board.push_back(row);
  }
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    for(int i = 0; i < BOARD_ROWS; i++){
      for(int j = 0; j < BOARD_COLS; j++){
        board[i][j] = Blank;
      }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
    if(column >= 0 && column < BOARD_COLS){

      //check from 0 to BOARD_ROWS. Even though row values are flipped, we still
      //want to start at the 0th row
      for(int i = 0; i < BOARD_ROWS; i++){
        //change this to pieceAt?
        if(board[i][column] == Blank){
          board[i][column] = turn;
          if(turn == X){ turn = O;}
          else{ turn = X;}
          return turn;
        }
      }
      if(turn == X){ turn = O;}
      else{ turn = X;}
      return Blank;
    }
    if(turn == X){ turn = O;}
    else{ turn = X;}
    return Invalid;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if(row < 0 || column < 0 || row >= BOARD_ROWS || column >= BOARD_COLS){
      return Invalid;
    }
    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j <BOARD_COLS; j++){
      if(pieceAt(i, j) == Blank){
        return Invalid;
      }
    }
  }
  int max_x = 0;
  int max_o = 0;
  int cur_x = 0;
  int cur_o = 0;
  //check rows for longest string of X's and O's by row
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j < BOARD_COLS; j++){
      if(pieceAt(i, j) == X){
        cur_x += 1;
        cur_o = 0;
      }
      else if(pieceAt(i, j) == O){
        cur_o += 1;
        cur_x = 0;
      }
      if(cur_x > max_x){
        max_x = cur_x;
      }
      if(cur_o > max_o){
        max_o = cur_o;
      }
    }
    cur_x = 0;
    cur_o = 0;
  }
  cur_x = 0;
  cur_o = 0;
  //check for longest string of X's and O's by col
  for(int i = 0; i < BOARD_COLS; i++){
    for(int j = 0; j < BOARD_ROWS; j++){
      if(pieceAt(j, i) == X){
        cur_x += 1;
        cur_o = 0;
      }
      else if(pieceAt(i, j) == O){
        cur_o += 1;
        cur_x = 0;
      }
      if(cur_x > max_x){
        max_x = cur_x;
      }
      if(cur_o > max_o){
        max_o = cur_o;
      }
    }
    cur_x = 0;
    cur_o = 0;
  }

  if(max_x > max_o){
    return X;
  }
  else if(max_o > max_x){
    return O;
  }
  else{
    return Blank;
  }
}
