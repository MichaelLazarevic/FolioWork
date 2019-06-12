#include "chess.h"



chess::chess()
{
	currentSpot.x = 6;
	currentSpot.y = 4;
}

chess::~chess()
{
}

void chess::setupBoard()
{
	// An initial set up of the board in regards to colours.
	// The black and white pattern is made up like so.
	bool t_black = true;

	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			chessBoard[i][k].pieceTeam = COLOUR_EMPTY;
			if (t_black)
			{
				chessBoard[i][k].colour = COLOUR_BLACK;
				chessBoard[i][k].prevColour = COLOUR_BLACK;
			}
			else
			{
				chessBoard[i][k].colour = COLOUR_WHITE;
				chessBoard[i][k].prevColour = COLOUR_WHITE;
			}
			t_black = !t_black;

			if (i == currentSpot.x && k == currentSpot.y)
			{
				chessBoard[i][k].colour = COLOUR_YELLOW;
			}
		}
		t_black = !t_black;
	}

	setupPieces();
}

void chess::setupPieces()
{
	// An initial setup of pieces for their first time on the board.
	float posX = -10;
	float posZ = -30;

	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			chessBoard[i][k].coord.x = i;
			chessBoard[i][k].coord.y = k;
			chessBoard[i][k].location = Matrix4::translation(Vector3(posX, -5, posZ));
			posZ += 3;
			if (i == 1)
			{
				chessBoard[i][k].piece = PT_OBJECT_BLACK_PAWN;
				chessBoard[i][k].pieceTeam = COLOUR_BLACK;

			}
			else if (i == 6)
			{
				chessBoard[i][k].piece = PT_OBJECT_WHITE_PAWN;
				chessBoard[i][k].pieceTeam = COLOUR_WHITE;
			}
			else
			{
				if (i == 0)
				{
					switch (k) {
					case 0:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_ROOK;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					case 1:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_KNIGHT;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					case 2:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_BISHOP;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					case 3:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_KING;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					case 4:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_QUEEN;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					case 5:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_BISHOP;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					case 6:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_KNIGHT;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					case 7:
						chessBoard[i][k].piece = PT_OBJECT_BLACK_ROOK;
						chessBoard[i][k].pieceTeam = COLOUR_BLACK;
						break;
					default:
						break;
					}
				}
				else if (i == 7)
				{
					switch (k) {
					case 0:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_ROOK;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					case 1:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_KNIGHT;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					case 2:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_BISHOP;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					case 3:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_KING;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					case 4:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_QUEEN;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					case 5:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_BISHOP;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					case 6:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_KNIGHT;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					case 7:
						chessBoard[i][k].piece = PT_OBJECT_WHITE_ROOK;
						chessBoard[i][k].pieceTeam = COLOUR_WHITE;
						break;
					default:
						break;
					}
				}
				else {
					chessBoard[i][k].piece = PIECE_EMPTY;
				}
			}
		}
		posX += 3;
		posZ = -30;
	}
}

void chess::refreshBoard()
{
	// Reset the colours of the board, runs every time the playerState changes
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			chessBoard[i][k].colour = chessBoard[i][k].prevColour;
			if (i == currentSpot.x && k == currentSpot.y)
			{
				chessBoard[i][k].colour = COLOUR_YELLOW;
			}
		}
	}
}

bool chess::checkMove(coord l_startSpot, coord l_targetSpot, ptMove l_type)
{
	// Confirms that the current spot and target spot are not both pieces of
	// the same team, which is an illegal move.
	bool condition = true;
	if (chessBoard[l_targetSpot.x][l_targetSpot.y].pieceTeam != chessBoard[l_startSpot.x][l_startSpot.y].pieceTeam)
	{
		if (chessBoard[l_targetSpot.x][l_targetSpot.y].piece == PIECE_EMPTY)
		{
			if (l_type == MOVE_ATTACK)
			{
				chessBoard[l_targetSpot.x][l_targetSpot.y].colour = COLOUR_RED;
			}
			else
			{
				chessBoard[l_targetSpot.x][l_targetSpot.y].targetted = true;
			}
		}
		else
		{
			if (l_type == MOVE_ATTACK)
			{
				chessBoard[l_targetSpot.x][l_targetSpot.y].colour = COLOUR_RED;
			}
			else
			{
				chessBoard[l_targetSpot.x][l_targetSpot.y].targetted = true;
			}
			condition = false;
		}
	}
	else
	{
		if (l_type == MOVE_DEFENSE)
		{
			chessBoard[l_targetSpot.x][l_targetSpot.y].targetted = true;
		}
		condition = false;
	}
	return condition;
}

