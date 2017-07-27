# Lusky_CSCI2270_FinalProject

This is going to be a motion planning program.  The graph will be created by uniform discretation of a 2d planar region.  All weights will be 1 except for edges and obstacles which will be set to max int.  Dijkstra's algorithm will be used to find the shortest path to some point on the 2d plane while navigating obstacles.  The second data structure is a stack to hold the pointers for the shortest path as they are loaded by the pathing algorithm.  

The graph is a 640 by 480 grid with all vertices connected to all surrounding points in a coordinate system(i.e. (1,1) is connected to (1,2), (2,1), and (2,2)).  All weights are set to 1 except for edges from obstacles which are significantly higher.
Start, finish and obstacles are preset though could easily be set to user inputs.  The output shows the vector of vertices the algorithm is going through then prints ANSWER and the vertices from start to finish in the shortest path found.

To run the file just download pathfind in bin/Release and run.  Alternatively you can download everything and use the makefile.
