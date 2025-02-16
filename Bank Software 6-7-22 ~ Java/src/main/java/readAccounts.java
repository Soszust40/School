import java.io.FileNotFoundException; //DONE
import java.io.FileReader;
import java.util.ArrayList;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class readAccounts {
  private static String returnValue; // String to allow all types of return values from JSON
  private static int timesRan;
  private static int jsonLength;
  
  public static String readDatabase(String action){
    // Open and Read JSON
    JSONParser jsonParser = new JSONParser();
    try (FileReader reader = new FileReader("Accounts.json")){
      Object obj = jsonParser.parse(reader);
      JSONArray accountList = (JSONArray) obj;
      // Search JSON for action given
      timesRan = 0;
      jsonLength = accountList.size();
      // Used code from here for the "forEach" in JSON file: https://stackoverflow.com/questions/33215539/foreach-with-jsonarray-and-jsonobject
      if (action.equals("testAccountLogin")){accountList.forEach( person -> testAccountLogin((JSONObject) person ));}
      if (action.equals("getAccountBalance")){accountList.forEach( person -> getAccountBalance((JSONObject) person ));}
      return returnValue;
    // Catch errors while reading JSON
    } catch (FileNotFoundException e) {System.out.println("The bank's database could not be located!");}
    catch (Exception e) {System.out.println("An error has been encounted with the database.");}
    return "FALSE";
  }
 
  private static void testAccountLogin(JSONObject account){
    // Get each bank account
    JSONObject memberObject = (JSONObject) account.get("Member");
    Login loginInfo = new Login();
    if ((memberObject.get("accountUsername")).equals(loginInfo.getUsername())){ // Check if username matches given one from Login
      if ((memberObject.get("accountPin")).equals(loginInfo.getPassword())){ // Check if password matches given one from Login
        returnValue = "accountConfirm";
        timesRan = jsonLength;
      }
    }
    timesRan++;
    if (timesRan < jsonLength) {returnValue = "Invalid";} // Returns false if whole JSON is searched without match  
  }

  public static void getAccountBalance(JSONObject account){
    JSONObject memberObject = (JSONObject) account.get("Member");
    Login loginInfo = new Login();
    if ((memberObject.get("accountUsername")).equals(loginInfo.getUsername())){ // Check if username matches given one from Login
      if ((memberObject.get("accountPin")).equals(loginInfo.getPassword())){ // Check if password matches given one from Login
        String accountBalance = (String) memberObject.get("accountBalance");
        returnValue = accountBalance;
      }
    }
  }
} 