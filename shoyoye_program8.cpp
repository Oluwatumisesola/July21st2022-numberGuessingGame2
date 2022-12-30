//THIS IS AN EXAMPLE TO HELP YOU GET STARTED WITH THIS ASSIGNMENT
/*
STUDENT NAME: Tumi Shoyoye
Due Date: July 21st 2022
Course:  C0P3014
Assignment:  Program 8 summer 2022
Professor: Sorgente

Description: number guessing game with a random number generator
introduction to class member functions, private and public member variables
mutator and accessor functions.

*************************************************************/

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator

using namespace std;

/*********************************************************
//Following is the declaration of gameNumberGuess
**********************************************************/

class gameNumberGuess
{
public:
	//constructor
	gameNumberGuess();

	//these functions are public so they can be accessed by non-member functions
	void SetUpperValue(int); //sets the upper range for the round (mutator)
	int  GetUpperValue()const; //returns the value of the private member variable (accessor)
	void SetMaxGuesses(int);//sets the number of guesses for the round (mutator)
	int  GetMaxGuesses()const;//returns the value of the private member variable (accessor)
	int  GetSolution()const; //returns the value of the private member variable (accessor)

	//Generates the solution number in the correct range
	void GenerateSolutionNumber();

	//Displays the range, prompts, and gets the next guess from the user
	void GetGuessInput();

	//returns true if the guess matches the solution
	//returns false if they do not match, lets the user know if the guess was too high or too low
	bool ProcessGuess();

	//these variables are public so they can be accessed by non-member functions
	int smallNum;
	int largeNum;
	bool above;
	bool below;

private:
	int level;
	int upperValue;
	int maxGuesses;
	int currentGuess;
	int solution;
};

//member function definitions will go here
//the default constructor is called when and object of
//guessGame is delared
gameNumberGuess::gameNumberGuess()
{
	cout << "The default number guess constructor has been called\n\n";
	level = 0; //game level (1 or 2) 
	upperValue = 0; //upper range value (example 100 or 1000)
	//initialize all the member variables here (public and private)
    smallNum = 0; //the smallest number for feedback
	largeNum = 0; //the largest number for feedback
	above = false; //feedback about whether you are above guess
	below = false; //feedback about whether you are below guess
	level= 0; //what level game you are on
	maxGuesses = 0; //max amount of guess
	currentGuess = 0; //the guess you are currently on
	solution = 0; //feedback for user to see the solution
};

//accessor and mutator functions
void gameNumberGuess::SetUpperValue(int upper)
//sets the upper range for the round (mutator)
{
	//set
	upperValue = upper;
}
int gameNumberGuess::GetUpperValue()const
//returns the value of the private member variable (accessor)
{
	//return
	return upperValue;
}
void gameNumberGuess::SetMaxGuesses(int max)
//sets the number of guesses for the round (mutator)
{
	//set
    maxGuesses = max;
}
int  gameNumberGuess::GetMaxGuesses()const
//returns the value of the private member variable (accessor)
{
	//return
    return maxGuesses;
}
int  gameNumberGuess::GetSolution()const
//returns the value of the private member variable (accessor)
{
	//return
    return solution;
}


// A pseudo random number has been generated in the correct range
void gameNumberGuess::GenerateSolutionNumber()
{
	srand((unsigned)time(0));
	solution = 1 + rand() % upperValue;
	//cout << "\nSolution is " << solution << endl;
}


//Displays the range, prompts, and gets the next guess from the user
void gameNumberGuess::GetGuessInput()
{
	if (below)
	{
		if (smallNum < currentGuess)
		{
			smallNum = currentGuess;
		}
	}
	if (above)
    {
        if (largeNum > currentGuess)
        {
            largeNum = currentGuess;
        }
    }
	
	cout << "\nEnter a guess between " << smallNum << " and " << largeNum << " : ";
	//get the guess from the user
    cin >> currentGuess;
}

