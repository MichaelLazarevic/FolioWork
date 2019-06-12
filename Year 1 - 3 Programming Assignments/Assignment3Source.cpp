// Title   : Assignment3Source.cpp
// Purpose : A console game as defined by the assignment brief
//           for the third Assignment in CM0403BNN01
// Author  : Anonymous
// Date    : 05/12/2015
// Updated : 05/01/2016 - Added new feature as specified.
// New special peg randomly appears on board, disappears after
// it has moved 3 times, cannot be jumped over.

// This program runs a game called 'Simple Solitaire'.
// The rules are as specified by the brief.
// The user can choose a peg, getting warned if he chooses
// an invalid peg or inputs the wrong data.
// He can choose a direction to move the peg, as well as cancel his choice.
// The pegs will move and delete the jumped over one as specified
// Each loop iteration will run the output subprogram to give
// the user a visual aid.
// Score will be displayed at the end, and if the score is higher than the
// High score, that will be displayed for every round after.

// While not specified, the program keeps track of all the possible
// Moves the user can make in the boards current state, outputting
// That information and ending the round thusly if it ever reaches 0.

// Include standard IO streams library, the standard string class and the
// standard character array 'cstring' library. The sstream library
// is also included for string int conversions.
#include <iostream>
#include <string>
#include <ctime>

// Using the standard namespace as this is a one programmer project.
// Put after the includes because of the C++ standard.  
using namespace std;

// Constant definitions for the size of the board.
// X and Y used for ease of use in co-ordinates.
const int XMAX = 5 ;
const int YMAX = 5 ;

// Constant definitions for the Minimum number of pegs required
// for the player to be eligible for score.
// The amount of points for the central peg bonus
// The base score per peg not remaining
// ScoreMax is the amount of score I take away from 
// Via the number of pegs.
const int MINPEGS = 8 ;
const int BONUS = 20 ;
const int SCOREBASE = 10 ;
const int SCOREMAX = 90 ;

// Constant used to refer to how many moves
// it takes to remove a special peg.
const int SPECIALMOVE = 3 ;

// A constant for what key will quit the game.
// A constant for what will cancel the chosen peg
// A constant for the character that represents a peg
// A constant for the character that represents an empty spot
const char QUITKEY = '0' ;
const char CANCEL = 'Q' ;
const char PEGICON = 'O' ;
const char EMPTYICON = '-' ;
const char SPECICON = '@' ;

// Enumeration for Pegs.
// The Pegs are used within the main board array, and tell the
// Output section of the program, which one is which.
enum Pegs { PEG, SPECIAL, EMPTY };

struct userChoice
{
  // Stores the users choice of peg / direction.
  int XcoOrd ;
  int YcoOrd ;
}; // End of Struct userChoice

void pressEnter()
{
  // Sub program that pauses the program until the user
  // presses enter. Anything the user types is put into a buffer
  // array, and never used.
  string buffer ;
  cout << "Hit enter to continue..." << endl ;
  getline(cin, buffer);
} // End of pressEnter

bool playAgain(string input)
{ 
  // *IN* Input
  // This function receives the input, checks if the first letter
  // is 'Y' and returns a boolean.
  // This is to decide if the user wishes to play a second round.
  bool choice ;
  char tempPlace[2] ;
  tempPlace[0] = toupper(input[0]) ;
  if (tempPlace[0] == 'Y')
  {
    choice = true ;
  } // End of IF
  else
  {
    choice = false ;
  } // End of IF ELSE
  return choice ; // *OUT* choice
} // End of playAgain

