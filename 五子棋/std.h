#ifndef std_h
#define std_h

#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

const double Pi = 3.1415926;
const int BoardSize = 15;//���̴�С
const int MaxBoard = 17;//���ϱ߽������̴�С
const int ChessSize = 28;//ÿһ�����ӵ���ʾ��С
const int WINDOW_SIZE = (BoardSize + 3) * ChessSize;
enum ChessColor { BLACK = 1, WHITE = -1, EMPTY = 0, BOARD = 2 };

//Ai���ֵĲ�������
const int EachTry = 7;//ÿһ��ѡ�÷�ǰ���������ӳ���
const int MaxLevel = 7;//һ������ʮ�㳢�ԣ�Ҳ��������ʮ��

#endif // !std_h
