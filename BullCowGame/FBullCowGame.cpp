#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullAndCowGame::FBullAndCowGame()
{
	Reset();
}

int32 FBullAndCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullAndCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullAndCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullAndCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullAndCowGame::CheckGuessValidity(FString Guess)  const
{
	// if the guess isn't an isogram, return an error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isn't all lowercase, return an error
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong, return an error
	else if (Guess.length() != MyHiddenWord.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	// otherwise return OK
	else
	{
		return EGuessStatus::OK;
	}
}

void FBullAndCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

// receives a valid guess, increments the number turn
FBullCowCount FBullAndCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all leters in the hidden word
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[MHWChar] == MyHiddenWord[GChar])
			{
				// increments bulls if they're in the same place
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				// increments cows if they're not
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullAndCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullAndCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
