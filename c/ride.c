/*
ID: haojuny2
LANG: C
PROG: ride
*/
#include<stdio.h>
#include<string.h>

int main(){
    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");

    char comet[8], group[8];
    int com=1, gro=1, i;
    fscanf(fin, "%s\n", comet);
    fscanf(fin, "%s\n", group);
    
    for(i=0; i<strlen(comet); i++){
      com = com * (comet[i]-'A'+1);
      com = com % 47;
    }

    for(i=0; i<strlen(group); i++){
      gro = gro * (group[i]-'A'+1);
      gro = gro % 47;
    }

    if(gro == com){
      fprintf(fout, "GO\n");
    }else{
      fprintf(fout, "STAY\n");
    }
    return(0);
}

