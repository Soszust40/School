import java.util.*;

class Main {
  private String userGuess;
  private String letterGuess;
  private boolean notInRightSpot;
  private int lettersCorrectSpots;
  private String[] wordLetters;
  private String[] letterShow;
  private ArrayList<String> wrongSpotLetters = new ArrayList<String>();
  private String correctWord;
  private static String gameVersion = "v1.1.0";

  // Main Method that prints startup text and will startup game
  public static void main(String[] args) {
    System.out.println("Welcome to to my Wordle! " + gameVersion + "\nCreated and published by Oszust Industries");
    System.out.println("\nYou have 6 guesses to solve a five letter word.\n-----------------------------------------------\n");
    Main runGame = new Main();
    runGame.setupGame();
    // The game will keep running until the user says n to replaying again.
    while ((runGame.playGame().toLowerCase()).equals("y")){
      runGame.setupGame();
      System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNew Wordle Game:\n\nYou have 6 guesses to solve a five letter word.\n-----------------------------------------------\n");
    }
    System.out.println("Thanks for playing!");
  }

  //Sets variables that are required for the game.
  //Output: Variables of all types that are used.
  public void setupGame(){
    userGuess = "";
    letterGuess = "";
    lettersCorrectSpots = 0;
    notInRightSpot = false;
    wordLetters = new String[5];
    wrongSpotLetters.clear();
    // Sets an array that has the letters that are shown to user
    letterShow = new String[5];
    for (int setupLetterShow = 0; setupLetterShow < 5; setupLetterShow++){
      letterShow[setupLetterShow] = "_";
    }
    WordCreator runCreator = new WordCreator();
    correctWord = runCreator.getWord();
    wordLetters = runCreator.getWordLetters();
  }

  public String playGame(){
    Scanner input = new Scanner(System.in);
    // Runs the game for the 6 attempts that the user has to play
    for (int x = 1; x <= 6;){
      System.out.print("Attempt " + x + "/6: ");
      // Prints out the blank spots for the five letter word
      for (int i = 0; i < letterShow.length; i++){
        System.out.print(letterShow[i] + " ");
      }
      // Prints out the letters that the user had in wrong spots
      // Will only print the wrong letter lists if letters in it
      if (wrongSpotLetters.size() > 0){System.out.print("\nLetters in wrong spots: [");}
      for (int z = 0; z < wrongSpotLetters.size(); z++){
          if (z < wrongSpotLetters.size() - 1){System.out.print(wrongSpotLetters.get(z) + ", ");}
          else{System.out.print(wrongSpotLetters.get(z));}
      }
      if (wrongSpotLetters.size() > 0){System.out.print("]\nType a word: ");}
      else{System.out.print("\nType a word: ");}
      userGuess = input.nextLine();
      // Checks to see if the user guess is 5 letters
      if (userGuess.length() == 5){
        lettersCorrectSpots = 0;
        System.out.print("\n");
        // Checks each letter of the user's guess for right spot
        for (int y = 0; y < 5; y++){
          letterGuess = userGuess.substring(y, y+1);
          letterGuess = letterGuess.toLowerCase();
          notInRightSpot = false;
          // Checks if the user's letter is put in wrong spot, but in the word
          for (String check : wordLetters){
            if (check.equals(letterGuess)){notInRightSpot = true;}
          }
          // Checks if the user has the correct letter in the right spot
          if (letterGuess.equals(wordLetters[y])){
            System.out.println(letterGuess + " - Correct Spot"); //Tells user the letter was in correct spot
            letterShow[y] = letterGuess.toUpperCase(); // Puts the user's guess into the blank spot for that word
            lettersCorrectSpots += 1;
            wrongSpotLetters.remove(letterGuess.toUpperCase()); // Removes the letter from wrong spot list
          }
          else if (notInRightSpot){
            // Tells user the letter was in wrong spot
            System.out.println(letterGuess + " - Wrong Spot");
            // Add letter to wrong spot list
            if (!wrongSpotLetters.contains(letterGuess.toUpperCase())){wrongSpotLetters.add(letterGuess.toUpperCase());}
          }
          else {System.out.println(letterGuess + " - Not in Word");} // Tells user the letter was not in the word
        }
        // The user has the letters all in the correct spots and guessed the word in time.
        if (lettersCorrectSpots == 5){
          System.out.print("\n\nYou guessed the word correctly! Nice Job!\nWould you like to play again? (y/n) ");
          userGuess = input.nextLine();
          return userGuess;
        }
        x++; // Causes the user to lose a turn
      }
      // If the user's guess is too short or too long, it will tell user and won't lose a turn.
      else if (userGuess.length() < 5){System.out.println("Your guess is too short. It must be 5 letters.");}
      else if (userGuess.length() > 5){System.out.println("Your guess is too long. It must be 5 letters.");}
      System.out.print("\n\n");
    }
    // User ran out of guesses and failed to solve the word in time
    System.out.print("You ran out of guess attempts. The word was: " + correctWord + ".\nWould you like to play again? (y/n) ");
    userGuess = input.nextLine();
    return userGuess;
  }
}