bool chess::showMoves(coord l_spot, ptMove l_type)
{
	// Takes in a spot on the board and deduces
	// where this piece can and can't move.
	// l_type denotes whether this is to be used to
	// actually move, or deduce unsafe spots.
	bool result = true;
	int j = 0;
	int l = 0;
	int xCord = l_spot.x;
	int yCord = l_spot.y;
	switch (chessBoard[xCord][yCord].piece)
	{
	case PT_OBJECT_BLACK_BISHOP:
	case PT_OBJECT_WHITE_BISHOP:
		printf("BISHOP MOVES\n");
		// SHOWING MOVES FOR BISHOPS

		j = yCord + 1;
		l = yCord - 1;
		for (int i = xCord + 1; i < 8; i++)
		{
			// LOOPING ACCROSS DIAGONALS WITH POSITIVE X
			if (j < 8)
			{
				if (!checkMove(coord(xCord, yCord), coord(i, j), l_type))
				{
					j = 8;
				}
			}
			if (l >= 0)
			{
				if (!checkMove(coord(xCord, yCord), coord(i, l), l_type))
				{
					l = -1;
				}
			}
			l--;
			j++;
		}

		j = yCord + 1;
		l = yCord - 1;
		for (int i = xCord - 1; i >= 0; i--)
		{
			// LOOPING ACCROSS DIAGONALS WITH NEGATIVE X
			if (j < 8)
			{
				if (!checkMove(coord(xCord, yCord), coord(i, j), l_type))
				{
					j = 8;
				}
			}
			if (l >= 0)
			{
				if (!checkMove(coord(xCord, yCord), coord(i, l), l_type))
				{
					l = -1;
				}
			}
			l--;
			j++;
		}
		break;
	case PT_OBJECT_BLACK_KNIGHT:
	case PT_OBJECT_WHITE_KNIGHT:
		printf("KNIGHT MOVES\n");
		if (xCord - 2 >= 0 && yCord - 1 >= 0)
		{
			checkMove(coord(xCord, yCord), coord(xCord - 2, yCord - 1), l_type);
		}
		if (xCord - 2 >= 0 && yCord + 1 < 8)
		{
			checkMove(coord(xCord, yCord), coord(xCord - 2, yCord + 1), l_type);
		}


		if (xCord + 2 < 8 && yCord - 1 >= 0)
		{
			checkMove(coord(xCord, yCord), coord(xCord + 2, yCord - 1), l_type);
		}
		if (xCord + 2 < 8 && yCord + 1 < 8)
		{
			checkMove(coord(xCord, yCord), coord(xCord + 2, yCord + 1), l_type);
		}


		if (xCord - 1 >= 0 && yCord - 2 >= 0)
		{
			checkMove(coord(xCord, yCord), coord(xCord - 1, yCord - 2), l_type);
		}
		if (xCord - 1 >= 0 && yCord + 2 < 8)
		{
			checkMove(coord(xCord, yCord), coord(xCord - 1, yCord + 2), l_type);
		}


		if (xCord + 1 < 8 && yCord - 2 >= 0)
		{

			checkMove(coord(xCord, yCord), coord(xCord + 1, yCord - 2), l_type);
		}
		if (xCord + 1 < 8 && yCord + 2 < 8)
		{
			checkMove(coord(xCord, yCord), coord(xCord + 1, yCord + 2), l_type);
		}

		break;
	case PT_OBJECT_BLACK_KING:
	case PT_OBJECT_WHITE_KING:
		printf("KING MOVES\n");
		for (int i = xCord - 1; i < xCord + 2; i++)
		{
			for (int k = yCord - 1; k < yCord + 2; k++)
			{
				if (i >= 0 && i < 8 && k < 8 && k >= 0)
				{
					if (!chessBoard[i][k].targetted)
					{
						if (chessBoard[i][k].pieceTeam != chessBoard[xCord][yCord].pieceTeam)
						{
							checkMove(coord(xCord, yCord), coord(i, k), l_type);
						}
					}
				}
			}
		}

		break;
	case PT_OBJECT_BLACK_QUEEN:
	case PT_OBJECT_WHITE_QUEEN:
		printf("QUEEN MOVES\n");
		j = yCord + 1;
		l = yCord - 1;
		printf("[%i], [%i]", xCord, yCord);
		for (int i = xCord + 1; i < 8; i++)
		{
			// LOOPING ACCROSS DIAGONALS WITH POSITIVE X
			if (j < 8)
			{
				if (!checkMove(coord(xCord, yCord), coord(i, j), l_type))
				{
					j = 8;
				}
			}
			if (l >= 0)
			{

				if (!checkMove(coord(xCord, yCord), coord(i, l), l_type))
				{
					l = -1;
				}
			}
			l--;
			j++;
		}

		j = yCord + 1;
		l = yCord - 1;
		for (int i = xCord - 1; i >= 0; i--)
		{
			// LOOPING ACCROSS DIAGONALS WITH NEGATIVE X
			if (j < 8)
			{

				if (!checkMove(coord(xCord, yCord), coord(i, j), l_type))
				{
					j = 8;
				}
			}
			if (l >= 0)
			{
				if (!checkMove(coord(xCord, yCord), coord(i, l), l_type))
				{
					l = -1;
				}
			}
			l--;
			j++;
		}

		for (int i = xCord + 1; i < 8; i++)
		{
			// LOOPING HORIZONTAL MOVEMENT, POSITIVE X
			if (!checkMove(coord(xCord, yCord), coord(i, yCord), l_type))
			{
				i = 8;
			}
		}


		for (int i = xCord - 1; i >= 0; i--)
		{
			// LOOPING HORIZONTAL MOVEMENT, POSITIVE X
			if (!checkMove(coord(xCord, yCord), coord(i, yCord), l_type))
			{
				i = -1;
			}
		}


		for (int i = yCord + 1; i < 8; i++)
		{
			// LOOPING HORIZONTAL MOVEMENT, POSITIVE Y
			if (!checkMove(coord(xCord, yCord), coord(xCord, i), l_type))
			{
				i = 8;
			}
		}


		for (int i = yCord - 1; i >= 0; i--)
		{
			// LOOPING HORIZONTAL MOVEMENT, NEGATIVE Y
			if (!checkMove(coord(xCord, yCord), coord(xCord, i), l_type))
			{
				i = -1;
			}
		}
		break;
	case PT_OBJECT_BLACK_ROOK:
	case PT_OBJECT_WHITE_ROOK:

		printf("ROOK MOVES\n");
		for (int i = xCord + 1; i < 8; i++)
		{
			// LOOPING HORIZONTAL MOVEMENT, POSITIVE X
			if (!checkMove(coord(xCord, yCord), coord(i, yCord), l_type))
			{
				i = 8;
			}
		}


		for (int i = xCord - 1; i >= 0; i--)
		{
			// LOOPING HORIZONTAL MOVEMENT, POSITIVE X
			if (!checkMove(coord(xCord, yCord), coord(i, yCord), l_type))
			{
				i = -1;
			}
		}


		for (int i = yCord + 1; i < 8; i++)
		{
			// LOOPING HORIZONTAL MOVEMENT, POSITIVE Y
			if (!checkMove(coord(xCord, yCord), coord(xCord, i), l_type))
			{
				i = 8;
			}
		}


		for (int i = yCord - 1; i >= 0; i--)
		{
			// LOOPING HORIZONTAL MOVEMENT, NEGATIVE Y
			if (!checkMove(coord(xCord, yCord), coord(xCord, i), l_type))
			{
				i = -1;
			}
		}
break;
	case PT_OBJECT_BLACK_PAWN:
		printf("PAWN MOVES\n");
		if ((xCord + 1) <= 7)
		{
			if (chessBoard[xCord + 1][yCord].piece == PIECE_EMPTY)
			{
				checkMove(coord(xCord, yCord), coord(xCord + 1, yCord), l_type);
				if (xCord == 1 && chessBoard[xCord + 2][yCord].piece == PIECE_EMPTY)
				{
					checkMove(coord(xCord, yCord), coord(xCord + 2, yCord), l_type);
				}
			}
			if (yCord + 1 < 8)
			{
				if (chessBoard[xCord + 1][yCord + 1].piece != PIECE_EMPTY)
				{
					checkMove(coord(xCord, yCord), coord(xCord + 1, yCord + 1), l_type);
				}
			}
			if (yCord - 1 >= 0)
			{
				if (chessBoard[xCord + 1][yCord - 1].piece != PIECE_EMPTY)
				{
					checkMove(coord(xCord, yCord), coord(xCord + 1, yCord - 1), l_type);
				}
			}
		}
		break;
	case PT_OBJECT_WHITE_PAWN:
		printf("PAWN MOVES\n");
		if ((xCord - 1) >= 0)
		{
			if (chessBoard[xCord - 1][yCord].piece == PIECE_EMPTY)
			{
				checkMove(coord(xCord, yCord), coord(xCord - 1, yCord), l_type);
				if (xCord == 6 && chessBoard[xCord - 2][yCord].piece == PIECE_EMPTY)
				{
					checkMove(coord(xCord, yCord), coord(xCord - 2, yCord), l_type);
				}
			}
			if (yCord + 1 < 8)
			{
				if (chessBoard[xCord - 1][yCord + 1].piece != PIECE_EMPTY)
				{
					checkMove(coord(xCord, yCord), coord(xCord - 1, yCord + 1), l_type);
				}
			}
			if (yCord - 1 >= 0)
			{
				if (chessBoard[xCord - 1][yCord - 1].piece != PIECE_EMPTY)
				{
					checkMove(coord(xCord, yCord), coord(xCord - 1, yCord - 1), l_type);
				}
			}
		}
		break;
	case PIECE_EMPTY:
	default:
		result = false;
		break;
	}
	if (result)
	{
		tallyMoves();
	}
	return result;
}

