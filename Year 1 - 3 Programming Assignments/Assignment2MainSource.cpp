// Title   : Assignment2MainSource.cpp
// Purpose : CM403 Assignment 2
// Author  : Anonymous
// Date    : 20 / 11 / 15
// Last Edited : 21 / 11 / 15

// This program uses pseudo random number generation
// and pre defined texts to create a random character
// with statistics and a backstory, as given in the assignment
// specification for GP1 asignment 2.

#include <iostream> // Input / Output stream library.
#include <cstring>  // Character String Library, used for char array
                    // manipulating functions.
#include <ctime>    // Library used for Pseudo Random Number Generation

using namespace std ; // Standard namespace

typedef int statistic ; // Data type used for anything relating to statistic
typedef int random ; // Data type used for any randoming
typedef int size ;

const char ERROR[6] = { "ERROR" } ; // Used for Error message displays.

const statistic STR = 0;          // These five constants are used
const statistic INT = 1;          // for the storage of all statistic
const statistic AGI = 2;          // in the corresponding arrays.
const statistic TOUGH = 3;        // READ ABOVE
const statistic CHAR = 4;         // READ ABOVE

const int HE = 0;       // These five constants are used 
const int HIM = 1 ;     // for the position in the
const int HIS = 2 ;     // pronoun char array
const int LHE = 3 ;     // Allows us to know which position gives what
const int UHIM = 4 ;    // pronoun. U = Capitalized, L = Lowercase
 
const statistic UNIQSTATS = 5 ;       // There are 5 unique statistic 
                                     // at this time.
const statistic STATMAX = 35 ;       // Total statistic cannot go above 35.
const statistic STATMIN = 15 ;       // Total statistic cannot go below 15.

const int ARRLENMAX = 100 ;   // Stores the max length for a char array 
const int ARRLISTMAX = 20 ;  // Stores the max amount of rows in a
                             // char array
const int ARRPARAMAX = 400 ; // Stores the max length for the parahraph
                             // output char array.
                             // 350 should work all the time, but 400 
                             // was set to be safe.

typedef char stringArr[ARRLENMAX] ; // Defines type for basic
                                    // Char Array declaration

typedef statistic stats[UNIQSTATS] ; // Defines type for statistic
                                    // array declaration.

enum class sentances {PAST, RACE, PET, JOB, RELATIONSHIP, // Used for
                      ZODIAC, RELATIVE, DREAM} ;        // selecting 
                                            // which sentances will be chosen.
const int totalSentances = 8 ; // Marks how many unique sentances there are.
const int MAXSentances = 4 ; // Max sentences used, does not include
                             // Initial name line.

enum class gender { FEMALE, MALE } ;     // Used to store characters gender
const int maxGender = 2 ;               // Marks how many genders there are

enum class pasts { ROYAL, POOR, NORMAL} ; // Used for storing characters past.
const int maxPasts = 3 ;                 // Marks how many pats there are.

enum class races { HUMAN, ELF, DWARF, ORC} ; // Used to store Race
const int maxRaces = 4 ;                    // Marks how many races there are.

typedef sentances lines[MAXSentances] ; // Used for storing lines arrays
typedef char genPro[ARRLISTMAX][ARRLENMAX] ; // Used to store gender pronouns
typedef char list[ARRLISTMAX][ARRLENMAX] ; // Used for storying any list.

struct Values
{ // Stores character values that affect other
  // random generations, except for statistic.
  gender Gender ; // Stores Gender
  pasts Past ; // Stores Past
  races Race ; // Stores Race
}; // End of Values Struct

races chooseRace()
{ // *OUT* Race
  // This function selects the players race randomly and returns it.
  races currentRace ; // Stores race for output
  races raceList[ARRLISTMAX] = {races::HUMAN, races::DWARF, races::ELF,
                                races::ORC} ; // Array containing all races.
  random raceChoice = rand() % maxRaces ;// Generates a random number
  currentRace = raceList[raceChoice] ;// Selects output based on random
  return currentRace ;
} // End of chooseRace

pasts choosePast()
{ // *OUT* Past
  // This function selects the players past randomly and returns it.
  pasts currentPast ; // Stores past for output
  pasts pastList[ARRLISTMAX] = { pasts::NORMAL, pasts::POOR, pasts::ROYAL} ;
                                // Array containing all pats.
  random pastChoice = rand() % maxPasts ;// Generates a random number
  currentPast = pastList[pastChoice];// Selects output based on random
  return  currentPast ;
} // End of choosePast

gender chooseGender()
{ // *OUT* Gender
  // This function selects the gender randomly and returns it.
  gender currentGender ; // Stores gender for output
  gender genderList[ARRLISTMAX] = { gender::MALE, gender::FEMALE} ;
                                    // Array containing all genders.
  random genderChoice = rand() % maxGender ; // Generates a random number
  currentGender = genderList[genderChoice] ; // Selects output based on random
  return currentGender ; // Returns Gender
} // End of chooseGender

void valueGen(Values &currentValues)
{ // *INOUT* currentValues This subprogram runs all of the
  // Functions to generate a new characters stats.
  currentValues.Gender = chooseGender() ;
  currentValues.Past = choosePast() ;
  currentValues.Race = chooseRace() ;
  // Each line in this subprogram sends an element of a
  // characters structure to the corresponding function
  // to return a value and store in the struct.
} // End of valueGen

size sizeArray(const char arrayCount[ARRLISTMAX][ARRLENMAX])
                                //*In* Array to be counted
{ // This function takes an array and counts how many rows / lines
  // actually have a string in, then returns the number.
  size arrListSize = 0 ; // Resets the variable to 0 each time it's called.

  bool arrContent = true ; // Boolean that shows true so long as the arrays
  // row has characters / strings inside.
  int counter = 0 ; // Used to check the content inside of each row

  do
  { // Loop used to cycle through array to check for content and
    // count how many rows it has. Runs at least once.
    if (strcmp(arrayCount[counter], ""))
    { // Checks that the row in the array
      // actually has content in it.
      // Returns true if something is inside.
      arrListSize++ ;
    } // IF end
    else
    { // This else only runs when there is no content
      // inside of the character array row.
      arrContent = false ;// Set to false to end the loop
                          // No point checking the array
                          // Further when there is no content.
    } // ELSE end
    counter++ ; // Increments each iteration so we can check the next
               // array value.
  } while (arrContent) ; // End of DO WHILE

  return arrListSize ; // Returns the number of rows an array has.
} // arrListCount

