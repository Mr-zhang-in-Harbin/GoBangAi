#include "Ai.h"

/*
	�ж�����ʱ��������ѡ�����а�������λ��������ϣ��������ж�ÿһ������е���û���赲
	û�еĻ��Ϳ��Ը��������������
	ÿ������λһ���У�20�����������
	Bingo
*/

void ScoreJudger::IfMax(int *Max, int i, int j, ChessColor color)
{
	int x = Max[EachTry - 1] / MaxBoard, y = Max[EachTry - 1] % MaxBoard;
	if (ScoreList[i][j] > ScoreList[x][y]) {
		Max[EachTry - 1] = i * MaxBoard + j;
		for (int i = EachTry - 1; i > 0; i--) {
			if (ScoreList[Max[i] / MaxBoard][Max[i] % MaxBoard] > ScoreList[Max[i - 1] / MaxBoard][Max[i - 1] % MaxBoard]) {
				int temp = Max[i];
				Max[i] = Max[i - 1];
				Max[i - 1] = temp;
			}
			else return;
		}
	}
}

bool ScoreJudger::TryChess(int i, int j, ChessColor color)
{
	if (ChessList[i][j] == EMPTY)
		ChessList[i][j] = color;
	else {
		printf("Wrong!!\n");
		return false;
	}
	return true;
}

int ScoreJudger::GetEnviroScore(ChessColor Color)
{
	int Temp, Res = 0;
	for (int j = 1; j < BoardSize + 1; j++) {
		for (int i = 1; i < BoardSize + 1; i++) {
			if (Color == EMPTY)
				Temp = GetEachScore(i, j, BLACK) + GetEachScore(i, j, WHITE);
			else Temp = GetEachScore(i, j, Color) - GetEachScore(i, j, ChessColor(Color * -1));
			Res += Temp;
			ScoreList[i - 1][j - 1] = Temp;
		}
	}
	return Res;
}

int* ScoreJudger::GetMax(ChessColor color)
{
	int *Res = new int[EachTry];
	for (int i = 0; i < EachTry; i++)
		Res[i] = 0;
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			IfMax(Res, i, j, color);

	for (int i = 0; i < EachTry; i++)
		Res[i] += 1 + MaxBoard;
	return Res;
}

int ScoreJudger::GetEachScore(int x, int y, ChessColor Color)
//���ڸ��������꣬�ж϶�ʮ������е��������Ȩ�зֲ�����
{
	int X_[4] = { -1,-1,-1,0 }, Y_[4] = { -1,0,1,1 };//��ϳ��ĸ�����
	int Score[5] = { 1,20,500,10000,200000 };//��һ�����ӵķ������л���
	int num = 0, Res[5] = { 0,0,0,0,0 };
	for (int i = 0; i < 4; i++) {//�������

		for (int k = -4; k < 1; k++) {//��ʼƫ��ֵ
			num = 0;
			for (int j = 0; j < 5 && num >= 0; j++) {//����ƫ��ֵ���������λ��
				ChessColor Temp = ChessList[x + X_[i] * (k + j)][y + Y_[i] * (k + j)];
				if (Temp == EMPTY) {
				}
				else if (Temp == Color)
					num++;
				else {
					k += j;
					num = -1;
				}
			}
			if (num > 0)
				Res[num - 1]++;
		}
	}
	int Return = 0;
	for (int i = 0; i < 5; i++) {
		Return += Res[i] * Score[i];
	}
	return Return;
}

int ScoreJudger::GetWholeScore()
{
	int x = 0, y = 0, Max = 0;
	for (int j = 1; j < BoardSize + 1; j++) {
		for (int i = 1; i < BoardSize + 1; i++) {
			if (ChessList[i][j] != EMPTY) {
				ScoreList[i - 1][j - 1] = 0;
				continue;
			}
			else {

				int Res = GetEachScore(i, j, BLACK) + GetEachScore(i, j, WHITE);
				ScoreList[i - 1][j - 1] = Res;
				if (Res > Max) {
					Max = Res;
					x = i;
					y = j;
				}
			}
		}
	}
	return x * MaxBoard + y;
}

int ScoreJudger::GetWholeScore(ChessColor Color)
{
	int Temp, Count = 0, Res = 0;
	for (int j = 1; j < BoardSize + 1; j++) {
		for (int i = 1; i < BoardSize + 1; i++) {
			if (ChessList[i][j] != EMPTY) {
				ScoreList[i - 1][j - 1] = 0;
				continue;
			}
			else {

				Count++;
				if (Color == EMPTY)
					Temp = GetEachScore(i, j, BLACK) + GetEachScore(i, j, WHITE);
				else Temp = GetEachScore(i, j, Color) - GetEachScore(i, j, ChessColor(Color * -1));
				Res += Temp;
				ScoreList[i - 1][j - 1] = Temp;
			}
		}
	}
	return Res;
}

void ScoreJudger::GetBoard(Board *p)
{
	for (int i = 0; i < BoardSize + 2; i++)
		for (int j = 0; j < BoardSize + 2; j++)
			ChessList[i][j] = (ChessColor)p->ChessList[i][j];
}