void instructions()
{
  // Sub program to output the instructions.
  // calls another sub program to delay the program until the user
  // willingly wants to move on.
  cout << "Hello and Welcome to Simple Solitaire!" << endl << endl ;
  cout << "Here I will explain the rules and commands." << endl ;
  cout << "You will be given a grid of pegs, represented by '" << PEGICON ;
  cout << " '" << endl ;
  cout << "You must select one by providing its respected co-ordinates,";
  cout << endl ;
  cout << "in a format like this : 1,1 or 2,2 or 3,1." << endl << endl ;
  cout << "Once you have chosen a peg, you will need to choose" << endl;
  cout << "A direction for it to go, specified by N - E - S - W." << endl;
  cout << "Of course, there will need to be an empty space to land," << endl ;
  cout << "as well as a peg between them to jump over." << endl << endl;
  cout << "Also, a randomly generated SPECIAL beg shall appear" << endl ;
  cout << "on the board, using this : " << SPECICON << "symbol," << endl ;
  cout << "You cannot jump over this peg, but it will disappear after" ;
  cout << endl << "it has jumped over three pegs itself." << endl << endl ;
  cout << "Once you've exhausted all possible moves, the" << endl ;
  cout << "number of pegs left will be counted for points," << endl ;
  cout << "with you getting more points the fewer pegs you have!" << endl ;
  cout << "And if you manage to keep a peg in the center, " << endl ;
  cout << "double points!" << endl << endl ;
  cout << "Typing 0,0 or 0 in the co-ord select will quit the game." << endl ;
  cout << "Typing H in the co-ord select will bring up this menu." << endl ;
  cout << "If after choosing a peg, you have changed your mind" << endl ;
  cout << "Entering Q instead of a direction will cancel." << endl ;
  cout << endl << "Error Messages concerning invalid moves / choices" << endl ;
  cout << "Will appear ABOVE the board after you do them. Check!" << endl ;
  cout << endl ;
  pressEnter() ;
} // End of Instructions

int countMoves(const Pegs board[][YMAX])
{
  // *IN* pegs
  // This function takes in the boards array and checks how many moves
  // are left. It tries moving each peg in every direction, and sees if
  // any of these attempts are valid, incrementing a variable,
  // before returning it.
  int moves = 0 ;
  int i = 0 ;
  int j = 0 ;

  for (i = 0; i < XMAX; i++)
  {
    for (j = 0; j < YMAX; j++)
    {
      if (board[i][j] == PEG)
      {
        if ((i - 2) >= 0 &&
             board[i  -1][j] == PEG &&
             board[i - 2][j] == EMPTY)
        {
          moves++ ;
        } // End of First Nested IF
        if ((i + 2) < XMAX &&
             board[i + 1][j] == PEG &&
             board[i + 2][j] == EMPTY)
        {
          moves++ ;
        } // End of Second Nested IF
        if ((j + 2) < YMAX &&
             board[i][j + 1] == PEG &&
             board[i][j + 2] == EMPTY)
        {
          moves++ ;
        } // End of Third Nested IF
        if ((j - 2) >= 0 &&
             board[i][j - 1] == PEG &&
             board[i][j - 2] == EMPTY)
        {
          moves++ ;
        } // End of Fourth Nested IF
      } // End of IF
    } // End of Nested For loop
  } // End of For loop
  return moves; // *OUT* number of moves remaining.
} // End of countMoves

void output(const Pegs board[][YMAX], int highScore, int specialMoves)
{
  // *INOUT* Board, *IN* highScore, specialMoves
  // Takes in the board array and outputs text
  // onto the string via the specified format requested.
  cout << endl ;
  int i = 0 ;
  int j = 0 ;
  int k = 0 ;
  int botBar = 1 ;
  int sideBar = XMAX ;
  bool firstLine = true ;
  for (i = 0; i < (XMAX + 1); i++)
  {
    if (firstLine)
    {
      cout << "Current High Score : " << highScore << endl << endl;
      firstLine = false ;
    }
    cout << ' ' ;
    for (j = 0; j < (YMAX + 1); j++)
    {
      if (j == YMAX)
      {
        if (i == XMAX)
        {
          cout << " X " ;
        } // End of Nested IF
        else
        {
          cout << " " << sideBar ;
          sideBar-- ;
        } // End of Nested IF ELSE
      } // End of IF
      else if (i == XMAX)
      {
        cout << "  " << botBar << " " ;
        botBar++ ;
      } // End of first ELSE IF
      else if (board[i][j] == PEG)
      {
        cout << " [" << PEGICON << "]" ;
      } // End of second ELSE IF
      else if (board[i][j] == SPECIAL)
      {
        cout << " [" << SPECICON << "]";
      } // End of second ELSE IF
      else
      {
        cout << " [" << EMPTYICON << "]" ;
      } // End of IF ELSE
    } // End of Nested FOR loop
    cout << endl ;
    cout << endl ;
  } // End of FOR loop
    cout << endl << "Possible Moves left : " << countMoves(board) ;
    cout << endl << endl ;
    cout << "Current Moves left to remove special peg : " << specialMoves;
    cout << endl << endl ;
} // End of output

