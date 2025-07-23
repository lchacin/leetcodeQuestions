/*
1717. Maximum Score From Removing Substrings



You are given a string s and two integers x and y. 
You can perform two types of operations any number of times.

Remove substring "ab" and gain x points.
For example, when removing "ab" from "cabxbae" it becomes "cxbae".
Remove substring "ba" and gain y points.
For example, when removing "ba" from "cabxbae" it becomes "cabxe".
Return the maximum points you can gain after applying the above operations on s.


Constraints:

1 <= s.length <= 105
1 <= x, y <= 104
s consists of lowercase English letters.


*/


#include<iostream>
#include<stack>


int maximumGain(std::string& s, int x, int y) {
        //stack1 will be used
        std::stack<char> stack1, stack2;
        int maxScore=0;
        int high, low; //to store the high and low score between x and y
        char first, second; //the first and second letters in the high score case

        //we now determine whether the high score comes from the 'ab' or 'ba' and dow the same 
        //for the low score
        if(x>y){
            high = x;
            low = y;
            first = 'a';
            second = 'b';
        }
        else{
            high = y;
            low = x;
            first = 'b';
            second = 'a';
        }

        //we first traverse the string pushing letters to stack1 in search of high score cases
        for(auto& letter: s){
            //case the letter in the string is the second letter of the high score
            if(letter == second){
                //case the top of the stack has the first letter of the high score
                if(!stack1.empty() && stack1.top() == first){
                    //we found a high score case so we add it to our max score and remove the
                    //top of the stack
                    maxScore += high;
                    stack1.pop();
                }

                //the top of the stack did not hava the first letter of the high score so we push
                //the letter into the stack
                else stack1.push(letter);
            }

            //case letter in the string was not the second letter of the high score
            //we just push it
            else stack1.push(letter);
        }

        //out of the for loop, we now have totalled all the high score cases in the string

        //now we iterate in reverse order over the remainder of the string left after
        //removing the high score cases. We do so with the help of a second stack.

        //we perform the removals of the low score cases until the first stack is empty
        while(!stack1.empty()){
            //tne low score case has first the second letter and then the first letter
            //we compare the top of the first stack to see if it is the second letter
            if(stack1.top() == second){
                //now we check if the second stack has the first letter in the top, because the
                //second letter of the low score case is the first letter
                if(!stack2.empty() && stack2.top() == first){
                    //we found the low case, we update the max score
                    //and remove the top letters of both first and second stacks
                    maxScore += low;
                    stack2.pop();
                    stack1.pop();
                }

                //the top of the second stack was not the first letter
                //so we just push the second letter to the second stack
                else{
                    stack2.push(stack1.top());
                    stack1.pop();
                }

            }

            //the letter in the top of stack 1 was not the second letter
            //so we push it to the second stack and remove it from the first stack.
            else{
                stack2.push(stack1.top());
                stack1.pop();
            }
        }

        return maxScore;
    }


int main(){
	std::string s = "cdbcbbaaabab";
	int x = 4, y = 5;

	std::cout << s << "\n";
	std::cout << "Maximum score from removing substrings : " << maximumGain(s, x, y) << "\n";

	return 0;

}
