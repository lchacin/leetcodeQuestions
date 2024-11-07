#include<iostream>
#include<bitset>
#include<vector>

bool canSortArray(std::vector<int>& nums) {

        
        int previousMax = *nums.begin();
        int previousBits = std::bitset<9>(*nums.begin()).count();
        auto iter = ++nums.begin();

        //we iterate until we find the first number whose bit count differs from the
        //the first number
        while(iter != nums.end() && std::bitset<9>(*iter).count() == previousBits){
            //as we iterate over the value we record the max number of the sublist of 
            //numbers with equal bit count
            if(*iter > previousMax) previousMax = *iter;
            ++iter;
        }
        
        //the case we reached the end and all values had the same bitcount. This mean
        //we would be able to sort by pure swapping (bubble sort).
        if(iter == nums.end()) return true;

        //if we reached here it means encountered a value that had a different bit count
        //as the bitcount of the first value

        //we record the bit count of the following sublist of values with equal bit count
        int currentBits = std::bitset<9>(*iter).count();
        int currentMax = *iter; //we also record the max number is this sublist

        //if the first value of following sublist is smaller than the max of the previous sublist
        //we return false because swap won't allow us to place this new value
        //in a lower index location than the max value in the previous sublist.
        if(currentMax < previousMax) return false;
        
        
        ++iter;

        //we iterate over the current sublist of values with equal bit count
        while(iter != nums.end()){
            //if we reach a value that has a different bit count than the values
            //in the current sublist then it means a new sublist with a new bitcount
            //will start
            if(std::bitset<9>(*iter).count() != currentBits){
                //we let the previousBits be the currentBits
                previousBits=currentBits;
                //and the currentBits will be the number of bits of the new value
                //we encountered with a different number of bits
                currentBits = std::bitset<9>(*iter).count();

                //we also update the max values of the previous and current sublists.
                //the previousMax is the currentMax and the currentMax becomes the current value
                previousMax=currentMax;
                currentMax = *iter;

                //as before if the currentMax is smaller than the preivousMax we won;t be able
                //to sort this list because the swap function won't allow us to move this value
                //below the previousMax
                if(currentMax < previousMax) return false;


                ++iter;
            }

            //the case the next value has the same bit count as the current sublist
            else if(std::bitset<9>(*iter).count() == currentBits){
                //we check if the current value is a larger value than the currentMax
                //if so we update it
                if(*iter > currentMax) currentMax= *iter;

                //the case the current value has the same number of set bits as the
                //current contiguous list of numbers with same number of bits
                //but the number of less than the max of the previous list of numbers
                //considered that had a different number of bits.
                //This means that if we try to sort this list using swap we would
                //need to move this value below a number with a different number of bits
                //But the swap function will not allow for this, unabling the list from being sorted
                if(*iter < previousMax) return false; 


                ++iter;
            }
        }

        //we reached the end of the list of numbers return true.
        return true;
}


int main(){
	std::vector<int> nums{9,9,3,15,15,18,5};

	std::cout << "Can the nums = ";
	for(int& x: nums)
		std::cout << x << ", ";
	std::cout << " be sorted? ";
	
	if(canSortArray(nums)) std::cout << "Yes\n";
	else	std::cout << "No\n";

	return 0;


}
