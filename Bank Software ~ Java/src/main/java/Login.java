import java.awt.*; // DONE
import java.awt.event.*;
import javax.swing.*;

class Login{
  private static String accountUsername;
  private static String accountPassword;

  public Login(){} //Allows other Classes to access the login
  public Login(String theUsername, String thePassword){
    accountUsername = theUsername;
    accountPassword = thePassword;
    // Launch the login GUI
    Login loginRunner = new Login();
    loginRunner.createGUI();
  }
  
  public String getUsername(){
    return accountUsername; // Get username
  }
  public String getPassword(){
    return accountPassword; // Get password
  }

  public String testLogin(){ // Test for matching account in database
    readAccounts runAccountReader = new readAccounts();
    return readAccounts.readDatabase("testAccountLogin");
  }

  // Login GUI
  public final JFrame loginFrame = new JFrame("Bank Login");
  public Dimension size = Toolkit.getDefaultToolkit().getScreenSize();
  public static JLabel usernameLabel = new JLabel("Username: ");
  public static JTextField usernameInput = new JTextField(8);
  public static JLabel passwordLabel = new JLabel("Pin: ");
  public static JLabel text = new JLabel("Deposit Amount: ");
  public static JPasswordField passwordInput = new JPasswordField(8);
  public static JButton confirm = new JButton("Login");
  
  public void createGUI()
  {
    loginFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    loginFrame.setSize((int)size.getWidth(),(int)size.getHeight());
    JPanel panel = new JPanel();
    // Add GUI Elements
    panel.add(usernameLabel);
    panel.add(usernameInput);
    panel.add(passwordLabel);
    panel.add(passwordInput);
    panel.add(confirm);
    // Finish GUI
    loginFrame.getContentPane().add(BorderLayout.CENTER, panel);
    loginFrame.setVisible(true);
    // Listens in for calls from the buttons
    Login.confirm.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        try{
          accountUsername = usernameInput.getText();
          accountPassword = passwordInput.getText();
          // Test for valid login
          Login loginRunner = new Login();
          Dashboard dashboardRunner = new Dashboard();
          if ((loginRunner.testLogin()).equals("accountConfirm")){
            // Good Login
            loginFrame.dispose();
            dashboardRunner.createGUI();
          }
          else{ // Invalid Login Pop-up
            passwordInput.setText("");
            JOptionPane.showMessageDialog(loginFrame, "Login Invalid");
          }
        }
        catch(Exception error) {
          passwordInput.setText("");
          JOptionPane.showMessageDialog(loginFrame, "Login Invalid");
        }
      }
    });
  }
}