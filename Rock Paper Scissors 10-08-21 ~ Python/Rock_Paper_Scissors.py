## Rock Paper Scissors - Simon Oszust
## Created on: 10-02-21 - Last update: 10-08-21
## Oszust Industries - Small Projects Collection
gameVersion = "v1.0.0"
def clear(): return ("\n" * 70)
import random

def gameSetup():
## Setup Game
    print("Loading...")
## Start Functions
    startMenu(False)

def startMenu(menuError):
## Game Start Menu
    if menuError == False: print(clear() + "Welcome to Rock Paper Scissors. " + gameVersion + "\nCreated and published by Oszust Industries\n\n\n")
    if menuError == "help": print("Welcome to Rock Paper Scissors. " + gameVersion + "\nCreated and published by Oszust Industries\n\n\n")
    elif menuError == True: print(clear() + "Please type a number. (1/2/3/4)\n\n\n")
    print("1 - One Player Game\n2 - Two Player Game\n3 - Game Help\n4 - Quit Game")
    option = input(str("\nType a number. (1/2/3/4) ")).lower().replace(" ", "")
    if option in ["1", "one", "oneplayer"]: onePlayerGame(0, 0, 0, 0, False, False)
    elif option in ["2", "two", "twoplayer"]: onePlayerGame(0, 0, 0, 0, False, True)
    elif option in ["3", "help", "tips"]:
        print(clear() + "Game Help:\n\n\nRock Paper Scissors is a game where you try to beat your opponent with the choice you make.\n\n-Rock beats scissors\n-Scissors beats paper\n-Paper beats rock\n\nThe one-player game is when you play against the computer. You choose an action, and the computer will make a choice."
        "\n\nThe two-player game is when you play against someone else on the same computer. You have to take turns typing in what action you want to perform.\n\nThe game keeps track of how many wins and losses each player has received.\n\n\n")
        startMenu("help")
    elif option in ["4", "exit", "stop", "quit"]: print("\n\n\nClosing application....\n")
    else: startMenu(True)

def player2Choice(gamesWon, gamesLost, gamesWon2, gamesLost2, choiceError):
## Player 2 Choice
    print(clear() + "Two player game - Player 2's turn:\n\nPlayer 1 Games won: " + str(gamesWon) + "  |  Player 1 Games lost: " + str(gamesLost) + "\nPlayer 2 Games won: " + str(gamesWon2) + "  |  Player 2 Games lost: " + str(gamesLost2) + ("\n" + "-" * 40))
    if choiceError == True: user2 = input(str("\nPlease type 'rock', 'paper', or 'scissors'.\n\nPlayer 2, enter a choice (rock, paper, scissors): ")).lower().replace(" ", "")
    else: user2 = input(str("\nPlayer 2, enter a choice (rock, paper, scissors): ")).lower().replace(" ", "")
    if user2 in ["rock", "r", "1"]: return "rock"
    elif user2 in ["paper", "p", "2"]: return "paper"
    elif user2 in ["scissors", "s", "3"]: return "scissors"

