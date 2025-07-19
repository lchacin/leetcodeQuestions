#include<iostream>
#include<algorithm>
#include<vector>


    std::vector<std::string> removeSubfolders(std::vector<std::string>& folder) {
        //sort the string lexicographically
        std::sort(folder.begin(), folder.end());

        int pointer1=0, pointer2;
        std::vector<std::string> returnVec;
        
        while(pointer1 < folder.size()){
            returnVec.push_back(folder[pointer1]);
            pointer2 = pointer1+1;
            while(pointer2 < folder.size()){
                //case the folder at pointer2 is not a sub-folder of that at pointer1
                //because the length of the file address of pointer2 is smaller or equal
                if(folder[pointer2].size() <= folder[pointer1].size()){
                    pointer1 = pointer2; //set pointer1 to pointer2 because the folder at pointer2
                                            //is not a sub-folder and should be added to returnVec
                    break;
                }
                

                //the case string at pointer2 is a subfolder of string at pointer1 becasue the file
                //address of pointer2 starts with that of pointer1 plus a slash
                if(equal(folder[pointer1].begin(), folder[pointer1].end(), folder[pointer2].begin()) && folder[pointer2][folder[pointer1].size()] == '/')
                    ++pointer2;

                //the case the folder at pointer2 is not a subfolder of that at pointer1 because they 
                //first characters of folder at pointer2 doesn't match that at pointer1
                else{
                    pointer1 = pointer2;
                    break;
                }

            }

            //case we broke from while loop because the end of folder vector was reached
            if(pointer2 == folder.size()) break;
        }

        return returnVec;
    }


int main(){
	std::vector<std::string> folder{"/a","/a/b","/c/d","/c/d/e","/c/f"};

	for(auto& f: folder)
		std::cout << f << " ";
	std::cout << "\n";

	auto parentFolders =  removeSubfolders(folder);

	for(auto& f: parentFolders)
		std::cout << f << " ";
	std::cout << "\n";

	return 0;

}
