#include <unordered_set>
#include <climits>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include "Graph.h"


//Min-Heap comparison overloading (myComp overloading inspired by geeksforgeeks)
//Allows for use of pair in minHeap
typedef pair<string, double> pd;

struct myComp {

    constexpr bool operator()(pair<string, double> const& a,pair<string, double> const& b)const noexcept
    {
        return a.second > b.second;
    }
};

//Fib-Heap GetMin...
pair<string, double> getFibMin(unordered_map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail){
    priority_queue<pd, vector<pd>, myComp> minHeap;
    //add each pair in paths to the minHeap.
    for (auto iter : paths) {
        if(avail.count(iter.first) == 1)
            minHeap.push(iter.second.at(0));
    }

    pair<string, double> min = minHeap.top();
    return min;
    //SO: I need to fib-Heap paths; a map<actors, list of <connecting movies>>
    //RESULT: should be the shortest connecting movie. So fib-heap the pairs.

}



//Used for A*: Instead of favoring the movie w/ the shortest dist of connections, favor the movie with the largest
pair<string, double> Graph::getH(unordered_map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail) {
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

pair<string, double> getMin(unordered_map<string, vector<pair<string, double>>>& paths, unordered_set<string> avail) {
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

unordered_map<string, pair<string, double>> Graph::getAdjacent(string vertex) {
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

unordered_map<string, vector<pair<string, double>>> Graph::dijkstra(string vertex, string destination) {
    unordered_map<string, vector<pair<string, double>>> paths; //read as map<actor, vector<movie>>
    unordered_set<string> notCompleted;
    for (auto iter : adjList) {
        paths[iter.first].push_back(make_pair("total:", (double)INT_MAX)); //insert starting value 
        notCompleted.insert(iter.first);
    }
    
    (paths[vertex]).at(0).second = 0;


    while (!notCompleted.empty()) {
        //pair<string, double> index = getMin(paths, notCompleted);
        pair<string, double> index = getFibMin(paths, notCompleted);
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

/*unordered_map<string, vector<pair<string, double>>> Graph::dijkstra(string vertex, string destination) {
    unordered_map<string, vector<pair<string, double>>> paths; //read as map<actor, vector<movie>>
    priority_queue<pd, vector<pd>, myComp> minHeap;
    unordered_set<string> notCompleted;

    minHeap.push(make_pair(vertex, 0.0));//initialize src vertex as root, w/ dist 0

    for (auto iter : adjList) {
        paths[iter.first].push_back(make_pair("total:", (double)INT_MAX)); //insert starting value 
        notCompleted.insert(iter.first);
        //minHeap.push(iter.second.at(0)); //causes M_construct null not valid error.
    }

    //this adds every pair in paths to the minheap
    for (auto iter : paths) {
        minHeap.push(iter.second.at(0));     
    }

    (paths[vertex]).at(0).second = 0;

    while(!minHeap.empty()){ //while not empty
      //extract min
      pair<string, double> index = minHeap.top();
      minHeap.pop();
      notCompleted.erase(index.first);
      //For every adjacent vertex v of index, check if v is in Min Heap. 
      //If v is in Min Heap and distance value is more than weight of u-v plus distance value of u, then update the distance value of v.
      for (auto iter : adjList[index.first]) {
          if(notCompleted.count(iter.first) == 1){ //if not already in heap
            if (paths[index.first].at(0).second + iter.second.second < paths[iter.first].at(0).second) {
                paths[iter.first] = paths[index.first];
                paths[iter.first].push_back(iter.second);
                paths[iter.first].at(0).second += iter.second.second;
            }
          }
        }
        if (index.first == destination) {
            //this is never reached. my minheap is emptying before it finds the solution.
            return paths;
        }
    }

    return paths;  
}*/

unordered_map<string, vector<pair<string, double>>> Graph::aStar(string vertex, string destination) {
    unordered_map<string, vector<pair<string, double>>> paths; //read as map<actor, vector<movie>>
    unordered_set<string> notCompleted;
    for (auto iter : adjList) {
        paths[iter.first].push_back(make_pair("total:", (double)INT_MAX)); //insert starting value 
        notCompleted.insert(iter.first);
    }
    
    (paths[vertex]).at(0).second = 0;
    

    while (!notCompleted.empty()) {
        pair<string, double> index = getH(paths, notCompleted);
        for (auto iter : adjList[index.first]) {
                paths[iter.first] = paths[index.first];
                paths[iter.first].push_back(iter.second);
                paths[iter.first].at(0).second += iter.second.second;
            if (iter.first == destination) {
                paths[iter.first] = paths[index.first];
                paths[iter.first].push_back(iter.second);
                paths[iter.first].at(0).second += iter.second.second;
                return paths;
            }
        }
        notCompleted.erase(index.first);
        if (index.first == destination) {
            return paths;
        }
    }
    return paths;
    }

vector<pair<string, double>> Graph::movieStar(string vertex, string destination) {
    unordered_set<string> visited;
    unordered_map<string, string> parents;
    queue<unordered_map<string, pair<string, double>>> q;
    unordered_map<string, vector<pair<string, double>>> BFS;

    q.push(adjList[vertex]);
    visited.insert(vertex);
    queue<string> current;
    current.push(vertex);
    while(!q.empty()) {
        for (auto iter : q.front()) {
            if (visited.count(iter.first) == 0) {
                parents[iter.first] = current.front();
                visited.insert(iter.first);
                q.push(adjList[iter.first]);
                current.push(iter.first);
                BFS[iter.first] = BFS[parents[iter.first]];
                BFS[iter.first].push_back(iter.second);
            }
        }
        if (visited.count(destination) == 1) {
            break;
        }
        q.pop();
        current.pop();
    }
    return BFS[destination];
}