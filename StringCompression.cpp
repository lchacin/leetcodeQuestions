/*


443. String Compression

Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:

If the group's length is 1, append the character to s.
Otherwise, append the character followed by the group's length.
The compressed string s should not be returned separately, but instead, be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.

You must write an algorithm that uses only constant extra space.


Constraints:
1 <= chars.length <= 2000
chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.


Approach:

We make use of the std::vector's erase method. This method is convenient because it removes 
elements from the vector without changing the underlying amount of memory allocated for the 
vector. It makes changes to its interface to simulate as if the vector has changed size, by
shifting down remaining elements below to the place where the removed elements where started.
The vector's size will be the size of the old vector minus the number of elements removed, and
the vector's past-the-end iterator will be the position after the last element of the elements 
above that were shifted down. 


We'll have two indexes traversing the vector of characters. The first index will keep track of a new
character encountered and the second index will iterate forward until it reaches a different character.
s the second index iterates we keep count the number of repeated characters and once the second index reaches
a non repeated character we record the numerical value past the first index and any additional characters
until the second index are removed using std::vector::erase.





*/

#include<iostream>
#include<vector>


//compress receives a reference to a vector of characters, compresses the characters in-situ, 
//and returns the length of the compressed version
int compress(std::vector<char>& chars){
	//the case where chars has only one character
        if(chars.size()==1) return 1;

	//i and j are two indexes to iterate over chars, counter keeps track of the number of repeated characters
	//of a given type
        short i=0, j=1, counter=1;
        std::string counterString; //counterString will store the string representation of counter

	//the while loop iterates until index i reaches the end of the chars vector
	//chars's size will change within the while loop due to the use of std::vector::erase
        while(i<chars.size()){
        	//index j keeps moving forward until it reaches a character not equal to the one as index i
            for(j=i+1; (j<chars.size() && chars[i]==chars[j]); ++j)
                    ++counter; //we update the number of repeations of the character at index i
                    
            if(counter==1) i=j; //the case where the character was not repeated

		//case where the character is repeated
            else{
                    ++i; //we move the following spot so we can record the numerical value of counter
                    counterString = std::to_string(counter); //we convert counter to sring
                    counter=1; //reset counter back to 1
                    for(auto& number: counterString){ //iterate over counterString and record its digits in chars
                            chars[i]=number;
                            ++i;
                    }
                    //erase the additional character left up to j that is waiting at the position of the new character
                    chars.erase(chars.begin()+i, chars.begin()+j);
            }
        }

        //out of the while loop, chars has been compressed, and due to the erae method, chars' size has been
        //updated to reflect its new compressed version 
    return chars.size();

}




int main(){
	std::vector<char> chars{'a','a','b','b','c','c','c'};
	std::cout<<"chars compressed. new size: "<<compress(chars)<<"\n";
	for(auto& c: chars) std::cout<<c<<" ";
	std::cout<<"\n";
	return 0;
}
