import java.awt.*; // DONE
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

class Dashboard
{
  // Get Account Money
  readAccounts readAccountsRunner = new readAccounts();
  Double accountBalance = Double.parseDouble(readAccountsRunner.readDatabase("getAccountBalance"));
  
  // Dashboard GUI
  public final JPanel panel = new JPanel();
  public Dimension size = Toolkit.getDefaultToolkit().getScreenSize();
  public static JLabel topText = new JLabel("Dashboard", SwingConstants.CENTER);
  public static JButton transactions = new JButton("Transactions");
  public static JButton loans = new JButton("Loans");
  public static JButton stocks = new JButton("Stock Market");
  
  public void createGUI()
  {
    final JFrame dashboardFrame = new JFrame("Dashboard");
    dashboardFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    dashboardFrame.setSize((int)size.getWidth(),(int)size.getHeight());
    // Add GUI Elements
    panel.add(topText);
    panel.add(transactions);
    panel.add(loans);
    panel.add(loans);
    panel.add(stocks);
    // Finish GUI
    dashboardFrame.getContentPane().add(BorderLayout.CENTER, panel);
    dashboardFrame.getContentPane().add(BorderLayout.NORTH, topText);
    dashboardFrame.setVisible(true);
    // Transactions Button Click
    Dashboard.transactions.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Random rand = new Random();
        int randPocketMoney = rand.nextInt(1000);
        Transactions transactionsRunner = new Transactions(randPocketMoney, accountBalance);
        transactionsRunner.createDepGUI();
      }
    });
    
    // Loans Button Click
    Dashboard.loans.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Loan loansRunner = new Loan(accountBalance);
        loansRunner.createGUI();
      }
    });
    
    // Stock Market Button Click
    Dashboard.stocks.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Stocks stocksRunner = new Stocks(accountBalance);
        stocksRunner.createGUI();
      }
    });
  }
}