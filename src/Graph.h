#pragma once
#include <map>
#include <string>
#include <unordered_set>
#include <utility>
using namespace std;

class Graph {
    private:
        map<string, map<string, pair<string, double>>> adjList;
        //read as map<actor, map<actor, movie>>, where movie is represented as a pair
    public:
        void insertEdge(string actor1, string actor2, string title, double length);
        pair<string, double> getFilm(string actor1, string actor2);
        map<string, pair<string, double>> getAdjacent(string vertex);
        map<string, vector<pair<string, double>>> dijkstra(string vertex, string destination);
        map<string, vector<pair<string, double>>> aStar(string vertex, string destination);
        pair<string, double> getH(map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail);
        //other search here
};

