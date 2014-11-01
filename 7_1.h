#ifndef __7_1_H__
#define __7_1_H__
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MIN_SIZE 5

HashTable create_hash_table(int table_size);
HashTable insert(int num, HashTable T); // return the table after insert
//List find(int num, HashTable T);
//int hash(int num);
int is_prime(int num);
void print_hash_table(HashTable H);
int next_prime(int num);
void dispose_hash_table(HashTable T);

int is_prime(int num){
  if (num <= 1)
    return 0;
  for (int i = 2; i < sqrt(num) + 1; i++){
    if (num % i == 0)
      return 0;
  }
  return 1;
}

int next_prime(int num){
  num += num % 2 == 0? 1: 2; // make the num odd
  while (!is_prime(num))
    num += 2;
  return num;
}

void test(void){
  int input[7] = {4371, 1323, 6173, 4199, 4344, 9679, 1989};
  HashTable T = create_hash_table(7);
  for (int i = 0; i < 7; i++){
    T = insert(input[i], T);
  }
  print_hash_table(T);
  dispose_hash_table(T);
}
#endif
