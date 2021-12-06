#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include "Graph.h"
using namespace std;

class Timer //Timer class credit to mcleary on GitHub, class defintion from https://gist.github.com/mcleary/b0bf4fa88830ff7c882d
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

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

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "[!] Invalid input!" << endl;
        cout << "Usage:\n";
        cout << "\t" << argv[0] << " <from actor> <algorithm> <to actor>" << endl;
        cout << "\n\nExamples:\n";
        cout << "\t" << argv[0] << " \"Emma Watson\" \"dijkstra\" \"Hugh Laurie\"\n";
        cout << "\n\nAlgorithm options:\n";
        cout << "\tDijkstras - Most accurate algorithm\n";
        cout << "\taStar - Faster, slightly less accurate algorithm\n";
        cout << "\tmovieStar - Fastest, but least accurate algorithm\n";
        cout << "\tcompare - Do all of the above\n";

        return -1;
    }
    Graph g;
    cout << "[*] Reading in hundreds of thousands of movies!" << endl;
    readData(g);
    cout << "[*] Done!\n" << endl;
    Timer t;

    string from = argv[1];
    string to = argv[3];
    string function = argv[2];

    cout << "[*] Starting algorithm...\n";
    if (function == "dijkstra") {
        t.start();
        unordered_map<string, vector<pair<string, double>>> paths = g.dijkstra(from, to);
        t.stop();

        cout << "Your movie marathon will take " << paths[to].at(0).second << " minutes." << endl;
        for (int i = 1; i < paths[to].size(); i++) {
            cout << " - " << paths[to].at(i).first << " - ";
            cout << paths[to].at(i).second << endl;
        }
        cout << "[*] Dijkstra elapsed time: " << t.elapsedSeconds() << " seconds";
    }
    else if (function == "aStar") {
        t.start();
        unordered_map<string, vector<pair<string, double>>> paths2 = g.aStar(from, to);
        t.stop();
        paths2[to].at(0).second = 0;
        for (int i = 1; i < paths2[to].size(); i++) {
            paths2[to].at(0).second += paths2[to].at(i).second;
        }
        cout << "Your movie marathon will take " << paths2[to].at(0).second << " minutes." << endl;
        for (int i = 1; i < paths2[to].size(); i++) {
            cout << " - " << paths2[to].at(i).first << " - ";
            cout << paths2[to].at(i).second << endl;
        }
        cout << "[*] aStar elapsed time: " << t.elapsedSeconds() << " seconds";
    }
    else if (function == "movieStar") {
        t.start();
        vector<pair<string, double>> movieS = g.movieStar(from, to);
        t.stop();
        double total;
        for (int i = 0; i < movieS.size(); i++) {
            total += movieS.at(i).second;
        }
        cout << "Your movie marathon will take " << total << " minutes." << endl;
        for (int i = 0; i < movieS.size(); i++) {
            cout << " - " << movieS.at(i).first << " - " << movieS.at(i).second << endl;
        }
        cout << "[*] movieStar elapsed time: " << t.elapsedSeconds() << " seconds";
    }
    else if (function == "compare") {
        cout << "\nDijsktras:" << endl;
        t.start();
        unordered_map<string, vector<pair<string, double>>> paths = g.dijkstra(from, to);
        t.stop();
        cout << "Your movie marathon will take " << paths[to].at(0).second << " minutes." << endl;
        for (int i = 1; i < paths[to].size(); i++) {
            cout << " - " << paths[to].at(i).first << " - ";
            cout << paths[to].at(i).second << endl;
        }
        cout << "[*] Dijkstra elapsed time: " << t.elapsedSeconds() << " seconds\n" << endl;

        cout << "A*:" << endl;

        t.start();
        unordered_map<string, vector<pair<string, double>>> paths2 = g.aStar(from, to);
        t.stop();
        paths2[to].at(0).second = 0;
        for (int i = 1; i < paths2[to].size(); i++) {
            paths2[to].at(0).second += paths2[to].at(i).second;
        }
        cout << "Your movie marathon will take " << paths2[to].at(0).second << " minutes." << endl;

        for (int i = 1; i < paths2[to].size(); i++) {
            cout << " - " << paths2[to].at(i).first << " ";
            cout << paths2[to].at(i).second << endl;
        }
        cout << "[*] A* elapsed time: " << t.elapsedSeconds() << " seconds\n" << endl;


        cout << "movieStar:" << endl;

        t.start();
        vector<pair<string, double>> movieS = g.movieStar(from, to);
        t.stop();
        double total;
        for (int i = 0; i < movieS.size(); i++) {
            total += movieS.at(i).second;
        }
        cout << "Your movie marathon will take " << total << " minutes." << endl;
        for (int i = 0; i < movieS.size(); i++) {
            cout << " - " << movieS.at(i).first << " " << movieS.at(i).second << endl;
        }
        cout << "[*] movieStar elapsed time: " << t.elapsedSeconds() << " seconds";
    }
    else{
        cout << "[!] Invalid search mode" << endl;
    }
    cout << endl;
    return 0;
}