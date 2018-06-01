# Greedy_And_BranchAndBound_Algorithm_Uni_Assignment
An Assignment I did in my Computer Science Degree for Algorithm and Data Structures Subject to understand how Branch and Bound and Greedy algorithms work

To Compile the program:
From command line enter:
./a4compile

to run enter:
./a4run


Greedy:

Algorithm Used:

Strategy: nearest neighbour:

A slight variation of Dijkstra algorithm was implemented found in the CSCI203 lecture notes.

Data Structure:

A queue is used to store the path, because the first node visited will be the first out, giving me a complete path. Dynamic arrays are used to store un-visited nodes and edge distances as they are easy to iterate through.

Output:

Cost of path found was not the optimum solution. As no optimization for finding the real least cost path is implemented the final cost can be considered as the upper bound. 

Branch and Bound:

Algorithm Used:

Strategy:

Best first, (breadth-first expansion) implemented with an STL priority queue (heap) ordered by lowest lower-bound at the top.

The heap holds node objects consisting of upper bound, lower bound and an STL vector to hold the partial solutions. Main body follows the general b&b pattern of popping the top and comparing lower bound against upper then expanding if less than current upper. 

Data Structures Used:

The STL priority queue is used as a pruning mechanism because it is ordered by lowest lower bound so the best solutions are considered first. It’s also easy to insert and extract new solutions. An STL vector is used to store partial solutions because it is easy to insert a new node at the back to expand the solution. Vectors are also easily iterated over.

Output:

Branch and bound finds an optimal tour. The implementation created 30128 nodes for road tour and only 13,289 for flights. If the heap and comparisons with upper bound were not implemented all combinations would be produced, which is approx. 〖2.92x10〗^10
 
Conclusion:

Branch and bound produces the optimum path but is complex and requires the expansion of many nodes as well as many bound calculations. Time complexity is higher than greedy. But greedy will not produce lowest cost path in most cases. Branch and bound uses a method to prune the tree, improving time efficiency while producing the best path, this one is the better one to use if the optimal path is required.

