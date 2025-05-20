#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"

int main()
{
    MerkelMain app{};
    app.init();

}














    //std::vector<OrderBookEntry> orders;

    //orders.push_back(  OrderBookEntry{ 5319.450228,
    //                        0.00020075,
    //                        "2020 / 03 / 17 17:01 : 24.884492,",
    //                        "btc/usdt",
    //                        OrderBookType::bid}  );

    //orders.push_back(OrderBookEntry{ 4000.450228,
    //                        0.00020075,
    //                        "2020 / 03 / 17 17:01 : 24.884492,",
    //                        "btc/usdt",
    //                        OrderBookType::bid });

    //for (OrderBookEntry& order : orders)
    //{
    //    std::cout << "The price is " << order.price << std::endl;
    //}