void chess::checkAllMoves(ptColour team)
{
	// Loops through every space on the board
	// and checks the possible movements for
	// every piece on the enemy team in order
	// to deduce which places are safe for your king
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (chessBoard[i][k].pieceTeam != team)
			{
				showMoves(coord(i, k), MOVE_DEFENSE);
			}
		}
	}
}

bool chess::movePiece()
{
	// Moves the piece from the currently selected spot
	// to the currently targetted spot in the list of possible moves.
	bool checkMate = false;
	if (chessBoard[targetSpot.x][targetSpot.y].piece == PT_OBJECT_BLACK_KING ||
		chessBoard[targetSpot.x][targetSpot.y].piece == PT_OBJECT_WHITE_KING)
	{
		checkMate = true;
	}

	if (chessBoard[currentSpot.x][currentSpot.y].piece == PT_OBJECT_WHITE_KING && 
		whiteKingFirst &&
		targetSpot.x == 7 && 
		targetSpot.y == 2 &&
		chessBoard[7][2].piece == PIECE_EMPTY &&
		chessBoard[7][0].piece == PT_OBJECT_WHITE_ROOK)
	{
		chessBoard[7][1].piece = PT_OBJECT_WHITE_KING;
		chessBoard[7][1].pieceTeam = COLOUR_WHITE;
		chessBoard[7][2].piece = PT_OBJECT_WHITE_ROOK;
		chessBoard[7][2].pieceTeam = COLOUR_WHITE;
		chessBoard[currentSpot.x][currentSpot.y].piece = PIECE_EMPTY;
		chessBoard[currentSpot.x][currentSpot.y].pieceTeam = COLOUR_EMPTY;
		chessBoard[7][0].piece = PIECE_EMPTY;
		chessBoard[7][0].pieceTeam = COLOUR_EMPTY;
		whiteKingFirst = false;
	}
	else if (chessBoard[currentSpot.x][currentSpot.y].piece == PT_OBJECT_BLACK_KING &&
		blackKingFirst &&
		targetSpot.x == 0 &&
		targetSpot.y == 2 &&
		chessBoard[0][2].piece == PIECE_EMPTY &&
		chessBoard[0][0].piece == PT_OBJECT_BLACK_ROOK)
	{
		chessBoard[0][1].piece = PT_OBJECT_BLACK_KING;
		chessBoard[0][1].pieceTeam = COLOUR_BLACK;
		chessBoard[0][2].piece = PT_OBJECT_BLACK_ROOK;
		chessBoard[0][2].pieceTeam = COLOUR_BLACK;
		chessBoard[currentSpot.x][currentSpot.y].piece = PIECE_EMPTY;
		chessBoard[currentSpot.x][currentSpot.y].pieceTeam = COLOUR_EMPTY;
		chessBoard[0][0].piece = PIECE_EMPTY;
		chessBoard[0][0].pieceTeam = COLOUR_EMPTY;
		blackKingFirst = false;
	}
	else
	{
		chessBoard[targetSpot.x][targetSpot.y].piece = chessBoard[currentSpot.x][currentSpot.y].piece;
		chessBoard[targetSpot.x][targetSpot.y].pieceTeam = chessBoard[currentSpot.x][currentSpot.y].pieceTeam;
		if (chessBoard[currentSpot.x][currentSpot.y].piece == PT_OBJECT_BLACK_KING)
		{
			blackKingFirst = false;
		}
		else if (chessBoard[currentSpot.x][currentSpot.y].piece == PT_OBJECT_WHITE_KING)
		{
			whiteKingFirst = false;
		}
		chessBoard[currentSpot.x][currentSpot.y].piece = PIECE_EMPTY;
		chessBoard[currentSpot.x][currentSpot.y].pieceTeam = COLOUR_EMPTY;
	}
	refreshTargets();
	refreshBoard();
	return checkMate;
}