void goNorth(Pegs board[][YMAX], 
             userChoice choice, 
             Pegs currentPeg, 
             int &specialMoves)
{
  // *IN*  choice, currentPeg, *INOUT* board, specialMoves
  // Runs when the user attempts to move a peg North.
  // Checks if the move is possible, then makes the
  // appropriate board changes.
  if ((choice.XcoOrd - 2) >= 0 &&
    (choice.XcoOrd - 2) < XMAX)
  {
    if (board[choice.XcoOrd - 1][choice.YcoOrd] == PEG)
    {
      if (board[choice.XcoOrd - 2][choice.YcoOrd] == EMPTY)
      {
        board[choice.XcoOrd][choice.YcoOrd] = EMPTY;
        board[choice.XcoOrd - 1][choice.YcoOrd] = EMPTY;
        if (currentPeg == SPECIAL)
        {
          specialMoves-- ;
          if (specialMoves == 0)
          {
            currentPeg = EMPTY;
          } // End of Nested, Nested, Nested, Nested IF
        } // End of Nested, Nested, Nested IF
        board[choice.XcoOrd - 2][choice.YcoOrd] = currentPeg;
      } // End of Nested, Nested IF
      else
      {
        cout << "No Empty spot to land!" << endl;
      } // End of Nested, Nested IF ELSE
    } // End of Nested IF
    else
    {
      cout << "No Applicable Peg to jump over!" << endl;
    } // End of Nsted IF ELSE
  } // End of IF
  else
  {
    cout << "Direction went off board! Error!" << endl;
  } // End of IF ELSE
} // End of goNorth


void goEast(Pegs board[][YMAX], 
            userChoice choice, 
            Pegs currentPeg, 
            int &specialMoves)
{
  // *IN*  choice, currentPeg, *INOUT* board, specialMoves
  // Runs when the user attempts to move a peg east.
  // Checks if the move is possible, then makes the
  // appropriate board changes.
  if ((choice.YcoOrd + 2) >= 0 &&
      (choice.YcoOrd + 2) < XMAX)
  {
    if (board[choice.XcoOrd][choice.YcoOrd + 1] == PEG)
    {
      if (board[choice.XcoOrd][choice.YcoOrd + 2] == EMPTY)
      {
        board[choice.XcoOrd][choice.YcoOrd] = EMPTY;
        board[choice.XcoOrd][choice.YcoOrd + 1] = EMPTY;
        if (currentPeg == SPECIAL)
        {
          specialMoves--;
          if (specialMoves == 0)
          {
            currentPeg = EMPTY;
          } // End of Nested, Nested, Nested, Nested IF
        } // End of Nested, Nested, Nested IF
        board[choice.XcoOrd][choice.YcoOrd + 2] = currentPeg;
      } // End of Nested, Nested IF
      else
      {
        cout << "No Empty spot to land!" << endl;
      } // End of Nested, Nested IF ELSE
    } // End of Nested IF
    else
    {
      cout << "No Applicable Peg to jump over!" << endl;
    } // End of Nsted IF ELSE
  } // End of IF
  else
  {
    cout << "Direction went off board! Error!" << endl;
  } // End of IF ELSE
} // End of GoEast


