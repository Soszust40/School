## Hangman Game - Oszust Industries
## Created on: 5-10-21 - Last update: 10-01-21
gameVersion = "v1.1.0-RETRO"
import random

def gameConfig():
## System Configures
    global exitSystem, gameHintsActivated, smartWordDetector, punishmentMode, systemName
    systemName = "Hangman"
    exitSystem = False
    gameHintsActivated = True
    smartWordDetector = True
    punishmentMode = True


def gameSetup():
## Setup Game
    global availablePossibleAnswers
    print("Loading...")
    availablePossibleAnswers = []
## Start Functions
    gameConfig()
    clear()
    availablePossibleAnswers.extend(("Dog", "Horse", "Cow", "Giraffe", "Tiger", "Sheep", "Zebra", "Rabbit", "Shark", "Reindeer"))
    availablePossibleAnswers.extend(("Star Wars", "Indiana Jones", "Snow White", "Wizard of Oz", "Back to the Future", "Forrest Gump", "Jaws", "Toy Story", "Jurassic Park", "Ghostbusters"))
    availablePossibleAnswers.extend(("Chicago", "Detroit", "New York", "Pittsburgh", "Denver", "Houston", "New Orleans", "San Francisco", "Miami", "Boston"))
    availablePossibleAnswers.extend(("Apple", "Popcorn", "Bacon and eggs", "Ice cream", "Cherries", "Cake", "Banana", "Pizza", "Pumpkin Pie", "Hot dogs"))
    if exitSystem == False:
        startMenu()

def clear():
## Clear Output
    print("\n" * 70)

def startMenu():
## Game Start Menu
    print("Welcome to Hangman. " + gameVersion + "\nCreated and published by Oszust Industries\n\n\n")
    print("1 - Start Game\n2 - Game Help\n3 - Quit")
    menuOption = input()
    if menuOption.lower() in ["1", "start", "game"]:
        menuOption = ""
        gameStart()
    elif menuOption.lower() in ["2", "help", "tips"]:
        clear()
        print("Game Help:\n")
        if gameHintsActivated == True: print("\nThe game will give you a category and a hint.")
        else: print("\nThe game will give you a category")
        print("The word you must guess is from that category.\n\nType a letter, and if it appears in the word, the blank spots will fill with that letter.\nIf the letter doesn't appear in the word, you will lose one of your three lives.\nOnce out of lives, you lose the game.\n\nIf you know the entire word/phrase, type 'solve'.\nYou will have one chance to guess the entire word/phrase.")
        if smartWordDetector == True: print("Smart Word Detector is active and allows you to type the entire word/phrase without having to type 'solve'.")
        if punishmentMode == True: print("\nPunishment Mode is active and will cause you to lose a life if you don't type a letter from the alphabet or type a letter you already used.")
        print("\n\n")
        startMenu()
    elif menuOption.lower() in ["3", "quit", "exit"]:
        return
    else:
        clear()
        print("\n\nPlease type a number. (1/2/3)\n\n\n")

def gameStart():
## Load Game
    global availablePossibleAnswers, currentCategory, firstTry, found, gameLives, lowerAnswer, properAnswer, usedLetters
    print("\n\nLoading Game...")
    clear()
    print("-" * 60)
    firstTry = True
    found = []
    gameLives = 3
    usedLetters = []
## Find Game Answer
    if len(availablePossibleAnswers) > 0:
        properAnswer = random.choice(availablePossibleAnswers)
## Find Game Category
        if properAnswer in ["Dog", "Horse", "Cow", "Giraffe", "Tiger", "Sheep", "Zebra", "Rabbit", "Shark", "Reindeer"]: currentCategory = "Animals"
        elif properAnswer in ["Star Wars", "Indiana Jones", "Snow White", "Wizard of Oz", "Back to the Future", "Forrest Gump", "Jaws", "Toy Story", "Jurassic Park", "Ghostbusters"]: currentCategory = "Movies"
        elif properAnswer in ["Chicago", "Detroit", "New York", "Pittsburgh", "Denver", "Houston", "New Orleans", "San Francisco", "Miami", "Boston"]: currentCategory = "US Cities"
        elif properAnswer in ["Apple", "Popcorn", "Bacon and eggs", "Ice cream", "Cherries", "Cake", "Banana", "Pizza", "Pumpkin Pie", "Hot dogs"]: currentCategory = "Foods"
        gameHints()
## Start Game
        if " " in properAnswer: found.append(" ")
        lowerAnswer = properAnswer.lower()
        lowerAnswer = lowerAnswer.replace(" ", "")
        if gameHintsActivated == True: print("Game Category: " + currentCategory + "\nGame Hint: " + gameHint)
        else: print("Game Category: " + currentCategory)
        HangmanGame()
    else:
        clear()
        startMenu("")

