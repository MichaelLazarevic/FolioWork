#ifndef __CHESS_BOARD__
#define __CHESS_BOARD__


#include "../toolkit/toolkit.h"

enum ptObjectsEnum {
	PT_OBJECT_BLACK_KNIGHT,
	PT_OBJECT_WHITE_KING,
	PT_OBJECT_BLACK_KING,
	PT_OBJECT_WHITE_QUEEN,
	PT_OBJECT_WHITE_KNIGHT,
	PT_OBJECT_WHITE_BISHOP,
	PT_OBJECT_WHITE_ROOK,
	PT_OBJECT_WHITE_PAWN,
	PT_OBJECT_BLACK_BISHOP,
	PT_OBJECT_BLACK_ROOK,
	PT_OBJECT_BLACK_QUEEN,
	PT_OBJECT_BLACK_PAWN,
	PT_OBJECT_BLACK_CUBE,
	PT_OBJECT_WHITE_CUBE,
	PT_OBJECT_YELLOW_CUBE,
	PT_OBJECT_RED_CUBE,
	PT_OBJECT_GREEN_CUBE,
	PIECE_EMPTY,
	PT_OBJECT_HARD,
	PT_OBJECT_CUBE,
	PT_OBJECT_COUNT = 20
};

enum ptColour {
	COLOUR_RED,
	COLOUR_WHITE,
	COLOUR_BLACK,
	COLOUR_YELLOW,
	COLOUR_GREEN,
	COLOUR_EMPTY,
};

enum ptMove {
	MOVE_ATTACK,
	MOVE_DEFENSE
};

struct coord {
	int x;
	int y;
	coord(int xt = 0, int yt = 0) : x(xt), y(yt) {}
};

struct boardSpot {
	coord coord;
	Matrix4 location;
	ptColour colour;
	ptColour prevColour;
	ptObjectsEnum piece;
	ptColour pieceTeam;
	bool targetted = false;
};

class chess
{
public:
	boardSpot chessBoard[8][8];
	coord* targetList = NULL;
	int listSize = 0;
	int listPosition = 0;
	coord currentSpot;
	coord targetSpot;
	chess();
	~chess();
	bool whiteKingFirst = true;
	bool blackKingFirst = true;

	void setupBoard();
	void setupPieces();
	void refreshBoard();
	bool checkMove(coord l_startSpot, coord l_targetSpot, ptMove l_type);
	bool showMoves(coord l_spot, ptMove l_type);
	void checkAllMoves(ptColour team);
	bool movePiece();
	void tallyMoves();
	void resetList();
	void cycleList(int i);
	void refreshTargets();
};

#endif // !__CHESS_BOARD__

