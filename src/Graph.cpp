#include <unordered_set>
#include <climits>
#include <vector>
#include <iostream>
#include "Graph.h"

//Used for A*: Instead of favoring the movie w/ the shortest dist of connections, favor the movie with the largest
pair<string, double> getH(map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail) {
    cout << "Entering getH " << endl;
    //returns the movie that has not been found yet with the shortest path to it
    pair<string, double> currentMax = make_pair("NULL", (double)INT_MIN); //shortest movie
    map<string, double> totalRunLength; //total run length of all movies in a given movie's path
    for (auto iter : paths) {
        //totalRunLength[iter.first] = 0; //initialization
        //for (int i = 0; i < iter.second.size(); i++) {
            totalRunLength[iter.first] = iter.second.size();
       // }
    }
    for (auto iter : totalRunLength) {
        if (iter.second > currentMax.second && avail.count(iter.first) == 1) { //if the current total run length is shorter than the saved run length...
            currentMax.first = iter.first;   //make the shortest total run length the current
            currentMax.second = iter.second;
        }
    }
    return currentMax;
}

pair<string, double> getMin(map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail) {
    //returns the movie that has not been found yet with the shortest path to it
    pair<string, double> currentShortest = make_pair("NULL", (double)INT_MAX); //shortest movie
    map<string, double> totalRunLength; //total run length of all movies in a given movie's path
    for (auto iter : paths) {
        totalRunLength[iter.first] = 0; //initialization
        for (int i = 0; i < iter.second.size(); i++) {
            totalRunLength[iter.first] += iter.second.at(i).second; 
        }
    }
    for (auto iter : totalRunLength) {
        if (iter.second < currentShortest.second && avail.count(iter.first) == 1) { //if the current total run length is shorter than the saved run length...
            currentShortest.first = iter.first;   //make the shortest total run length the current
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
    //used to find the current length of movies in a vector
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v.at(i).second;
    }
    return sum;
}

map<string, vector<pair<string, double>>> Graph::dijkstra(string vertex) {
    map<string, vector<pair<string, double>>> paths; //read as map<actor, vector<movie>>
    map<string, string> parents; 
    unordered_set<string> completed;
    unordered_set<string> notCompleted;
    for (auto iter : adjList) {
        paths[iter.first].push_back(make_pair("NULL", (double)INT_MAX)); //insert starting value 
        notCompleted.insert(iter.first);
    }
    
    (paths[vertex]).clear();
    
    while (!notCompleted.empty()) {
        pair<string, double> index = getMin(paths, notCompleted);
        cout << index.first << "found!" << endl;
        for (auto iter : adjList[index.first]) {
            
            if (getSum(paths[index.first]) + iter.second.second < getSum(paths[iter.first])) {
                paths[iter.first] = paths[index.first];
                paths[iter.first].push_back(iter.second);
                parents[iter.first] = index.first;
            }
        }
        if (notCompleted.count(index.first) != 0) {
           notCompleted.erase(index.first);
        }
        else {
            break;
        }
        completed.insert(index.first);
    }
    return paths;
}
map<string, vector<pair<string, double>>> Graph::aStar(string vertex) {
    map<string, vector<pair<string, double>>> paths; //read as map<actor, vector<movie>>
    map<string, string> parents;
    unordered_set<string> completed;
    unordered_set<string> notCompleted;
    for (auto iter : adjList) {
        paths[iter.first].push_back(make_pair("NULL", (double)INT_MAX)); //insert starting value
        notCompleted.insert(iter.first);
    }

    (paths[vertex]).clear();

    while (!notCompleted.empty()) {
        pair<string, double> index = getH(paths, notCompleted);
        cout << index.first << "found!" << endl;
        for (auto iter : adjList[index.first]) {

        if (getSum(paths[index.first]) + iter.second.second < getSum(paths[iter.first])) {
            paths[iter.first] = paths[index.first];
            paths[iter.first].push_back(iter.second);
            parents[iter.first] = index.first;
        }
        }
        if (notCompleted.count(index.first) != 0) {
            notCompleted.erase(index.first);
        }
        else {
            break;
        }
    completed.insert(index.first);
    }
return paths;
}