def gameHints():
## Find Game Hint
    global gameHint
    if gameHintsActivated == True:
        if currentCategory == "Animals":
            if properAnswer == "Dog": gameHint = "Man's best friend"
            elif properAnswer == "Horse": gameHint = "Racing Animal"
            elif properAnswer == "Cow": gameHint = "Animal to milk"
            elif properAnswer == "Giraffe": gameHint = "Long-necked animal"
            elif properAnswer == "Tiger": gameHint = "Large wild cat"
            elif properAnswer == "Sheep": gameHint = "Woolly animal"
            elif properAnswer == "Zebra": gameHint = "Striped animal"
            elif properAnswer == "Rabbit": gameHint = "Long-eared animal"
            elif properAnswer == "Shark": gameHint = "Predatory fish"
            elif properAnswer == "Reindeer": gameHint = "Arctic animal"
        elif currentCategory == "Movies":
            if properAnswer == "Star Wars": gameHint = "No. I am your father."
            elif properAnswer == "Indiana Jones": gameHint = "It belongs in a museum!"
            elif properAnswer == "Snow White": gameHint = "Who's the fairest of them all?"
            elif properAnswer == "Wizard of Oz": gameHint = "There's no place like home."
            elif properAnswer == "Back to the Future": gameHint = "When this baby hits 88 miles per hour."
            elif properAnswer == "Forrest Gump": gameHint = "Life is a box of chocolates."
            elif properAnswer == "Jaws": gameHint = "You're gonna need a bigger boat."
            elif properAnswer == "Toy Story": gameHint = "To infinity, and beyond!"
            elif properAnswer == "Jurassic Park": gameHint = "Life uh... finds a way."
            elif properAnswer == "Ghostbusters": gameHint = "Who you gonna call?"
        elif currentCategory == "US Cities":
            if properAnswer == "Chicago": gameHint = "Windy City"
            elif properAnswer == "Detroit": gameHint = "Motor City"
            elif properAnswer == "New York": gameHint = "The Big Apple"
            elif properAnswer == "Pittsburgh": gameHint = "Steel City"
            elif properAnswer == "Denver": gameHint = "Mile High City"
            elif properAnswer == "Houston": gameHint = "Space City"
            elif properAnswer == "New Orleans": gameHint = "The Big Easy"
            elif properAnswer == "San Francisco": gameHint = "The Golden City"
            elif properAnswer == "Miami": gameHint = "The Magic City"
            elif properAnswer == "Boston": gameHint = "The Hub"
        elif currentCategory == "Foods":
            if properAnswer == "Apple": gameHint = "One a day keeps the doctor away."
            elif properAnswer == "Popcorn": gameHint = "Common movie snack"
            elif properAnswer == "Bacon and eggs": gameHint = "Common breakfast food"
            elif properAnswer == "Ice cream": gameHint = "Popular summer treat"
            elif properAnswer == "Cherries": gameHint = "Michigan grown fruit"
            elif properAnswer == "Cake": gameHint = "Dessert for birthdays"
            elif properAnswer == "Banana": gameHint = "Monkeys enjoy eating this"
            elif properAnswer == "Pizza": gameHint = "Cheese and pepperoni"
            elif properAnswer == "Pumpkin Pie": gameHint = "Common at Thanksgiving dinner"
            elif properAnswer == "Hot dogs": gameHint = "Popular ballpark food"
        else:
            print("Game Error: (Restarting game)...")
            gameStart()
    else: gameHint = "No Hints"

def HangmanGame():
## Start Game
    global firstTry, found, gameLives, usedLetters, userGuess
## Lives Left
    if gameLives <= 0:
        print("----|\n|   0\n|  l|l\n|   |\n|   ^\n")
        print("You ran out of lives.\n\n\nThe letters you used were: " + str(usedLetters) + "\nThe correct answer was: " + properAnswer + "\n\n")
        playAgain("Incorrect")
## Whole Word Guessed
    else:
        if len(set(properAnswer.lower())) == len(found):
            if 3 - gameLives == 1: print("Nice Job! You guessed the word correctly.\n\n\nYou only used " + str(3 - gameLives) + " life.\nThe letters you used were: " + str(usedLetters) + "\nThe answer was: " + properAnswer + "\n\n")
            else: print("Nice Job! You guessed the word correctly.\n\n\nYou only used " + str(3 - gameLives) + " lives.\nThe letters you used were: " + str(usedLetters) + "\nThe answer was: " + properAnswer + "\n\n")
            playAgain("Correct")
            return
        else:
            if firstTry == True: print("\n\n")
            if gameLives == 1: print("----|\n|   0\n|  l|l\n|   \n|   ") 
            elif gameLives == 2: print("----|\n|   0\n|   \n|   \n|   ") 
            elif gameLives == 3: print("----|\n|   \n|   \n|   \n|   ") 
            print("\nLives Remaining: " + str(gameLives) + "\n")
            print(" ".join(i if i in found else '_' for i in properAnswer.lower()))
