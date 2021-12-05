#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Graph.h"
using namespace std;

void readData(Graph& g) {
    string line;
    ifstream myfile ("../tools/ModernDatabase.tsv");
    vector<string> vInput;
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            vInput.clear();
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
    cout << "data read!" << endl;
    map<string, vector<pair<string, double>>> paths2 = g.aStar("Daniel Radcliffe", "Emma Watson");
    paths2["Emma Watson"].at(0).second = 0;
    for (int i = 1; i < paths2["Emma Watson"].size(); i++) {
        paths2["Emma Watson"].at(0).second += paths2["Emma Watson"].at(i).second;
    }
    for (int i = 0; i < paths2["Emma Watson"].size(); i++) {
        cout << paths2["Emma Watson"].at(i).first << " ";
        cout << paths2["Emma Watson"].at(i).second << " ";
    }
    map<string, vector<pair<string, double>>> paths = g.dijkstra("Daniel Radcliffe", "Emma Watson");
    for (int i = 0; i < paths["Emma Watson"].size(); i++) {
        cout << paths["Emma Watson"].at(i).first << " ";
        cout << paths["Emma Watson"].at(i).second << " ";
    }
    cout << "Test" << endl;
    return 0;
}