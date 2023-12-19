#include "WordCounter.h"

/* Takes in a string, replaces all characters except a-z with space and converty capital letters to lower case
*Input is not changed, new string is the return value
*/
std::string stripEnglishAndLowerCase(const std::string& input) {
	std::string result = input;

	for (unsigned int i = 0; i < result.size(); i++) {
		//check for A-Z
		if (result[i] >= 'A' && result[i] <= 'Z') {
			result[i] = result[i] + 32; //converts to lower case
			continue;
		}
		//check for a-z
		if (result[i] >= 'a' && result[i] <= 'z') {
			//no action needed
			continue;
		}
		//remove all other characters
		result[i] = ' ';
	}
	return result;
}

/* Loads a txt file from disk and stores both an unchanged and a converted version
* Takes path to the file to load
* Returns true if file could be loaded otherwise returns false
*/
bool WordCounter::loadText(const std::string& path) {
	std::ifstream file(path); //taking file as inputstream
	if(file) {
		std::ostringstream ss;
		ss << file.rdbuf(); // reading data
		this->textOriginal= ss.str();
	}
	else {
		return false;
	}
	if (this->convert != NULL) {
		this->textStripped = convert(this->textOriginal);
	}
	return true;
}
/* Function to get a word count for a list of search strings
* Takes a vector of strings to search for, vector is expected to not contain duplicates
* Returns a vector of integers, giving the count for the string at the same index in the search list
* Search is conducted on the converted text
*/
std::vector<unsigned int> WordCounter::countWords(const std::vector<std::string>& searchlist) {
	std::vector<unsigned int> resultList;
	resultList.resize(searchlist.size(), 0U);
	// Initialise the istringstream
	std::istringstream stringstream(this->textStripped);

	// Iterate the stripped text from space to space
	do {
		std::string word;
		stringstream >> word;
		//compare word with searchlist
		for (unsigned int i = 0; i < searchlist.size(); i++) {
			if (searchlist[i] == word) {
				resultList[i]++;
				break; //assuming the search list is sane and does not include duplicated entries
			}
		}
	} while (stringstream);

	return resultList;
}

/* Changes the function pointer used to strip the text
* If you want to change the strip behaviour hand over a pointer to a function that returns a string and takes a const string reference
*/
void WordCounter::setConvertFunction(std::string(*func) (const std::string&)) {
	if (func != NULL) {
		this->convert = func;
	}
}

/* Initializes the function pointer used to convert the text
*If you want to change the convert behaviour hand over a pointer to a function that returns a string and takes a const string reference
*/
WordCounter::WordCounter(std::string(*func) (const std::string&)) {
	if (func != NULL) {
		this->convert = func;
	}
	else {
		this->convert = stripEnglishAndLowerCase;
	}
}

// Generic Constructor that takes nothing and sets the function pointer to the default function
WordCounter::WordCounter() {
	this->convert = stripEnglishAndLowerCase;
}