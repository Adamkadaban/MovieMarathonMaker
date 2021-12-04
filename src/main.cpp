#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Graph.h"
void readData(graph& g) {
    string line;
    ifstream myfile ("Database.tsv")
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
            vInput.push_back(input.substr(start, input.length() - start));
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
    g.dijkstra("test");
}