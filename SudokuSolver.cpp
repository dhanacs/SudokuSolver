// Sudoku Solver.
// Backtracking.

#include <stdio.h>
#include <iostream>

using namespace std;

bool done = false;
int blankCells = 0;
int board[10][10] = {0};
int answer[10][10] = {0};
int box[10][10] = {0};
int boxStartEnd[10][4] = {0};

// Maintain the candidates for each cell.
int candidates[10][10][10] = {0};
int candidatesCount[10][10] = {0};

void initializeBoxNumbers()
{
  // Box 1.
  boxStartEnd[1][0] = 1;
  boxStartEnd[1][1] = 1;
  boxStartEnd[1][2] = 3;
  boxStartEnd[1][3] = 3;
  for(int i = 1; i <= 3; ++i)
   for(int j = 1; j <= 3; ++j)
    box[i][j] = 1;

  // Box 2.
  boxStartEnd[2][0] = 1;
  boxStartEnd[2][1] = 4;
  boxStartEnd[2][2] = 3;
  boxStartEnd[2][3] = 6;
  for(int i = 1; i <= 3; ++i)
   for(int j = 4; j <= 6; ++j)
    box[i][j] = 2;

  // Box 3.
  boxStartEnd[3][0] = 1;
  boxStartEnd[3][1] = 7;
  boxStartEnd[3][2] = 3;
  boxStartEnd[3][3] = 9;
  for(int i = 1; i <= 3; ++i)
   for(int j = 7; j <= 9; ++j)
    box[i][j] = 3;

  // Box 4.
  boxStartEnd[4][0] = 4;
  boxStartEnd[4][1] = 1;
  boxStartEnd[4][2] = 6;
  boxStartEnd[4][3] = 3;
  for(int i = 4; i <= 6; ++i)
   for(int j = 1; j <= 3; ++j)
    box[i][j] = 4;

  // Box 5.
  boxStartEnd[5][0] = 4;
  boxStartEnd[5][1] = 4;
  boxStartEnd[5][2] = 6;
  boxStartEnd[5][3] = 6;
  for(int i = 4; i <= 6; ++i)
   for(int j = 4; j <= 6; ++j)
    box[i][j] = 5;

  // Box 6.
  boxStartEnd[6][0] = 4;
  boxStartEnd[6][1] = 7;
  boxStartEnd[6][2] = 6;
  boxStartEnd[6][3] = 9;
  for(int i = 4; i <= 6; ++i)
   for(int j = 7; j <= 9; ++j)
    box[i][j] = 6;

  // Box 7.
  boxStartEnd[7][0] = 7;
  boxStartEnd[7][1] = 1;
  boxStartEnd[7][2] = 9;
  boxStartEnd[7][3] = 3;
  for(int i = 7; i <= 9; ++i)
   for(int j = 1; j <= 3; ++j)
    box[i][j] = 7;

  // Box 8.
  boxStartEnd[8][0] = 7;
  boxStartEnd[8][1] = 4;
  boxStartEnd[8][2] = 9;
  boxStartEnd[8][3] = 6;
  for(int i = 7; i <= 9; ++i)
   for(int j = 4; j <= 6; ++j)
    box[i][j] = 8;

  // Box 9.
  boxStartEnd[9][0] = 7;
  boxStartEnd[9][1] = 7;
  boxStartEnd[9][2] = 9;
  boxStartEnd[9][3] = 9;
  for(int i = 7; i <= 9; ++i)
   for(int j = 7; j <= 9; ++j)
    box[i][j] = 9;
}

void countBlankCells()
{
  for(int i = 1; i <= 9; ++i)
   for(int j = 1; j <= 9; ++j)
    if(board[i][j] == 0) ++blankCells;
}

// Check if the current placement is valid.
bool isValid(int row, int col, int value)
{
  // Row check.
  for(int j = 1; j <= 9; ++j)
   if(j != col && board[row][j] == value) return false;

  // Col check.
  for(int i = 1; i <= 9; ++i)
   if(i != row && board[i][col] == value) return false;

  // Box check.
  int boxNumber = box[row][col];
  int top0 = boxStartEnd[boxNumber][0];
  int left0 = boxStartEnd[boxNumber][1];
  int bottom0 = boxStartEnd[boxNumber][2];
  int right0 = boxStartEnd[boxNumber][3];

  for(int i = top0; i <= bottom0; ++i)
   for(int j = left0; j <= right0; ++j)
    if(!(i == row && j == col) && board[i][j] == value) 
     return false;

  return true;
}

void initializeCandidates()
{
  for(int i = 1; i <= 9; ++i)
   for(int j = 1; j <= 9; ++j)
    for(int k = 1; k <= 9; ++k)
     if(isValid(i, j, k))
     {
       candidates[i][j][candidatesCount[i][j]++] = k;
     } 
}

void solve(int count)
{
  if(count == blankCells) 
  {
    done = true;

    for(int i = 1; i <= 9; ++i)
     for(int j = 1; j <= 9; ++j)
      answer[i][j] = board[i][j];

    return;
  }

  for(int i = 1; i <= 9 && !done; ++i)
   for(int j = 1; j <= 9 && !done; ++j)
    if(board[i][j] == 0)
    {
      for(int k = 0; k < candidatesCount[i][j] && !done; ++k)
      {
        if(!isValid(i, j, candidates[i][j][k])) continue;

        ++count;
        board[i][j] = candidates[i][j][k];
        solve(count);
        board[i][j] = 0;
        --count;
      }
   }
}

void fixSingleCandidates()
{
  bool done = false;

  while(!done)
  {
    done = true;

    for(int i = 1; i <= 9 && !done; ++i)
     for(int j = 1; j <= 9 && !done; ++j)
      if(candidatesCount[i][j] == 1)
      {
        board[i][j] = candidates[i][j][0];
        candidatesCount[i][j] = 0;
        initializeCandidates();
        done = false;
      }
  }
}

int main()
{
  for(int i = 1; i <= 9; ++i)
   for(int j = 1; j <= 9; ++j)
    scanf("%d", &board[i][j]);

  initializeBoxNumbers();
  countBlankCells();
  initializeCandidates();
  fixSingleCandidates();
  solve(0);

  // Print the solution.
  for(int i = 1; i <= 9; ++i)
  {
    for(int j = 1; j <= 9; ++j)
     printf("%d ", answer[i][j]);
    printf("\n");
  }

  return 0;
}
