#ifndef Board_h
#define Board_h

#include "Ai.h"



void Board::DisBackground()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int N = 30;//圆圈总个数
	int M = 30;//圆圈细腻程度
	for (int i = N; i > 0; i--) {
		double R = WINDOW_SIZE / N * i;
		glColor3f(1 - i * 0.02, 1.0 * 153 / 256 + i * 0.02, 0 + i * 0.02);
		glBegin(GL_POLYGON);
		for (int j = M; j > 0; j--) {
			glVertex2f(R*sin(2 * Pi / M * j) + WINDOW_SIZE / 2, R*cos(2 * Pi / M * j) + WINDOW_SIZE / 2);
		}
		glEnd();
	}
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < BoardSize + 4; i++) {
		glBegin(GL_LINES);
		glVertex2f(i*ChessSize, 0);
		glVertex2f(i*ChessSize, WINDOW_SIZE);
		glVertex2f(0, i*ChessSize);
		glVertex2f(WINDOW_SIZE, i*ChessSize);
		glEnd();
	}
	glColor3f(0.5, 0.5, 0.7);
	glRectf(0, 0, WINDOW_SIZE, ChessSize);
	glRectf(0, 0, ChessSize, WINDOW_SIZE);
	glRectf(WINDOW_SIZE, WINDOW_SIZE, 0, WINDOW_SIZE - ChessSize);
	glRectf(WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE - ChessSize, 0);

	//加几个定位点(仅对于15*15的棋盘大小有效)
	glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(4 * ChessSize, 4 * ChessSize);
	glVertex2f(9 * ChessSize, 9 * ChessSize);
	glVertex2f(14 * ChessSize, 4 * ChessSize);
	glVertex2f(14 * ChessSize, 14 * ChessSize);
	glVertex2f(4 * ChessSize, 14 * ChessSize);
	glEnd();


}

void Board::DisChess()
{
	for (int i = 1; i < BoardSize + 1; i++)
		for (int j = 1; j < BoardSize + 1; j++) {
			if (ChessList[i][j] != EMPTY)
				DisSingle(i, j);
		}
}

void Board::DisSingle(int x, int y)
{
	int M = 10;//圆圈细腻程度
	double R = ChessSize / 2.05;
	if (ChessList[x][y] == BLACK)
		glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int j = M; j > 0; j--)
	{
		//printf("%lf\n", R*sin(2.0 * Pi / M * j));
		glVertex2f(R*sin(2.0 * Pi / M * j) + (x + 1) * ChessSize, WINDOW_SIZE + R * cos(2.0 * Pi / M * j) - (y + 1) * ChessSize);
	}
	glEnd();
}

void Board::Victory(ChessColor Target)
{
	for (int i = 0; i < 100; i++) {
		int a = rand() % BoardSize, b = rand() % BoardSize;
		ChessList[a + 1][b + 1] = Target;
		onDisplay();
		glutSwapBuffers();
		Sleep(10);
	}
	Sleep(1000);
}

ChessColor Board::Judge()
{
	for (int i = 1; i < BoardSize + 1; i++)
		for (int j = 1; j < BoardSize + 1; j++)
		{
			if (ChessList[i][j] == EMPTY)
				continue;
			int length = 1;
			while (ChessList[i + length][j] == ChessList[i][j])
				length++;
			if (length >= 5)
				return (ChessColor)ChessList[i][j];
			length = 1;
			while (ChessList[i][j + length] == ChessList[i][j])
				length++;
			if (length >= 5)
				return (ChessColor)ChessList[i][j];
			length = 1;
			while (ChessList[i + length][j + length] == ChessList[i][j])
				length++;
			if (length >= 5)
				return (ChessColor)ChessList[i][j];
			length = 1;
			while (ChessList[i - length][j + length] == ChessList[i][j])
				length++;
			if (length >= 5)
				return (ChessColor)ChessList[i][j];
		}
	return EMPTY;
}

void Board::init() {
	for (int i = 1; i < BoardSize + 1; i++)
		for (int j = 1; j < BoardSize + 1; j++) {
			ChessList[i][j] = EMPTY;
		}
}

Board::Board()
{
	for (int i = 0; i < BoardSize + 2; i++)
		for (int j = 0; j < BoardSize + 2; j++)
			if (i == 0 || j == 0 || i == BoardSize + 1 || j == BoardSize + 1)
				ChessList[i][j] = BOARD;
			else ChessList[i][j] = EMPTY;
}

void Board::onDisplay()
{
	DisBackground();
	DisChess();
}

bool Board::onUpdate()
{
	ChessColor Res = Judge();
	if (Res != EMPTY) {
		Victory(Res);
		init();
		return true;
	}
	return false;
}

bool Board::myMouse(ChessColor color, int x, int y)
{
	if (ChessList[x][y] != EMPTY)
		return false;
	ChessList[x][y] = color;
	return true;
}

#endif // !Board_h
