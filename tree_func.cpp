#include <RcppArmadillo.h>
#include <igraph.h>

using namespace Rcpp;
using namespace arma;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
mat findMinST(const mat& W) {
  int n = W.n_rows;
  igraph_t G, mst;
  igraph_vector_t weights;
  igraph_matrix_t adj_matrix_G, adj_matrix_MST;
  
  igraph_vector_init(&weights, n * n);
  igraph_matrix_init(&adj_matrix_G, n, n);
  igraph_matrix_init(&adj_matrix_MST, n, n);
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        igraph_matrix_set(&adj_matrix_G,i,j, W(i, j));
      }
    }
  }
  
  igraph_weighted_adjacency(&G, &adj_matrix_G, IGRAPH_ADJ_UNDIRECTED, &weights,
                            IGRAPH_NO_LOOPS);
  
  mat A_T(n, n);
  
  igraph_minimum_spanning_tree_prim(&G, &mst, &weights);
  
  igraph_get_adjacency(&mst, &adj_matrix_MST, IGRAPH_GET_ADJACENCY_BOTH, NULL,IGRAPH_NO_LOOPS);
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A_T(i, j) = MATRIX(adj_matrix_MST, i, j);
    }
  }
  
  igraph_destroy(&G);
  igraph_destroy(&mst);
  igraph_vector_destroy(&weights);
  igraph_matrix_destroy(&adj_matrix_G);
  igraph_matrix_destroy(&adj_matrix_MST);
  
  return A_T;
}

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
int gumbelMaxC(const vec& logWeight){
  int n = logWeight.n_elem;
  vec noisy_weights = logWeight + (-log(-log(randu(n))));
  int v = noisy_weights.index_max();
  return v;
}

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
mat randomWalkCover(const mat& logW) {
  // Initialize variables
  int n = logW.n_rows;
  arma::mat A_T_(n, n, arma::fill::zeros);
  arma::Col<int> InTree(n, arma::fill::zeros);
  arma::Col<int> Next(n);
  
  // Set up Next and InTree
  int r = 0;
  InTree(r) = 1;
  Next(r) = 0;
  
  // Compute A_T_
  for (int i = 0; i < n; i++) {
    int u = i;
    //do a random walk, until getting back to the tree
    while (!InTree(u)) {
      int v = gumbelMaxC(logW.col(u));
      Next(u) = v;
      u = v;
    }
    u = i;
    //go through this path that we just walked, change the label of each node to InTree = True
    while (!InTree(u)) {
      InTree(u) = 1;
      u = Next(u);
    }
  }
  
  // Construct adjacency matrix
  for (int u = 1; u < n; u++) {
    A_T_(u, Next(u)) = 1;
    A_T_(Next(u), u) = 1;
  }
  
  return A_T_;
}



