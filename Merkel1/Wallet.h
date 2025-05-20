#pragma once
#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
public:
	Wallet();
	/**Insert currency to wallet*/
	void insertCurrency(std::string type, double amount);
	/**remove currency to wallet*/
	bool removeCurrency(std::string type, double amount);

	/**Check if wallet contains this currency or more*/
	bool containsCurrency(std::string type, double amount);
	/**check if the wallet can cope with this ask or bid*/
	bool canFulfillOrder(OrderBookEntry order);
	/**updates the content of the wallet , assume the order was made by the owner of the wallet*/
	void processSale(OrderBookEntry& sale);

	/**generate a string representation of the wallet*/
	std::string toString();



private:
	std::map<std::string,double> currencies;


};

