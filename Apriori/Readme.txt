AIM - To find the frequent itemsets from the given dataset.

ALGORITHM - Standard Apriori Algorithm 

1.) Generate candidate 1-itemset & frequent 1-itemset.

for(k=2,3,....upto n)
{
Generate candidate k-itemset from frequent (k-1)-itemset.
Prune the candidate k-itemset
Generate frequent k-itemset from candidate k-itemset.
}
Repeat until k-frequent itemset is not null.

Sample Input - "transaction.txt" (minsup = .22)

Sample output - 

Frequent itemsets - {1},{2},{3},{4},{5},{1,2},{1,3}{1,5},{2,3},{2,4},{2,5},{1,2,3},{1,2,5}
 