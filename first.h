#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

int hits = 0;
int miss = 0;
int reads = 0;
int writes = 0;

struct cache{
  char* tag;
  int rank;
  int valid;
};

void update(int assoc, struct cache **table, char *tag, int dec, char oper){

  int i, j;
  int found = 0;

  struct cache **ptr = table;

  for(i = 0; i < assoc; i++){

    if((ptr[dec][i].valid == 1) && (strcmp(ptr[dec][i].tag, tag) == 0)){

      found = 1;

      if(oper == 'W'){

        hits++;
        writes++;

      }else if(oper == 'R'){

        hits++;

      }
      break;
    }
  }
 if(found == 0){

    for(i = 0; i < assoc; i++){

      if(ptr[dec][i].rank == assoc){

        strcpy(ptr[dec][i].tag, tag);
        ptr[dec][i].rank = 1;

        for(j = 0; j < i; j++){
          ptr[dec][j].rank++;
        }

        for(j = i + 1; j < assoc; j++){
          ptr[dec][j].rank++;
        }

        break;
      }
      else if(ptr[dec][i].valid == 0){

        ptr[dec][i].valid = 1;
        ptr[dec][i].rank = 1;
        strcpy(ptr[dec][i].tag, tag);

        for(j = 0; j < i; j++){

          ptr[dec][j].rank++;

        }
        break;
      }
    }

    if(oper == 'W'){

      miss++;
      reads++;
      writes++;

    }
    else if (oper == 'R'){

      miss++;
      reads++;

    }
  }
  return;
}


int convertBin(char *index_bits, int set_index){
  if(set_index == 0){
    return 0;
  }
  int sum = 0;
  int base = 1;
  int val = 0, i;
  for(i = set_index - 1; i >= 0; i--){
    if(index_bits[i] == '0'){
      val = 0;
    }else{
      val = 1;
    }
    sum = sum + val * base;
    base = base * 2;
  }
  return sum;
}
char *getIndexA(char *f_bin, int tag, int set_index){
  if(set_index == 0){
    return "NULL";
  }
  char *set_bitsA = (char *) malloc(sizeof(char) * (set_index + 1));
  int i;
  int index = tag;
  for(i = 0; i < set_index; i++){
    set_bitsA[i] = f_bin[index];
    index++;
  }
  set_bitsA[set_index] = '\0';
  return (char *) set_bitsA;
}

char *getTagA(char *f_bin, int tag){
  char *tag_bitsA = (char *) malloc(sizeof(char) * (tag + 1));
  int i;

  for(i = 0; i < tag; i++){
    tag_bitsA[i] = f_bin[i];
  }
  tag_bitsA[tag] = '\0';
  return (char *) tag_bitsA;
}
// returns 0 if tag is in set, else return 1                                    
int check ( struct cache* set, char* tag, int ways ){

  int i;

  for( i = 0 ; i < ways ; i++ ){

    if ( strcmp ( set[i].tag, tag ) == 0 ) return 0 ;

  }
  return 1;
}

// if set is full return 0                                                      
int checkFull( struct cache* set, int ways ){

  int i;

  for( i = 0 ; i < ways ; i++ ){

    if ( set[i].rank == ways ) return 0;
  }

  return 1;
}

// find item with highest order cache to replace                                
int findReplaceIndex( struct cache* set, int ways ){

  int i;

  for ( i = 0 ; i < ways ; i++ ){

    if ( set[i].rank == ways ) return i;
  }

  printf("shit be buggin");
  return 0;
}
int findZeroRank( struct cache* set, int ways ){

  int i;

  for ( i = 0 ; i <ways ; i++ ){

    if ( set[i].rank == 0 ) return i;
  }

  printf("shit be buggin");
  return 0;

}



struct cache* updateRank( struct cache* set, int ways , int skip){

  int i;

  for ( i = 0 ; i < ways ; i++ ){

    if ( set[i].rank != 0 && i != skip )
      set[i].rank++;

  }

  return set;
}
struct cache **createCache(int numSets, int ways, int tag){

