/* This is the main file of the game. It contains all the high level funciton calls that makes 
the game run*/

#include "pch.h"
#include "FBullCowGame.h"
#include <iostream>
#include <string>

// This is done to make types more in accordance to the unreal standards
using FText = std::string;
using int32 = int;
FBullCowGame BCGame; // instantiate a new game

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


int main()
{
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}


void PrintIntro() {
	// introduce the game
	std::cout << "\n\nWeclcome to Bulls and Cows a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 NumberOfTries = BCGame.GetMaxTries();
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


// loop continually untill the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	do
	{
		// get a geuss from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		FText Guess = "";
		std::cout << "Try (" << CurrentTry << "/" << BCGame.GetMaxTries();
		std::cout << ")" << " Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess); // check validity

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter only " << BCGame.GetHiddenWordLength() << " letter word\n\n";
			break;
		case EGuessStatus::Not_lowercase:
			std::cout << "Please use only lowercase for input.\n\n";
			break;
		case EGuessStatus::NO_Isogram:
			std::cout << "Please Enter only isograms(words without any repeating letters).\n\n";
			break;
		default:
			return Guess; 
		}
	} while (Status != EGuessStatus::OK);
}


bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you wanna play with the same word again (y/n)?\n";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Good going\n";
	}
	else
	{
		std::cout << "Better Luck Next time.\n";
	}

	return;
}

 