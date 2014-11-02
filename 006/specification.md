Hash
=======

##7-1
Given input {4371, 1323, 6173, 4199, 4344, 9679, 1989} and 
a hash function h(X) = X (mod 10), show the resulting: 

a. Separate chaining hash table. 

b. Open addressing hash table using linear probing. 

c. Open addressing hash table using quadratic probing. 

d. Open addressing hash table with second hash function 
h2(X) = 7 - (X mod 7). 

##7-2
Show the result of rehashing the hash tables in Exercise 7-1.

The Disjoint Set ADT
====================

##8-7
Write a program to implement the algorithm in Section 8.7.

** What's in Section 8.7 **
We have a network of computers and a list of bi-directional
connections. Each of these connections allows a file transfer from one
computer to another. Is it possible to send a file from any computer
on the network to any other?

Input: Input consists of several test cases. For each test case, the
first line contains N (<=10,000), the total number of computers in a
network.  Each computer in the network is then represented by a
positive integer between 1 and N. Then in the following lines, the
input is given in the format:

`I c1 c2` where `I` stands for inputting a connection between `c1` and `c2`;
or

`C c1 c2` where `C` stands for checking if it is possible to transfer
files between `c1` and `c2`; or

`S` where `S` stands for stopping this case.

Output: For each C case, print in one line the word yes or no if it is
possible or impossible to transfer files between `c1` and `c2`,
respectively.  At the end of each case, print in one line The network
is connected. if there is a path between any pair of computers; or
There are `k` components. where `k` is the number of connected components
in this network. Print a blank line between test cases.

Sample Input:

    3
    C 1 2 
    I 1 2 
    C 1 2 
    S
    
    3 
    I 3 1 
    I 2 3
    C 1 2 
    S

Sample Output:

    no 
    yes 
    There are 2 components. 
    
    yes 
    The network is connected. 