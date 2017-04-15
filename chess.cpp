// Chess.cpp : Defines the entry point for the console application.
// Code by claycot

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

#define CHARACTER_BUFFER '0'
#define CHARACTER_WHITEPAWN 'P'
#define CHARACTER_WHITEROOK 'R'
#define CHARACTER_WHITEKNIGHT 'N'
#define CHARACTER_WHITEBISHOP 'B'
#define CHARACTER_WHITEQUEEN 'Q'
#define CHARACTER_WHITEKING 'K'
#define CHARACTER_BLACKPAWN 'p'
#define CHARACTER_BLACKROOK 'r'
#define CHARACTER_BLACKKNIGHT 'n'
#define CHARACTER_BLACKBISHOP 'b'
#define CHARACTER_BLACKQUEEN 'q'
#define CHARACTER_BLACKKING 'k'

using namespace std;

enum Team {
	TEAM_WHITE,
	TEAM_BLACK
};

enum PieceType {
	PIECE_PAWN,
	PIECE_ROOK,
	PIECE_KNIGHT,
	PIECE_BISHOP,
	PIECE_QUEEN,
	PIECE_KING
};

enum Status {
	STATUS_ALIVE,
	STATUS_DEAD,
	STATUS_UPGRADED
};

int charToInt(char inputChar);
char intToChar(int inputInt);

class Piece {
private:
	char m_posCol;
	int m_posRow;
	PieceType m_type;
	Team m_team;	
	Status m_status;

public:
	//Default piece constructor
	Piece(char posCol = 'A', int posRow = 1, PieceType type = PIECE_PAWN, 
		Team team = TEAM_WHITE, Status status = STATUS_ALIVE) {
		m_posCol = posCol;
		m_posRow = posRow; 
		m_type = type;
		m_team = team;		
		m_status = status;
	}
	
	//Debug function to see details about a piece
	void PrintDetails() {
		cout << "At row " << m_posRow << " and col " << m_posCol
			<< " there is a piece " << m_team << " " << m_type << endl;
	}

	//Get functions
	int getCol() {
		return charToInt(m_posCol);
	}
	int getRow() {
		return m_posRow;
	}
	PieceType getType() {
		return m_type;
	}
	Team getTeam() {
		return m_team;
	}
	Status getStatus() {
		return m_status;
	}

	//Set functions
	//For use when a pawn reaches the end of the board
	void upgradePiece(PieceType newType) {
		m_type = newType;
		m_status = STATUS_UPGRADED;
	}
};


void clearBoard(char gameBoard[10][10]);
void refreshBoard(char gameBoard[10][10], vector<Piece> &gamePieces);
void drawBoard(char gameBoard[10][10]);
void resetPieces(vector<Piece> &gamePieces);

int main()
{
	//Make a gameboard with buffer all around
	char gameBoard[10][10] = { CHARACTER_BUFFER };
	
	//Make a vector to hold all of the pieces
	vector<Piece> gamePieces;
	//Reset the vector with starting positions for all pieces
	resetPieces(gamePieces);

	//Update the gameboard
	refreshBoard(gameBoard, gamePieces);

	//Draw the gameboard
	drawBoard(gameBoard);

	system("PAUSE");

    return 0;
}

//Convert a character A through H to an int for indexing
int charToInt(char inputChar){
	string matchMe = "ABCDEFGH";
	for (int index = 1; index <= 8; index++) {
		if (inputChar == matchMe[index - 1]) {
			return index;
		}
	}
	return -1;
}

//Convert an int 1 through 8 to a char for board
char intToChar(int inputInt) {
	string convertMe = "ABCDEFGH";
	return convertMe[inputInt - 1];
}

//Set the board back to all blank, with buffer reset
void clearBoard(char gameBoard[10][10]) {
	for (int row = 0; row <= 9; row++) {
		for (int col = 0; col <= 9; col++) {
			switch (row) {
			//Fill first row and last row with buffer
			case 0:
				gameBoard[row][col] = CHARACTER_BUFFER;
				break;
			case 9:
				gameBoard[row][col] = CHARACTER_BUFFER;
				break;
			//Fill middle rows
			default:
				switch (col) {
				//Fill first and last col with buffer
				case 0:
					gameBoard[row][col] = CHARACTER_BUFFER;
					break;
				case 9:
					gameBoard[row][col] = CHARACTER_BUFFER;
					break;
				//Fill actual playing space
				default:
					gameBoard[row][col] = ' ';
				}
			}
		}
	}
}

