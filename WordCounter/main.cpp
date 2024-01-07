#include "WordCounter.h"

int main(){
	//load
	WordCounter wc(true, true);
	wc.loadText("./bible.txt");
	//search
	std::vector<std::string> searchList;
	std::vector<unsigned int> resultList;
	searchList.push_back("Lord");
	searchList.push_back("God");
	resultList = wc.countWords(searchList);
	//print
	for (unsigned int i = 0; i < resultList.size(); i++) {
		std::cout << searchList[i] << " -> " << resultList[i] << std::endl;
	}
	std::cin.ignore();
	return 0;
}