// Assignment 1.
// Created 27/10/15

#include <iostream>
#include <ctime>
#include <limits>

using namespace std ;

void instructions()
{
  // Subprogram to output instructions for user.
  cout << "There are twenty one coins." << endl;
  cout << "You and the computer take turns to pick up the coins." << endl;
  cout << "Each turn you must take at least one coin, or up to" << endl;
  cout << "five coins." << endl;
  cout << "Whoever takes the last coin loses!" << endl;
}

void pennyDisplay(int pennyCount)
{
  // Moved Penny Display Loop to subprogram to make code cleaner.
  for (int pennyDisplay = 0; pennyDisplay < pennyCount; pennyDisplay++)
  {
    // Penny Display loop.
    // this for loop runs when there are more than 0 pennyCount
    // and displays an O for each iteration it runs.
    cout << " O";
    // End of the Penny Display loop.
  }
}

int randomize(int orBelow)
{
  // Sub Program creates a random number
  int random ;
  srand((unsigned)time(NULL)) ;
  // Random number gained via current time.
  random = rand() % orBelow ;
  // Number Moduled down until 0-4
  random++ ;
  // Increased by 1 so 1-5
  return random ;
}

int compManual(int &pennyCount)
{
  // Sub program purely to keep code clean.
  switch (pennyCount)
  {
    // Switch decides on what the computer does
    // Depending on how many coins are left.
  case 1:
  case 2:
    pennyCount--; // Lowers Penny total by 1.
    cout << "1" << endl;
    break;
  case 3:
    pennyCount = pennyCount - 2; // Lowers Penny total by 2.
    cout << "2" << endl;
    break;
  case 4:
    pennyCount = pennyCount - 3; // Lowers Penny total by 3.
    cout << "3" << endl;
    break;
  case 5:
    pennyCount = pennyCount - 4; // Lowers Penny total by 4.
    cout << "4" << endl;
    break;
  case 6:
    pennyCount = pennyCount - 5; // Lowers Penny total by 5.
    cout << "5" << endl;
    break;
  case 7:
  case 8:
    pennyCount--; // Lowers Penny total by 1.
    cout << "1" << endl;
    break;
  case 9:
    pennyCount = pennyCount - 2;// Lowers Penny total by 2.
    cout << "2" << endl;
    break;
  case 10:
    pennyCount = pennyCount - 3;// Lowers Penny total by 3.
    cout << "3" << endl;
    break;
  case 11:
    pennyCount = pennyCount - 4;// Lowers Penny total by 4.
    cout << "4" << endl;
    break;
  case 12:
    pennyCount = pennyCount - 5;// Lowers Penny total by 5.
    cout << "5" << endl;
    break;
  case 13:
  case 14:
    pennyCount--; // Lowers Penny total by 1.
    cout << "1" << endl;
    break;
  case 15:
    pennyCount = pennyCount - 2;// Lowers Penny total by 2.
    cout << "2" << endl;
    break;
  case 16:
    pennyCount = pennyCount - 3;// Lowers Penny total by 3.
    cout << "3" << endl;
    break;
  case 17:
    pennyCount = pennyCount - 4;// Lowers Penny total by 4.
    cout << "4" << endl;
    break;
  case 18:
  case 19:
  case 20:
  case 21:
    pennyCount = pennyCount - 5;// Lowers Penny total by 5.
    cout << "5" << endl;
    break;
  default:
    cout << "Unknown Error" << endl;
    // Default should never run.
    // End of Switch for Comp manual turn.
  }
  return pennyCount ;
  // End of Sub program - Comp Turn Manual
}