  int i, j, x;
  struct cache **table = (struct cache **) malloc(sizeof(struct cache*) * numSe\
ts);
  for(i = 0; i < numSets; i++){
    table[i] = (struct cache *) malloc(sizeof(struct cache) * ways);
  }
  for(i = 0; i < numSets; i++){
    for(j = 0; j < ways; j++){
      table[i][j].tag = (char *) malloc(sizeof(char) * (tag + 1));
      table[i][j].valid = 0;
      table[i][j].rank = 0;
      for(x = 0; x < tag; x++){
        table[i][j].tag[x] = '0';
      }
      table[i][j].tag[tag] = '\0';
    }
  }
  return table;
}
int myLog2( int x ) {

  int count = 0;
  while ( x > 1 ){
    x /= 2;
    count++;
  }
  return count;
}

void direct_m_bitLoad( char * bin, char * indArray, char * tagArray, int indSta\
rt, int offStart ){

  int x = 0;
  int i;

  for( i = 0 ; i < indStart ; i++ ){

    tagArray[i] = bin[i];

  }

  for( i = indStart ; i < offStart ; i++ ){

    indArray[x] = bin[i];
    x++;
  }
}
int power( int base , int pow ){

  int result = 1;
  int count = pow;
  while (count != 0){
    result *= base;
    count--;
  }
  return result;
}

int bin2Dec( char * bin ){

  int result = 0;
  int i;

  for( i = 0 ; i < strlen(bin) ; i++ ){
    if ( bin[i] == '0' ) continue;
    result += power( 2 , strlen(bin) - 1 - i ) ;
  }
  return result;
}
char *xtend_Binary(char *binary){
  int missing_bits = 48 - strlen(binary);
  char *bin = (char *) malloc(sizeof(char) * (strlen(binary) + missing_bits + 1\
));
  int i;
  for(i = 0; i < missing_bits; i++){
    bin[i] = '0';
  }
  bin[missing_bits] = '\0';
  strcat(bin, binary);
  return (char *) bin;
}
char *hex2Bin(char token){
  char *binary = (char *) malloc(sizeof(char) * 5);
  switch(token){
  case '0':
    strcat(binary, "0000\0"); break;
  case '1':
    strcat(binary, "0001\0"); break;
  case '2':
    strcat(binary, "0010\0"); break;
  case '3':
    strcat(binary, "0011\0"); break;
  case '4':
    strcat(binary, "0100\0"); break;
  case '5':
    strcat(binary, "0101\0"); break;
  case '6':
    strcat(binary, "0110\0"); break;
  case '7':
    strcat(binary, "0111\0"); break;
  case '8':
    strcat(binary, "1000\0"); break;
  case '9':
    strcat(binary, "1001\0"); break;
  case 'a':
    strcat(binary, "1010\0"); break;
  case 'b':
    strcat(binary, "1011\0"); break;
  case 'c':
    strcat(binary, "1100\0"); break;
  case 'd':
    strcat(binary, "1101\0"); break;
  case 'e':
    strcat(binary, "1110\0"); break;
  case 'f':
    strcat(binary, "1111\0"); break;
  default:
    break;
  }
  return (char *) binary;
}
char* getBinary ( char* address ){


  char* bin, *temp;
  int i,j,count;
  count = 0;

  char *binary = (char *) malloc(sizeof(char) * strlen(address) * 4);
  for(i = 2; i < strlen(address); i++){
    temp = hex2Bin(address[i]);
    for(j = 0; j < 4; j++){
      binary[count] = temp[j];
      count++;
    }
  }

  bin = xtend_Binary(binary);
  free(binary);
  return bin;
}
char *convertHex(char slot){
  char *binary = (char *) malloc(sizeof(char) * 5);
  switch(slot){
  case '0':
    strcat(binary, "0000\0"); break;
  case '1':
    strcat(binary, "0001\0"); break;
  case '2':
    strcat(binary, "0010\0"); break;
  case '3':
    strcat(binary, "0011\0"); break;
  case '4':
    strcat(binary, "0100\0"); break;
  case '5':
    strcat(binary, "0101\0"); break;
  case '6':
    strcat(binary, "0110\0"); break;
  case '7':
    strcat(binary, "0111\0"); break;
  case '8':
    strcat(binary, "1000\0"); break;
  case '9':
    strcat(binary, "1001\0"); break;
  case 'a':
    strcat(binary, "1010\0"); break;
  case 'b':
    strcat(binary, "1011\0"); break;
  case 'c':
    strcat(binary, "1100\0"); break;
  case 'd':
    strcat(binary, "1101\0"); break;
  case 'e':
    strcat(binary, "1110\0"); break;
  case 'f':
    strcat(binary, "1111\0"); break;
  default:
    break;
  }
  return (char *) binary;
}