## Show Used Letters
        if firstTry == False: print("\nLetters that you have used: " + str(usedLetters) + "\n")
        userGuess = input(str("\nWhat letter would you like to guess? ")).replace(" ", "")
        if userGuess.lower() not in ["quit", "exit", "terminate", "menu", "mainmenu", "back"]:
            clear()
            print("-" * 60)
            if gameHintsActivated == True: print("Game Category: " + currentCategory + "\nGame Hint: " + gameHint + "\n")
            else: print("Game Category: " + currentCategory + "\n")
## Letter Checks
        if userGuess.isalpha() == False:
            print("Please type a letter from the alphabet.\n\n")
            if punishmentMode == True: gameLives -= 1
            HangmanGame()
        elif userGuess.lower() in ["quit", "exit", "terminate"]:
            return
        elif userGuess.lower() in ["menu", "mainmenu", "back"]:
            print("\n\n\nExiting to the menu...")
            clear()
            startMenu("")
        elif userGuess.lower() in ["solve", "answer"]:
            userGuess = ""
            solveWord()
            return
        elif userGuess.lower() == lowerAnswer:
            if smartWordDetector == True: solveWord()
            else:
                print("You can only guess one letter at a time.\nYou can type 'solve' if you know the entire word/phrase.\n\n")
                if punishmentMode == True: gameLives -= 1
                HangmanGame()
        elif len(userGuess) != 1 and userGuess.lower() not in ["quit", "exit", "terminate", "menu", "mainmenu", "quit", "exit", "terminate"]:
            print("You can only guess one letter at a time.\nYou can type 'solve' if you know the entire word/phrase.\n\n")
            if punishmentMode == True: gameLives -= 1
            HangmanGame()
## Letter Already Used
        else:
            if userGuess.lower() in usedLetters:
                print("\nYou already tried this letter.\n\n")
                if punishmentMode == True: gameLives -= 1
                HangmanGame()
## Letter in Word
            else:
                firstTry = False
                usedLetters.append(userGuess.lower())
                if userGuess.lower() in lowerAnswer:
                    print("\nYes, that is in the word.\n\n")
                    found.append(userGuess.lower())
                    HangmanGame()
                else:
                    gameLives -= 1
                    print("\nNo, that is not in the word.\n\n")
                    HangmanGame()

def solveWord():
## Solve Entire Word
    global userGuess
    print(" ".join(i if i in found else '_' for i in properAnswer.lower()))
    if userGuess == "": userGuess = input(str("\n\nYou only get one chance!\n\nWhat word/phrase do you think it is? "))
    userGuess = userGuess.replace(" ", "")
    userGuess = userGuess.lower()
    if userGuess == lowerAnswer:
        if 3 - gameLives == 1: print("\n\nWow! You got the word right.\n\n\nYou only used " + str(3 - gameLives) + " life.")
        else: print("\n\nWow! You got the word right.\n\n\nYou only used " + str(3 - gameLives) + " lives.")
        if not usedLetters: print("You didn't use any letters.\nThe answer was: " + properAnswer + "\n\n")
        else: print("The letters you used were: " + str(usedLetters) + "\nThe answer was: " + properAnswer + "\n\n")
        playAgain("Correct")
    else:
        if not usedLetters: print("\n\nSorry, that was not the word.\nYou didn't use any letters.\nThe correct answer was: " + properAnswer + "\n\n")
        else: print("\n\nSorry, that was not the word.\n\n\nThe letters you used were: " + str(usedLetters) + "\nThe correct answer was: " + properAnswer + "\n\n")
        playAgain("Incorrect")

def playAgain(gameResult):
## Play Again
    global availablePossibleAnswers, oneGamePlayed
    oneGamePlayed = True
    if gameResult != "Retry":
        availablePossibleAnswers.remove(properAnswer)
    againAnswer = input(str("Would you like to play another game or return to the menu? (Yes/No/Menu) ")).replace(" ", "")
    if  againAnswer.lower() in ["y", "yes", "next"]:
        gameStart()
    elif againAnswer.lower() in ["n", "no"]:
        print("\n\n\n\nThanks so much for playing!\n")
    elif againAnswer.lower() in ["m", "menu", "mainmenu"]:
        clear()
        startMenu()
    else:
        print("\n\nPlease type Yes/No/Menu\n\n")
        playAgain("Retry")


## Start System
gameSetup()