/*

901. Online Stock Span


Design an algorithm that collects daily price quotes for some stock and returns the span of that stock's price for the current day.

The span of the stock's price in one day is the maximum number of consecutive days (starting from that day and going backward) 
for which the stock price was less than or equal to the price of that day.

For example, if the prices of the stock in the last four days is [7,2,1,2] and the price of the stock today is 2, then the span of today is 
4 because starting from today, the price of the stock was less than or equal 2 for 4 consecutive days.

Also, if the prices of the stock in the last four days is [7,34,1,2] and the price of the stock today is 8, 
then the span of today is 3 because starting from today, the price of the stock was less than or equal 8 for 3 consecutive days.


Implement the StockSpanner class:

StockSpanner() Initializes the object of the class.
int next(int price) Returns the span of the stock's price given that today's price is price.


*/



#include<vector>
#include<stack>
#include<iostream>



//StockSpanner is a class that generates objects capable of outputting the number of consecutive prior days (inclusive)  where the stock price was 
//less than or equal the current price.
//It has a default constructor and a mutator method called next 
class StockSpanner{
	private:
		std::vector<int> span; //vector to store the span of each price
		std::stack<std::pair<int,int>> decreasingStack; //stack to store monotonically decreasing stock prices
		int index; //index of the latest price passed to next
		int consecutiveDays; //variable to store a cummulative sum of span values from prior prices left in decreasingStack

	public:
		//default constructor sets the index to 0 and consecutive days to 1
		//span and decreasingStack are default constructed implicitly
		StockSpanner(): index(0), consecutiveDays(1) {}

		//next is a mutator method
		//it accepts a integer parameter representing a stock price
		//it calculates the span of the stock price passed as argument
		int next(int price){
			//the case when the stack is empty
			//we add the price to the stack and record a span of 1
			if(decreasingStack.empty()){
				decreasingStack.push({price, index++});
				span.push_back(consecutiveDays);
			}
			else{
				//this while loop performs a cummulative sum of span values of top prices in the decreasingStack
				//while the top of the stack has a lower price than the price passed as argument				
				while(!decreasingStack.empty() && decreasingStack.top().first <=  price){
					consecutiveDays += span[decreasingStack.top().second];
					decreasingStack.pop(); //once we add the span of the price at the top of the stack we pop the price
				}
				//out of the while loop our decreasing stack remains monotonically decreasing since all the top prices
				//less than the price passed as argument have been poppped
				decreasingStack.push({price,index++}); //we add the new price to the stack with its corresponding index
				span.push_back(consecutiveDays); //after accumulating the span values we have the span value of the new price
								//and we record its span
				consecutiveDays=1; //we reset consecutive days back to 1
			}
			return span.back(); //we return the span of the price passed by argument located at the back of the span vector
		}
};


int main(){
	StockSpanner mySpanner;
	std::cout<<mySpanner.next(100)<<" ";
	std::cout<<mySpanner.next(80)<<" ";
	std::cout<<mySpanner.next(60)<<" ";
	std::cout<<mySpanner.next(70)<<" ";
	std::cout<<mySpanner.next(60)<<" ";
	std::cout<<mySpanner.next(75)<<" ";
	std::cout<<mySpanner.next(85)<<"\n";


	return 0;
}