void statisticGen(statistic CharStats[]) // *INOUT* Array to store character
// statistic
{
  statistic statTotal = 0 ; // The sum of all statistic
  int loopCount = 0 ; // A simple for loop counter variable.
  bool successGen = false ; // Bool set to keep Do While going.
  do
  { // Do while for generating the char statistic.
    statTotal = 0 ; // Resets the stat total with every iteration.
    loopCount = 0 ; // Resets the loop counter for next loop
    // for each iteration.
    CharStats[STR] = (rand() % 10) + 1 ; // Sets each stat to a random
    CharStats[INT] = (rand() % 10) + 1 ; // number between 1~10
    CharStats[AGI] = (rand() % 10) + 1 ;
    CharStats[TOUGH] = (rand() % 10) + 1 ;
    CharStats[CHAR] = (rand() % 10) + 1 ;
    for (loopCount = 0; loopCount < UNIQSTATS; loopCount++)
    { // Creates the sum of all statistic generated above.
      statTotal += CharStats[loopCount] ; // Sum of all of the statistic.
    } // End of For Loop
    if (statTotal >= STATMIN && statTotal <= STATMAX)
    { // This IF checks that the total of all the statistic is between the
      // required limits.
      successGen = true ; // Changed to true to escape the do while loop.
    } // End of IF
  } while (!successGen) ; // End of DO While
} // End of StatisticGen

void addToArr(const char genList[ARRLISTMAX][ARRLENMAX],
  char currentList[ARRLISTMAX][ARRLENMAX])
{ // *IN genList
  //  *INOUT* currentList
  int loopCounter = 0 ; // Used for loops
  size listSize = 0 ;
  listSize = sizeArray(genList) ; // Counts contents
  int movingName = sizeArray(currentList) ; // Counts contents of second arr.
  for (loopCounter = 0; loopCounter <= listSize; loopCounter++)
  { 
    strcpy_s(currentList[movingName], ARRLENMAX, genList[loopCounter]) ;
    // Copies the the element of the first array, adding it to the second.
    movingName++ ;
    // Increments the variable
  } // End of FOR loop
} // End of genderNameAdd

void nameGen(gender currentGender, char currentName[ARRLENMAX])
{ // *IN* Gender
  // *INOUT* currentName
  // Takes in the decided gender and outputs a name based off of that.
  list names = // Array to store names.
  { // 
    "Alex", "Morgan", "Casey"
  } ; // End of Char Array Initialize
  size nameListCount = 0 ; // Used to store how many names are in array.
  random nameChoice = 0 ; // Used to store the random choice of name
  list maleNames = // Stores Male names
  {
    "John", "Bill", "Thor", "Larry", "Dave", "Chris", "Michael", "Adam"
  } ; // end of Male Names
  list femaleNames = // Stores Female names
  {
    "Cindy", "Chloe", "Shannon", "Luna", "Lily", "Zara", "May"
  } ; // end of Female Names
  if (currentGender == gender::FEMALE) // Checks Gender and adds more names
                                       // based on that.
  {
    addToArr(femaleNames, names) ; // Adds the female names to
                                          // the full nameList array.
  }
  else
  {
    addToArr(maleNames, names) ; // Adds the male names to
                                       // the full nameList array.
  } // end of IF Else
  nameListCount = sizeArray(names) ; // Counts the array after more added
  nameChoice = rand() % nameListCount ; // Generates a random number off that
  strcpy_s(currentName, ARRLENMAX, names[nameChoice]) ; // Copies the
                             // chosen name to the character array given
} // End of nameGen

void descGen(char currentDesc[ARRLENMAX])
{ // *INOUT* Current Description
  // Adds a random dscriptor to the char array
  random descChoice = 0 ;
  list descs = { // List of Descriptors.
    "Bloodthirsty", "Wicked", "Saintly", "Magical", "Lovely",
    "Amazing", "Despicable", "Foul", "Rich", "Naive"
  } ;
  size descListCount = sizeArray(descs) ;
  descChoice = rand() % descListCount ;
  strcpy_s(currentDesc, ARRLENMAX, descs[descChoice]) ;
} // end of descGen

void chooseCity(pasts currentPast,  // *IN* Past value
                char currentCity[ARRPARAMAX] ) // *INOUT* Chosen City 
{ // This subprogram chooses the city the character is from.
  random cityChoice = 0 ; // Choice in array
  size cityCount = 0 ; // Sizes array
  list cities = { // List of Cities.
    "Capital city Ridya", "Capital city Chrizzian",
    "Capital city of Swollaw"
  }; // city List
  list nonRoyal = {
    "City-State of Monopa", "City of Lillum", "City-state of Zogg",
    "City of Newcastle"
  } ; // nonRoyal list.
  if (currentPast != pasts::ROYAL)
  { // Checks if past is not royal and adds non capital cities
    // to array.
    addToArr(nonRoyal, cities) ;
  }
  cityCount = sizeArray(cities) ; // Gets size
  cityChoice = rand() % cityCount ; // Gets random num
  strcpy_s(currentCity, ARRLENMAX, cities[cityChoice]) ; //Copies city
}  //end of chooseCity

void genFirstSentance(char firstLine[],     // *INOUT* First Sentance
                      Values CurrentValues)    // *IN* Values Struct
