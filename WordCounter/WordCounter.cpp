#include "WordCounter.h"

/* Takes in a string, replaces all characters except a-z with space and converty capital letters to lower case
*Input is not changed, new string is the return value
*/
std::string stripEnglishAndLowerCase(const std::string& input, const bool setLowerCase) {
	std::string result = input;

	for (unsigned int i = 0; i < result.size(); i++) {
		//check for A-Z
		if (result[i] >= 'A' && result[i] <= 'Z') {
			if (setLowerCase) {
				result[i] = std::tolower(result[i]);
			}
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

// helper to convert string to lowerCase without changing input
std::string str_toLower(std::string input) {
	for (auto& character : input) {
		character = std::tolower(character);
	}
	return input;
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
		// if caseSensitive is off the stripped text will be converted to lower case
		this->textStripped = convert(this->textOriginal, !this->caseSensitive);
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
			std::string target = this->caseSensitive ? searchlist[i] : str_toLower(searchlist[i]);
			bool match = this->allowPartialMatch ? (word.find(target) != std::string::npos) : word == target;
			if (match) {
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
void WordCounter::setConvertFunction(std::string(*func) (const std::string&, const bool)) {
	if (func != NULL) {
		this->convert = func;
	}
}

/* setter for mode CaseSensitive
*  re-converts stripped text if needed
*/
void WordCounter::setCaseSensitive(const bool mode) {
	if (mode != this->caseSensitive) {
		this->caseSensitive = mode;
		if (this->convert != NULL) {
			// if caseSensitive is off the stripped text will be converted to lower case
			this->textStripped = convert(this->textOriginal, !this->caseSensitive);
		}
	}
}

//setter for mode AllowPartialMatch
void WordCounter::setAllowPartialMatch(const bool mode) {
	if (mode != this->allowPartialMatch) {
		this->allowPartialMatch = mode;
	}
}

/* Initializes the function pointer used to convert the text
* If you want to change the convert behaviour hand over a pointer to a function that returns a string and takes a const string reference
* Also sets modes for CaseSensitive and AllowPartialMatch
*/
WordCounter::WordCounter(std::string(*func) (const std::string&, const bool), const bool initCaseSensitive, const bool initAllowPartialMatch) {
	this->caseSensitive = initCaseSensitive;
	this->allowPartialMatch = initAllowPartialMatch;
	if (func != NULL) {
		this->convert = func;
	}
	else {
		this->convert = stripEnglishAndLowerCase;
	}
}

// Constructor that takes modes for caseSensitive and AllowPartialMatch but sets the function pointer to the default function
WordCounter::WordCounter(const bool initCaseSensitive, const bool initAllowPartialMatch) : WordCounter(stripEnglishAndLowerCase, initCaseSensitive, initAllowPartialMatch) {}

// Generic Constructor that takes nothing and sets everything to default
WordCounter::WordCounter() : WordCounter(stripEnglishAndLowerCase, false, false) {}