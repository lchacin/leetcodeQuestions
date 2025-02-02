/*

1833. Maximum Ice Cream Bars

It is a sweltering summer day, and a boy wants to buy some ice cream bars.

At the store, there are n ice cream bars. You are given an array costs of length n, 
where costs[i] is the price of the ith ice cream bar in coins. 
The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 

Note: The boy can buy the ice cream bars in any order.

Return the maximum number of ice cream bars the boy can buy with coins coins.

You must solve the problem by counting sort.


Constraints:

costs.length == n
1 <= n <= 105
1 <= costs[i] <= 105
1 <= coins <= 108



*/


#include<iostream>
#include<vector>
#include<algorithm>	//for std::max_element


int maxIceCream(std::vector<int>& costs, int& coins) {
        //we first find the largest cost
        const int SIZE = 1 + *std::max_element(costs.begin(), costs.end());

        //we create a vector where each index value is a price and the
        //the element stored at the index is the number of ice creams
        //with that price 
        std::vector<int> costCount(SIZE, 0);
        for(auto& cost: costs)
            ++costCount[cost];
        

        int purchaseSize;
        int count=0;

        //now we iterate over the ice cream count and count
        //how many we can buy for each of the prices
        for(int i=1; i<SIZE; ++i){
            if(costCount[i]!=0){
                //we calculate how many ice creams with price i we can buy
                //with the available coins and take the minimum between those
                //available and the maximum we can buy with the amount of money
                purchaseSize = std::min(coins / i, costCount[i]);

                //we couldn't buy any of them it means we no longer have enough
                //money to buy more ice creams, so we return false.
                if(purchaseSize == 0) return count;

                //otherwise we update the total number of ice creams purchased
                count += purchaseSize;

                //update the amount of money available
                coins -= purchaseSize*i;
            }
        }

        return count;
    }


int main(){
	std::vector<int> costs{1,3,2,4,1};
	int coins = 7;

	std::cout << maxIceCream(costs, coins) << "\n";

	return 0;

}
