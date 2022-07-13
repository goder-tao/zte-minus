//
// Created by tao on 2021/4/10.
//


#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "random"

char file1_path[] = "/home/web/ztedatabase/3/input1.csv";
char file2_path[] = "/home/web/ztedatabase/3/input2.csv";
FILE *file1,*file2;

char desc1[][20] = {"数据库","芯片","单片机","计算机网络","云计算","Docker","K8s"};
char desc2[][20] = {"硬件","软件","平台","中台","数据中心","边缘云"};
char desc3[][20] = {"mysql","mongdb","sql server","faas","paas","iaas","SaaS","树莓派","寒光芯片","麒麟9000","骁龙888"};

void newLine(int id,char line[]){
    int i = rand() % 200000;
    int j = rand() % 200000;
    int k = rand() % 200000;
    sprintf(line,"%d,\"%d\",\"%d\",\"%d\"\n",id,i,j,k);
}

int main(){
    file1 = fopen(file1_path,"w");
    file2 = fopen(file2_path,"w");
    char newline[70];
    for(int i = 0;i < 400000;i++){
        newLine(i,newline);
        fputs(newline,file1);
        newLine(i,newline);
        fputs(newline,file2);
    }

    fclose(file1);
    fclose(file2);

    return 0;
}



char prime_table_path[] = "/home/web/ztedatabase/prime_table.csv";



int prime(int n){
    FILE * prime_file = fopen(prime_table_path,"w");
    char  str[70];

    int i;
    int count = 0;
    bool *prime = new bool[n+1];
    for(i=2;i<n;i++){
        prime[i] = true;
    }

    for(i=2;i<=n;i++){
        if(prime[i]){
            sprintf(str,"%d,",i);
            fputs(str,prime_file);
            count++;
            if(count != 0 && count % 20 == 0)
                fputs("\n",prime_file);
            for(int j=i+i;j<n;j+=i){
                prime[j] = false;
            }
        }
    }
    return 0;
}

//int main(){
//    prime(100000);
//    return 0;
//}
