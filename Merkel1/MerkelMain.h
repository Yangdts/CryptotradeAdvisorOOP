#pragma once
#include<vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

//Advisorbot
class MerkelMain 
{
public:
	MerkelMain();
    /**Call this to start the sim*/
    void init();
private:
    //All functions of advisorbot
    void advisorBot();
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void listProd();
    void listPrice();
    void listMinBid();
    void listMinAsk();
    void listMaxBid();
    void listMaxAsk();
    void listAvg();
    void displayTime();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    std::string currentTime;
    OrderBook orderBook{ "20200601.csv" };
    Wallet wallet;
};

