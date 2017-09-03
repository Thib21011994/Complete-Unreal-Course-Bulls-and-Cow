/*
This is the console executable of the game which is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText Guess);
void PrintGameSummary();
bool AskToPlayAgain();

FBullAndCowGame BCGame;

// entry point in the application
int main()
{	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	
	return 0;
}

// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// loop for the number of turns asking for guesses
void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();
	constexpr int32 NUMBER_OF_TURNS = 5;

	// TODO change from FOR loop to WHILE when validation logic is added
	// while the game is not won and there are tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".";

		std::cout << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary();
	return;
}

// get a guess from the player
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry;
		std::cout << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check valid guesses
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please, enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please, enter a word with no repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please, enter all lowercase letters.";
			break;
		default:
			break;
		}
		return Guess;
	} 
	while (Status != EGuessStatus::OK);		
}

// print the guess back
void PrintGuess(FText Guess)
{
	std::cout << "Your guess was: " << Guess;
	std::cout << std::endl;
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done, you won!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		return true;
	}
	else
	{
		return false;
	}
}