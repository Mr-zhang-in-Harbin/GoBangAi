#include "Ai.h"

//For Debug
void SetColor(unsigned short ForeColor = 7, unsigned short BackColor = 0)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, ForeColor + BackColor * 0x10);
}

int MAX(int *TempList, int BOARD)
{
	int Max = TempList[0];
	for (int i = 1; i < BOARD; i++)
		Max = max(Max, TempList[i]);
	return Max;
}

int MIN(int *TempList, int BOARD)
{
	int Min = TempList[0];
	for (int i = 1; i < BOARD; i++)
		Min = min(Min, TempList[i]);
	return Min;
}

Ai_JudgeTree::Ai_JudgeTree(int X, int Y, ChessColor color)
{
	X_Loc = X;
	Y_Loc = Y;
	Ai_Color = color;
	for (int i = 0; i < TreeSize; i++)
		List[i] = NULL;
	Score = -1;
}

int Ai_JudgeTree::Judge(int Level, ScoreJudger *CPU, ChessColor Ai_Color, int *LevelBest)
{
	SetColor();
	if (Level <= 0) {
		//到了最底层就返回当前抉择路径结果的环境分数
		CPU->TryChess(X_Loc, Y_Loc, Ai_Color);
		int Res = CPU->GetEnviroScore(Ai_Color);
		CPU->ChessList[X_Loc][Y_Loc] = EMPTY;
		return Res;
	}
	if (X_Loc > -1) {
		//如果不是首层
		if (Level == 5)
			CPU->Dis();
		int BOARD = EachTry;//选择最值的边界
		CPU->TryChess(X_Loc, Y_Loc, Ai_Color);
		CPU->GetWholeScore();
		int *TempList = CPU->GetMax(Ai_Color);
		for (int i = 0; i < EachTry; i++) {
			List[i] = new Ai_JudgeTree(TempList[i] / MaxBoard, TempList[i] % MaxBoard, Ai_Color);
			TempList[i] = List[i]->Judge(Level - 1, CPU, (ChessColor)(Ai_Color * -1), LevelBest);
			if (LevelBest[Level] == -1) {

			}
			else if ((Level % 2 == 0 && TempList[i] < LevelBest[Level])
				|| (Level % 2 == 1 && TempList[i] > LevelBest[Level])) {
				BOARD = i + 1;
				break;
			}
		}
		CPU->ChessList[X_Loc][Y_Loc] = EMPTY;
		if (Level % 2 == 1)
			this->Score = MAX(TempList, BOARD);
		else this->Score = MIN(TempList, BOARD);
		delete TempList;
		for (int i = 0; i < EachTry; i++)
			List[i]->~Ai_JudgeTree();
		LevelBest[Level - 1] = -1;
		if (Level % 2 == 1)
			LevelBest[Level] = LevelBest[Level] == -1 ? this->Score : min(LevelBest[Level], this->Score);
		else
			LevelBest[Level] = LevelBest[Level] == -1 ? this->Score : max(LevelBest[Level], this->Score);
		SetColor(3, 0);
		return this->Score;
	}
	else {
		//如果是首层
		CPU->GetWholeScore();
		int *TempList = CPU->GetMax(Ai_Color);
		int Score[10];
		for (int i = 0; i < EachTry; i++) {
			List[i] = new Ai_JudgeTree(TempList[i] / MaxBoard, TempList[i] % MaxBoard, Ai_Color);
			Score[i] = List[i]->Judge(Level - 1, CPU, ChessColor(Ai_Color * -1), LevelBest);
		}
		int Max = 0;
		for (int i = 1; i < EachTry; i++) {
			if (Score[i] > Score[Max])
				Max = i;
		}
		Max = TempList[Max];
		delete TempList;
		return Max;
	}
}
