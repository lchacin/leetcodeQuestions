/*

649. Dota2 Senate

In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a change in the Dota2 game. 
The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:

Ban one senator's right: A senator can make another senator lose all his rights in this and all the following rounds.
Announce the victory: If this senator found the senators who still have rights to vote are all from the same party, 
he can announce the victory and decide on the change in the game.

Given a string senate representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party. 
Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order. 
This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party. 
Predict which party will finally announce the victory and change the Dota2 game. The output should be "Radiant" or "Dire".


Constraints:

n == senate.length
1 <= n <= 104
senate[i] is either 'R' or 'D'.



Approach:

If you explore different examples you'll reach the conclusion that the choice of which opposing 
senator should a given senator ban does make a difference on whether his or her party will succeed or not.

In particular if you look at the example: "DRDDRDRRR", if the first Dire senator bans the first Radiant senator and all other
senators ban the first opposing senator they come accross, then Dire party wins.
But if he decides to ban the second Radiant senator instead, the Radiant party wins.

This an important observation, because it indeed confirms the fact that there is a best strategy when it comes to deciding
which opposing senator to ban.

The best strategy is for each senator to ban the first opposing senator encountered, and the reasoning behind
this greedy approach is that it prevents opposing party senators from ban your party's senators first: a first-mover advantage.


The solution makes use of a queue to store the senate. We keep a tally of the number of Radiant or Dire senators that need to get
removed (banned) from the senate, by increasing the corresponding counts based on whether the senator at the front of the queue
is from Radiant or Dire. When senator from a given party is at the front of the queue and the count of senators from the corresponding party
is zero, then we don't ban, and instead we pop it and move it to the back of the queue and increase the count of senators of the opposing
party that need to get removed 

*/



#include<iostream>
#include<queue>


std::string predictPartyVictory(std::string& senate){
	std::queue<char> q; //create the queue that stores the senators in char form
	//we add the senators to the queue
	for(auto& c: senate)
		q.push(c);

	//totalR and totalD will keep track of the total number of Radiant and Dire senators that need to get removed
	int totalR=0, totalD=0;

	//we use a do-while loop because we want to traverse the queue of senators at least once
	do{
		//case where the senator at the front is a Dire senator
		if(q.front()=='D'){
			//the case where the senator get banned
			if(totalD!=0){
				//we remove him from the queue and update totalD 
				q.pop();
				--totalD;
			}
			//the case where the senator is not banned
			else{
				//increase the number of Radiant senators to ban, remove the Dire senator from the front
				//and add him to the back of the queue
				++totalR;
				q.push(q.front());
				q.pop();
			}
		}

		//we repeat the same process for the case of a Radiant senator
		else if(q.front()=='R'){
			if(totalR!=0){
				q.pop();
				--totalR;
			}
			else{
				++totalD;
				q.push(q.front());
				q.pop();
			}
		}

		

	}while(totalR<q.size() && totalD<q.size()); //we exit the while loop when number of Radiant or Dire senators to be removed
							//exceeds the size of the queue. This happens when the queue is left with
							//only senators of one pary, signalling that process is over

	//we return the party name corresponding which type of senators are left in the queue
	if(q.front()=='D') return "Dire";
	else return "Radiant";

}




int main(){
	std::string senate(
	"RDRDRDDRDRDRDRDRRDRDRDRDRDRDDDDRRDRDRDRDRDRDRDRRRRRDRDRDRDRDDDDDRDRDRDRDRDRDRDRRDRDRDRDRDRDRRDRDRDRDRDRDRDRDRRDRDRDRDRDRRD");

	std::cout<<predictPartyVictory(senate)<<"\n";

	return 0;
}
