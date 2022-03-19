# MovieMarathonMaker
Adam Hassan, Lisa Reichelson, Michael Hayworth

Discord bot that retrieves the shortest movie marathon to get from one actor to another

Video: [https://www.youtube.com/watch?v=ntkkdWRPRvo](https://www.youtube.com/watch?v=ntkkdWRPRvo)

### Extended and Refined Proposal
Problem: How long would it take to get from a Danny Devito movie to an Anne Hathaway movie? What is the smallest degree of separation between two actors? 

### Data
[IMDB](https://www.imdb.com/interfaces/)

Each vertex is an actor and two vertices are connected by an edge if they have been in a movie together. Each vertex is weighted by the duration of that movie; there will be multiple edges if actors have been in multiple movies, and the shortest shared movie will be used to calculate Dijsktra’s.

### Tools 
The graph API, A*, BFS, and Dijkstra’s Shortest Path algorithms will be coded in C++, and the final executable will be compiled C++ code. Some python will be used to organize the data we download from our database, as well as to create the discord bot that will be able to execute our code.

### Visuals
Because this project is heavily technical with the implementation of multiple graph algorithms, we are leaning towards command line compilation, along with a discord bot that allows a user to prompt our bot to run our program.

### Complexity Analysis

**Fibanacci Heap Dijkstra’s: O(Elog(V))**

The complexity of our Fibonacci-Heap optimized Dijkstra’s algorithm is O(Elog(V)), where E represents the edges of our graph (movies), and V represents the vertices of our graph (actors). Because we used a min-heap to calculate the minimum path to take at each step, the number of edges (movies) that are compared is multiplied by the log of the number of vertices (actors) in our graph.

**A\*: O(V\*outdegree(V))**

The complexity of an A* search directly depends on the heuristic used. In our code, we calculated the vertice with the highest outdegree in O(outdegree) time, where outdegree(V) is the number of successors in the node with the most paths (movies) connecting to it. Since this heuristic is used in Dijkstra’s, it will be run V, or the number of vertices (actors), times. 

**Breadth-First-Search: O(V+E)**

The worst-case complexity of our BFS implementation is O(V+E), since we implemented our graph using an adjacency list representation. V represents the number of vertices (actors), and E represents the number of connecting edges (movies) between them. 

### References:
-Priority queue pair overloading (geeks4geeks)
-https://www.imdb.com/interfaces/