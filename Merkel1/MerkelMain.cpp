#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

//AdvisorBot
MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int input;
    //Current time from orderbook
    currentTime = orderBook.getEarliestTime();
    //Starting currency for user
    wallet.insertCurrency("BTC", 10);
    while (true)
    {
        printMenu();
        advisorBot();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    //Menu for user to choose function
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Make an ask" << std::endl;
    std::cout << "4: Make a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: List products for current timestamp" << std::endl;
    std::cout << "7: List min bid of product" << std::endl;
    std::cout << "8: List min ask of product" << std::endl;
    std::cout << "9: List max bid of product" << std::endl;
    std::cout << "10: List max ask of product" << std::endl;
    std::cout << "11: List average of product" << std::endl;
    std::cout << "12: Predict" << std::endl;
    std::cout << "13: Display current time." << std::endl;
    std::cout << "14: Continue to next timestamp" << std::endl;
    std::cout << "15: Help Menu" << std::endl;
    std::cout << "16: Help Commands" << std::endl;

    std::cout << "===========================" << std::endl;
}

void MerkelMain::advisorBot()
{
    //Message to user
    std::cout << "Advisorbot > Please enter a command according to the menu." << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help-your aim is to make money. analyse the market" << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const p: orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                p,
                                                                currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price,amount ,eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad Input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else{
                std::cout << "Wallet has insufficient funds " << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "MerkelMain::enterAsk Bad input! " << std::endl;
        }
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price,amount ,eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad Input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else{
                std::cout << "Wallet has insufficient funds " << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "MerkelMain::enterBid Bad input! " << std::endl;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::listProd()
{
    //getKnownProducts function provides all avaliable orders.
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p , currentTime);
    }
}

void MerkelMain::listPrice()
{

}

void MerkelMain::listMinBid()
{
    std::string x;
    std::cout << "Enter product: eg ETH/BTC" << std::endl;
    //Get input of product
    std::cin >> x;
    std::cout << "You are looking for " << x<<std::endl;
    //Get lowest entry(min value) by looping and getLowPrice function
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid,
            p,
            currentTime);
        if (p == x) {
            //std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
            std::cout << "The min bid for " + x + "is " << OrderBook::getLowPrice(entries) << std::endl;
        }
    }
}

void MerkelMain::listMinAsk()
{
    std::string x;
    std::cout << "Enter product: eg ETH/BTC" << std::endl;
    //Get input of product
    std::cin >> x;
    std::cout << "You are looking for " << x << std::endl;
    //Get lowest entry(min value) by looping and getLowPrice function
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p,
            currentTime);
        if (p == x) {
            //std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
            std::cout << "The min ask for " + x + "is " << OrderBook::getLowPrice(entries) << std::endl;
        }
    }
}

void MerkelMain::listMaxBid()
{
    std::string x;
    std::cout << "Enter product: eg ETH/BTC" << std::endl;
    //Get input of product
    std::cin >> x;
    std::cout << "You are looking for " << x<<std::endl;
    //Get highest entry(max value) by looping and getHighPrice function
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid,
            p,
            currentTime);
        if (p == x) {
            //std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
            std::cout << "The Max bid for " + x + "is " << OrderBook::getHighPrice(entries) << std::endl;
        }
    }
}

void MerkelMain::listMaxAsk()
{
    std::string x;
    std::cout << "Enter product: eg ETH/BTC" << std::endl;
    //Get input of product
    std::cin >> x;
    std::cout << "You are looking for " << x << std::endl;
    //Get highest entry(max value) by looping and getHighPrice function
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p,
            currentTime);
        if (p == x) {
            //std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
            std::cout << "The Max ask for " + x + "is " << OrderBook::getHighPrice(entries) << std::endl;
        }
    }
}

void MerkelMain::listAvg()
{
    // 3 variables to accept user input
    std::string x;
    int y;
    int z=0;
    std::cout << "Enter currency: eg ETH/BTC" << std::endl;
    std::cin >> x;
    std::cout << "Enter timestep eg 5" << std::endl;
    std::cin >> y;
    for (std::string const p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p,
            currentTime);
        z = z + OrderBook::getLowPrice(entries);
        //std::cout << entries.size() << std::endl;
        std::cout << OrderBook::getLowPrice(entries) << std::endl;
    }
    std::cout << "The average "<< x << " ask price over the last" << y << " timesteps was " << (z / y) << std::endl;
    //std::cout << z << std::endl;
}

void MerkelMain::displayTime()
{
    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame." << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    //update sales if any.
    for (OrderBookEntry& sale : sales)
    {
        std::cout << "Sale price: " << sale.price << " Amount" << sale.amount << std::endl;
        if (sale.username == "simuser")
        {
            //update the wallet
            wallet.processSale(sale);
        }
    }
    //update current time
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption =0;
    std::string line;

    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e)
    {
        //
    }

    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0)
    {
        std::cout << "Invalid choice. Choose again." << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        listProd();
    }
    if (userOption == 7)
    {
        listMinBid();
    }
    if (userOption == 8)
    {
        listMinAsk();
    }
    if (userOption == 9)
    {
        listMaxBid();
    }
    if (userOption == 10)
    {
        listMaxAsk();
    }
    if (userOption == 11)
    {
        listAvg();
    }
    if (userOption == 12)
    {
        std::cout << "Predict command unavailable" << std::endl;
    }
    if (userOption == 13)
    {
        displayTime();
    }
    if (userOption == 14)
    {
        gotoNextTimeframe();
    }
    if (userOption == 15)
    {
        std::cout << "The available commands are 1 to 15 according to the menu " << std::endl;
    }
    if (userOption == 16)
    {
        std::cout << "Min - > Enter Currency type eg. ETH/BTC" << std::endl;
        std::cout << "Max - > Enter Currency type eg. ETH/BTC" << std::endl;
        std::cout << "Avg - > Enter Currency type eg. ETH/BTC Followed by Timestep in number eg 5" << std::endl;
    }
}