//
// Created by tao on 2021/4/18.
//

#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "ctime"
#define MAX_LINE_SIZE 100

//#2
typedef struct List2{
    char * spec = nullptr;
    struct List2 * next_brother_node = nullptr;
    struct List2 * child_node = nullptr;
} SpecList;


void insertSpecList(SpecList * root,char *specs[],const int order[]);
void deleteSpecList(SpecList * root,char *specs[],const int order[]);
void printSpecList(SpecList * root,const int order[]);
bool line2Specs(char *specs[],char * line);


char f1_path[] = "/home/web/ztedatabase/1/input1.csv";
char f2_path[] = "/home/web/ztedatabase/1/input2.csv";
FILE *file1,*file2;
clock_t  start,finish;

//#2
void insertSpecList(SpecList * root,char *specs[],const int order[]){
    if(specs == nullptr || root == nullptr) return;
    SpecList * move1 = root,*move2,*move3;

    while (move1->next_brother_node != nullptr){
        if(strcmp(move1->next_brother_node->spec,specs[order[0]]) == 0){//spec1 exist
            move2 = move1->next_brother_node->child_node;
            if(move2 == nullptr) return;
            while (move2->next_brother_node != nullptr){
                if(strcmp(move2->next_brother_node->spec,specs[order[1]]) == 0){//spec2 exist
                    move3 = move2->next_brother_node->child_node;
                    if(move3 == nullptr) return;
                    while (move3->next_brother_node != nullptr){
                        if(strcmp(move3->next_brother_node->spec,specs[order[2]]) == 0){//spec3 exist
                            return;
                        }
                        move3 = move3->next_brother_node;
                    }
                    //spec3 not exist
                    SpecList *temp = (SpecList *) malloc(sizeof(SpecList));
                    if (temp == nullptr) return;
                    temp->next_brother_node = nullptr;
                    temp->child_node = nullptr;
                    temp->spec = (char *) malloc(sizeof(char ) * strlen(specs[order[2]]));
                    if (temp->spec == nullptr) return;
                    strcpy(temp->spec, specs[order[2]]);
                    move3->next_brother_node = temp;
                    return;
                }
                move2 = move2->next_brother_node;
            }
            //spec2 not exist
            SpecList *temp2 = (SpecList *) malloc(sizeof(SpecList));
            SpecList *head3 = (SpecList *) malloc(sizeof(SpecList));
            SpecList *temp3 = (SpecList *) malloc(sizeof(SpecList));
            if (temp2 == nullptr || head3 == nullptr || temp3 == nullptr) return;
            temp3->spec = (char *) malloc(sizeof(char ) * strlen(specs[order[2]]));
            if (temp3->spec == nullptr) return;
            strcpy(temp3->spec, specs[order[2]]);
            head3->next_brother_node = temp3;
            head3->child_node = nullptr;
            head3->spec = nullptr;
            temp2->next_brother_node = nullptr;
            temp2->child_node = head3;
            temp2->spec = (char *) malloc(sizeof(char ) * strlen(specs[order[1]]));
            if (temp2->spec == nullptr) return;
            strcpy(temp2->spec, specs[order[1]]);
            move2->next_brother_node = temp2;
            return;
        }
        move1 = move1->next_brother_node;
    }
    //spec1 not exist
    SpecList *temp1 = (SpecList *) malloc(sizeof(SpecList));
    SpecList *temp2 = (SpecList *) malloc(sizeof(SpecList));
    SpecList *temp3 = (SpecList *) malloc(sizeof(SpecList));
    SpecList *head2 = (SpecList *) malloc(sizeof(SpecList));
    SpecList *head3 = (SpecList *) malloc(sizeof(SpecList));
    if (temp1 == nullptr || temp2 == nullptr || head3 == nullptr || head2 == nullptr || temp3 == nullptr) return;
    temp3->next_brother_node = nullptr;
    temp3->child_node = nullptr;
    temp3->spec = (char *) malloc(sizeof(char ) * strlen(specs[order[2]]));
    if (temp3->spec == nullptr) return;
    strcpy(temp3->spec, specs[order[2]]);
    head3->next_brother_node = temp3;
    head3->child_node = nullptr;
    head3->spec = nullptr;
    temp2->next_brother_node = nullptr;
    temp2->child_node = head3;
    temp2->spec = (char *) malloc(sizeof(char) * strlen(specs[order[1]]));
    if (temp2->spec == nullptr) return;
    strcpy(temp2->spec, specs[order[1]]);
    head2->next_brother_node = temp2;
    head2->child_node = nullptr;
    head2->spec = nullptr;
    temp1->next_brother_node = nullptr;
    temp1->child_node = head2;
    temp1->spec = (char *) malloc(sizeof(char) * strlen(specs[order[0]]));
    if (temp1->spec == nullptr) return;
    strcpy(temp1->spec, specs[order[0]]);
    move1->next_brother_node = temp1;
}


