import java.util.*;

class WordCreator {
  public String randomWord;

  //Picks a random word from the WordList.java file.
  //Output: Returns the random word as a String.
  public String getWord() {
    WordList getWordList = new WordList();
    String[] wordList = getWordList.everyWord();
    Random randomNum = new Random();
    randomWord = wordList[randomNum.nextInt(wordList.length)];
    return randomWord;
  }

  //Breaks the Wordle Word into 5 separate array indexes.
  //Output: Returns the string array with 5 letters.
  public String[] getWordLetters(){
    String[] wordLetters = new String[5];
    for (int x = 0; x < randomWord.length(); x++){wordLetters[x] = randomWord.substring(x, x+1);}
    return wordLetters;
  }
}
