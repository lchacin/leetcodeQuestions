/*

119. Pascal's Triangle II

Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

Constraints:
0 <= rowIndex <= 33


Approach:

SImilar to Pascal Triangle I problem. We calculate each row one at a time startinf rom the top
of the traingle. This time we calculate up to the desired row index given by the function argument.

We use the previously calculated row to create the new row. They in this process is to cast each new row
created into an rvalue so we add new rows to the pascal triangle using move constructor and not by copy.

*/

#include<iostream>
#include<vector>


std::vector<int> getRow(int& rowIndex) {
        //create a vector of integer vectors to store the pascal triangle
        std::vector<std::vector<int>> pTriangle; 
        pTriangle.push_back({{1}}); //we add the peak of the triangle
        int rowNum, rowVal; //indexes for the row and value in the row of the triangle

        //for each iteration of this for loop we create a new row in the triangle
        //we use a 0-indexed row number
        
        ++rowIndex;
        for(rowNum=1; rowNum<rowIndex; ++rowNum){
            std::vector<int> newRow(rowNum+1,1); //create the new row filles with 1s
            //this for loops calculates the values in the new row from the second to 
            //penultimate values
            for(rowVal=1; rowVal<rowNum; ++rowVal)
                //the new value is the sum of the "top" two values in the last row
                //created
                newRow[rowVal] = pTriangle.back()[rowVal-1]+pTriangle.back()[rowVal];

            //the new row is now done being created. We add it to the pascal triangle
            //using push_back and we make usre to use std::move so it gets casted
            //to an rvalue and it calls the overloaded push_back method that performs
            //a move operation and not a copy.
            pTriangle.push_back(std::move(newRow));
        }

        return pTriangle.back(); //return the last row of the pascal triangle
    }


int main(){
	int rowNum = 5;
	auto rowChosen = getRow(rowNum);

	std::cout<<"row number "<<rowNum<<": ";
	for(auto& val: rowChosen) std::cout<<val<<" ";
	std::cout<<"\n";

	return 0;

}
