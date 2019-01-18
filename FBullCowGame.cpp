/*This file defines all the backend functions*/
#pragma once
#include "pch.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// This is done to make types more in accordance to the unreal standards
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // the default constructos

void FBullCowGame::Reset() 
{ 
	const FString HIDDEN_WORD = "mango"; // This MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIswon = false;
	return; 
}

int32 FBullCowGame::GetMaxTries() const
{
	// the difficulty is chosen according to the word length
	TMap<int32, int32> LettersToMaxTreis = { {1, 10}, {2, 10}, {3, 10}, {4, 8}, {5, 6}, {6, 6}, {7, 5} };
	return LettersToMaxTreis[MyHiddenWord.length()];
}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIswon; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{ 
	if (!IsIsogram(Guess)) // If the guess isn't a isogram then 
	{
		return EGuessStatus::NO_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase then
	{
		return EGuessStatus::Not_lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length; 
	}
	else
	{
		return EGuessStatus::OK;
	}

}

// Expects a valid guess and returns count of bulls and cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming correct word length

	for (int32 i = 0; i < WordLength; i++) {
		for (int32 j = 0; j < WordLength; j++) {
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++; // if match letter and position
				}
				else {
					BullCowCount.Cows++; // if only letter match
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) // max possible no of bulls
	{
		bGameIswon = true;
	}
	else
	{
		bGameIswon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// consider 0 or 1 letter word as isogram
	if (Guess.length() <= 1) { return true; }


	TMap<char, bool> LetterSeen;
	for (char Letter : Guess) // for each letter of the guess
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])// see if it is already contained in the hash
		{
			return false; // because can't repeat letters
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true; // for when null is entered and default reutrn
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	char Temp;
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}		
	}
	return true;
}
