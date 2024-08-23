#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

//maximumPopulation receives a 2D-vector parameter by reference
    // each element in logs is a vector of size two containing the birth and death years of specific person
    //it returns the earliest year with the largest population 
    int maximumPopulation(std::vector<std::vector<int>>& logs) {
        //we create integer vectors of size 101 to account for the years of 1950 to 2050 inclusive
        //to store the number of births, deaths and living population of each of the years
        std::vector<int> births(101,0), deaths(101,0), livingPop(101,0);
        const int LOWESTYEAR=1950; //lowest year possible is 1950

        //we iterate over the elements in logs and record the number of births and deaths in 
        //each year. TO account for the index we decrease the years by 1950
        for(auto& lifeYears: logs){
            ++births[lifeYears[0]-LOWESTYEAR];
            ++deaths[lifeYears[1]-LOWESTYEAR];
        }

        //we now use partial_sum to compute the prefix sum of the births and death vectors
        std::partial_sum(births.begin(), births.end(), births.begin());
        std::partial_sum(deaths.begin(), deaths.end(), deaths.begin());

        //we use transform to subtract each corresponding index component of the birth and death vectors
        //and store the results in the livinPop vector
        std::transform(births.begin(), births.end(), deaths.begin(), livingPop.begin(), [](auto& living, auto& dead)->int{ return living-dead;});

        //now we search for the earliest year with the largest population
        int maxYear=1950, maxPop=0;
        for(int i=0; i<101; ++i){
            if(livingPop[i] > maxPop) { //if the living population in year 1950+i is larger than the maximum
                                        //population so far obtained, we update maxPop and record the year
                maxYear = LOWESTYEAR + i; 
                maxPop = livingPop[i];
            }
        }
        
        return maxYear;
    }



int main(){
	std::vector<std::vector<int>> logs{{1950,1961},{1960,1971},{1970,1981}};
	
	std::cout << "Year with the maximum population: " << maximumPopulation(logs) << "\n";

	return 0;

}
