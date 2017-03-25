/*
ID: haojuny2
LANG: C
PROG: gift1
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
  char name[16];
  int gifts;
  struct Node *left;
  struct Node *right;
} tNode;

char gNames[10][16];

tNode *InsertOrderTree(tNode *root, char *str);
tNode *FindOrderTree(tNode *root, char *str);
void PrintOrderTree(tNode *root);


int main(){
  FILE *fin = fopen("gift1.in", "r");
  FILE *fout = fopen("gift1.out", "w");

  int i,j;
  int NP, money, num;
  char str[16];
  tNode *orderTree = NULL, *target;

  memset(gNames, 0, sizeof(gNames));
  fscanf(fin, "%d\n", &NP);
  for(i=0; i<NP; i++){
    fscanf(fin, "%s\n", str);
    strcpy(gNames[i], str);
    orderTree = InsertOrderTree(orderTree, str);
    if(orderTree == NULL){
      printf("%s fail to insert into orderTree!", str);
    }
  }
  
  // 设置二叉排序树
  for(i=0; i<NP; i++){
    fscanf(fin, "%s\n", str);
    fscanf(fin, "%d %d\n", &money, &num);
    if(num != 0){
      int gift = money / num;
      int give = 0 - gift * num;
      // 设置giver
      target = FindOrderTree(orderTree, str);
      if(target == NULL){
        printf("can't find node %s\n", str);
        exit(0);
      }else{
        target->gifts += give;
      }
      // 设置receiver
      for(j=0; j<num; j++){
        fscanf(fin, "%s\n", str);
        target = FindOrderTree(orderTree, str);
        if(target == NULL){
          printf("can't find node %s\n", str);
          exit(0);
        }else{
          target->gifts += gift;
        }
      }
    }
  }
  
  // 按原序输出
  for(i=0; i<NP; i++){
    target = FindOrderTree(orderTree, gNames[i]);
    fprintf(fout, "%s %d\n", target->name, target->gifts);
  }

  // 打印二叉排序树
  //PrintOrderTree(orderTree);

  return 0;
}


// @brief   向二叉排序树插入节点
// @param   root  二叉排序树的根节点指针
//          str   插入的新节点名称
// @return  二叉排序树的根节点
tNode *InsertOrderTree(tNode *root, char *str){
  int condi;

  if(root == NULL){
    // str为新节点
    tNode *Node = (tNode *)malloc(sizeof(tNode));
    if(Node == NULL)
      // 无法申请节点空间，直接返回NULL
      return NULL;
    strcpy(Node->name, str);
    Node->gifts = 0;
    Node->left = NULL;
    Node->right = NULL;
    root = Node;
  }else if((condi = strcmp(str, root->name)) == 0){
    // 该节点已经存在
  }else if(condi < 0){
    root->left = InsertOrderTree(root->left, str);
  }else{
    root->right = InsertOrderTree(root->right, str);
  }
  return root;
}

// @brief   在二叉排序树中查找节点名为str的节点
// @param   root  二叉排序树的根节点指针
//          str   查找新节点的名称
// @return  查找到的节点指针或NULL
tNode *FindOrderTree(tNode *root, char *str){
  int condi;

  if(root == NULL){
    return NULL;
  }else if((condi = strcmp(str, root->name)) == 0){
    // 该节点已经找到
    return root;
  }else if(condi < 0){
    return FindOrderTree(root->left, str);
  }else{
    return FindOrderTree(root->right, str);
  }
}


// @brief   按递增顺序输出二叉排序树节点
// @param   root  二叉排序树的根节点指针
// @return  void
void PrintOrderTree(tNode *root){
  if(root == NULL){
    return;
  }else{
    // 打印左边
    PrintOrderTree(root->left);
    
    printf("name:%s\t\tgifts:%d\n", root->name, root->gifts);

    // 打印右边
    PrintOrderTree(root->right);
  }
}