void deleteSpecList(SpecList * root,char *specs[],const int order[]){
    if(specs == nullptr || root == nullptr) return;
    SpecList * tmp;
    SpecList * move1 = root,*move2,*move3;
    while (move1->next_brother_node != nullptr){
        if(strcmp(move1->next_brother_node->spec,specs[order[0]]) == 0){
            move2 = move1->next_brother_node->child_node;
            if(move2 == nullptr) return;
            while (move2->next_brother_node != nullptr){
                if(strcmp(move2->next_brother_node->spec,specs[order[1]]) == 0){
                    move3 = move2->next_brother_node->child_node;
                    if(move3 == nullptr) return;
                    while (move3->next_brother_node != nullptr){
                        if(strcmp(move3->next_brother_node->spec,specs[order[2]]) == 0){//specs exist, execute delete
                            tmp = move3->next_brother_node;
                            move3->next_brother_node = tmp->next_brother_node;
                            free(tmp->spec);
                            tmp->spec = nullptr;
                            free(tmp);
                            tmp = nullptr;

                            if(move2->next_brother_node->child_node->next_brother_node == nullptr){// no any spec3 after this spec2
                                free(move2->next_brother_node->child_node); //head3
                                move2->next_brother_node->child_node = nullptr;
                                tmp = move2->next_brother_node;
                                move2->next_brother_node = tmp->next_brother_node;
                                free(tmp->spec);
                                tmp->spec = nullptr;
                                free(tmp);
                                tmp = nullptr;
                            }

                            if(move1->next_brother_node->child_node->next_brother_node == nullptr){//no any spec2 after this spec1
                                free(move1->next_brother_node->child_node);
                                move1->next_brother_node->child_node = nullptr;
                                tmp = move1->next_brother_node;
                                move1->next_brother_node = tmp->next_brother_node;
                                free(tmp->spec);
                                tmp->spec = nullptr;
                                free(tmp);
                                tmp = nullptr;
                            }
                            return;
                        }else
                            move3 = move3->next_brother_node;
                    }
                    return;
                }else
                    move2 = move2->next_brother_node;
            }
            return;
        }else
            move1 = move1->next_brother_node;
    }
}

void printSpecList(SpecList * root,const int order[]){
    if(root == nullptr) return;
    SpecList * move1 = root,*move2,*move3;
    char *specs[3] ;

    while(move1->next_brother_node != nullptr){
        move2 = move1->next_brother_node->child_node;
        while (move2->next_brother_node != nullptr){
            move3 = move2->next_brother_node->child_node;
            while (move3->next_brother_node != nullptr){
                specs[order[0]] = move1->next_brother_node->spec;
                specs[order[1]] = move2->next_brother_node->spec;
                specs[order[2]] = move3->next_brother_node->spec;
                printf("%s,%s,%s\n",specs[0],specs[1],specs[2]);
                move3 = move3->next_brother_node;
            }
            move2 = move2->next_brother_node;
        }
        move1 = move1->next_brother_node;
    }
}


bool line2Specs(char *specs[],char * line){
    if(line == nullptr) return false;
    char *tmp = nullptr;
    tmp = strtok(line,",");
    if (tmp == nullptr) return false;
    strcpy(specs[0],tmp);
    tmp = strtok(nullptr,",");
    if (tmp == nullptr) return false;
    strcpy(specs[1],tmp);
    tmp = strtok(nullptr,"\n");
    if (tmp == nullptr) return false;
    strcpy(specs[2],tmp);
    return true;
}

int main(){
    start = clock();

    char f1_line[MAX_LINE_SIZE] = "";
    char f2_line[MAX_LINE_SIZE] = "";

    char *specs[3] = {nullptr,nullptr,nullptr};
    specs[0] = (char *) malloc(sizeof (char) * MAX_LINE_SIZE);
    specs[1] = (char *) malloc(sizeof (char) * MAX_LINE_SIZE);
    specs[2] = (char *) malloc(sizeof (char) * MAX_LINE_SIZE);

    if(specs[0] == nullptr || specs[1] == nullptr || specs[2] == nullptr)
        return -1;

    if ((file1 = fopen(f1_path,"r")) == nullptr || (file2 = fopen(f2_path,"r")) == nullptr ){
        printf("file open error!");
        return -1;
    }


    int order[3] = {0,1,2};     //按照某种spec order存储或者读取，123表示1


    SpecList * root = (SpecList *)malloc(sizeof (SpecList));
    if (root == nullptr) return -1;

    while (fgets(f1_line,sizeof (char) * MAX_LINE_SIZE,file1)){
        char *p = strchr(f1_line,',');
        if (p == nullptr || p+1 == nullptr || strcmp(p+1,"\n") == 0) continue;
        if(line2Specs(specs,p+1))
            insertSpecList(root,specs,order);
    }

    while (fgets(f2_line,sizeof (char) * MAX_LINE_SIZE,file2)){
        char *p = strchr(f2_line,',');
        if (p == nullptr || p+1 == nullptr || strcmp(p+1,"\n") == 0) continue;
        if(line2Specs(specs,p+1))
            deleteSpecList(root, specs,order);
    }

    printSpecList(root,order);

    fclose(file1);
    fclose(file2);

    finish = clock();
    double total_time = (double)(finish - start)/CLOCKS_PER_SEC;
    printf("total time:%.4f sec\n",total_time);
    return 0;
}
