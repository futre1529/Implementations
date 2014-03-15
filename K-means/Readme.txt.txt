AIM - Clustering of data using k-means method

ALGORITHM - 

(1) arbitrarily choose k objects from D as the initial cluster centers;
(2) repeat
(3) (re)assign each object to the cluster to which the object is the most similar,
based on the mean value of the objects in the cluster;
(4) update the cluster means, i.e., calculate the mean value of the objects for
each cluster;
(5) until no change;

Sample Input :

(2,10), (5,8), (1,2), (2,5), (8,4), (7,5), (6,4), (4,9)

Sample Output - 

Cluster 1 - Centre(3.67,9)
Points -> (2,10), (5,8), (4,9)

Cluster 2 - Centre(7,4.33)
Points -> (8,4), (7,5), (6,4)

Cluster 3 - Centre(1.5,3.5)
Points -> (1,2), (2,5)