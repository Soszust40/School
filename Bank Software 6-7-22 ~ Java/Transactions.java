import java.awt.*; //DONE
import java.awt.event.*;
import javax.swing.*;

class Transactions
{
  private static double normalBalance;
  private static double accountBalance;

  public Transactions(double theNormalBalance, double theAccountBalance)
  {
     normalBalance = theNormalBalance;
     accountBalance = theAccountBalance;
  }
  
  // Adds money to the users accountBalance while subtracting from the normalBalance
  public double Deposit(double amount)
  {
    if (amount <= normalBalance && amount > 0)
    {
      accountBalance += amount;
      normalBalance -= amount;
    } else if (amount > normalBalance) { // Checks if user has enough pocket money to deposit
      JOptionPane.showMessageDialog(TransactionFrame, "You do not have enough in your pocket to deposit.");
    } else if (amount < 0) { // Checks if user entered a number above -1
      JOptionPane.showMessageDialog(TransactionFrame, "The deposit amount must be postive!");
    } else {
      JOptionPane.showMessageDialog(TransactionFrame, "An unknown error has occured.");
    }
    return accountBalance;
  }

 // Adds money to the users normalBalance while subtracting from the accountBalance
 public void Withdraw(double amount)
  {
    if (amount <= accountBalance && amount > 0) // Checks if user has enough money to withdraw
    {
      accountBalance -= amount;
      normalBalance += amount;
    } else if (amount < 0) { // Checks if user entered a number above -1
      JOptionPane.showMessageDialog(TransactionFrame, "The withdraw amount must be postive!");
    } else {
      JOptionPane.showMessageDialog(TransactionFrame, "You do not have enough in your bank account to withdraw.");
    }
  }

  // Transactions GUI
  final JFrame TransactionFrame = new JFrame("Transaction menu");
  public Dimension size = Toolkit.getDefaultToolkit().getScreenSize();
  public static JTextField depositAmountEntered = new JTextField(5);
  public static JTextField withdrawAmountEntered = new JTextField(5);
  public static JButton deposit = new JButton("Deposit");
  public static JButton withdraw = new JButton("Withdraw");
  public static JButton homeButton = new JButton("Home");
  public static JLabel text = new JLabel("Deposit Amount: ");
  public static JLabel textWith = new JLabel("Withdraw Amount: ");
  public JLabel balances = new JLabel("Bank account: $" + accountBalance + "      Pocket balance: $" + normalBalance);
  
  public void createDepGUI(){
    TransactionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    TransactionFrame.setSize((int)size.getWidth(),(int)size.getHeight());
    JPanel panel = new JPanel();
    // Update GUI text to show price / amount
    balances.setText("Bank account: $" + accountBalance + "      Pocket balance: $" + normalBalance);
    // Appends buttons and text labels to the GUI
    panel.add(text);
    panel.add(depositAmountEntered);
    panel.add(deposit);
    panel.add(balances);
    panel.add(textWith);
    panel.add(withdrawAmountEntered);
    panel.add(withdraw);
    panel.add(homeButton);
    // Finish GUI
    deposit.setActionCommand("Deposit");
    TransactionFrame.getContentPane().add(BorderLayout.CENTER, panel);
    TransactionFrame.getContentPane().add(BorderLayout.SOUTH, balances);
    TransactionFrame.setVisible(true);
    deposit.setLayout(new GridLayout(3, 3, 20, 25));
    // Listens in for calls from the buttons
    // Home Button
    Transactions.homeButton.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Dashboard dashboardRunner = new Dashboard();
        dashboardRunner.createGUI();
      }
    });
    
    // Deposit Money
    Transactions.deposit.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        try{ // Tests if value is number
          Deposit(Double.parseDouble(depositAmountEntered.getText()));  
          balances.setText("Bank account: $" + accountBalance + "      Pocket balance: $" + normalBalance); // Update GUI text to amount
          depositAmountEntered.setText("");
        }
        catch(Exception error) {
          JOptionPane.showMessageDialog(TransactionFrame, "The value entered is not a number.");
        }
      }
    });

    // Withdraw Money
    Transactions.withdraw.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        try{ // Tests if value is number
          Withdraw(Double.parseDouble(withdrawAmountEntered.getText()));  
          balances.setText("Bank account: $" + accountBalance + "      Pocket balance: $" + normalBalance); // Update GUI text to amount
          withdrawAmountEntered.setText("");
        }
        catch(Exception error) {
          JOptionPane.showMessageDialog(TransactionFrame, "The value entered is not a number.");
        }
      }
    });
  }
}