def onePlayerGame(gamesWon, gamesLost, gamesWon2, gamesLost2, choiceError, twoPlayerGame):
## One Player Game
    global userMoves
    if twoPlayerGame == False: print(clear() + "One player game:\n\nGames won: " + str(gamesWon) + "  |  Games lost: " + str(gamesLost) + ("\n" + "-" * 40))
    elif twoPlayerGame == True: print(clear() + "Two player game - Player 1's turn:\n\nPlayer 1 Games won: " + str(gamesWon) + "  |  Player 1 Games lost: " + str(gamesLost) + "\nPlayer 2 Games won: " + str(gamesWon2) + "  |  Player 2 Games lost: " + str(gamesLost2) + ("\n" + "-" * 40))
    if choiceError == True: print("\nPlease type 'rock', 'paper', or 'scissors'.")
    if twoPlayerGame == False: user = input(str("\nEnter a choice (rock, paper, scissors): ")).lower().replace(" ", "")
    elif twoPlayerGame == True: user = input(str("\nPlayer 1, enter a choice (rock, paper, scissors): ")).lower().replace(" ", "")
    if user in ["rock", "r", "1"]: user = "rock"
    elif user in ["paper", "p", "2"]: user = "paper"
    elif user in ["scissors", "s", "3"]: user = "scissors"
    else:
        if twoPlayerGame == False: onePlayerGame(gamesWon, gamesLost, gamesWon2, gamesLost2, True, False)
        elif twoPlayerGame == True: onePlayerGame(gamesWon, gamesLost, gamesWon2, gamesLost2, True, True)
        return
    if twoPlayerGame == False:
        CPU = random.randrange(1,10)
        try:
            if len(userMoves) > 2 and CPU < 7:
                if gamesWon - gamesLost < random.randrange(2,6):
                    if max(set(userMoves), key = userMoves.count) == "rock": CPU = "paper"
                    elif max(set(userMoves), key = userMoves.count) == "paper": CPU = "scissors"
                    elif max(set(userMoves), key = userMoves.count) == "scissors": CPU = "rock"
                else:
                    if max(set(userMoves), key = userMoves.count) == "rock": CPU = "rock"
                    elif max(set(userMoves), key = userMoves.count) == "paper": CPU = "paper"
                    elif max(set(userMoves), key = userMoves.count) == "scissors": CPU = "scissors"
            else: CPU = random.choice(["rock", "paper", "scissors"])
        except:
            userMoves = []
            CPU = random.choice(["rock", "paper", "scissors"])
    elif twoPlayerGame == True:
        CPU = player2Choice(gamesWon, gamesLost, gamesWon2, gamesLost2, False)
        while CPU == None: CPU = player2Choice(gamesWon, gamesLost, gamesWon2, gamesLost2, True)
        print(clear() + "Two player game - Results:\n\nPlayer 1 Games won: " + str(gamesWon) + "  |  Player 1 Games lost: " + str(gamesLost) + "\nPlayer 2 Games won: " + str(gamesWon2) + "  |  Player 2 Games lost: " + str(gamesLost2) + ("\n" + "-" * 40))
    if twoPlayerGame == False: print("\nYou chose: " + user + "\nThe CPU chose: " + CPU + "\n\n\n")
    elif twoPlayerGame == True: print("\nPlayer 1 chose: " + user + "\nPlayer 2 chose: " + CPU + "\n\n\n")
    if user == CPU and twoPlayerGame == False: print("You and CPU both selected " + user + ". It's a tie.")
    elif user == CPU and twoPlayerGame == True: print("Player 1 and Player 2 both selected " + user + ". It's a tie.")
    elif user == "rock":
        if CPU == "scissors":
            gamesWon += 1
            if twoPlayerGame == False: print("Rock beats scissors! You win!")
            else:
                print("Rock beats scissors! Player 1 wins.")
                gamesLost2 += 1
        else:
            gamesLost += 1
            if twoPlayerGame == False: print("Paper beats rock! You lose.")
            else:
                print("Paper beats rock! Player 2 wins.")
                gamesWon2 += 1
    elif user == "paper":
        if CPU == "rock":
            gamesWon += 1
            if twoPlayerGame == False: print("Paper beats rock! You win!")
            else:
                print("Paper beats rock! Player 1 wins.")
                gamesLost2 += 1
        else:
            gamesLost += 1
            if twoPlayerGame == False: print("Scissors beats paper! You lose.")
            else:
                print("Scissors beats paper! Player 2 wins.")
                gamesWon2 += 1
    elif user == "scissors":
        if CPU == "paper":
            gamesWon += 1
            if twoPlayerGame == False: print("Scissors beats paper! You win!")
            else:
                print("Scissors beats paper! Player 1 wins.")
                gamesLost2 += 1
        else:
            gamesLost += 1
            if twoPlayerGame == False: print("Rock beats scissors! You lose.")
            else:
                print("Rock beats scissors! Player 2 wins.")
                gamesWon2 += 1
    if twoPlayerGame == False:
        userMoves.append(user)
        if len(userMoves) > 4: userMoves.remove(userMoves[0])
    while user not in ["yes", "y", "again", "menu", "m", "no", "n", "exit", "quit"]:
        user = input("\nDo you want to play another game? (Yes, No, or Menu) ").lower().replace(" ", "")
        if user in ["yes", "y", "again"] and twoPlayerGame == False: onePlayerGame(gamesWon, gamesLost, gamesWon2, gamesLost2, False, False)
        elif user in ["yes", "y", "again"] and twoPlayerGame == True: onePlayerGame(gamesWon, gamesLost, gamesWon2, gamesLost2, False, True)
        elif user in ["menu", "m"]: startMenu(False)
        elif user in ["no", "n", "exit", "quit"]: print("\n\n\nClosing application....\n")
        else: print("\nPlease type 'yes', 'no', or 'menu'.")

## Start System
gameSetup()