// This subprogram takes in the required variables
// And begins constructing the first sentance, which always run.
{
  random ranChoice = rand() % 2 ; // Used for any 
  char name[ARRLENMAX] ;
  char desc[ARRLENMAX] ;
  char city[ARRLENMAX] ;
  descGen(desc) ; // creates a descriptor.
  nameGen(CurrentValues.Gender, name) ; // Chooses a name, sending Gender
  chooseCity(CurrentValues.Past, city) ; // Chooses a city, sending Past
  if (ranChoice == 0) // Checks the random number
  { // Runs if name goes first, followed by the descriptor.
    strcpy_s(firstLine, ARRPARAMAX, name) ;
    strcat_s(firstLine, ARRPARAMAX, " the ") ;
    strcat_s(firstLine, ARRPARAMAX, desc) ;
  }
  else
  { // Runs if name follows the descriptor.
    strcpy_s(firstLine, ARRPARAMAX, "The ") ;
    strcat_s(firstLine, ARRPARAMAX, desc) ;
    strcat_s(firstLine, ARRPARAMAX, " ") ;
    strcat_s(firstLine, ARRPARAMAX, name) ;
  } // End of IF Else
  strcat_s(firstLine, ARRPARAMAX, " was born in the ") ;
  strcat_s(firstLine, ARRPARAMAX, city) ; // Adds the city into the first
                                          // sentance, with proper grammar.
  strcat_s(firstLine, ARRPARAMAX, ". ") ;
} // end of genFirstSentance

void sentArrSwap(sentances sentList[ARRLISTMAX], // *INOUT* SentanceList
                 int chosenPosi,  // *IN* Chosen Line
                 int endPosi)     // *IN* Last usable Line
{ // This subprogram takes the sentance last chosen
  // and swaps it to the last available choise.
  // This prevents the program from choosing the same sentance twice.
  sentances tempPlacement = sentList[chosenPosi] ;
  // Copies chosen value to temporary placement variable.
  sentList[chosenPosi] = sentList[endPosi] ;
  // Copies last available value to Chosen ones spot.
  sentList[endPosi] = tempPlacement ;
  // Copies Chosen variable into the last available ones spot.
} // End of SentArrSwap

void chooseSentance(sentances chosenSentances[MAXSentances]) 
  // *INOUT* chosenSentances - sentances Array
{ // This subprogram takes in an array, runs until it hits the MAXSentances
  // and chooses that many unique sentances from the array, placing each
  // into the array provided for returning.
  sentances sentanceList[ARRLISTMAX] = { sentances::PAST, sentances::RACE, 
       sentances::PET, sentances::JOB, 
       sentances::RELATIONSHIP, sentances::ZODIAC, 
       sentances::RELATIVE, sentances::DREAM } ; // This array stores all of
       // the possible sentences to choose from.
  int sentanceNumber = 0 ;
  for (sentanceNumber = 0; sentanceNumber < MAXSentances; sentanceNumber++)
  { // Loops for each sentance until the max is hit.
    int sentanceCount = totalSentances ; // Starts at the total provided.
    if (sentanceNumber > 0)
    { // This if checks the loop iteration, and lowers the count
      // to prevent choosing the same sentance twice.
      sentanceCount -= sentanceNumber ; 
    } // IF End
    random sentanceChoice = rand() % sentanceCount; // Selects random sentance
    chosenSentances[sentanceNumber] = sentanceList[sentanceChoice] ;
    // sets the sentance choice into t
    sentArrSwap(sentanceList, sentanceChoice, (sentanceCount - 1)) ;
  } // End of FOR loop
} // End of chooseSentance

void getDream(const genPro currentPronouns, // *IN* currentPronouns
              const stats currentStats, // *IN* currentStats
              char currentDream[ARRLENMAX]) // *INOUT* currentDream
{ // This subprogram selects the DREAM sentance, adding it
  // to the appropriate character array.
  list dream =
  { // The list of possible dreams.
    "ruling the world!", "eating an entire Apple pie!",
    "seeing England winning the Ashes!", "thinking of a half decent dream!",
    "mastering C++.", "defeating the dark lord!", 
    "watching hitchhikers guide to the galaxy!"
  } ; // end of dream
  size listSize = sizeArray(dream);
  if (currentStats[INT] > 7) // Checks the players Intelligence.
  { // If above 7, adds below string for possible chance of output.
    strcpy_s(dream[listSize], ARRLENMAX, "Getting a 30 on Assignment 2") ;
    listSize++ ; // Increments to take into account added string.
  } // End of IF
  random dreamChoice = rand() % listSize ; // Selects random value
  strcpy_s(currentDream, ARRLENMAX, currentPronouns[HE]) ;
  strcat_s(currentDream, ARRLENMAX, "dreams of one day ") ;
  strcat_s(currentDream, ARRLENMAX, dream[dreamChoice]) ;
  strcat_s(currentDream, ARRLENMAX, " ") ;
  // Creates sentance and adds it to array.
} // End of getDream

void getRace(const genPro currentPronouns,  // *IN* currentPronouns
             races chosenRace,  // *IN* Race, predetermined at start.
             char currentRace[ARRLENMAX]) // *INOUT* Array to store line.
{ // Takes in input and outputs a new sentance.
  char charRace[ARRLENMAX] ; // Storage for the race
  char raceSpecial[ARRLENMAX] ; // Storage for the racial advantage.
  switch (chosenRace) // Checks chosenRace and goes to right case.
  {
    case races::DWARF:
      strcpy_s(charRace, ARRLENMAX, "Dwarf Race,") ;
      strcpy_s(raceSpecial, ARRLENMAX, "Axes!") ;
      break ; // Runs when character is a dwarf.
    case races::ELF:
      strcpy_s(charRace, ARRLENMAX, "Elf Race,") ;
      strcpy_s(raceSpecial, ARRLENMAX, "Magic or Bows!") ;
      break ; // Runs when character is an elf.
    case races::HUMAN:
      strcpy_s(charRace, ARRLENMAX, "Human Race,") ;
      strcpy_s(raceSpecial, ARRLENMAX, "One handed swords or Magic!") ;
      break ; // Runs when character is a human.
    case races::ORC:
      strcpy_s(charRace, ARRLENMAX, "Orc Race,") ;
      strcpy_s(raceSpecial, ARRLENMAX, "Large brutish weapons!") ;
      break ; // Runs when character is an orc.
    default :
      cout << ERROR << endl ; // Outputs error message, should never run.
  }
  strcpy_s(currentRace, ARRLENMAX, "As a member of the ") ;
  strcat_s(currentRace, ARRLENMAX, charRace) ;
  strcat_s(currentRace, ARRLENMAX, currentPronouns[LHE]) ;
  strcat_s(currentRace, ARRLENMAX, "gains a natural bonus when using ") ;
  strcat_s(currentRace, ARRLENMAX, raceSpecial) ;
  strcat_s(currentRace, ARRLENMAX, " ") ;
  // Adds the strings and array values to the final array for output.
} // End of getRace