void goSouth(Pegs board[][YMAX], 
             userChoice choice, 
             Pegs currentPeg, 
             int &specialMoves)
{
  // *IN*  choice, currentPeg, *INOUT* board, specialMoves
  // Runs when the user attempts to move a peg South.
  // Checks if the move is possible, then makes the
  // appropriate board changes.
  if ((choice.XcoOrd + 2) >= 0 &&
    (choice.XcoOrd + 2) < XMAX)
  {
    if (board[choice.XcoOrd + 1][choice.YcoOrd] == PEG)
    {
      if (board[choice.XcoOrd + 2][choice.YcoOrd] == EMPTY)
      {
        board[choice.XcoOrd][choice.YcoOrd] = EMPTY;
        board[choice.XcoOrd + 1][choice.YcoOrd] = EMPTY;
        if (currentPeg == SPECIAL)
        {
          specialMoves--;
          if (specialMoves == 0)
          {
            currentPeg = EMPTY;
          } // End of Nested, Nested, Nested, Nested IF
        } // End of Nested, Nested, Nested IF
        board[choice.XcoOrd + 2][choice.YcoOrd] = currentPeg;
      } // End of Nested, Nested IF
      else
      {
        cout << "No Empty spot to land!" << endl;
      } // End of Nested, Nested IF ELSE
    } // End of Nested IF
    else
    {
      cout << "No Applicable Peg to jump over!" << endl;
    } // End of Nsted IF ELSE
  } // End of IF
  else
  {
    cout << "Direction went off board! Error!" << endl;
  } // End of IF ELSE
} // End of goSouth


void goWest(Pegs board[][YMAX], 
            userChoice choice, 
            Pegs currentPeg, 
            int &specialMoves)
{
  // *IN*  choice, currentPeg, *INOUT* board, specialMoves
  // Runs when the user attempts to move a peg West.
  // Checks if the move is possible, then makes the
  // appropriate board changes.
  if ((choice.YcoOrd - 2) >= 0 &&
    (choice.YcoOrd - 2) < XMAX)
  {
    if (board[choice.XcoOrd][choice.YcoOrd - 1] == PEG)
    {
      if (board[choice.XcoOrd][choice.YcoOrd - 2] == EMPTY)
      {
        board[choice.XcoOrd][choice.YcoOrd] = EMPTY;
        board[choice.XcoOrd][choice.YcoOrd - 1] = EMPTY;
        if (currentPeg == SPECIAL)
        {
          specialMoves--;
          if (specialMoves == 0)
          {
            currentPeg = EMPTY;
          } // End of Nested, Nested, Nested, Nested IF
        } // End of Nested, Nested, Nested IF
        board[choice.XcoOrd][choice.YcoOrd - 2] = currentPeg;
      } // End of Nested, Nested IF
      else
      {
        cout << "No Empty spot to land!" << endl;
      } // End of Nested, Nested IF ELSE
    } // End of Nested IF
    else
    {
      cout << "No Applicable Peg to jump over!" << endl;
    } // End of Nested IF ELSE
  } // End of IF
  else
  {
    cout << "Direction went off board! Error!" << endl;
  } // End of IF ELSE
} // End of goWest


void chooseDirec(Pegs board[][YMAX], 
                 userChoice &choice, 
                 Pegs currentPeg, 
                 int &specialMoves)
{
  // *IN*  choice, currentPeg, *INOUT* board, specialMoves
  // This subprogram takes input from the user, checks what it is,
  // then moves to the appropriate sub program to further the game.
  string input ;
  cout << "Co-Ords accepted. Which direction would you" ;
  cout << " like to jump? N E S W" << endl ;
  getline(cin, input) ;
  input[0] = toupper(input[0]) ;
  switch (input[0])
  {
    case 'N':
      goNorth(board, choice, currentPeg, specialMoves);
      break ; // End of Case N
    case 'E':
      goEast(board, choice, currentPeg, specialMoves);
      break ; // End of Case E
    case 'S':
      goSouth(board, choice, currentPeg, specialMoves);
      break ; // End of Case S
    case 'W':
      goWest(board, choice, currentPeg, specialMoves);
      break ; // End of Case W
    case 'Q':
      break ; // End of Case Q
    default:
      cout << "Unrecognised Input!" << endl ;
  } // End of Switch
} // End of chooseDirec

