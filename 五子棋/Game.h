#ifndef Game_h
#define Game_h

#include "std.h"
#include "Board.h"

class Game {
private:
	ScoreJudger * Adun;
	Board * chess;
	ChessColor Turn;
	Ai *Super;
public:
	Game();
	void onDisplay();
	bool onUpdate();
	void myMouse(int button, int state, int x, int y);
};

Game::Game()
{
	chess = new Board();
	Turn = BLACK;
	Adun = new ScoreJudger();
	Super = new Ai();
}

void Game::onDisplay()
{
	chess->onDisplay();
}

bool Game::onUpdate()
{
	return chess->onUpdate();
}

void Game::myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		/*printf("%d %d\n", x / ChessSize - 1, y / ChessSize - 1);*/
		system("cls");
		if (chess->myMouse(Turn, (x + ChessSize / 2) / ChessSize - 1, (y + ChessSize / 2) / ChessSize - 1))
			Turn = Turn == BLACK ? WHITE : BLACK;
		onDisplay();
		glutSwapBuffers();
		onDisplay();
		glutSwapBuffers();
		if (onUpdate())
			return;
		int Clock = clock();
		int Res = Super->Judge(chess, Turn);
		printf("Cost Time %d\n", clock() - Clock);
		chess->myMouse(Turn, Res / MaxBoard, Res % MaxBoard);
		Turn = Turn == BLACK ? WHITE : BLACK;
	}
}

#endif // !Game_h
