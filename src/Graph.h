#pragma once
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <utility>
using namespace std;

class Graph {
    private:
        unordered_map<string, unordered_map<string, pair<string, double>>> adjList;
        //read as map<actor, map<actor, movie>>, where movie is represented as a pair
    public:
        void insertEdge(string actor1, string actor2, string title, double length);
        pair<string, double> getFilm(string actor1, string actor2);
        unordered_map<string, pair<string, double>> getAdjacent(string vertex);
        unordered_map<string, vector<pair<string, double>>> dijkstra(string vertex, string destination);
        unordered_map<string, vector<pair<string, double>>> aStar(string vertex, string destination);
        pair<string, string> getH(unordered_map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail, unordered_set<string> completed);
        vector<pair<string, double>> movieStar(string vertex, string destination);
        //other search here
};

