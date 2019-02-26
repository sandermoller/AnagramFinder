#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

int main(int argc, char** argv) {
	int startTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();

	string result;
	string path = argv[1];
	string initialWord = argv[2];
	transform(initialWord.begin(), initialWord.end(), initialWord.begin(), ::tolower);

	ifstream dictionary(path);
	if (dictionary.is_open()) {
		string line;
		unsigned int count = 0;
		while (getline(dictionary, line)) {

			transform(line.begin(), line.end(), line.begin(), ::tolower);
			line.erase(std::find_if(line.rbegin(), line.rend(), [](int ch) {
        			return !std::isspace(ch);
    			}).base(), line.end());

			if (initialWord.length() == line.length() && 		 //Ugly if statement, but does the trick
				 ((line.length() < 7) ? true : (line.find(initialWord[0]) != std::string::npos) ? true : false)) { 
				string word = line;
				for (unsigned int i = 0; i < initialWord.length(); i++){
					if (word.find(initialWord[i]) != std::string::npos){
						count++;
						word.erase(word.find(initialWord[i]), 1);
					}
				}
				if (count == initialWord.length()){
					result += ", " + line;
				}
				count = 0;
			}
		}
	} else
		cout << "Unable to open or find dictionary file!";

	int endTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count() - startTime;
	cout << endTime << result << "\n";
	return 0;
}