//returns true(guess matches solution) 
//(lets the user know if the guess was too high or too low)
bool gameNumberGuess::ProcessGuess()
{
	if (currentGuess > solution)
	{
		cout << "\nYour guess was too high.\n";
		above = true;
		return false;
	}
	else if(currentGuess < solution)
    {
        cout << "\nYour guess was too low.\n";
        below = true;
        return false;
    }
    else
    {
        cout <<"\nYour guess was correct!";
        return true;
    }
}




//function prototype for PlayOneRound NOT a member function
//Name:  PlayOneRound
//Precondition: The data variable (string) and object (gameNumberGuess) have been declared
//			the string has a value before calling this function
//Postcondition: One round of the game Number Guess has been completed
//Description:  Plays one round of the game Number Guess
void PlayOneRound(const string&, gameNumberGuess&);

//function prototype for SetUp NOT a member function
//Name:  SetUpLevel
//Precondition: The object (gameNumberGuess) has been declared before calling this function
//Postcondition: The member variables have been reset for a round of the game
//Description:  Sets up one round of the game
void SetUpLevel(gameNumberGuess&);


int main()
{
	string yesOrNo;
	string name;

	//declare a number game object (current game)
    gameNumberGuess currentGame;
	
	//ask and get the first name
    cout << "What is your name? ";
    cin >> name;  
	//want to play?
    cout << "\nDo you want to play? (Y) or (N)";
    cin >> yesOrNo;
	//while begin loop
    while(yesOrNo != "n" && yesOrNo != "N")
	{
        //play round
		PlayOneRound(name, currentGame);
		//again?
        cout << "\nDo you want to play again?" << endl;
        cin >> yesOrNo;
	}
	//good bye and thanks
     cout << name << " goodbye and thank you for playing!!" << endl;
	return  0;
}

//*************************************************************************************
//Name:  PlayOneRound
//Precondition: The data variable (string) and object (gameNumberGuess) have been declared
//			the string has a value before calling this function
//Postcondition: One round of the game Number Guess has been completed
//Description:  Plays one round of the game Number Guess
//*************************************************************************************

void PlayOneRound(const string& name, gameNumberGuess& currentGame)
{
	//set up the level
	SetUpLevel(currentGame);

	//generate the random number solution
	currentGame.GenerateSolutionNumber(); //member function

	//initalize bool and high/low values
	currentGame.above = 0;
	currentGame.below = 0;
	currentGame.smallNum = 1;
	//accessor function
	currentGame.largeNum = currentGame.GetUpperValue();

	for (int i = 1; i < currentGame.GetMaxGuesses(); i++)
	{
		//tell the user what guess number they are on
        cout << "You are on Guess " << i << " of " << currentGame.GetMaxGuesses();
		//get the next guess
		currentGame.GetGuessInput();

		//reset above and below bool values to false
		currentGame.below = 0;//public member variables
		currentGame.above = 0;

		if (currentGame.ProcessGuess() == true)
		{
			cout << "\nYou won that round, " << name << "!\n";
			i = currentGame.GetMaxGuesses();//stop the loop without a break statement
		}
        else 
        {
            cout << "\nYou lost that round, " << name << "!\n";
        }
	}
	//display the solution when they win or lose
    cout << "\nSolution is " << currentGame.GetSolution() << endl;
}

//*************************************************************************************
//Name:  SetUpLevel
//Precondition: The object (gameNumberGuess) has been declared before calling this function
//Postcondition: The member variables have been reset for a round of the game
//Description:  Sets up one round of the game
//*************************************************************************************

void SetUpLevel(gameNumberGuess& currentGame)
{
	int level;
	do {
		cout << "\n\nwhat level(Enter 1 or 2)? \n(1) Level 1 - 5 guesses, numbers 1 through 100 \n" <<
			"(2) Level 2 - 8 guesses, numbers 1 through 1906\n";

		cin >> level;
	} while (level > 2 || level < 1);

	if (level == 1)
	{
		currentGame.SetUpperValue(100); //mutator function
		currentGame.SetMaxGuesses(5);
	}
	//level 2
    else if (level == 2)
    {
        currentGame.SetUpperValue(1906); //mutator function
        currentGame.SetMaxGuesses(8);
    }
	else  cout << "That is not a valid level\n";

}