A small R and C++ library that provides the following functionality:

1. Compute the minimum spanning tree. When there are more than one optimal solution, it will output the first one it finds.

2. Sample a spanning tree using the random walk covering algorithm, with probability proportional to  exp( \sum_{(i,j)}   logW[i,j]).
