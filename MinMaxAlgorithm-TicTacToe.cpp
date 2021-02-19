// Author : Mohamed Sameh
/*
0 -> O
1 -> X
the game start with O
*/
#include <bits/stdc++.h>
using namespace std;
const int BoardSize = 3;
int board[BoardSize][BoardSize], winner;
bool CompuerTurn, Current, ComputerValue;
void init()
{
  winner = -1;
  memset(board, -1, sizeof board);
}
void PrintRow(int sz)
{
 for (int i = 0; i < sz; i++) cout << "#" << " \n"[i == sz-1];
}
void PrintTheBoard()
{
 PrintRow(BoardSize); 
  for (int i = 0; i < BoardSize; i++)
    for (int j = 0; j < BoardSize; j++)
      cout << (board[i][j] == 1 ? "X" : (board[i][j] == 0 ? "O" : "-")) <<" \n"[ j == BoardSize - 1];
 PrintRow(BoardSize);
 cout << "\n"; 
}
bool valid(int r, int c)
{
  return !(min(r,c) < 0 || max(r, c) >= BoardSize || ~board[r][c]); 
}
void SetWinner(int val)
{
  winner = val;
}
void PrintWinner ()
{
 if (winner == ComputerValue)
    cout <<"Computer Won\n";
  else if (winner == (ComputerValue^1))
    cout <<"You Won\n";
  else
    cout <<"Draw\n";
}
bool RowWin(int row)
{
 int j = 1; 
 while(j < BoardSize && board[row][j] == board[row][j-1] && ~board[row][j-1])
  j++; 
 j--;
 if (j == BoardSize - 1)
 {
  SetWinner(board[row][j]);
  return 1;
 }
 return 0; 
}
bool ColWin(int col)
{
 int j = 1; 
 while(j < BoardSize && board[j][col] == board[j-1][col] && ~board[j-1][col])
  j++; 
 j--; 
 if (j == BoardSize - 1)
 {
  SetWinner(board[j][col]); 
  return 1; 
 }
 return 0; 
}
bool CheckRowAndCol()
{
 // check if row or col i is wining, 
 for (int i = 0; i < BoardSize; i++)
  if (RowWin(i) || ColWin(i)) 
   return 1; 
 return 0; 
}
bool CheckPrimaryDiagonal()
{
 int i = 1; 
 while(i < BoardSize && board[i][i] == board[i-1][i-1] && ~board[i-1][i-1])
  i++; 
 i--; 
 if (i == BoardSize-1)
 {
  SetWinner(board[i][i]);
  return 1; 
 }
 return 0; 
}
bool CheckOtherDiagonal()
{
 int i = 1, j = BoardSize - 2; 
 while(i < BoardSize && board[i][j] == board[i-1][j+1] && ~board[i-1][j+1])
  j--, i++; 
 j++;
 i--;
 if (i == BoardSize - 1)
 {
  SetWinner(board[i][j]); 
  return 1; 
 }
 return 0; 
}
bool CheckTheDiagonals()
{
 // check the two diagonals 
 return (CheckPrimaryDiagonal() || CheckOtherDiagonal()); 
}
bool EndState()
{
  if(CheckRowAndCol() || CheckTheDiagonals()) return 1; 
  // if there are empty cells 
  for (int i = 0; i < BoardSize; i++)
    for (int j = 0; j < BoardSize; j++)
      if (board[i][j] == -1)
       return 0;
  // no empty cells and no winner, so it's a draw 
  SetWinner(-1);
  return 1;
}
int best, row, col;
int FindBest(bool Cmove = 0, int depth = 0)
{
  if (EndState())
  {
    if (winner == -1)return 0; 
    return winner == ComputerValue? 10000 - depth: -10000 + depth;
  }
  int ret = (Cmove ? -1e9 : 1e9);
  for (int i = 0; i < BoardSize; i++)
  {
    for (int j = 0; j < BoardSize; j++)
    {
      if (board[i][j] == -1)
      {
        board[i][j] = (ComputerValue^(!Cmove)); 
        int cur_cost = FindBest(Cmove ^ 1, depth + 1);
        if (Cmove)
          ret = max(ret, cur_cost);
        else
          ret = min (ret, cur_cost);
        board[i][j] = -1;
      }
    }
  }
  return ret;
}
void chooseBest()
{
  best = -1e9;
  for (int i = 0; i < BoardSize; i++)
  {
    for (int j = 0; j < BoardSize; j++)
    {
      if (board[i][j] == -1)
      {
        board[i][j] = ComputerValue;
        int cur_cost = FindBest();
        if (cur_cost > best)
        {
          best = cur_cost;
          row = i;
          col = j;
        }
        board[i][j] = -1;
      }
    }
  }
}
void takeInput()
{
  string input;
  cout <<"who Plays first?\n1-Me.\n2-Computer.\n";
  cin >> input;
  CompuerTurn = (input == "1" ? 0 : 1);
  ComputerValue = (CompuerTurn ? 0 : 1);
}
int main()
{
  bool  playagin;
  do{
  init();
  takeInput();
  bool Finsh = 0;
  Current = 0;
  while (!Finsh)
  {
    if (CompuerTurn)
    {
      chooseBest();
      board[row][col]=Current;
    }else
    {
      int r, c;
      do{
      cout <<"Enter The pairs row and colmun you will chose\n";
      cin >> r >> c;
      r--;
      c--;
      if (!valid(r, c))
        cout <<"Not Valid\n";
      else
        break;
      }
      while(1);
      board[r][c] = Current;
    }
    PrintTheBoard();
    Finsh = EndState();
    CompuerTurn ^= 1;
    Current ^= 1;
  }
  PrintWinner();
  cout <<"Do You want to play agina?\ntype(1 or 0)\n";
  cin >> playagin;
}
while(playagin);
}
