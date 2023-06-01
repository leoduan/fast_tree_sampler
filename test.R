rm(list=ls())

setwd("~/git/tree_sampler/")

library(Rcpp)
library(RcppArmadillo)


sourceCpp('tree_func.cpp')


# require(igraph)
# 
# findMSTr= function(logS){
#   G<- graph_from_adjacency_matrix(logS, mode = "undirected",weighted = TRUE,diag=FALSE)
#   G_mst<- mst(graph = G)
#   A_T_<- as.matrix(get.adjacency(G_mst))
#   A_T_
# }

A_T<- abs(matrix(rnorm(100),10,10))
A_T <- A_T+t(A_T)

a<- randomWalkCover(log(A_T))

b<- randomWalkLoopErased(log(A_T))