void checkPeg(Pegs board[][YMAX],
              userChoice choice, 
              int &specialMoves)
{
  Pegs currentPeg = EMPTY ;
  // *INOUT* board
  // *IN* choice - Direction & Co-ords
  // Checks if the co-ordinates correspond with a peg.
  // Moves to the next sub program if so.
  if (board[choice.XcoOrd][choice.YcoOrd] == PEG ||
      board[choice.XcoOrd][choice.YcoOrd] == SPECIAL)
  {
    currentPeg = board[choice.XcoOrd][choice.YcoOrd] ;
    chooseDirec(board, choice, currentPeg, specialMoves) ;
  } // End of IF
  else
  {
    cout << "No Applicable Peg on those co-ordinates!" << endl ;
  } // End of IF ELSE
} // End of checkPeg

int flipNumber(int currentNumber)
{
  // *IN* currentNumber
  // This function takes in the users input
  // and flips the number approprietely.
  // This inverts the board, to make it easier to view.
  int i = 0 ;
  int flippedNumber = XMAX - 1 ;
  int numbers[XMAX] ;
  int newNumber ;
  for (i = 0; i < XMAX; i++)
  { // This array serves to make sure that the game works
    // with any size board.
    numbers[i] = flippedNumber ;
    flippedNumber-- ;
  } // End of IF
  newNumber = numbers[currentNumber] ;
  return newNumber ; // *OUT* newNumber
} // End of flipNumber

void getInput(Pegs board[][YMAX], bool &Round, int &specialMoves)
{
  // gets the users input.
  // If 0, it will quit.
  // If its a co-ordinate, it will move on.
  // H runs instructions
  // Anything else gets an error message.
  char buffer[2] ;
  userChoice choice ;
  string input ;
  cout << "Choose your peg by typing in its co-ordinates" ;
  cout << " seperated by a comma. E.G 2,1" << endl ;
  getline(cin, input) ;
  if (input[0] == QUITKEY)
  {
    cout << "Are you sure you wish to end this round? Y / N" << endl ;
    getline(cin, input) ;
    Round = playAgain(input) ;
    if (Round)
    {
      cout << "The round has successfully ended." << endl ;
    }
  } // End of IF
  else if ((input[0] > '0' && input[0] <= '9') && 
           (input[2] > '0' && input[2] <= '9') )
  { // Checks if the input is a number between 0~10
    buffer[0] = input[0] ;
    choice.XcoOrd = atoi(buffer) ;
    buffer[0] = input[2] ;
    choice.YcoOrd = atoi(buffer) ;
    choice.XcoOrd-- ;
    choice.YcoOrd-- ;
    choice.XcoOrd = flipNumber(choice.XcoOrd) ;
    if ((choice.XcoOrd >= 0 && choice.XcoOrd < XMAX) &&
        (choice.YcoOrd >= 0 && choice.YcoOrd < YMAX))
    { // After converting to an int, checks if the int is
      // a valid co-ord. IE, between 0 and MAX
      checkPeg(board, choice, specialMoves) ;
    } // End of NESTED IF
    else
    {
      cout << "Co-ordinates chosen are off of the board. Try again!" << endl ;
    } // End of Nested IF ELSE
  } // End of ELSE IF
  else
  {
    buffer[0] = toupper(input[0]) ;
    if (buffer[0] == 'H')
    {
      instructions() ;
    } // End of Nested IF
    else
    {
      cout << "Unrecognised Input!" << endl ;
    } // End of Nested IF ELSE
  } // End of IF ELSE
} // End of getInput

