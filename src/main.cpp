#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Graph.h"
using namespace std;

void readData(Graph& g) {
    string line;
    ifstream myfile ("Database.tsv");
    vector<string> vInput;
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            int start = 0;
            //converts input string into a vector of strings, split by the ' ' char
            for (int i = 0; i < line.length(); i++) {
                if (line.at(i) == '\t') {
                    vInput.push_back(line.substr(start, i - start));
                    start = i + 1;
                }  
            }
            vInput.push_back(line.substr(start, line.length() - start));
            for (int i = 2; i < vInput.size(); i++) {
                for (int j = i + 1; j < vInput.size(); j++) {
                    if (i == j) { //dont want a self-loop!
                        continue; 
                    }
                    g.insertEdge(vInput[i], vInput[j], vInput[0], stod(vInput[1]));
                }
            }
        }
    }
}

int main() {
    Graph g;
    readData(g);
    map<string, vector<pair<string, double>>> paths = g.dijkstra("Person5");
    for (int i = 0; i < paths["Person8"].size(); i++) {
        cout << paths["Person8"].at(i).first << " ";
        cout << paths["Person8"].at(i).second << " ";
    }
    cout << "Test" << endl;
}