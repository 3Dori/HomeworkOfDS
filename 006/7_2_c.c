#include "7_2_bcd.h"

int main(void){
  test();
  return 0;
}

// find routine with quardratic probing
int find(int num, HashTable T){
  int current_pos;
  int hash_value; // to record hash value in case there is a infinite find
  int collision_num = 0;

  current_pos = hash_value = hash(num, T);
  while (T->elements[current_pos].status != empty &&
	 T->elements[current_pos].element != num){
    current_pos += ++collision_num * 2 - 1;
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
