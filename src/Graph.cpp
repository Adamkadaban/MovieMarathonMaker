#include <unordered_set>
#include <climits>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include "Graph.h"

//Used for A*: Instead of favoring the movie w/ the shortest dist of connections, favor the movie with the largest
pair<string, double> Graph::getH(map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail) {
    //returns the movie that has not been found yet with the shortest path to it
    pair<string, int> largestOutdeg = make_pair("NULL", (double)0); //shortest movie
    
    for (auto iter : adjList) {
        if (iter.second.size() > largestOutdeg.second && avail.count(iter.first) == 1) {
            largestOutdeg.second = iter.second.size();
            largestOutdeg.first = iter.first;
        }
    }
    return make_pair(largestOutdeg.first, paths[largestOutdeg.first].at(0).second);
}

pair<string, double> getMin(map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail) {
    //returns the movie that has not been found yet with the shortest path to it
    pair<string, double> currentShortest = make_pair("NULL", (double)INT_MAX); //shortest movie
    
    for (auto iter : paths) {
        if (iter.second.at(0).second < currentShortest.second && avail.count(iter.first) == 1) { //if the current total run length is shorter than the saved run length...
            currentShortest.first = iter.first;   //make the shortest total run length the current
            currentShortest.second = iter.second.at(0).second;
        }
    }
    return currentShortest;
}

void Graph::insertEdge(string actor1, string actor2, string title, double length) {
    if (adjList[actor1].count(actor2) == 1) { //case if there already exists a movie between two actors
        if (((adjList[actor1])[actor2]).second > length) {
            ((adjList[actor1])[actor2]).first = title;
            ((adjList[actor1])[actor2]).second = length;
            ((adjList[actor2])[actor1]).first = title;
            ((adjList[actor2])[actor1]).second = length;
        }
    }
    else { //case if no movie between two actors has been added yet
        ((adjList[actor1])[actor2]).first = title;
        ((adjList[actor1])[actor2]).second = length;
        ((adjList[actor2])[actor1]).first = title;
        ((adjList[actor2])[actor1]).second = length;
    }
}

pair<string, double> Graph::getFilm(string actor1, string actor2) {
    if (adjList[actor1].count(actor2) == 1) {
        return ((adjList[actor1])[actor2]);
    }
    return make_pair("NULL", -1); //case for no movie between two actors
}

map<string, pair<string, double>> Graph::getAdjacent(string vertex) {
    return adjList[vertex];
}

double getSum(vector<pair<string, double>>& v) {
    //used to find the current length of movies in a vector
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v.at(i).second;
    }
    return sum;
}

map<string, vector<pair<string, double>>> Graph::dijkstra(string vertex, string destination) {
    map<string, vector<pair<string, double>>> paths; //read as map<actor, vector<movie>>
    unordered_set<string> notCompleted;
    for (auto iter : adjList) {
        paths[iter.first].push_back(make_pair("total:", (double)INT_MAX)); //insert starting value 
        notCompleted.insert(iter.first);
    }
    
    (paths[vertex]).at(0).second = 0;


    while (!notCompleted.empty()) {
        pair<string, double> index = getMin(paths, notCompleted);
        for (auto iter : adjList[index.first]) {
            
            if (paths[index.first].at(0).second + iter.second.second < paths[iter.first].at(0).second) {
                paths[iter.first] = paths[index.first];
                paths[iter.first].push_back(iter.second);
                paths[iter.first].at(0).second += iter.second.second;
            }
        }
        notCompleted.erase(index.first);
        if (index.first == destination) {
            return paths;
        }
    }
    return paths;
}

map<string, vector<pair<string, double>>> Graph::aStar(string vertex, string destination) {
    map<string, vector<pair<string, double>>> paths; //read as map<actor, vector<movie>>
    unordered_set<string> notCompleted;
    for (auto iter : adjList) {
        paths[iter.first].push_back(make_pair("total:", (double)INT_MAX)); //insert starting value 
        notCompleted.insert(iter.first);
    }
    
    (paths[vertex]).at(0).second = 0;


    while (!notCompleted.empty()) {
        pair<string, double> index = getH(paths, notCompleted);
        for (auto iter : adjList[index.first]) {
            if (paths[index.first].at(0).second + iter.second.second < paths[iter.first].at(0).second) {
                if (paths[iter.first].at(0).second == INT_MAX) {
                    paths[iter.first].at(0).second = 0;
                }
                paths[iter.first] = paths[index.first];
                paths[iter.first].push_back(iter.second);
                paths[iter.first].at(0).second += iter.second.second;
            }
            if (iter.first == destination) {
                if (paths[iter.first].at(0).second == INT_MAX) {
                    paths[iter.first].at(0).second = 0;
                }
                paths[iter.first] = paths[index.first];
                paths[iter.first].push_back(iter.second);
                paths[iter.first].at(0).second += iter.second.second;
                return paths;
            }
        }
        notCompleted.erase(index.first);
        cout << index.first << " found";
        if (index.first == destination) {
            return paths;
        }
    }
    return paths;
    }

vector<pair<string, double>> Graph::movieStar(string vertex, string destination) {
    unordered_set<string> visited;
    queue<map<string, pair<string, double>>> q;
    map<string, vector<pair<string, double>>> BFS;

    q.push(adjList[vertex]);
    visited.insert(vertex);
    //BFS[vertex].at(0).first = "total:";
    //BFS[vertex].at(0).second = 0;
    while(!q.empty()) {
        for (auto iter : q.front()) {
            if (visited.count(iter.first) == 0) {
                visited.insert(iter.first);
                q.push(adjList[iter.first]);
                BFS[iter.first].push_back(iter.second);
            }
        }
        if (visited.count(destination) == 1) {
            break;
        }
        q.pop();
    }
    return BFS[destination];
}