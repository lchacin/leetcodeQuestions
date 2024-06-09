/*

118. Pascal's Triangle

Given an integer numRows, return the first numRows of Pascal's triangle.
In Pascal's triangle, each number is the sum of the two numbers directly 
above it as shown:

Constraints:
1 <= numRows <= 30

Approach:

We obtain the triangle starting from the very top and construct the row below at
a time using the last row built. We crate a new vector to store the new row,
where for each element in the new row we reference the two corresponding values
in the last row built and add them to obtain the value in the row.


*/

#include<iostream>
#include<vector>


std::vector<std::vector<int>> generate(int& numRows) {
	//create a vector of integer vectors to store the pascal triangle
        std::vector<std::vector<int>> pTriangle; 
        pTriangle.push_back({{1}}); //we add the peak of the triangle
        int rowNum, rowIndex; //indexes for the row and value in the row of the triangle

	//for each iteration of this for loop we create a new row in the triangle
	//we use a 0-indexed row number
        for(rowNum=1; rowNum<numRows; ++rowNum){
            std::vector<int> newRow(rowNum+1,1); //create the new row filles with 1s

            //this for loops calculates the values in the new row from the second to 
            //penultimate values
            for(rowIndex=1; rowIndex<rowNum; ++rowIndex)
            	//the new value is the sum of the "top" two values in the last row
            	//created
                newRow[rowIndex] = pTriangle.back()[rowIndex-1]+pTriangle.back()[rowIndex];

	    //the new row is now done being created. We add it to the pascal triangle
	    //using push_back and we make usre to use std::move so it gets casted
	    //to an rvalue and it calls the overloaded push_back method that performs
	    //a move operation and not a copy.
            pTriangle.push_back(std::move(newRow));
        }

        return pTriangle;
    }


int main(){
	int numRows=6;
	auto pascalTriangle = generate(numRows);

	for(auto& row: pascalTriangle){
		for(auto& val: row) std::cout<<val<<" ";
		std::cout<<"\n";
	}

	return 0;
}