int scoreCheck(const Pegs board[][YMAX])
{
  // *IN* board
  // Takes in the board and checks how many pegs exist
  // If over 8 are on the board, 0 points.
  // If there are less than that, it calculates points via the
  // following expression.
  // 90 - (Number of Pegs * 10), e.g : 90 - (5 * 10) = 40.
  // Then adds bonus points if one of them is in the center.
  int numberOfPegs = 0 ;
  int score = 0 ;
  int i = 0 ;
  int j = 0 ;
  for (i = 0; i < XMAX; i++)
  {
    for (j = 0; j < YMAX; j++)
    {
      if (board[i][j] == PEG || board[i][j] == SPECIAL)
      {
        numberOfPegs++ ;
      } // End of IF
    } // End of nested loop
  } // End of first loop
  if (numberOfPegs > MINPEGS)
  {
    score = 0 ;
  } // End of IF
  else
  {
    score = (SCOREMAX - (numberOfPegs * SCOREBASE)) ;
  } // End of IF ELSE
  if (board[XMAX / 2][YMAX / 2] == PEG || SPECIAL)
  {
    score+= BONUS ;
  } // End of IF
  return score ;   // *OUT* score
} // End of scoreCheck

void avoidCentral(int &coOrdX, int &coOrdY)
{
  // This sub program takes in an X and Y co-ordinate and checks
  // if they are in the centre of the board.
  // If they are, it changes the co-ords to the top right corner.
  // This prevents the empty spot in the middle from being filled.
  if (coOrdX == (XMAX / 2) && coOrdY == (YMAX / 2))
  {
    coOrdX = (XMAX - 1) ;
    coOrdY = (YMAX - 1) ;
  } // End of IF
} // End of avoidCentral

void setBoard(Pegs board[][YMAX])
{
  // *INOUT* Board
  // This subprogram takes in the board array and makes the central point
  // empty, then adds a special peg into the mix.
  board[XMAX / 2][YMAX / 2] = EMPTY; // Sets central spot to be empty.
  int specialX = 0 ;
  int specialY = 0 ;
  specialX = rand() % XMAX ;
  specialY = rand() % YMAX ;
  avoidCentral(specialX, specialY) ;
  board[specialX][specialY] = SPECIAL ;
} // end of setBoard

int main()
{ 
  // Main program of game.
  srand((unsigned)time(NULL));
  bool gameOver = false ;
  bool roundOver = false ;
  int score = 0 ;
  int highScore = 0 ;
  int previousScore = 0 ;
  int specialMoves = 0 ;
  string input ;
  instructions() ;
  while (!gameOver) // Main loop for the game.
  {
    roundOver = false ;
    Pegs board [XMAX][YMAX] = { PEG } ; // Sets all contents to have a peg
    setBoard(board);
    specialMoves = SPECIALMOVE;
    while (!roundOver) // Runs most of the in round content.
    {
      if (countMoves(board) > 0)
      {
        output(board, highScore, specialMoves) ;
        getInput(board, roundOver, specialMoves) ;
      } // End of IF
      else
      {
        cout << "There are no moves remaining." << endl ;
        roundOver = true ;
      } // End of IF ELSE
    } // End of Round Loop
    score = scoreCheck(board) ;
    if (score > highScore)
    {
      previousScore = highScore ;
      highScore = score ;
      output(board,highScore, specialMoves) ;
      cout << "Congratulations, you have bested your previous" ;
      cout << " high score of  : " ;
      cout << previousScore << endl << "with your new score of : " ;
      cout << highScore << endl ;
    } // End of IF
    else
    {
      output(board,highScore, specialMoves) ;
      cout << "You scored : " << score << " points this round." << endl ;
    } // End of ELSE IF
    cout << "Do you wish to play again? Y / N " << endl ;
    getline(cin, input) ;
    if (!(playAgain(input)))
    {
      gameOver = true ;
    } // End of IF
  } // End of main game loop
  return 0 ; // *OUT* Main
} // End of MAIN