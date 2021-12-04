#pragma once
#include <map>
#include <string>
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
        map<string, map<string, pair<string, double>>> dijkstra(string vertex);
        //other search here
};

