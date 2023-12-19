#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

/*Defines a class to load a text file (plain ASCII) and count strings within that text
* Usage: create instance of this class
* either define your own convert function or use the default which removes special characters and converts the text to all lower case
* call loadText() with the path to the file to load
* call countWords() with a vector of strings that represents the words to search for
* countWords() returns a vector of unsigned integers, each entry representing how often the word at the same index in the search list appears in the text
*/
class WordCounter {
public:
	bool loadText(const std::string& path);
	std::vector<unsigned int> countWords(const std::vector<std::string>& searchlist);
	void setConvertFunction(std::string(*func) (const std::string&));
	//Constructors
	WordCounter();
	WordCounter(std::string(*func) (const std::string&));
private:
	std::string textOriginal;
	std::string textStripped;
	//function pointer to convert function
	std::string(*convert) (const std::string&);
};