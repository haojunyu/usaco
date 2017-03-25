/*
ID: haojuny2
LANG: C
PROG: gift1
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXPEOPLE 10
#define MAXLEN 16
typedef struct Person{
  char name[MAXLEN];
  int gifts;
  int order;
} Person;

Person people[MAXPEOPLE];

int CompByName(const void *a, const void *b);
int CompByOrder(const void *a, const void *b);

int main(){
  FILE *fin = fopen("gift1.in", "r");
  FILE *fout = fopen("gift1.out", "w");

  int i,j;
  int NP, money, num;
  Person *target, tmp;

  memset(people, 0, sizeof(people));
  fscanf(fin, "%d\n", &NP);
  for(i=0; i<NP; i++){
    fscanf(fin, "%s\n", people[i].name);
    people[i].gifts = 0;
    people[i].order = i;
  }
  
  // 按照name排序结构体数组
  qsort(people, NP, sizeof(Person), CompByName);

  for(i=0; i<NP; i++){
    fscanf(fin, "%s\n", tmp.name);
    fscanf(fin, "%d %d\n", &money, &num);
    if(num != 0){
      int gift = money / num;
      int give = 0 - gift * num;
      // 设置giver
      target = bsearch(&tmp, people, NP, sizeof(Person), CompByName);
      if(target == NULL){
        printf("can't find node %s\n", tmp.name);
        exit(0);
      }else{
        target->gifts += give;
      }
      // 设置receiver
      for(j=0; j<num; j++){
        fscanf(fin, "%s\n", tmp.name);
        target = bsearch(&tmp, people, NP, sizeof(Person), CompByName);
        if(target == NULL){
          printf("can't find node %s\n", tmp.name);
          exit(0);
        }else{
          target->gifts += gift;
        }
      }
    }
  }
  
  // 按order排序
  qsort(people, NP, sizeof(Person), CompByOrder);

  for(i=0; i<NP; i++){
    fprintf(fout, "%s %d\n", people[i].name, people[i].gifts);
    /* printf("%s %d\n", people[i].name, people[i].gifts); */
  }

  return 0;
}


// @brief   按名称进行比较
// @param   a   Person结构体
//          b   Person结构体
// @return  strcmp(a.name, b.name)
int CompByName(const void *a, const void *b){
  return strcmp(((Person *)a)->name, ((Person *)b)->name);
}

// @brief   按次序进行比较
// @param   a   Person结构体
//          b   Person结构体
// @return  a.order-b.order
int CompByOrder(const void *a, const void *b){
  return ((Person *)a)->order - ((Person *)b)->order;
}