void getPast(const genPro currentPronouns, // *IN* currentPronouns
             pasts chosenPast,  // *IN* Past, predetermined at start.
             gender chosenGen, // *IN* Gender, predetermined at start.
             char currentPast[ARRLENMAX]) // *INOUT* currentPast, output.
{ // Takes in values and outputs a sentance based off of them.
  char pastList[ARRLISTMAX][ARRLENMAX] =
  {
    "was raised in a ", "was brought up in a ", "was born to a "
  } ; // Sets the default past descriptors.
  random pastChoice = 0 ; // Holds the random choice for a past
  size pastArrSize = 0; // Holds the array size
  char pastFiller[ARRLENMAX] ; // Holds the secondary descriptor.
  switch (chosenPast) // Checks chosen Past
  {
    case pasts::ROYAL:
      strcpy_s(pastFiller, ARRLENMAX, "castle, as a ") ;
      if (chosenGen == gender::MALE) // Checks gender for proper grammar.
      {
        strcat_s(pastFiller, ARRLENMAX, "Prince.") ;
      }
      else
      {
        strcat_s(pastFiller, ARRLENMAX, "Princess.") ;
      }
      break ; // Runs if Royal.
    case pasts::POOR:
      pastArrSize = sizeArray(pastList) ;
      strcpy_s(pastList[pastArrSize], ARRLENMAX,
        "was abandoned on the streets as a ") ;
      strcpy_s(pastFiller, ARRLENMAX, "poor home. ") ;
      break ; // Runs if Poor
    case pasts::NORMAL:
      strcpy_s(pastFiller, ARRLENMAX, "normal middleclass home. ") ;
      break ; // Runs if Normal
    default:
      cout << ERROR << endl ; // Displays error, Should never run.
  } // End of Switch
  pastArrSize = sizeArray(pastList) ; // Counts array
  pastChoice = rand() % pastArrSize ; // Gets random number
  if (!(strcmp(pastList[pastChoice], "was abandoned on the streets as a ")))
  { // Checks if the poor descriptor was chosen
    strcpy_s(pastFiller, ARRLENMAX, "street Urchin. ") ;
    // Changes secondary descriptor to match.
  }
  strcpy_s(currentPast, ARRLENMAX, currentPronouns[HE]) ;
  strcat_s(currentPast, ARRLENMAX, pastList[pastChoice]) ;
  strcat_s(currentPast, ARRLENMAX, pastFiller) ;
  // Adds values to array.
} // End of getPast

void getPet(const genPro currentPronouns, // *IN* currentPronouns
            statistic Intel,                  // *IN* intelligence stat
            char currentPet[ARRLENMAX]) // *INOUT* CurrentPet, output.
{ // Takes in inputs and chooses a pet with a name, adding it to the array
  random petChoice = 0 ; // For storing random numbers
  size petSize = 0 ; // Stores array sizes
  bool stupid = false ; // Flag for low INT
  list pets =  // List types of pets
  {
    "dog", "cat", "parrot", "lizard", "dragon",
    "hutt", "raccoon"
  } ; // end of pets
  char chosenPet[ARRLENMAX] ; // Stores pet
  char chosenName[ARRLENMAX] ; // Stores Name
  list petNames = // List of pet names
  {
    "Larry", "Frodo", "Agrajag", "Almighty Bob", "Colin", "Pizza"
  } ; // end of petNames
  if (Intel > 8) // Checks for high intel
  {
    petSize = sizeArray(pets) ; // Counts size
    strcpy_s(pets[petSize], ARRLENMAX, "University Lecturer") ;
    // adds new entry.
  }
  else if (Intel < 4)
  { 
    stupid = true ; // toggles low intel flag
  }
  petSize = sizeArray(pets) ; // Counts size
  petChoice = rand() % petSize ; // Gets random number
  if (stupid) // If flag true, sets pet
  {
    strcpy_s(chosenPet, ARRLENMAX, "rock") ;
  }
  else
  { // Otherwise, get via random choice.
    strcpy_s(chosenPet, ARRLENMAX, pets[petChoice]) ;
  }
  petSize = sizeArray(petNames) ; // Counts size
  petChoice = rand() % petSize ; // Gets random number
  strcpy_s(chosenName, ARRLENMAX, petNames[petChoice]) ; // Grabs name
  if (!(strcmp(chosenPet, "University Lecturer"))) // Checks content
  {
    strcpy_s(currentPet, ARRLENMAX, "Being as smart as") ;
    strcat_s(currentPet, ARRLENMAX, currentPronouns[LHE]) ;
    strcat_s(currentPet, ARRLENMAX, "is,") ;
    strcat_s(currentPet, ARRLENMAX, currentPronouns[LHE]) ;
    strcat_s(currentPet, ARRLENMAX, "defeated") ;
    strcat_s(currentPet, ARRLENMAX, currentPronouns[HIS]) ;
    strcat_s(currentPet, ARRLENMAX, chosenPet) ;
    strcat_s(currentPet, ARRLENMAX, " and has now tamed it as a pet! ") ;
  } // Outputs specific line, end of IF
  else if (!(strcmp(chosenPet, "rock")))
  {
    strcpy_s(currentPet, ARRLENMAX, "Being as stupid as") ;
    strcat_s(currentPet, ARRLENMAX, currentPronouns[LHE]) ;
    strcat_s(currentPet, ARRLENMAX, "is, it was only safe for") ;
    strcat_s(currentPet, ARRLENMAX, currentPronouns[HIM]) ;
    strcat_s(currentPet, ARRLENMAX, "to look after a pet ");
    strcat_s(currentPet, ARRLENMAX, chosenPet) ;
    strcat_s(currentPet, ARRLENMAX, ". ") ;
  } // Outputs specific line, end of Else IF
  else
  {
    strcpy_s(currentPet, ARRLENMAX, currentPronouns[HE]) ;
    strcat_s(currentPet, ARRLENMAX, "has a pet ") ;
    strcat_s(currentPet, ARRLENMAX, chosenPet) ;
    strcat_s(currentPet, ARRLENMAX, " named ") ;
    strcat_s(currentPet, ARRLENMAX, chosenName) ;
    strcat_s(currentPet, ARRLENMAX, ". ") ;
  } // Outputs generic line with varied outputs, end of Else
} // End of getPet

