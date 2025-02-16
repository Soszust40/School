import java.awt.*; // DONE
import java.awt.event.*;
import javax.swing.*;

class Loan {
  private double amountDue;
  private int daysTillDue;
  private static double accountBalance;

  public Loan(Double theAccountBalance)
  {
    amountDue = 0;
    daysTillDue = 0;
    accountBalance = theAccountBalance;
  }
  
  public Loan(double amountDue)
  {
    this.amountDue = amountDue;
    daysTillDue = 10;
  }

  public void setAmountDue(double amountDue)
  {
    this.amountDue = amountDue;
  }
  
  public double getAmountDue()
  {
    return amountDue;
  }
  
  public void setDueDate(int daysTillDue)
  {
    this.daysTillDue = daysTillDue;
  }
  
  public int getDueDate()
  {
    return daysTillDue;
  }
  
  public String toString()
  {
    return "You are currently loaning $" + amountDue + ", you have " + daysTillDue + " to return the money";
  }

  // Loan GUI
  public final JFrame loanFrame = new JFrame("Loan Menu");
  public Dimension size = Toolkit.getDefaultToolkit().getScreenSize();
  public static JTextField loanAmountEntered = new JTextField(5);
  public static JButton loaner = new JButton("loaner");
  public static JLabel topText = new JLabel("Loaning Page", SwingConstants.CENTER);
  public static JLabel text = new JLabel("Loan Amount: ");
  public static JLabel balances = new JLabel("Bank account: $" + accountBalance);
  public static JButton homeButton = new JButton("Home");

  public void createGUI(){
    loanFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    loanFrame.setSize((int)size.getWidth(),(int)size.getHeight());
    JPanel panel = new JPanel();
    // Reset the Bank Account Balance label
    balances.setText("Bank account: $" + accountBalance);
    // Add GUI Elements
    panel.add(topText, text);
    panel.add(text);
    panel.add(loanAmountEntered);
    panel.add(loaner);
    panel.add(balances);
    panel.add(homeButton);
    // Finish GUI
    loaner.setActionCommand("Loan");
    loanFrame.getContentPane().add(BorderLayout.CENTER, panel);
    loanFrame.getContentPane().add(BorderLayout.NORTH, topText);
    loanFrame.getContentPane().add(BorderLayout.SOUTH, balances);
    loanFrame.setVisible(true);
    // Listens in for calls from the buttons
    Loan.loaner.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        try{
          if (Double.parseDouble(loanAmountEntered.getText()) > 0){
            accountBalance += Double.parseDouble(loanAmountEntered.getText());
            balances.setText("Bank account: $" + accountBalance);
            loanAmountEntered.setText("");
          }
          else{
            JOptionPane.showMessageDialog(loanFrame, "The loan amount must be postive!");
          }
        }
        catch(Exception error) {
          JOptionPane.showMessageDialog(loanFrame, "The value entered is not a number.");
        }
      }
    });
    // Home Button
    Loan.homeButton.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Dashboard dashboardRunner = new Dashboard();
        dashboardRunner.createGUI();
        loanFrame.dispose();
      }
    });
  }
}