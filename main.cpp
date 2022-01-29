#if 0
Title:		Covid Self Checker
Name:		Eric Choi
#endif

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>

using namespace std;

const string F_SWAPS = "swaps.txt";
const string F_MESSAGE = "message.txt";

vector<string> vec_messages;

/**
* This function performs the task to split the given data by distinguisher
*
* @param string line	data
* @return char			distinguisher
*/
std::string* split(std::string line, char distinguisher)
{
	stringstream ss(line);
	vector<string> result;
	std::string* str;

	while (ss.good())
	{
		string substr;
		getline(ss, substr, distinguisher);

		if (substr != "")
			result.push_back(substr);
	}

	str = new std::string[result.size()];

	for (int k = 0; k < result.size(); k++) {
		str[k] = result[k];
	}

	return str;
}

/**
* This function stores data in "message.txt"
*/
void init() {
	string line;				// each line of the file

	ifstream mfile(F_MESSAGE);

	if (mfile.is_open())
	{
		while (getline(mfile, line))
		{
			vec_messages.push_back(line);
		}
		mfile.close();
	}
}

/**
* This function replaces '_search' with '_replace' in each line of "message.txt"
*
* @param string _search
* @param string _replace
*/
void replace(string _search, string _replace) {
	for (int k = 0; k < vec_messages.size(); k++) {
		vec_messages[k] = regex_replace(vec_messages[k], regex(_search), _replace);
	}
}

/**
* This function decodes "swaps.txt" and performs the job to replace
*/
void swap() {
	int num_of_swaps = 0;		// # of swaps
	string line;				// each line of the file

	ifstream sfile(F_SWAPS);

	if (sfile.is_open())
	{
		while (getline(sfile, line))
		{
			if (num_of_swaps == 0)
				num_of_swaps = stoi(line);	// # of swaps
			else {
				string* str = split(line, ' ');	// 'search' and 'replace'

				replace(str[0], str[1]);	// replace 'search' with 'replace'
			}
		}
		sfile.close();
	}
	else
		cout << "Unable to open file: " << F_SWAPS << endl;

	// output first layer
	cout << "First Layer:" << endl;
	for (int k = 0; k < vec_messages.size(); k++) {
		cout << "\t" << vec_messages[k] << endl;
	}
}

/**
* This function checks whether the tags in each line match, and if yes, then store # of characters in the string
*
* @return vector<int> nums_of_char
*/
vector<int> match() {
	vector<int> nums_of_char;	// total # of characters in "inner" strings where the tags match
	cout << "Second Layer:" << endl;

	for (int k = 0; k < vec_messages.size(); k++) {
		smatch m;
		regex re("<(.*)>(.*)<(.*)>");
		regex_search(vec_messages[k], m, re);

		if (m[1] == m[3]) {
			cout << "\t" << m[2] << endl;		// output a series of "inner" strings where the tags match
			int num_of_char = m[2].length();	// store # of characters in the string
			nums_of_char.push_back(num_of_char);
		}
	}

	return nums_of_char;
}

/**
* This function displays an alphabetical output using data in a variable, nums_of_char
*
* @param vector<int> nums_of_char
*/
void output(vector<int> nums_of_char) {
	string alphabets = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	cout << "Final Layer:" << endl;
	cout << "\t";

	for (int k = 0; k < nums_of_char.size(); k++) {
		int index = nums_of_char[k] - 1;

		if (index < 27)
			cout << alphabets[index];
		else
			cout << ' ';
	}
}

int main() {
	init();		// store data in message.txt

	swap();									// swap		(First Layer)
	cout << "***" << endl;
	vector<int> nums_of_char = match();		// match	(Second Layer)
	cout << "***" << endl;
	output(nums_of_char);					// output	(Final)

	cin.ignore();

	return 0;
}