#include "Ai.h"

Ai::Ai()
{
	CPU = new ScoreJudger();
	Head = new Ai_JudgeTree(-1, -1, WHITE);
	for (int i = 0; i < MaxLevel; i++)
		LevelBest[i] = -1;
}

int Ai::Judge(Board *p,ChessColor color)
{
	CPU->GetBoard(p);
	return Head->Judge(MaxLevel, CPU, color, LevelBest);
}