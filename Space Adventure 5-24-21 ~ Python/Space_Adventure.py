## Space Adventure Game (School Project) - Oszust Industries
## Created on: 5-24-21 - Last update: 2-27-22
gameVersion = "v1.1.0"
def clear(): return ("\n" * 70)
def clearStory(): return (("-" * 200) + "\n\n")
from random import randrange
import random
 
def gameSetup():
    ## Setup game
    global alreadyRead, crewChoosing, engineFailure, gameChoice, menuOption, missionPlanet, missionTimer, playerAttack, playerCargo, playerDefense, playerSpeed, randomNumber, scoutPlanet
    print("Loading..." + clear())
    playerDefense, playerAttack, playerSpeed, playerCargo, alreadyRead, crewChoosing, randomNumber, missionPlanet, missionTimer, scoutPlanet, engineFailure, menuOption, gameChoice = 0, 0, 0, 0, False, 1, 0, "", -1, False, False, "", ""
    ## Start Functions
    startMenu("")

def crashMessage():
    ## Display Crash
    global Argument
    import webbrowser
    webbrowser.open("https://github.com/Oszust-Industries/School-Projects",  new = 2, autoraise = True)
    print(clear() + "Crash Log:\n" + ("-" * 50 + "\n") + str(Argument) + ("\n" + "-" * 50) + "\n")
    crash = input("Space Adventure Game (School Project) has crashed. Please report your crash to the issues tab in GitHub.\n\nPress enter to restart Space Adventure Game (School Project)...\n")
    if crash not in ["exit()", "exit", "quit"]:
        try: gameSetup()
        except Exception as Argument: crashMessage()
    else: exit()

def startMenu(menuOption):
    ## Game Start Menu
    if menuOption == "": print("Welcome to Space Adventure. " + gameVersion + "\nCreated and published by Oszust Industries\n\n\n")
    menuOption = input(str("1 - Start Game\n2 - Game Help\n3 - Quit Game\n\nType a number. (1/2/3) ")).replace(" ", "")
    if menuOption.lower() in ["1", "start", "game"]:
        print(clear())
        captainChoice()
    elif menuOption.lower() in ["2", "help", "tips"]:
        print(clear())
        print("Game Help:\n\n\nThis game is a choose your own adventure game."
        "\nYou are a captain of a spaceship on a random mission."
        "\nYour choices will change the mission's outcome."
        "\n\nYou will start by picking a ship."
        "\nEach ship has their own stats that will affect your mission."
        "\n\nNext, you will pick crew members that will increase your ship's stats."
        "\nThe amount of crew members you can choose, is determined by how much your ship can hold."
        "\n\nYour ship's stats can change the story and cause random events to occur."
        "\nBe sure to balance your stats. All of the stats are equally important.\n\n\n")
        startMenu("")
    elif menuOption.lower() in ["3", "quit", "exit"]:
        print("\n\n\nDo not close application.\nSaving and exiting...\n")
        exit()
    else:
        print(clear() + "Please type a number. (1/2/3)\n\n\n")
        startMenu("Again")

def commonPrintMessages(message):
    ## Messages that are printed often
    global alreadyRead, storyLocation
    if message == "showUserStats":
        print(("-" * 20) + "\nShip Defense: " + str(playerDefense) + "\nShip Attack: " + str(playerAttack) + "\nShip Speed: " + str(playerSpeed) + "\nShip Storage: " + str(playerCargo))
        if missionTimer > -1: print("Mission Time Remaining: " + str(missionTimer) + " hours")
        print("-" * 20 + "\n")
    elif message == "NotANumber":
        print("\nPlease type a number.")
        alreadyRead = True
        crewSize()
    elif message == "notEnoughSpace":
        print("\nYou do not have enough room to fit the new crew members. Please pick a lower number.")
        alreadyRead = True
        crewSize()
    elif message == "spaceLeft":
        print(("-" * 85) + "\nYou have room for " + str(crewMemberAmount) + " crew members.")
    elif message == "askToRestart":
        storyLocation = 0
        gameChoice = input(str("\n\n\nPush Enter to quit to the menu..."))
        gameSetup()

