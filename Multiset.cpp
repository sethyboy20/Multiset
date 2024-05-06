#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;

void ReadMultiset(const string& data, vector<string>& multiset) {
	istringstream stream(data);

	// Remove the beginning of the line
	string begin;
	getline(stream, begin, '{');

	string tempElems;
	getline(stream, tempElems);

	// Read the correct number of elements
	unsigned int numElems = 1;
	for (unsigned int i = 0; i < tempElems.size(); i++) {
		if (tempElems[i] == ',') {
			numElems++;
		}
	}

	string elem;
	istringstream elemStream(tempElems);
	for (unsigned int i = 0; i < numElems - 1; i++) {
		getline(elemStream, elem, ',');
		multiset.push_back(elem);
	}
	getline(elemStream, elem, '}');
	// check if the multiset does not have 0 elements
	if (!(numElems == 1 && elem == "")) {
		multiset.push_back(elem);
	}
}

int main(int argc, const char** argv)
{
	try {
		// Check if there is 1 string entered
		if (argc != 2) {
			throw runtime_error("Wrong number of arguments");
		}

		// Read the filename from argument
		string filename = argv[1];

		if (filename.size() > 4 &&
			filename.substr(filename.size() - 4, filename.size()) != ".txt") {
			throw runtime_error("Invalid extension");
		}

		vector<string> multiset1;
		vector<string> multiset2;

		ifstream inFile;
		inFile.open(filename);

		// Read data file
		if (inFile.is_open()) {
			string currLine;

			getline(inFile, currLine);
			ReadMultiset(currLine, multiset1);

			getline(inFile, currLine);
			ReadMultiset(currLine, multiset2);
			
			cout << filename << " read" << endl;
		}
		else {
			cout << "Could not open " << filename << endl;
		}
		inFile.close();

		ofstream outFile("output.txt");

		// Output results to file
		if (outFile.is_open()) {
			outFile << "Multisets:" << endl;
			outFile << "\t" << "A={";
			for (unsigned int i = 0; i < multiset1.size(); i++) {
				outFile << multiset1[i];
				if (i != multiset1.size() - 1)
					outFile << ",";
			}
			outFile << "}";
			outFile << endl;

			outFile << "\t" << "B={";
			for (unsigned int i = 0; i < multiset2.size(); i++) {
				outFile << multiset2[i];
				if (i != multiset2.size() - 1)
					outFile << ",";
			}
			outFile << "}";
			outFile << endl << endl;

			// Sort the vectors to compare them properly
			sort(multiset1.begin(), multiset1.end());
			sort(multiset2.begin(), multiset2.end());


			outFile << "Solutions:" << endl;

			// Union
			vector<string> unionSet = multiset1;

			vector<string> compareSet = multiset1;
			for (unsigned int i = 0; i < multiset2.size(); i++) {
				bool inSet = false;
				for (unsigned int j = 0; j < compareSet.size(); j++) {
					if (multiset2[i] == compareSet[j]) {
						inSet = true;
						compareSet.erase(compareSet.begin() + j);
						break;
					}
				}

				if (!inSet) {
					unionSet.push_back(multiset2[i]);
				}
			}
			
			sort(unionSet.begin(), unionSet.end());
			outFile << "\t" << "A" << u8"∪" << "B={";
			for (unsigned int i = 0; i < unionSet.size(); i++) {
				outFile << unionSet[i];
				if (i != unionSet.size() - 1)
					outFile << ",";
			}
			outFile << "}";
			outFile << endl;

			// Intersection
			vector<string> interSet;

			compareSet = multiset1;
			for (unsigned int i = 0; i < multiset2.size(); i++) {
				for (unsigned int j = 0; j < compareSet.size(); j++) {
					if (multiset2[i] == compareSet[j]) {
						interSet.push_back(multiset2[i]);
						compareSet.erase(compareSet.begin() + j);
						break;
					}
				}
			}

			sort(interSet.begin(), interSet.end());
			outFile << "\t" << "A" << u8"∩" << "B={";
			for (unsigned int i = 0; i < interSet.size(); i++) {
				outFile << interSet[i];
				if (i != interSet.size() - 1)
					outFile << ",";
			}
			outFile << "}";
			outFile << endl;

			// Difference A - B
			vector<string> diffSet1;

			compareSet = multiset1;
			for (unsigned int i = 0; i < multiset2.size(); i++) {
				for (unsigned int j = 0; j < compareSet.size(); j++) {
					if (multiset2[i] == compareSet[j]) {
						compareSet.erase(compareSet.begin() + j);
						break;
					}
				}
			}

			diffSet1 = compareSet;

			sort(diffSet1.begin(), diffSet1.end());
			outFile << "\t" << "A-B={";
			for (unsigned int i = 0; i < diffSet1.size(); i++) {
				outFile << diffSet1[i];
				if (i != diffSet1.size() - 1)
					outFile << ",";
			}
			outFile << "}";
			outFile << endl;

			// Difference B - A
			vector<string> diffSet2;

			compareSet = multiset2;
			for (unsigned int i = 0; i < multiset1.size(); i++) {
				for (unsigned int j = 0; j < compareSet.size(); j++) {
					if (multiset1[i] == compareSet[j]) {
						compareSet.erase(compareSet.begin() + j);
						break;
					}
				}
			}

			diffSet2 = compareSet;

			sort(diffSet2.begin(), diffSet2.end());
			outFile << "\t" << "B-A={";
			for (unsigned int i = 0; i < diffSet2.size(); i++) {
				outFile << diffSet2[i];
				if (i != diffSet2.size() - 1)
					outFile << ",";
			}
			outFile << "}";
			outFile << endl;

			// Addition
			vector<string> sumSet = multiset1;

			for (unsigned int i = 0; i < multiset2.size(); i++) {
				sumSet.push_back(multiset2[i]);
			}

			sort(sumSet.begin(), sumSet.end());
			outFile << "\t" << "A+B={";
			for (unsigned int i = 0; i < sumSet.size(); i++) {
				outFile << sumSet[i];
				if (i != sumSet.size() - 1)
					outFile << ",";
			}
			outFile << "}";
			outFile << endl;

			cout << "Results written to output.txt" << endl;
		}
		else {
			cout << "Could not write to file" << endl;
		}
	}
	catch (runtime_error& excpt) {
		cout << "ERROR: " << excpt.what() << endl;
		cout << "Please enter a filename to read, with extension .txt (ex: multisets.txt)" << endl;
	}

	return 0;
}