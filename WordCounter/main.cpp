#include "WordCounter.h"

int main(){
	//load
	WordCounter wc;
	wc.loadText("./bible.txt");
	//search
	std::vector<std::string> searchList;
	std::vector<unsigned int> resultList;
	searchList.push_back("lord");
	searchList.push_back("god");
	resultList = wc.countWords(searchList);
	//print
	for (unsigned int i = 0; i < resultList.size(); i++) {
		std::cout << searchList[i] << " -> " << resultList[i] << std::endl;
	}
	std::cin.ignore();
	return 0;
}