int main()
{

  bool runGame = true ;
  // Main loop to run game.

  int numOfRound = 0 ;
  // Counts the number of rounds.

  while (runGame)
  {
    // This loop runs the core of the game, and ends when the user wants
    // to quit.
    cout << "\n\n\nTWENTY ONE!" << endl ;
    numOfRound++;
    if (numOfRound == 1)
    {
      // Start Welcome IF.
      cout << "Welcome to your first game!" << endl << endl ;
      // Text output, only runs once.
      // End Welcome IF.
    }
    else
    {
      // Start welcome Else.
      cout << "Welcome to Round " << numOfRound << endl << endl ;
      // End Welcome Else.
    }
    cout << "Instructions are below." << endl ;
    instructions(); // Subprogram to output the instructions.
    // This increments the number of rounds.
    bool runRound = true ;
    bool playerTurn = true ;
    // Variable to dictate who's turn it is
    // running specific code based off of that.
    // To switch who goes first, change value.
    bool compRandom = true ;
    // Variable to dictate when the computer uses RNG
    // instead of having a pre-defined choise.

    int pennyCount = 21 ; // Number of pennyCount.

    while (runRound)
    {
    // This loop runs the rounds. When a round is won or lost
    // The game escapes to the previous loop so the game can run again.

      int userInput = 0; 
      // Users numerical input.
      bool inputValid = true;
      // Boolean for validating user Input ( Getting correct ints)
      if (pennyCount <= 0)
      {
        // Checks to see if there are 0 pennyCount or less.
        // If so, ends round.
        if (playerTurn)
        {
          // Checks the current turn.
          // If its player turn, it means the computer went to
          // zeo or below. Works vice versa.
          cout << "Congratulations, you have won!" << endl ;
        }
        else
        {
          cout << "You have lost!" << endl ;
        }
        break;
        // Break exits round loop when 0 pennies.
        // End of check IF.
      }

      int randomNumber = 0;
      //Declares and Initializes random number variable.
      pennyDisplay(pennyCount) ;
      // SubProgram to run a loop for displaying an O for each coin.
      cout << endl ; // Ends the line after penny's have been displayed.

    if (playerTurn)
    {
      // This code runs when it is the players turn.
      cout << "It is YOUR turn " ;

      while (inputValid)
      {
          // Number Input Validation loop.
          cout << "- Enter a number between 1-5 : " ;
          cin >> userInput ; // Takes user input for an Int.
          cout << endl ; // New line after input.

          inputValid = cin.fail() || userInput < 1 || userInput > 5 || 
            pennyCount < userInput ;
          // This checks whether the input has failed or is valid
          // If the input is completely fine, the boolean becomes false
          // and escapes the loop when it finishes.
          if (inputValid)
          {
            // IF statement that only runs when input was invalid.
            if (!pennyCount < userInput || cin.fail())
            {
              // IF statement for Invalid input.
              cout << "Your input was not a number from 1 to 5." << endl ;
              cout << "Please try again!" << endl ;
              // end of validation IF
            }
            else
            {
              // Too few coins for that choice.
              cout << "There aren't enough coins for that choice." << endl;
              cout << "Choose again!" << endl;
              // Else end.
            }
            //Validation IF end.
          }
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n') ;
          // Code clears the input stream, en case of errors being
          // stuck inside of it.

          // end of Validation loop.
        }
      cout << "You have chosen : " << userInput << endl ;
        pennyCount = pennyCount - userInput ;
        // Lowering the pennies.
        playerTurn = false ;
        // Setting to Computers turn.
        // end of Players Turn IF.
      }
      else
      {
        // This code runs when it is the computers turn.
        if (randomize(5) == 1)
        {
          // 20% chance that the computer will
          // randomly pick a number in any situation.
          compRandom = true;
        }
        if (compRandom)
        {
          // IF checks whether computer is to randomly pick a number.
          while (compRandom)
          {
            // Loop that will keep running until we have a valid random
            randomNumber = randomize(5);
            if (randomNumber < pennyCount)
            {
              // IF Checks that the number is less than the number of pennies.

              cout << "The Computer chooses : " << randomNumber << endl ;
              pennyCount = pennyCount - randomNumber ;
              // Removes computers number from penny Count.
              compRandom = false ;
              //Chances Bool to end loop.
              // End IF
            }
            // End of Random Loop
          }
          // End of random IF statement.
        }
        else
        {
          cout << "The Computer chooses : " ;
          compManual(pennyCount) ;
          // End of Else for Comp Manual Turn
        }
        playerTurn = true ;
        // Switches back to player turn.
        // end of Computers Turn ELSE.
      }
      // End of Round loop.
    }
    // End of Main game loop.
  }

  return 0 ; 
  // End of Main
}