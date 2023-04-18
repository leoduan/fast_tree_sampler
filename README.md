A small R and C++ library that provides the following functionality:

1. Compute the minimum spanning tree. When there are more than one optimal solutions, it will output the first one it finds.

2. Random walk covering algorithm to sample a spanning tree, with probability proportional to  exp( \sum_{(i,j)}   logW[i,j]).
