#include <unordered_set>
#include <climits>
#include "Graph.h"

pair<string, double> getMin(map<string, vector<pair<string, double>>>& paths, unordered_set<int> avail) {
    pair<string, double> currentShortest = ("NULL", INT_MAX);
    map<string, double> totalRunLength;
    for (auto iter : paths) {
        totalRunLength[iter.first] = 0;
        for (int i = 0; i < iter.second.size(); i++) {
            totalRunLength[iter.first] += iter.second;
        }
    }
    for (auto iter : totalRunLength) {
        if (iter.second < currentShortest.second && avail.count(iter.first) == 1) {
            currentShortest.first = iter.first;
            currentShortest.second = iter.second;
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
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v.second;
    }
    return sum;
}

map<string, vector<pair<string, double>>> Graph::dijkstra(string vertex) {
    map<string, vector<pair<string, double>>> paths;
    map<string, string> parents;
    unordered_set<string> completed;
    unordered_set<string> notCompleted;
    for (auto iter : adjList) {
        iter.second.push_back(make_pair("NULL", INT_MAX));
        notCompleted.insert(iter.first);
    }
    
    (paths[vertex]).at(0).second = 0;
    
    while (!notCompleted.empty()) {
        pair<string, double> index = getMin(paths, notCompleted);
        
        for (auto iter : adjList[index.first]) {
            
            if (sum(paths[index.first]) + iter.second.second < sum(paths[iter.first])) {
                if (paths[iter.first].at(0).second == INT_MAX) {
                    paths[iter.first] = paths[index.first];
                }
                else {
                    paths[iter.first].push_back(iter.second);
                }
                parents[iter.first] = index.first;
            }
        }
        if (notCompleted.count(index.first) != 0) {
           notCompleted.erase(index.first);
        }
        else {
            cout << "this shouldn't happen";
            break;
        }
        completed.insert(index);
    }
    return paths;
}