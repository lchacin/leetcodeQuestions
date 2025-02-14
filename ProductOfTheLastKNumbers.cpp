/*

1352. Product of the Last K Numbers


Design an algorithm that accepts a stream of integers and retrieves the product of the last k integers of the stream.

Implement the ProductOfNumbers class:

ProductOfNumbers() : Initializes the object with an empty stream.
void add(int num) : Appends the integer num to the stream.
int getProduct(int k) : Returns the product of the last k numbers in the current list. 

You can assume that always the current list has at least k numbers.
The test cases are generated so that, at any time, the product of any contiguous sequence 
of numbers will fit into a single 32-bit integer without overflowing.


Constraints:

0 <= num <= 100
1 <= k <= 4 * 104
At most 4 * 104 calls will be made to add and getProduct.
The product of the stream at any point in time will fit in a 32-bit integer.

*/


#include<iostream>
#include<vector>


class ProductOfNumbers {
public:
    //keeps a prefix product of all of the previous values added excluding the zeros
    std::vector<int> prefixProduct;

    //last zero stores the index where the last zero was added
    int lastZero;

    //constructor sets lastZero to 0 and the prefixProduct vector to a vector with the number 1
    ProductOfNumbers(): lastZero(0), prefixProduct({1}) {}
    
    //extends the prefix product with a new value
    void add(int num) {
        //the case where the new value is zero
        if(num==0){
            //we record the index where the zero took place
            lastZero = prefixProduct.size();

            //and we add a 1 to the prefix product so we can calculate the product all the following
            //non zero values
            prefixProduct.push_back(1);
        }
        //case the new value is not zero
        //we calculate and add the new prefix product value
        else
            prefixProduct.push_back(prefixProduct.back()*num);
    }
    
    //returns the product of the last k values added
    int getProduct(int k) {
        //if k is less than or equal to the index of the last zero added
        //this means the product of the last k values will be zero
        if(prefixProduct.size()-k <= lastZero) return 0;

        //otherwise we divide out the values whose indexes are beyond the previous last k values
        return prefixProduct.back() / prefixProduct[prefixProduct.size()-k-1]; 
    }
};



int main(){
	/*

	["ProductOfNumbers", "add", "add", "add", "add", "getProduct", "add", "add", "add", "add", "add", "getProduct", 
		"add", "getProduct", "add", "getProduct", "getProduct", "add", "add", "add", "add"]

	[[], [2], [2], [5], [10], [2], [0], [5], [0], [2], [3], [3], [10], [4], [7], [2], [1], [8], [2], [6], [5]]


	*/

	ProductOfNumbers* obj = new ProductOfNumbers();
	obj->add(2);
	obj->add(2);
	obj->add(5);
	obj->add(10);
	std::cout << obj->getProduct(2) << "\n";
	obj->add(0);
	obj->add(5);
	obj->add(0);
	obj->add(2);
	obj->add(3);
	std::cout << obj->getProduct(3) << "\n";
	obj->add(10);
	std::cout << obj->getProduct(4) << "\n";
	obj->add(7);
	std::cout << obj->getProduct(2) << "\n";
	std::cout << obj->getProduct(1) << "\n";
	obj->add(8);
	obj->add(2);
	obj->add(6);


	return 0;


}
