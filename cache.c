include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "first.h"
#include <math.h>


 int main( int argc, char** argv){

   int cacheSize, blockSize, numSets, assoc, r, x;
   char op;
   char* bin;
   int count = 0;


  FILE* traceFile = fopen(argv[5], "r");
  if (traceFile == NULL){
    printf( "File Not Found yerr");
    return 0;
  }

  cacheSize = atoi(argv[1]);
  blockSize = atoi(argv[2]);

  if(strcmp(argv[4], "direct") == 0){
    assoc = 1;
    numSets = cacheSize / blockSize;
  }else if(strcmp(argv[4], "assoc") == 0){
    assoc = cacheSize / blockSize;
    numSets = 1;
  }else{
    assoc = argv[4][6] - '0';
    numSets = cacheSize / (blockSize * assoc);
  }

  int setIndex = myLog2( numSets );
  int blockOffset = myLog2( blockSize );
  int tag = 48 -(blockOffset + setIndex);
  
  struct cache** table = createCache( numSets, assoc, tag );

  char oper;
  char address[20];
  char *temp, *f_bin;
  char *tag_bitsA, *index_bitsA;
  char *tag_bitsB, *index_bitsB;
  int i, j, decA, decB;

  while( fscanf(traceFile, " %c %s \n",  &oper, address) != EOF ){

    count = 0;
    char *binary = (char *) malloc(sizeof(char) * strlen(address) * 4);
    for(i = 2; i < strlen(address); i++){
      temp = convertHex(address[i]);
      for(j = 0; j < 4; j++){
        binary[count] = temp[j];
        count++;
      }
    }

    f_bin = xtend_Binary(binary);

    tag_bitsA = getTagA(f_bin, tag);
    index_bitsA = getIndexA(f_bin, tag, setIndex);
    decA = convertBin(index_bitsA, setIndex);

    update(assoc, table, tag_bitsA, decA, oper);

  }

  printf("Memory reads: %d\n", reads);
  printf("Memory writes: %d\n", writes);
  printf("Cache hits: %d\n", hits);
  printf("Cache misses: %d\n", miss);
  return 0;
}
