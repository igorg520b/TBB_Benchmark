# Comparing Intel TBB set and consurrent set to single-core implementations

Results obtained on i7-12700

```
inserting 10000000 elements with N distinct values; time in milliseconds
N         std_set        tbb_single     tbb_multi      std_unordered  tbb_unordered  
1000      582            951            156            67             50             
10000     1000           1604           214            173            52             
100000    4841           5043           258            274            96             
1000000   13062          15907          649            865            189  
```