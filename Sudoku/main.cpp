
#include <iostream>
#include <string>
using namespace std;
// int board[9][9] =
// {
//   {5,0,4, 0,0,2, 0,0,0},
//   {8,0,0, 0,0,0, 0,7,0},
//   {6,0,0, 0,9,0, 4,0,8},
//   {3,0,0, 6,0,7, 9,0,1},
//   {4,1,6, 2,5,0, 0,0,0},
//   {0,5,0, 8,3,0, 2,0,4},
//   {7,6,8, 5,0,4, 3,9,2},
//   {0,3,0, 9,0,6, 0,0,7},
//   {2,0,9, 3,7,8, 0,1,5}
// };

int board[9][9] =
{
  {0,0,0, 2,0,0, 0,0,0},
  {0,6,0, 0,0,0, 0,4,0},
  {0,0,5, 1,0,0, 0,0,0},
  {0,0,0, 0,0,0, 0,0,0},
  {0,0,1, 5,0,0, 0,0,2},
  {0,4,0, 0,0,9, 0,0,0},
  {9,0,0, 0,0,4, 0,0,0},
  {0,3,2, 0,0,0, 0,0,5},
  {0,0,0, 0,0,6, 7,0,0}
};

int sudoku[9][9][9];
void init() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] > 0 && board[i][j] < 10) {
        for (int k = 0; k < 9; k++) {
          sudoku[i][j][k] = -1;//不再是候选
        }
        sudoku[i][j][board[i][j]-1] = board[i][j];
      } else {
        for (int k = 0; k < 9; k++) {
          sudoku[i][j][k] = 0;//候选
        }
      }
    }
  }
}

void think() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      //已经有值
      if (board[i][j] > 0 && board[i][j] < 10) {
        continue;
      }
      //行
      for (int k = 0; k < 9; k++) {
        if (board[i][k] > 0 && board[i][k] < 10) {
          sudoku[i][j][board[i][k]-1] = -1;
        }
      }
      //列
      for (int k = 0; k < 9; k++) {
        if (board[k][j] > 0 && board[k][j] < 10) {
          sudoku[i][j][board[k][j]-1] = -1;
        }
      }

      //3*3块
      int r = i / 3;
      int c = j / 3;
      for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
          int y = r * 3 + m;
          int x = c * 3 + n;
          if (y == i && x == j) {
            continue;
          }
          if (board[y][x] > 0 && board[y][x] < 10) {
            sudoku[i][j][board[y][x]-1] = -1;
          }
        }
      }

      int sum = 0;
      int value = 0;
      for (int k = 0; k < 9; k++) {
        if (sudoku[i][j][k] == 0) {//统计候选项个数
          sum++;
          value = k+1;
        }
      }
      if (sum == 1 && value > 0 && value < 10) {
        board[i][j] = value;
        sudoku[i][j][value-1] = value;
      }
    }
  }

}

void print_sudoku() {
  for (int i = 0; i < 9; i++) {
    //std::cout << i << " : " << std::endl;
    for (int j = 0; j < 9; j++) {
      //std::cout << "[" << i << "][" << j << "] :" << std::endl;
      for (int k = 0; k < 9; k++) {
        if (sudoku[i][j][k] == -1) {
          std::cout << " ";
        } else if(sudoku[i][j][k] == 0){
          std::cout << "_";
        }else {
          std::cout << sudoku[i][j][k];
        }
      }
      std::cout << "\t ";//std::endl;
    }
    std::cout << std::endl;
  }
}

int print() {
  int sum_right = 0;
  for (int i = 0; i < 9; i++) {
    if (i %3 == 0) {
      std::cout << std::endl;
    }
    for (int j = 0; j < 9; j++) {
      if (j % 3 == 0){
        std::cout << " ";
      }
      std::cout << board[i][j] << " ";
      if (board[i][j] > 0) {
        sum_right++;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "right : " << sum_right << std::endl << std::endl;


  std::cout << "各行之和" << std::endl;
  for (int i = 0; i < 9; i++) {
    int sum = 0;
    for (int j = 0; j < 9; j++) {
      sum += board[i][j];
    }
    std::cout << sum << " ";
  }
  std::cout << std::endl << "各列之和" << std::endl;
  for (int i = 0; i < 9; i++) {
    int sum = 0;
    for (int j = 0; j < 9; j++) {
      sum += board[j][i];
    }
    std::cout << sum << " ";
  }

  std::cout << std::endl<< "各3*3子块之和" << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      //
      int sum = 0;
      for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
          sum += board[i * 3 + m][j * 3 + n];
        }
      }
      std::cout << sum << " ";
    }
    std::cout << std::endl;
  }

  return sum_right;
}

int main() {
  print();
  init();
  print_sudoku();

  for (int i = 0; i < 10; i++) {
    std::cout <<"[[[" << i+1 << "]]]"<<std::endl;
    think();
    int sum_right = print();
    print_sudoku();
    if (sum_right == 81){
      break;
    }

  }


}
