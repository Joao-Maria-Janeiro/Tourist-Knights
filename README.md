# Tourist-Knights
Final project for the Algorithms and Data Structures course at [Instituto Superior Técnico](https://tecnico.ulisboa.pt), second year first semester where we got 19/20 in the automatic submissions (done on Mooshak) and 17 after submiting the report and the professor's review.

The project had three different challenges:
* Given a Source point and a Destination source find the shortest path between them (Part A)
* Given a set of point in a defined order, find the shortest path to go from each point to next in the given order (Part B)
* Given a set of points, find the order to pass through all points that will generate the smallest path between them (Part C)

In order to solve these problems we used Dijkstra's algorithm with a heap.

* For part A we just applied the Dijkstra's algorithm between the two given points
* For Part B we just repeated part A from each point to the next
* For Part C we generated all permutations using Branch and Bound and applied Dijkstra's algorithm to find the best permutation