void getRelative(const genPro currentPronouns, // *IN* currentPronouns
                 char currentRelative[ARRPARAMAX]) // *INOUT* currentRelative
{ // Generates a random name and famous feature for the relative
  // and outputs to array.
  random relativeChoice = 0 ; // Stores random numbers
  size listSize = 0 ; // stores array sizes
  char chosenRelative[ARRLENMAX] ; // Stores relative once chosen
  char chosenFame[ARRLENMAX] ; // Stores fame once chosen
  list relatives =  // List of relatives
  {
    "King Dave", "Prince Harry", "Jimbob", "Hillbilly Dan", "Richard",
    "Henry the IV", "Odin"
  } ; // end of relatives
  list fame = // List of Fame
  {
    "winning the lottery! ", "killing 100 men! ", "eating a giant pie. ",
    "slaying a dragon. ", "passing Games Programming! ", 
    "Achieving a 30 in the second games programming assignment. ",
    "pulling the sword out of the stone! "
  } ; // end of fameList
  listSize = sizeArray(relatives) ; // Gets size of array
  relativeChoice = rand() % listSize ; // Gets random number
  strcpy_s(chosenRelative, ARRLENMAX, relatives[relativeChoice]) ;
  // Copies chosen relative to temporary aray.
  listSize = sizeArray(fame) ; // Gets size of array
  relativeChoice = rand() % listSize ; // Gets random number
  strcpy_s(chosenFame, ARRLENMAX, fame[relativeChoice]) ;
  // Copies chosen fame to temporary aray.

  strcpy_s(currentRelative, ARRPARAMAX, currentPronouns[HE]) ;
  strcat_s(currentRelative, ARRPARAMAX, "is related to ") ;
  strcat_s(currentRelative, ARRPARAMAX, chosenRelative) ;
  strcat_s(currentRelative, ARRPARAMAX, " who is famous for ") ;
  strcat_s(currentRelative, ARRPARAMAX, chosenFame) ;
  strcat_s(currentRelative, ARRPARAMAX, "\0") ;
  // Adds strings and values to char array for ouput.
} // end of getRelative

void getRelationship(const genPro currentPronouns, // *IN* currentPronouns
                     char currentRelationship[ARRLENMAX])
                     // *INOUT* currentRelationship, output array
{ // generates a sentance about the characters relationship status.
  random randomStatus = rand() % 3 ;
  bool hasKids = false ;
  char relationship[ARRLENMAX] ;
  if (randomStatus == 0)
  { // Marks dating
    strcpy_s(relationship, ARRLENMAX, "dating someone. ") ;
  } // End of IF
  else if(randomStatus == 1)
  { // Marks Married
    strcpy_s(relationship, ARRLENMAX, "married with ") ;
    randomStatus = rand() % 3 ; // New random for kid chance.
    if (randomStatus == 0)
    { // Marks no kids.
      strcat_s(relationship, ARRLENMAX, "no kids. ") ;
    } // End of Nested IF
    else if (randomStatus == 1)
    { // Marks a child
      strcat_s(relationship, ARRLENMAX, "a child. ") ;
    } // End of Nested Else IF
    else
    { // Marks multiple kids.
      strcat_s(relationship, ARRLENMAX, "several kids. ") ;
    } // End of Nested ELSE
  } // End of Else IF
  else
  { // Marks Single
    strcpy_s(relationship, ARRLENMAX, "single. ") ;
  } // End of Else
  strcpy_s(currentRelationship, ARRLENMAX, currentPronouns[HE]) ;
  strcat_s(currentRelationship, ARRLENMAX, "is ") ;
  strcat_s(currentRelationship, ARRLENMAX, relationship) ;
  // Adds strings to char array for output.
} // end of getRelationship

void getZodiac(const genPro currentPronouns, // *IN* currentPronouns
               char currentZodiac[ARRLENMAX])
                       // *INOUT* currentZodiac, output array.
{ // Randomly chooses a birthmonth.
  list months = // Stores Months of the year
  {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
  } ; // end of months
  list signs = // Stores the star signs.
  {
    "The goat, Capricorn. ", "The water bearer, Aquarius. ",
    "The fish, Pisces. ", "The ram, Aries. ", "The bull, Taurus. ",
    "The twins, Gemini. ", "The crab, Cancer. ", "The lion, Leo. ",
    "The virgin, Virgo. ", "The scales, Libra. ", "The scorpion, Scorpio. ",
    "The archer, Sagittarius. "
  } ; // end of signs
  size arraySize = sizeArray(months) ; // Counts array size, encase new ones
                                      // are added.
  random zodiacChoice = rand() % arraySize ; // Gets random Number
  random secondChoice = rand() % 2 ; // Decides which way the sign will
                                     // lean.
  char chosenMonth[ARRLENMAX] ; // Stores month
  char chosenZodiac[ARRLENMAX] ; // Stores sign
  strcpy_s(chosenMonth, ARRLENMAX, months[zodiacChoice]) ;
  // Puts month into temporary array storage.
  if (secondChoice == 0)
  { // Zodiacs work between the halfs of two months
    // this IF statement has a 50% chance of running
    // and will change the zodiac of any month.
    if (zodiacChoice == 0)
    { // All other numbers can simply take a -1 to work
      // but for 0, that would become -1, so it changes to 11. 
      zodiacChoice = 11 ;
    } // End of Nested IF
    else
    { // Takes one off.
      zodiacChoice-- ;
    } // End of Nested Else
  } // End of IF
  strcpy_s(chosenZodiac, ARRLENMAX, signs[zodiacChoice]) ;
  
  strcpy_s(currentZodiac, ARRLENMAX, currentPronouns[HE]) ;
  strcat_s(currentZodiac, ARRLENMAX, "was born in the month of ") ;
  strcat_s(currentZodiac, ARRLENMAX, chosenMonth) ;
  strcat_s(currentZodiac, ARRLENMAX, " blessed by the star of ") ;
  strcat_s(currentZodiac, ARRLENMAX, chosenZodiac) ;
  // Adds strings to array for output
} // End of getZodiac