void chess::tallyMoves()
{
	// This function counts how many
	// places a piece can move to
	// and lists them in a dynamic array
	// so that the player can cycle through them
	if (targetList != NULL)
	{
		resetList();
	}
	int counter = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (chessBoard[i][k].colour == COLOUR_RED)
			{
				counter++;
			}
		}
	}
	targetList = new coord[counter];
	listSize = counter;
	if (counter > 0)
	{
		counter = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (chessBoard[i][k].colour == COLOUR_RED)
				{
					targetList[counter] = chessBoard[i][k].coord;
					printf("Cords: [%i], [%i]\n", targetList[counter].x, targetList[counter].y);
					counter++;
				}
			}
		}
		cycleList(0);
	}
}

void chess::resetList()
{
	// This function resets the list of possible moves. Runs whenever a piece moves
	// or a movement is cancelled.
	delete[] targetList;
	targetList = NULL;
	listSize = 0;
	listPosition = 0;
}

void chess::cycleList(int i)
{
	// This function cycles through elements in the list
	// depending on the number provided
	if (listSize > 0)
	{
		int x = targetList[listPosition].x;
		int y = targetList[listPosition].y;

		chessBoard[x][y].colour = COLOUR_RED;

		listPosition += i;
		if (listPosition >= listSize)
		{
			listPosition = 0;
		}
		else if (listPosition < 0)
		{
			listPosition = listSize - 1;
		}
		x = targetList[listPosition].x;
		y = targetList[listPosition].y;

		chessBoard[x][y].colour = COLOUR_GREEN;
		targetSpot.x = x;
		targetSpot.y = y;
	}
}

void chess::refreshTargets()
{
	// This resets the board to a default state
	// "Targetted" refers to when a space can be
	// targetted by an opponent piece. Preventing
	// the Kings from moving to said spaces.
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			chessBoard[i][k].targetted = false;
		}
	}
}