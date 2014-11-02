#include "7_1_bcd.h"

int hash2(int num){
  return 7 - num % 7;
}

int main(void){
  test();
  return 0;
}

// find routine with quardratic probing
int find(int num, HashTable T){
  int current_pos;
  int hash_value; // to record hash value in case there is a infinite find
  int hash2_value;
  int collision_num = 0;

  current_pos = hash_value = hash(num);
  hash2_value = hash2(num);
  while (T->elements[current_pos].status != empty &&
	 T->elements[current_pos].element != num){
    current_pos += hash2_value;
    if (current_pos >= T->table_size)
      current_pos -= T->table_size;
    if (current_pos == hash_value){
      /*
      printf("Infinite find routine\n");
      exit(1);
      */
      return -1; // not find
    }
  }

  return current_pos;
}
