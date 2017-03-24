// Source : http://train.usaco.org/usacoprob2?a=pauYUPcUIws&S=gift1
// Title  : Greedy Gift Givers
// Author : David
// Date   : 2017-03-23

/*******************************************************************************
**  DESCRIPTION:
* A group of NP (2 ≤ NP ≤ 10) uniquely named friends has decided to exchange gifts of money. Each of these friends might or might not give some money to any or all of the other friends. Likewise, each friend might or might not receive money from any or all of the other friends. Your goal in this problem is to deduce how much more money each person gives than they receive.
*
* The rules for gift-giving are potentially different than you might expect. Each person sets aside a certain amount of money to give and divides this money evenly among all those to whom he or she is giving a gift. No fractional money is available, so dividing 3 among 2 friends would be 1 each for the friends with 1 left over -- that 1 left over stays in the giver's "account".
*
* In any group of friends, some people are more giving than others (or at least may have more acquaintances) and some people have more money than others.
*
* Given a group of friends, no one of whom has a name longer than 14 characters, the money each person in the group spends on gifts, and a (sub)list of friends to whom each person gives gifts, determine how much more (or less) each person in the group gives than they receive.
*
*
**  INPUT:
* Line 1:           The single integer, NP
* Lines 2..NP+1:    Each line contains the name of a group member
* Lines NP+2..end:  NP groups of lines organized like this:
*                   The first line in the group tells the person's name who will be giving gifts.
*                   The second line in the group contains two numbers: The initial amount of money (in the range 0..2000) to be divided up into gifts by the giver and then the number of people to whom the giver will give gifts, NGi (0 ≤ NG_i ≤ NP-1).
*                   If NG_i is nonzero, each of the next NGi lines lists the name of a recipient of a gift.
*
* Sample:
* 5
* dave
* laura
* owen
* vick
* amr
* dave
* 200 3
* laura
* owen
* vick
* owen
* 500 1
* dave
* amr
* 150 2
* vick
* owen
* laura
* 0 2
* amr
* vick
* vick
* 0 0
*
*
** OUTPUT:
* The output is NP lines, each with the name of a person followed by a single blank followed by the net gain or loss (final_money_value - initial_money_value) for that person. The names should be printed in the same order they appear starting on line 2 of the input.
*
* All gifts are integers. Each person gives the same integer amount of money to each friend to whom any money is given, and gives as much as possible that meets this constraint. Any money not given is kept by the giver.
*
* Sample:
* dave 302
* laura 66
* owen -359
* vick 141
* amr -150
*
*******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
  char name[16];
  int gifts;
  struct Node *left;
  struct Node *right;
} tNode;


tNode *InsertOrderTree(tNode *root, char *str);
void PrintOrderTree(tNode *root);


int main(){
  FILE *fin = fopen("gift1.in", "r");
  FILE *fout = fopen("gift1.out", "w");

  int i;
  int NP;
  char str[16];
  tNode *orderTree = NULL;

  fscanf(fin, "%d\n", &NP);
  for(i=0; i<NP; i++){
    fscanf(fin, "%s\n", str);
    orderTree = InsertOrderTree(orderTree, str);
    if(orderTree == NULL){
      printf("%s fail to insert into orderTree!", str);
    }
  }
  
  PrintOrderTree(orderTree);

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