void checkStats(const stats currentStats, // *IN* Stats
                list jobs,  // *INOUT* Job list
                list workPlaces) // *INOUT* Workplace list
{ // Takes in stats and adds contents to arrays when
  // appropriate.
  size arraySize = sizeArray(jobs) ; // Sizes the array
  if (currentStats[INT] > 8)
  { // With Int above 8, adds this job.
    strcpy_s(jobs[arraySize], ARRLENMAX, "Lecturer") ;
    strcpy_s(workPlaces[arraySize], ARRLENMAX, "Northumbria University") ;
    arraySize++ ;
  } // End of first IF
  if (currentStats[CHAR] < 4)
  { // With Char below 4, adds this job.
    strcpy_s(jobs[arraySize], ARRLENMAX, "Drive Thru Attendant") ;
    strcpy_s(workPlaces[arraySize], ARRLENMAX, "McDonalds") ;
    arraySize++ ;
  } // End of Second IF
  if (currentStats[TOUGH] > 7)
  { // Tough above 7, adds this job.
    strcpy_s(jobs[arraySize], ARRLENMAX, "Boxer") ;
    strcpy_s(workPlaces[arraySize], ARRLENMAX, "a Boxing gym") ;
    arraySize++ ;
  } // End of Third IF
  if (currentStats[STR] > 7)
  { // STR above 7, adds this job.
    strcpy_s(jobs[arraySize], ARRLENMAX, "Woodcutter") ;
    strcpy_s(workPlaces[arraySize], ARRLENMAX, "a Sawmill") ;
    arraySize++ ;
  } // End of Fourth IF
  if (currentStats[AGI] > 7)
  { // AGI above 7, adds this job
    strcpy_s(jobs[arraySize], ARRLENMAX, "Ballet Teacher") ;
    strcpy_s(workPlaces[arraySize], ARRLENMAX, "a Dance school") ;
  } // End of Fifth IF
} // End of checkStats

