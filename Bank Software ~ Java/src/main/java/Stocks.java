import java.awt.*; // DONE
import java.awt.event.*;
import javax.swing.*;  

class Stocks extends stockMarket {
  private static int appleOwned = 0;
  private static int microsoftOwned = 0;
  private static int googleOwned = 0;
  private static double accountBalance;
  
  public Stocks(double theAccountBalance){
    super();
    accountBalance = theAccountBalance;
  }
  
  // Stocks GUI
  final JFrame stockFrame = new JFrame("Transaction menu");
  public Dimension size = Toolkit.getDefaultToolkit().getScreenSize();
  public static final stockMarket priceGrabber = new stockMarket();
  public static JLabel appleLabel = new JLabel("APPLE VALUE");    
  public static JButton appleBuy = new JButton("Buy");    
  public static JButton appleSell = new JButton("Sell");    
  public static JLabel microsoftLabel = new JLabel("Microsoft VALUE");    
  public static JButton microsoftBuy = new JButton("Buy");    
  public static JButton microsoftSell = new JButton("Sell");    
  public static JLabel googleLabel = new JLabel("GOOGLE VALUE");    
  public static JButton googleBuy = new JButton("Buy");    
  public static JButton googleSell = new JButton("Sell");
  public static JLabel balanceLabel = new JLabel("BANK VALUE");   
  public static JButton home = new JButton("Home");

  // Update all the Stock Prices and the Bank Account Balance
  public static void updateStockPrices(){
    appleLabel.setText("Apple: $" + priceGrabber.getStockPrice("Apple") + ", Owned: " + appleOwned);
    microsoftLabel.setText("Microsoft: $" + priceGrabber.getStockPrice("Microsoft") + ", Owned: " + microsoftOwned);
    googleLabel.setText("Google: $" + priceGrabber.getStockPrice("Google") + ", Owned: " + googleOwned);
    balanceLabel.setText("Bank account: $" + ((Math.round(accountBalance * 100))/100)); // Round to the nearest dollar
  }
  
  public void createGUI(){  
    stockFrame.setSize((int)size.getWidth(),(int)size.getHeight());
    // Update GUI text to show price / amount
    Stocks.updateStockPrices();
    // Add GUI Elements
    stockFrame.add(appleLabel); stockFrame.add(appleBuy); stockFrame.add(appleSell);  
    stockFrame.add(microsoftLabel); stockFrame.add(microsoftBuy); stockFrame.add(microsoftSell);  
    stockFrame.add(googleLabel); stockFrame.add(googleBuy); stockFrame.add(googleSell);
    stockFrame.add(balanceLabel); stockFrame.add(home);
    // Finish GUI
    stockFrame.setLayout(new GridLayout(4, 3, 20, 25));    
    stockFrame.setVisible(true);
    // Listens in for calls from the buttons
    // Home Button
    Stocks.home.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Dashboard dashboardRunner = new Dashboard();
        dashboardRunner.createGUI();
      }
    });
    // Apple Buy Stocks
    Stocks.appleBuy.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (accountBalance >= priceGrabber.getStockPrice("Apple")){ // Check if user has enough money to buy stock at current price
          accountBalance -= priceGrabber.getStockPrice("Apple"); // Subtract price from user's account
          appleOwned += 1; // Add number of owned Apple stocks 
          priceGrabber.changeRandomPrice(); // Change the Stock Market Prices
          Stocks.updateStockPrices(); // Update GUI
        } else {
          JOptionPane.showMessageDialog(stockFrame, "Not enough funds to buy."); // Not enough money error message
        }
      }
    });
    // Apple Sell Stocks
    Stocks.appleSell.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (appleOwned > 0){ // Check if user has enough stocks to sell stock
          accountBalance += priceGrabber.getStockPrice("Apple"); // Add price to user's account
          appleOwned -= 1; // Subtract number of owned Apple stocks 
          priceGrabber.changeRandomPrice(); // Change the Stock Market Prices
          Stocks.updateStockPrices(); // Update GUI
        } else {
          JOptionPane.showMessageDialog(stockFrame, "Not enough stocks to sell."); // Not enough stocks error message
        }
      }
    });
    // Microsoft Buy Stocks
    Stocks.microsoftBuy.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (accountBalance >= priceGrabber.getStockPrice("Microsoft")){ // Check if user has enough money to buy stock at current price
          accountBalance -= priceGrabber.getStockPrice("Microsoft"); // Subtract price from user's account
          microsoftOwned += 1; // Add number of owned Apple stocks
          priceGrabber.changeRandomPrice(); // Change the Stock Market Prices
          Stocks.updateStockPrices(); // Update GUI
        } else {
          JOptionPane.showMessageDialog(stockFrame, "Not enough funds to buy."); // Not enough money error message
        }
      }
    });
    // Microsoft Sell Stocks
    Stocks.microsoftSell.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (microsoftOwned > 0){ // Check if user has enough stocks to sell stock
          accountBalance += priceGrabber.getStockPrice("Microsoft"); // Add price to user's account
          microsoftOwned -= 1; // Subtract number of owned Microsoft stocks 
          priceGrabber.changeRandomPrice(); // Change the Stock Market Prices
          Stocks.updateStockPrices(); // Update GUI
        } else {
          JOptionPane.showMessageDialog(stockFrame, "Not enough stocks to sell."); // Not enough stocks error message
        }
      }
    });
    // Google Buy Stocks
    Stocks.googleBuy.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (accountBalance >= priceGrabber.getStockPrice("Google")){ // Check if user has enough money to buy stock at current price
          accountBalance -= priceGrabber.getStockPrice("Google"); // Subtract price from user's account
          googleOwned += 1; // Add number of owned Google stocks 
          priceGrabber.changeRandomPrice(); // Change the Stock Market Prices
          Stocks.updateStockPrices(); // Update GUI
        } else {
          JOptionPane.showMessageDialog(stockFrame, "Not enough funds to buy."); // Not enough money error message
        }
      }
    });
    // Google Sell Stocks
    Stocks.googleSell.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (googleOwned > 0){ // Check if user has enough stocks to sell stock
          accountBalance += priceGrabber.getStockPrice("Google");  // Add price to user's account
          googleOwned -= 1; // Subtract number of owned Google stocks 
          priceGrabber.changeRandomPrice(); // Change the Stock Market Prices
          Stocks.updateStockPrices(); // Update GUI
        } else {
          JOptionPane.showMessageDialog(stockFrame, "Not enough stocks to sell."); // Not enough stocks error message
        }
      }
    });
  }  
}