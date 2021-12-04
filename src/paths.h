#include <map>
#include <string>
#include <utility>
#include <iostream>
#include <vector>
using namespace std;

class paths{
private:
    //In order: destination; list of all movies & lengths in path to dest.
    map<string, vector<pair<string, double>>> pathList;

public:
    paths(map<string, vector<pair<string, double>>> allPaths){
        pathList = allPaths;
    }

    //adds a movie to existing path to a destination
    void addToPath(string dest, pair<string, double> movie){
        pathList[dest].push_back(movie);
    }

    double getPathLength(string dest){
        //sum all doubles in vector<pair> for given path
        double length = 0;
        for(int x = 0; x < pathList[dest].size(); ++x){
            length += pathList[dest][x].second;
        }
        return length;
    }

    //Prints path to given dest in a very ugly cmd format
    void printPath(string dest){
        cout << "Path to " << dest << " :" << endl;
        for(int x = 0; x < pathList[dest].size(); ++x) {
            cout << "Movie " << x << ": " << pathList[dest][x].first << ", Duration: " << pathList[dest][x].second << endl;
        }
        cout << "Total Time: " << getPathLength(dest) << endl;
    }

};