void getJob(const stats currentStats, // *IN* Stats
            const genPro Pronouns, // *IN* Pronouns
            char currentJob[ARRLENMAX]) // *INOUT* Array for output
{ // Takes in stats and returns a sentance about 
  // where the character works, and what position.
  size arraySize = 0 ; // Sizes arrays
  random jobChoice = 0 ; // Random Number
  char chosenJob[ARRLENMAX] ; // Stores Job
  char chosenPlace[ARRLENMAX] ; // Stores workplace
  list jobs = // Lists jobs
  {
    "Mule Handler", "Stableboy", "Cook", "Cleaner", "Shelf Stacker",
    "Shop assistant"
  } ; // End of jobs
  list workPlace = // Lists workplaces
  {
    "the Army", "a Stable", "Nandos", "a Travel Lodge",
    "a Library", "a Tesco"
  } ; // Each job has a corresponding work place in space spot.
  // End of workPlace
  checkStats(currentStats, jobs, workPlace) ; // Checks stats to add
                                              // more content
  arraySize = sizeArray(jobs) ; // Sizes array
  jobChoice = rand() % arraySize ; // Gets random number
  strcpy_s(chosenJob, ARRLENMAX, jobs[jobChoice]) ; // Copies job 
  strcpy_s(chosenPlace, ARRLENMAX, workPlace[jobChoice]) ; // Copies workPlace
  jobChoice = rand() % 2 ; // Gets new number for structure
  if (jobChoice == 0)
  { // Checks a random variable and outputs the following
    // sentance structure, 50% of the time.
    strcpy_s(currentJob, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(currentJob, ARRLENMAX, "works as a ") ;
    strcat_s(currentJob, ARRLENMAX, chosenJob) ;
    strcat_s(currentJob, ARRLENMAX, " at ") ;
    strcat_s(currentJob, ARRLENMAX,chosenPlace) ;
    strcat_s(currentJob, ARRLENMAX,". ") ;
  } // End of IF
  else
  { // Checks a random variable and outputs the following
    // sentance structure, 50% of the time.
    strcpy_s(currentJob, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(currentJob, ARRLENMAX, "joined ") ;
    strcat_s(currentJob, ARRLENMAX,chosenPlace) ;
    strcat_s(currentJob, ARRLENMAX, " as a ") ;
    strcat_s(currentJob, ARRLENMAX, chosenJob) ;
    strcat_s(currentJob, ARRLENMAX,". ") ;
  } // End of Else
} // End of getJob

void constructPara(lines chosenLines, // *IN* chosenLines
                   const genPro genPronouns, // *IN* Gender Pronouns
                   const stats currentStats, // *IN* Stats
                   Values currentValues, // *IN* Values
                   char finalOutput[ARRPARAMAX])   // *INOUT* finalOutput
{ // Sorts through pre determined sentance flags and
  // calls up appropriate sub programs to generate the sentances
  // adding them all to the final Output provided.
  int currentLine = 0 ; // Marks the current line
  char tempSentance[ARRPARAMAX] ; // Used to temporarily 
                                  // store the chosen line
  for (currentLine = 0; currentLine < MAXSentances; currentLine++)
  { // Counts through each lines, based on the max.
    switch (chosenLines[currentLine])
    { // Calls the appropriate sub program based off of the pre determined
      // sentance values.
      case sentances::DREAM:
        getDream(genPronouns, currentStats, tempSentance) ;
        break; // Runs for Dream, getting that sentance.
      case sentances::RACE:
        getRace(genPronouns, currentValues.Race,tempSentance) ;
        break; // Runs for Race, getting that sentance.
      case sentances::PAST:
        getPast(genPronouns, currentValues.Past,
        currentValues.Gender, tempSentance) ;
        break; // Runs for Past, getting that sentance.
      case sentances::PET:
        getPet(genPronouns, currentStats[INT], tempSentance) ;
        break; // Runs for Pet, getting tht sentance.
      case sentances::RELATIVE:
        getRelative(genPronouns, tempSentance) ;
        break; // Runs for Relative, getting that sentance.
      case sentances::RELATIONSHIP:
        getRelationship(genPronouns, tempSentance) ;
        break; // Runs for Relationship, getting that sentance.
      case sentances::JOB:
        getJob(currentStats, genPronouns, tempSentance) ;
        break; // Runs for Job, getting that sentance.
      case sentances::ZODIAC:
        getZodiac(genPronouns, tempSentance) ;
        break; // Runs for Zodiac, getting that sentance.
      default:
        cout << ERROR << endl ; // Outputs an error, should never run
                                // New lines will need to be added
                                // manually.
    }
      strcat_s(finalOutput, ARRPARAMAX, tempSentance) ; // Adds each sentance
                                                       // to final output.
  }
} // End of constructPara

void getPronouns(gender charGender, genPro Pronouns) // *IN* Gender
                                                     // *INOUT* Pronouns
{ // Takes in gender and puts the appropriate pronouns in the array.
  if (charGender == gender::FEMALE)
  { // Sets female pronouns
    strcpy_s(Pronouns[0], ARRLISTMAX, "She ") ;
    strcpy_s(Pronouns[1], ARRLISTMAX, " her ") ;
    strcpy_s(Pronouns[2], ARRLISTMAX, " her ") ;
    strcpy_s(Pronouns[3], ARRLISTMAX, " she ") ;
    strcpy_s(Pronouns[4], ARRLISTMAX, "Her ") ;
  } // End of IF
  else
  { // Sets male pronouns
    strcpy_s(Pronouns[0], ARRLISTMAX, "He ") ;
    strcpy_s(Pronouns[1], ARRLISTMAX, " him ") ;
    strcpy_s(Pronouns[2], ARRLISTMAX, " his ") ;
    strcpy_s(Pronouns[3], ARRLISTMAX, " he ") ;
    strcpy_s(Pronouns[4], ARRLISTMAX, "His ") ;
  } // End of Else  
} // End of GetPronouns

void genIntel(statistic Intel,  //  *IN* Intel
              char tempOutput[ARRLENMAX], // *INOUT* tempOutput
              const genPro Pronouns) // *IN* Pronouns
{ // Takes in Int and outputs a line based off of it.
  switch (Intel)
  { // Sets the output based off of int.
  case 1:
  case 2:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is very stupid!") ;
    break ; // Runs if Intel is 1/2
  case 3:
  case 4:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, 
    "is isn't the sharpest tool in the drawer.") ;
    break ; // Runs if Intel is 3/4
  case 5:
  case 6:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is as smart as the average person.") ;
    break ; // Runs if Intel is 5/6
  case 7:
  case 8:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is quite intelligent!") ;
    break ; // Runs if Intel is 7/8
  case 9:
  case 10:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is a genius!") ;
    break ; // Runs if Intel is 9/10
  default: // Should never run
    cout << ERROR << endl ; // Error output
  } // End of Switch
} // End of genIntel

void genStren(statistic Stren,  //  *IN* Stren
  char tempOutput[ARRLENMAX], // *INOUT* tempOutput
  const genPro Pronouns) // *IN* Pronouns
{ // Takes in Str and outputs a line based off of it.
  switch (Stren)
  { // Sets the output based off of int.
  case 1:
  case 2:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is very feable!") ;
    break ; // Runs if Stren is 1/2
  case 3:
  case 4:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX,
      "is quite the wimp.") ;
    break ; // Runs if Stren is 3/4
  case 5:
  case 6:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "has an average body.") ;
    break ; // Runs if Stren is 5/6
  case 7:
  case 8:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is quite toned!") ;
    break ; // Runs if Stren is 7/8
  case 9:
  case 10:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is so strong that") ;
    strcat_s(tempOutput, ARRLENMAX, Pronouns[LHE]) ;
    strcat_s(tempOutput, ARRLENMAX, "crushes rocks with") ;
    strcat_s(tempOutput, ARRLENMAX, Pronouns[HIS]) ;
    strcat_s(tempOutput, ARRLENMAX, "bare hands!") ;
    break ; // Runs if Stren is 9/10
  default: // Should never run
    cout << ERROR << endl ; // Error output
  } // End of Switch
} // End of genStren

void genAgil(statistic Agil,  //  *IN* Agil
  char tempOutput[ARRLENMAX], // *INOUT* tempOutput
  const genPro Pronouns) // *IN* Pronouns
{ // Takes in Agi and outputs a line based off of it.
  switch (Agil)
  { // Sets the output based off of int.
  case 1:
  case 2:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is as slow as a snail!") ;
    break ; // Runs if Agil is 1/2
  case 3:
  case 4:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX,"is quite slow and inflexible.") ;
    break ; // Runs if Agil is 3/4
  case 5:
  case 6:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "isn't too agile.") ;
    break ; // Runs if Agil is 5/6
  case 7:
  case 8:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is quite agile!!") ;
    break ; // Runs if Agil is 7/8
  case 9:
  case 10:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is so agile that") ;
    strcat_s(tempOutput, ARRLENMAX, Pronouns[LHE]) ;
    strcat_s(tempOutput, ARRLENMAX, "gains a bonus to dodge chance!") ;
    break ; // Runs if Agil is 9/10
  default: // Should never run
    cout << ERROR << endl ; // Error output
  } // End of Switch
} // End of genAgil