//Update every square on the game board
void refreshBoard(char gameBoard[10][10], vector<Piece> &gamePieces) {
	//Clear the board
	clearBoard(gameBoard);

	//Loop through each piece on the array
	for (Piece thisPiece : gamePieces) {
		//Temp variables to hold characteristics of the piece
		int row = thisPiece.getRow();
		int col = thisPiece.getCol();
		PieceType type = thisPiece.getType();
		Team team = thisPiece.getTeam();
		Status status = thisPiece.getStatus();
		
		//If the piece isn't dead, add it to the board
		if (status != STATUS_DEAD) {
			switch (team) {
				//Draw white pieces one way
				case TEAM_WHITE:
					switch (type) {
					case PIECE_PAWN:
						gameBoard[row][col] = CHARACTER_WHITEPAWN;
						break;
					case PIECE_ROOK:
						gameBoard[row][col] = CHARACTER_WHITEROOK;
						break;
					case PIECE_KNIGHT:
						gameBoard[row][col] = CHARACTER_WHITEKNIGHT;
						break;
					case PIECE_BISHOP:
						gameBoard[row][col] = CHARACTER_WHITEBISHOP;
						break;
					case PIECE_QUEEN:
						gameBoard[row][col] = CHARACTER_WHITEQUEEN;
						break;
					case PIECE_KING:
						gameBoard[row][col] = CHARACTER_WHITEKING;
						break;
					}
				break;
				//Draw black pieces another way
				case TEAM_BLACK:
					switch (type) {
					case PIECE_PAWN:
						gameBoard[row][col] = CHARACTER_BLACKPAWN;
						break;
					case PIECE_ROOK:
						gameBoard[row][col] = CHARACTER_BLACKROOK;
						break;
					case PIECE_KNIGHT:
						gameBoard[row][col] = CHARACTER_BLACKKNIGHT;
						break;
					case PIECE_BISHOP:
						gameBoard[row][col] = CHARACTER_BLACKBISHOP;
						break;
					case PIECE_QUEEN:
						gameBoard[row][col] = CHARACTER_BLACKQUEEN;
						break;
					case PIECE_KING:
						gameBoard[row][col] = CHARACTER_BLACKKING;
						break;
					}
				break;
			}
		}
	}
}

//Draw the board (with headers for row and col)
void drawBoard(char gameBoard[10][10]) {
	//Draw column headers
	cout << "  A B C D E F G H" << endl;

	//Loop through each row on the board
	for (int row = 8; row >= 1; row--) {
		//Draw row headers
		cout << row << " ";
		
		//Loop through each col on the board
		for (int col = 1; col <= 8; col++) {
			//Draw the piece on the board
			cout << gameBoard[row][col] << " ";
		}

		//Go onto the next line for the next row
		cout << endl;
	}
}

void resetPieces(vector<Piece> &gamePieces) {
	//Clear the array
	gamePieces.clear();

	//Place everything except for the pawns
	gamePieces.push_back(Piece('A', 1, PIECE_ROOK));
	gamePieces.push_back(Piece('B', 1, PIECE_KNIGHT));
	gamePieces.push_back(Piece('C', 1, PIECE_BISHOP));
	gamePieces.push_back(Piece('D', 1, PIECE_KING));
	gamePieces.push_back(Piece('E', 1, PIECE_QUEEN));
	gamePieces.push_back(Piece('F', 1, PIECE_BISHOP));
	gamePieces.push_back(Piece('G', 1, PIECE_KNIGHT));
	gamePieces.push_back(Piece('H', 1, PIECE_ROOK));
	gamePieces.push_back(Piece('A', 8, PIECE_ROOK, TEAM_BLACK));
	gamePieces.push_back(Piece('B', 8, PIECE_KNIGHT, TEAM_BLACK));
	gamePieces.push_back(Piece('C', 8, PIECE_BISHOP, TEAM_BLACK));
	gamePieces.push_back(Piece('D', 8, PIECE_KING, TEAM_BLACK));
	gamePieces.push_back(Piece('E', 8, PIECE_QUEEN, TEAM_BLACK));
	gamePieces.push_back(Piece('F', 8, PIECE_BISHOP, TEAM_BLACK));
	gamePieces.push_back(Piece('G', 8, PIECE_KNIGHT, TEAM_BLACK));
	gamePieces.push_back(Piece('H', 8, PIECE_ROOK, TEAM_BLACK));

	//Place all the pawns
	for (int col = charToInt('A'); col <= charToInt('H'); col++){
		//White pawn
		gamePieces.push_back(Piece(intToChar(col), 2));
		//Black pawn
		gamePieces.push_back(Piece(intToChar(col), 7, PIECE_PAWN, TEAM_BLACK));
	}

	return;
}