def captainChoice():
    ## User Picks Ship
    global gameChoice, playerAttack, playerCargo, playerDefense, playerSpeed, shipStatsPackage
    if gameChoice == "":
        print("Time to pick a captain with a spaceship.\n\n\nEach captain owns their own ship with its own specs.\n\n\nShip Specifications:\n\nDefense - How well the ship can withstand enemy attack\n\nAttack - How well the ship can attack other ships.\n\nSpeed - How fast the ship can fly.\n\nCargo - How many resources the ship can hold.\n" + ("-" * 90))
        print("\nCaptains:\n\n1.Captain Morpheus - Ship Defense: 15, Ship Attack: 30, Ship Speed: 10, Ship Cargo: 65\n\n2.Captain Solo - Ship Defense: 15, Ship Attack: 10, Ship Speed: 20, Ship Cargo: 75\n\n3.Captain Kirk - Ship Defense: 25, Ship Attack: 15, Ship Speed: 10, Ship Cargo: 70\n\n4.Captain Star-Lord - Ship Defense: 10, Ship Attack: 15, Ship Speed: 40, Ship Cargo: 55\n" + ("-" * 90))
    gameChoice = input(str("\nWhich captain would you like to use on your mission? (Type 1/2/3/4) ")).replace(" ", "")
    if gameChoice == "1": shipStatsPackage =[15, 30, 10, 65]
    elif gameChoice == "2": shipStatsPackage =[15, 10, 20, 75]
    elif gameChoice == "3": shipStatsPackage =[25, 10, 20, 70]
    elif gameChoice == "4": shipStatsPackage =[10, 15, 40, 55]
    else:
        print("\nPlease type 1, 2, 3, or 4 to choose a captain.\n" + ("-" * 80))
        captainChoice()
    playerDefense += shipStatsPackage[0]
    playerAttack += shipStatsPackage[1]
    playerSpeed += shipStatsPackage[2]
    playerCargo += shipStatsPackage[3]
    print(clear())
    crewSize()

def crewSize():
    ## User Picks Crew
    global alreadyRead, crewChoosing, crewMemberAmount, gameChoice, playerAttack, playerCargo, playerDefense, playerSpeed
    crewMemberAmount = int((playerCargo - 10) / 5)
    if alreadyRead == False: print("Time to pick your crew members for your mission.\n\n\nThere are three types of people that you can recruit.\n\n\nRecruit Types:\n\nMechanic - Increases your ship's defense\n\nTactical Officers - Increases your ships's attack\n\nPilot - Increases your ship's speed")
    if crewChoosing == 1:
        commonPrintMessages("spaceLeft")
        gameChoice = input("\n\nHow many mechanics would you like on your mission? (Type a number) ").replace(" ", "")
        if gameChoice.isdigit():
            if (playerCargo - (int(gameChoice) * 5)) >= 10:
                crewChoosing, alreadyRead, crewMemberAmount = 2, True, int((playerCargo - 10) / 5)
                playerCargo -= (int(gameChoice) * 5)
                playerDefense += (int(gameChoice) * 5)
                if gameChoice == "1": print("\n" + gameChoice + " mechanic has been added to your ship.\nYour ship's defense is now: " + str(playerDefense))
                else: print("\n" + gameChoice + " mechanics have been added to your ship.\nYour ship's defense is now: " + str(playerDefense))
                crewSize()
            else: commonPrintMessages("notEnoughSpace")
        else: commonPrintMessages("NotANumber")
    elif crewChoosing == 2:
        if crewMemberAmount == 0:
            print(("-" * 85) + "\nYou don't have room for any tactical officers.")
            crewChoosing = 3
            crewSize()
        else:
            commonPrintMessages("spaceLeft")
            gameChoice = input("\n\nHow many tactical officers would you like on your mission? (Type a number) ").replace(" ", "")
            if gameChoice.isdigit():
                if (playerCargo - (int(gameChoice) * 5)) >= 10:
                    crewChoosing, crewMemberAmount = 3, int((playerCargo - 10) / 5)
                    playerCargo -= (int(gameChoice) * 5)
                    playerAttack += (int(gameChoice) * 5)
                    if gameChoice == "1": print("\n" + gameChoice + " guard has been added to your ship.\nYour ship's attack is now: " + str(playerAttack))
                    else: print("\n" + gameChoice + " guards have been added to your ship.\nYour ship's attack is now: " + str(playerAttack))
                    crewSize()
                else: commonPrintMessages("notEnoughSpace")
            else: commonPrintMessages("NotANumber")
    elif crewChoosing == 3:
        if crewMemberAmount == 0:
            print(("-" * 85) + "\nYou don't have room for any pilots.")
            crewChoosing = 4
            crewSize()
        else:
            commonPrintMessages("spaceLeft")
            gameChoice = input("\n\nHow many pilots would you like on your mission? (Type a number) ").replace(" ", "")
            if gameChoice.isdigit():
                if (playerCargo - (int(gameChoice) * 5)) >= 10:
                    crewChoosing, crewMemberAmount = 4, int((playerCargo - 10) / 5)
                    playerCargo -= (int(gameChoice) * 5)
                    playerSpeed += (int(gameChoice) * 5)
                    if gameChoice == "1": print("\n" + gameChoice + " pilot has been added to your ship.\nYour ship's speed is now: " + str(playerSpeed))
                    else: print("\n" + gameChoice + " pilots have been added to your ship.\nYour ship's speed is now: " + str(playerSpeed))
                    crewSize()
                else: commonPrintMessages("notEnoughSpace")
            else: commonPrintMessages("NotANumber")
    elif crewChoosing == 4:
        print(("-" * 85) + "\n\nUpdated Ship Stats:")
        commonPrintMessages("showUserStats")
        gameChoice = input(str("\n\nPush Enter to Start your mission..."))
        print(clear())
        startMission()

