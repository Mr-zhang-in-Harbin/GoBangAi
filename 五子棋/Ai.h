#ifndef Ai_h
#define Ai_h

#include "std.h"

const int TreeSize = 10;//每一层树所要进行的判断个数

class Board
{
private:
	friend class ScoreJudger;

	//for Debug
	friend class Ai_JudgeTree;

	int ChessList[BoardSize + 2][BoardSize + 2];
	void DisBackground();//背景色，后面可能会换成贴图,还有棋盘的绘制
	void DisChess();//棋子的绘制
	void DisSingle(int x, int y);//单个棋子给定坐标，找点绘制。
	void Victory(ChessColor Target);
protected:
	ChessColor Judge();//判断是否胜利
	void init();
public:
	Board();
	void onDisplay();
	bool onUpdate();
	bool myMouse(ChessColor color, int x, int y);//这里传入的是转化后的坐标，即具体到棋盘上的第几行第几列
};

class Ai_JudgeTree
{
private:
	friend ScoreJudger;
	int X_Loc, Y_Loc, Score;
	ChessColor Ai_Color;
	Ai_JudgeTree *List[TreeSize];
protected:

public:
	int Judge(int Level, ScoreJudger *CPU, ChessColor Ai_Color, int *LevelBest);
	Ai_JudgeTree(int X, int Y, ChessColor color);
};

class ScoreJudger
{
private:
	ChessColor ChessList[BoardSize + 2][BoardSize + 2];
	int ScoreList[BoardSize][BoardSize];
	int ConstList[6561];//分数表
	friend Ai_JudgeTree;
protected:
	void IfMax(int *Max, int i, int j, ChessColor color);
	bool TryChess(int i, int j, ChessColor color);//试落子，要保证落子后删除
public:

	void DisEachChess(int x, int y)
	{
		int M = 10;//圆圈细腻程度
		double R = ChessSize / 6.05;
		if (ChessList[x][y] == BLACK)
			glColor3f(0.0, 0.0, 0.0);
		else if (ChessList[x][y] == WHITE)
			glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		for (int j = M; j > 0; j--)
		{
			//printf("%lf\n", R*sin(2.0 * Pi / M * j));
			glVertex2f(R*sin(2.0 * Pi / M * j) + (x + 1) * ChessSize, WINDOW_SIZE + R * cos(2.0 * Pi / M * j) - (y + 1) * ChessSize);
		}
		glEnd();
	}

	void DisChess()
	{
		for (int i = 1; i < BoardSize + 1; i++)
			for (int j = 1; j < BoardSize + 1; j++) {
				if (ChessList[i][j] != EMPTY)
					DisEachChess(i, j);
			}
	}
	void Dis()
	{
		DisChess();
		glutSwapBuffers();
	}
	//For Debug


	int GetEnviroScore(ChessColor Color);
	int* GetMax(ChessColor color);
	int GetEachScore(int x, int y, ChessColor Color);
	int GetWholeScore();//返回单体最高，不分颜色
	int GetWholeScore(ChessColor Color);//返回总体平均得分,只判断单个颜色，EMPTY判断总和分数，返回的是平均分数
	void GetBoard(Board *p);
};

class Ai//Ai总类，在Game中唯一能调用的组成
{
private:
	ScoreJudger * CPU;//用来计算分数
	Ai_JudgeTree *Head;//用来保存分数结果
protected:
	int LevelBest[MaxLevel];
public:
	int Judge(Board *p, ChessColor color);
	Ai();
};

#endif // !Ai_h