void genTough(statistic Tough,  //  *IN* Tough
  char tempOutput[ARRLENMAX], // *INOUT* tempOutput
  const genPro Pronouns) // *IN* Pronouns
{ // Takes in Toughness and outputs a line based off of it.
  switch (Tough)
  { // Sets the output based off of int.
  case 1:
  case 2:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "bruises easily!") ;
    break ; // Runs if Tough is 1/2
  case 3:
  case 4:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is quite pathetic...") ;
    break ; // Runs if Tough is 3/4
  case 5:
  case 6:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "takes damage normally.") ;
    break ; // Runs if Tough is 5/6
  case 7:
  case 8:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is quite adept at taking blows!") ;
    break ; // Runs if Tough is 7/8
  case 9:
  case 10:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is so tough that") ;
    strcat_s(tempOutput, ARRLENMAX, Pronouns[LHE]) ;
    strcat_s(tempOutput, ARRLENMAX, 
    "has a tattoo! (10% bonus on taking damage!)") ;
    break ; // Runs if Tough is 9/10
  default: // Should never run
    cout << ERROR << endl ; // Error output
  } // End of Switch
} // End of genTough

void genChar(statistic Char,  //  *IN* Char
  char tempOutput[ARRLENMAX], // *INOUT* tempOutput
  const genPro Pronouns) // *IN* Pronouns
{ // Takes in Charisma and outputs a line based off of it.
  switch (Char)
  { // Sets the output based off of int.
  case 1:
  case 2:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is terrible with people!") ;
    break ; // Runs if Char is 1/2
  case 3:
  case 4:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "hasn't got the best people skills...") ;
    break ; // Runs if Char is 3/4
  case 5:
  case 6:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "can convince fools...") ;
    break ; // Runs if Char is 5/6
  case 7:
  case 8:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is charismatic enough to impress!") ;
    break ; // Runs if Char is 7/8
  case 9:
  case 10:
    strcpy_s(tempOutput, ARRLENMAX, Pronouns[HE]) ;
    strcat_s(tempOutput, ARRLENMAX, "is so charismatic that") ;
    strcat_s(tempOutput, ARRLENMAX, Pronouns[LHE]) ;
    strcat_s(tempOutput, ARRLENMAX, "can woo the heart of any person!") ;
    break ; // Runs if Char is 9/10
  default: // Should never run
    cout << ERROR << endl ; // Error output
  } // End of Switch
} // End of genChar

void getStatOutput(const stats charStats, // *IN* stats.
                   const genPro Pronouns, // *IN* Pronouns
                   char statOutput[ARRPARAMAX]) // *INOUT* Output
{ // Calls the proper sub programs and combines their outputs
  // then adds them to an array to return to main.
  char tempStr[ARRLENMAX] ; // Temporary string storage
  genStren(charStats[STR], tempStr, Pronouns) ; // Gets Stren Line.
  strcpy_s(statOutput, ARRPARAMAX, "\n\n") ; // Line breaks twice.
  strcat_s(statOutput, ARRPARAMAX, tempStr) ; // Adds line to Output
  genIntel(charStats[INT], tempStr, Pronouns) ; // Gets Intel line.
  strcat_s(statOutput, ARRPARAMAX, "\n\n") ; // Line breaks twice.
  strcat_s(statOutput, ARRPARAMAX, tempStr) ; // Adds line to Output
  genAgil(charStats[AGI], tempStr, Pronouns) ; // Gets Agil Line.
  strcat_s(statOutput, ARRPARAMAX, "\n\n") ; // Line breaks twice.
  strcat_s(statOutput, ARRPARAMAX, tempStr) ; // Adds line to Output
  genTough(charStats[TOUGH], tempStr, Pronouns) ; // Gets Tough Line
  strcat_s(statOutput, ARRPARAMAX, "\n\n") ; // Line breaks twice.
  strcat_s(statOutput, ARRPARAMAX, tempStr) ; // Adds line to Output
  genChar(charStats[CHAR], tempStr, Pronouns) ; // Gets Charisma line.
  strcat_s(statOutput, ARRPARAMAX, "\n\n") ; // Line breaks twice.
  strcat_s(statOutput, ARRPARAMAX, tempStr) ; // Adds line to Output
  strcat_s(statOutput, ARRPARAMAX, "\n\n") ; // Line breaks twice.

} // End of genStatOutput

int main() 
{ // Main Source
  srand((unsigned)time(NULL)) ; // Srand is declared instantly for 
                               // Pseudo Random Number Generation.
  stats charStats ; // Array to store statistic.
  statisticGen(charStats) ; // Runs the subprogram to generate the
                        // characters statistic and store them in an array.
  Values charValues ; // Declares the struct for character values
  valueGen(charValues) ; // Generates charValues
  
  char backStory[ARRPARAMAX] ; // Declares the character array used for output
  
  genFirstSentance(backStory, charValues) ; // Generates the first sentance and
                                         // adds to output array.
  lines chosenLines ;   // Declares a character array used to specificy
                        // what the lines in the paragraph will be.
  chooseSentance(chosenLines) ; // Decides on what lines will be used.
  genPro Pronouns; // Creates array for pronouns
  getPronouns(charValues.Gender, Pronouns) ;
  constructPara(chosenLines, Pronouns, charStats, charValues, backStory) ;
  // Calls a subprogram that takes in various inputs and outputs
  // the max sentances requested.
  cout << backStory << endl ; // Outputs the character array for the backstory.
  char statOutput[ARRPARAMAX] ; // Creates char array for stat output
  getStatOutput(charStats, Pronouns, statOutput) ; // Gets Statoutput
  cout << statOutput << endl ; // Outputs stat lines.
  return 0 ;
} // Main Source End