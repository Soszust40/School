#include <iostream>
#include <cmath>
using namespace std;

using std::cout; using std::endl;
#include <string>
using std::string;
#include <algorithm>
using std::sort;


std::int64_t LocToDec(std::string const& loc) {
	int sum = 0;
	for (char c: loc) {
		sum += pow(2, (int(c) - 97));
	}
	return sum;
}

std::string Abbreviate(std::string const& loc) {
	string sortedString = loc;
	for (int counter = 0; counter < static_cast<int>(sortedString.size()); counter++) {
		sort(sortedString.begin(), sortedString.end());
		if (sortedString[counter] == sortedString[counter+1]) {
			string replaceLetter;
			replaceLetter = (char)((int(sortedString[counter]) + 1));
			sortedString.replace(counter, 2, replaceLetter);
			counter--;
		}
	}
	return sortedString;
}

std::string DecToLoc(std::int64_t dec) {
	string locResult = "";
	bool keepRunning = true;
	while (dec > 0) {
		int greaterthan = 0;
		int greaterThanTest = 0;
		while (keepRunning) {
			greaterThanTest = pow(2, greaterthan);
			if (greaterThanTest > dec) {
				keepRunning = false;
			}
			else {
				greaterthan++;
			}
		}
		locResult.push_back((char)((greaterthan + 96)));
		dec -= pow(2, (greaterthan-1));
		keepRunning = true;
		sort(locResult.begin(), locResult.end());
	}
	return locResult;
}

std::int64_t AddLoc(std::string const& loc1, std::string const& loc2) {
	return (LocToDec(loc1) + LocToDec(loc2));

}

int main()
{
	string locationString = "";
	int locationInterger = 0;
	string locationStringTwo = "";
	string locationStringThree = "";
	cout << "Give me a location string: " << endl; // Type Location String and press enter
	cin >> locationString; // Get user input from the keyboard

	cout << "Give me an integer : " << endl; // Type Location Integer and press enter
	cin >> locationInterger; // Get user input from the keyboard

	cout << locationString << " to dec: " << LocToDec(locationString) << endl;
	cout << locationString << " abbreviated: " << Abbreviate(locationString) << endl;
	cout << locationInterger << " to loc: " << DecToLoc(locationInterger) << endl;

	cout << "Give me two more location strings : " << endl; // Type Location String two and three and press enter
	cin >> locationStringTwo; // Get user input from the keyboard
	cin >> locationStringThree; // Get user input from the keyboard

	cout << "Sum of " << locationStringTwo << " and " << locationStringThree << " is: " << AddLoc(locationStringTwo, locationStringThree) << endl;
	return 0;
}