def startMission():
    ## Pick Mission
    global missionPlanet, randomNumber, storyLocation
    planetNames, storyLocation = ["Mars", "Ego", "Coruscant"], 0
    missionPlanet = (random.choice(planetNames))
    randomNumber = randrange(1,2)
    if randomNumber == 1:
        packageMission()
    else:
        print("GAME ERROR(No Available Mission)")

def checkMissionTime():
    ## Check Mission Time Left
    global storyLocation
    if storyLocation != 0 and missionTimer <= 0:
        storyLocation = -1
        print("You ran out of time and failed your mission.")
        commonPrintMessages("askToRestart")

def packageMission():
    ## Package Pickup Mission
    global  engineFailure, gameChoice, missionTimer, playerAttack, playerCargo, playerDefense, playerSpeed, scoutPlanet, storyLocation
    print(clearStory())
    checkMissionTime()
    if storyLocation == 0:
        print("Your mission: Fly to planet " + str(missionPlanet) + " and retrieve a package. Return to Earth with the package. The package is being guarded by an enemy alien race. You have only 24 hours to complete your mission. Good Luck on your mission.")
        print("Type 'stats' at any time to see your ship's current stats and mission time remaining.")
        missionTimer, storyLocation = 24, 1
    ## One section of the story
    elif storyLocation == 1:
        ## Launch
        print("One of your crew members tells you, 'We are ready for takeoff. Let us know when you are ready.' \n\n1-We are a go for launch \n2-Double-check the equipment(-0.5 hours)")
        gameChoice = input(str("")).replace(" ", "")
        if gameChoice.lower() == "stats": commonPrintMessages("showUserStats")
        elif gameChoice == "1":
            storyLocation = 2
            print("\nYou decide that there is no time to double-check equipment and clear the ship for launch.")
        elif gameChoice == "2":
            storyLocation = 2
            print("\nYour crew spends the next half an hour checking the equipment aboard the ship. You find you're missing a few weapons and replace them before taking off. (+5 Ship Attack)")
            missionTimer -= 0.5
            playerAttack += 5
        else: print("\nPlease type 1 or 2.")
    ## End of section
    elif storyLocation == 2:
        ## Take-off
        print("Your spaceship takes off, and the launch is fairly smooth. You make your way to the ship bridge. The pilots ask you, 'Would you like me to fly directly to the planet or allow you to scout it out from a distance?' \n\n1-Fly straight to planet \n2-Let me scout out the planet out.")
        gameChoice = input(str("")).replace(" ", "")
        if gameChoice.lower() == "stats": commonPrintMessages("showUserStats")
        elif gameChoice == "1":
            storyLocation = 3
            print("\nYou tell the pilot to fly directly to the planet. He says, 'You got it, captain.' He hits a few buttons at his console, and the ship takes off.")
            scoutPlanet = False
        elif gameChoice == "2":
            storyLocation = 3
            print("\nYou tell the pilot to let you scout the planet first. He says, 'You got it, captain.' He hits a few buttons at his console, and the ship takes off.")
            scoutPlanet = True
        else: print("\nPlease type 1 or 2.")
    elif storyLocation == 3:
        ## Engine Failure
        if playerSpeed < 50:
            print("The flight to the planet is going well. Almost too perfect, suddenly red lights begin to flash around the bridge. Someone yells, 'Captain, we have engine problems. We are losing fuel fast.\nWe could attempt to continue flying or stop and make repairs. The repairs could take a few hours.' \n\n1-We better make repairs(-3 hours) \n2-Stay the course")
            gameChoice = input(str("")).replace(" ", "")
            if gameChoice.lower() == "stats": commonPrintMessages("showUserStats")
            elif gameChoice == "1":
                storyLocation = 4
                missionTimer -= 3
                print("\nYou know better than to fly with a damaged ship. You tell the crew to stop and make repairs. The next three hours go by slowly.")
            elif gameChoice == "2":
                storyLocation = 4
                print("\nYou tell the crew to stay the course. Nothing will stop you from achieving your mission. (-10 Ship Speed)")
                engineFailure = True
                playerSpeed -= 10
            else: print("\nPlease type 1 or 2.")
        else:
            print("\nThe flight to the planet is smooth. It was a good thing you hired so many pilots.")
            storyLocation = 4
    elif storyLocation == 4:
        ## Approach Planet
        if engineFailure == False:
            if scoutPlanet == False:
                print("The pilot tells you, 'Captain, we are approaching the planet. The ship exits Hyperspeed and appears in the middle of three battleships.' \n\n1-Shields up \n2-Open fire!")
                gameChoice = input(str("")).replace(" ", "")
                if gameChoice.lower() == "stats": commonPrintMessages("showUserStats")
                elif gameChoice == "1":
                    if playerDefense < 40:
                        print("\nYou tell the crew to put shields up. Gunfire emerges from the other ships and begins hitting you. \nYour defense is too weak, and the opposing ships take a couple of blasts and leave your ship beyond repair. You failed your mission.")
                        commonPrintMessages("askToRestart")
                    else:
                        storyLocation = 5
                        print("\nYou tell the crew to put shields up. Gunfire emerges from the other ships and begins hitting you. Your defense is powerful, and you continue to fly by the other ships to the planet.")
                elif gameChoice == "2":
                    if playerAttack < 40:
                        print("\nYou tell the crew to open fire. Gunfire emerges from your ship and begins hitting the other ships. \nYour attack is too weak. After a few blasts from the other ships, they leave your ship beyond repair. You failed your mission.")
                        commonPrintMessages("askToRestart")
                    else:
                        storyLocation = 5
                        print("\nYou tell the crew to open fire. Gunfire emerges from your ship and begins hitting the other ships. Your attack is powerful, and in no time, you destroy the other ships.")
                else: print("\nPlease type 1 or 2.")
            else:
                print("The pilot tells you, 'Captain, we are approaching the planet. The ship exits Hyperspeed, and you are about 100,000 feet away from the planet. It was a good thing you scouted the planet. You see three vessels ahead blocking the planet.' \n\n1-Shields up \n2-Open fire!")
                missionTimer -= 1
                gameChoice = input(str("")).replace(" ", "")
                if gameChoice.lower() == "stats": commonPrintMessages("showUserStats")
                elif gameChoice == "1":
                    if playerDefense < 40:
                        print("\nYou tell the crew to put shields up. Gunfire emerges from the other ships and begins hitting you. \nYour defense is too weak, and the opposing ships take a couple of blasts and leave your ship beyond repair. You failed your mission.")
                        commonPrintMessages("askToRestart")
                    else:
                        storyLocation = 5
                        print("\nYou tell the crew to put shields up. Gunfire emerges from the other ships and begins hitting you. Your defense is powerful, and you continue to fly by the other ships to the planet.")
                elif gameChoice == "2":
                    if playerAttack < 40:
                        print("\nYou tell the crew to open fire. Gunfire emerges from your ship and begins hitting the other ships. \nYour attack is too weak. After a few blasts from the other ships, they leave your ship beyond repair. You failed your mission.")
                        commonPrintMessages("askToRestart")
                    else:
                        storyLocation = 5
                        print("\nYou tell the crew to open fire. Gunfire emerges from your ship and begins hitting the other ships. Your attack is powerful, and in no time, you destroy the other ships.")
                else: print("\nPlease type 1 or 2.")
        else:
            print("You continue your flight until suddenly, red lights brightly flash again around the cabin. A pilot says, 'Captain, we have lost all fuel and are now stranded.' You failed your mission.")
            commonPrintMessages("askToRestart")
    elif storyLocation == 5:
        ## Finish
        print("You land on the planet and secure the package. You return to your ship and begin to head home. You begin to hear noises from the package. \n\n1-Open the package \n2-Better not touch it")
        gameChoice = input(str("")).replace(" ", "")
        if gameChoice.lower() == "stats": commonPrintMessages("showUserStats")
        elif gameChoice == "1":
            print("\nYou decide to open the package. A weird slimy alien emerges and instantly makes a run for it. The alien is running loose on your ship causing issues. You failed your mission.")
            commonPrintMessages("askToRestart")
        elif gameChoice == "2":
            storyLocation = 6
            print("\nYou know whatever is in the package is well above your pay grade. You leave it alone and fly back to planet Earth.")
        else: print("\nPlease type 1 or 2.")
    elif storyLocation == 6:
        ## Story Done
        print("\nYou land on planet Earth. You have successfully completed your mission. The commanders approach you and say, \n'We are surprised to see you again. We heard about the blockade and believed you wouldn't return home. You did it and got the package. Nice job!'")
        commonPrintMessages("askToRestart")
    else:
        print("GAME ERROR(Broken Mission Hole - packageMission)")
        exit()
    if storyLocation != 0: packageMission()
 

## Start System
try: gameSetup()
except Exception as Argument: crashMessage()
