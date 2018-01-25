#ifndef Ai_h
#define Ai_h

#include "std.h"

const int TreeSize = 10;//ÿһ������Ҫ���е��жϸ���

class Board
{
private:
	friend class ScoreJudger;

	//for Debug
	friend class Ai_JudgeTree;

	int ChessList[BoardSize + 2][BoardSize + 2];
	void DisBackground();//����ɫ��������ܻỻ����ͼ,�������̵Ļ���
	void DisChess();//���ӵĻ���
	void DisSingle(int x, int y);//�������Ӹ������꣬�ҵ���ơ�
	void Victory(ChessColor Target);
protected:
	ChessColor Judge();//�ж��Ƿ�ʤ��
	void init();
public:
	Board();
	void onDisplay();
	bool onUpdate();
	bool myMouse(ChessColor color, int x, int y);//���ﴫ�����ת��������꣬�����嵽�����ϵĵڼ��еڼ���
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
	int ConstList[6561];//������
	friend Ai_JudgeTree;
protected:
	void IfMax(int *Max, int i, int j, ChessColor color);
	bool TryChess(int i, int j, ChessColor color);//�����ӣ�Ҫ��֤���Ӻ�ɾ��
public:

	void DisEachChess(int x, int y)
	{
		int M = 10;//ԲȦϸ��̶�
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
	int GetWholeScore();//���ص�����ߣ�������ɫ
	int GetWholeScore(ChessColor Color);//��������ƽ���÷�,ֻ�жϵ�����ɫ��EMPTY�ж��ܺͷ��������ص���ƽ������
	void GetBoard(Board *p);
};

class Ai//Ai���࣬��Game��Ψһ�ܵ��õ����
{
private:
	ScoreJudger * CPU;//�����������
	Ai_JudgeTree *Head;//��������������
protected:
	int LevelBest[MaxLevel];
public:
	int Judge(Board *p, ChessColor color);
	Ai();
};

#endif // !Ai_h
