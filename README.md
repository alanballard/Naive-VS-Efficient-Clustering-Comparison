# Naive-VS-Efficient-Clustering-Comparison
Code for comparing naive and efficient undirected likelihood, modularity, and Louvain Method clustering on a user-supplied network

This code was created to support the paper "Improving computational performance in likelihood-based network clustering" by Alan Ballard and Marcus B. Perry (Stat. 2019; 8:e256. https://doi.org/10.1002/sta4.256)

Given an undirected network, this code will cluster it into a user-specified k number of clusters using the likelihood objective function proposed by Perry et al (2013) in "On the statistical detection of clusters in undirected networks", the efficient version of this likelihood objective function proposed in the current paper and the modularity objective function proposed by Newman (2006) in "Modularity and community structure in networks". 
This clustering is accomplished using simulated annealing and the k value, along with the simulated annealing cooling schedule, are adjustable within the code.
The network is also clustered using the so-called Louvain Method of optimizing modularity proposed by Blondel et al (2008) in "Fast unfolding of communities in large networks". This is an agglommerative, greedy clustering method that is known for its speed and although it differs from simulated annealing in optimization mechanics, it is included here for comparison of clustering quality and time-to-solution.

A sample edge list file, karate_club.txt, is included in this repository. This is an edge list for the undirected 'Zachary's Karate Club' network.  This is an example of how network data must be formatted for input into this code. The code used to input data into the program is not sophisticated and requires strict adherence to this formatting.

Vertex numbering must start at zero and no numbers can be skipped. For example, if there are N vertices, they should be numbered {0,1,2,....,(N-1)} with no missing integers in the set. If vertex 0<=L<=(N-1) is missing from the edge list, the program may accept the data but it will load the edges to incorrect positions and produce corrupted results.

Each edge should appear twice in the edge list. If vertices 0 and 1 are connected then there should be two rows in the edge list: 0 1 and 1 0. 

The edge list should be sorted least-to-greatest first on the left column and then likewise on the right column.
