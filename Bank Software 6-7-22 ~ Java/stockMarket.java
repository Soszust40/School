import java.util.ArrayList; //DONE
import java.util.Random;

class stockMarket{
  // Stock Market ArrayList
  private static ArrayList<String> stockMarketCompanies = new ArrayList<String>();
  private static ArrayList<Double> stockMarketPrice = new ArrayList<Double>();

  // Variables for changing Stock price
  Random rand = new Random();
  int randomCompany;
  double randomPricePercent;
  int changePosOrNeg;
  double currentPrice;
  double newPrice;

  // Setup the whole Stock Market
  public stockMarket(){
    stockMarket.setCompanyList();
    stockMarket.setPriceList();
  }

  // Sets the companies available in Stock Market
  public static void setCompanyList(){
    stockMarketCompanies.add("Apple");
    stockMarketCompanies.add("Microsoft");
    stockMarketCompanies.add("Google");
    stockMarketCompanies.add("Amazon");
    stockMarketCompanies.add("Tesla");
    stockMarketCompanies.add("Meta");
    stockMarketCompanies.add("NVIDIA");
    stockMarketCompanies.add("Java Bank");
    stockMarketCompanies.add("Shell");
    stockMarketCompanies.add("Walt Disney");
  }

  // Sets default Stock prices for companies in the Stock Market
  public static void setPriceList(){
    stockMarketPrice.add(147.47);
    stockMarketPrice.add(261.68);
    stockMarketPrice.add(2350.0);
    stockMarketPrice.add(2233.0);
    stockMarketPrice.add(781.24);
    stockMarketPrice.add(198.81);
    stockMarketPrice.add(178.19);
    stockMarketPrice.add(5.0);
    stockMarketPrice.add(56.81);
    stockMarketPrice.add(107.23);
  }

  // Creates a random change to one of the stock prices
  public void changeRandomPrice(){
    randomCompany = rand.nextInt(13); // Finds random Company to change
    randomPricePercent = Math.random()*(1-0.9)+0.9; // Finds amount to change price
    changePosOrNeg = rand.nextInt(2); // Should price go up or down
    currentPrice = stockMarketPrice.get(randomCompany); // Gets the current company price
    if (changePosOrNeg == 1){newPrice = currentPrice * randomPricePercent;} // Makes the price go down
    else{newPrice = currentPrice / randomPricePercent;} // Makes the price go up
    newPrice = Math.round(newPrice * 100); // Round to 2 decimal places
    stockMarketPrice.set(randomCompany, newPrice/100); // Sets new price in Stock Market
  }

  // Get and return the double value of price of Stock based on name of Company
  public double getStockPrice(String stock)
  {
    double price = 0;
    for (String company: stockMarketCompanies){
      if (stock.equalsIgnoreCase(company)){
        price = stockMarketPrice.get(stockMarketCompanies.indexOf(company));
      }
    }
    return price;
  }
}