#ifndef std_h
#define std_h

#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

const double Pi = 3.1415926;
const int BoardSize = 15;//棋盘大小
const int MaxBoard = 17;//加上边界后的棋盘大小
const int ChessSize = 28;//每一个格子的显示大小
const int WINDOW_SIZE = (BoardSize + 3) * ChessSize;
enum ChessColor { BLACK = 1, WHITE = -1, EMPTY = 0, BOARD = 2 };

//Ai部分的参数设置
const int EachTry = 7;//每一层选得分前几进行落子尝试
const int MaxLevel = 7;//一共进行十层尝试，也就是往后看十步

#endif // !std_h
