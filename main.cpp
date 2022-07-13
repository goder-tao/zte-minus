
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "ctime"
#define MAX_LINE_SIZE 100

//#1
typedef struct List
{
    char *line;
    struct List * next;
} LineList;

void removeAll(LineList *head,char *comp_line);
void removeRepeation(LineList *first);



char f1_path[] = "/home/web/ztedatabase/3/input1.csv";
char f2_path[] = "/home/web/ztedatabase/3/input2.csv";
FILE *file1,*file2;
clock_t  start,finish;





//#1
//function
char *strRemove(char *str,char ch){
    static char res[60];
    printf("res size:%d, res:%s\n", sizeof (res),res);
    int k = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != ch)
            res[k++] = str[i];
    }
    res[k] = '\0';
    printf("res size:%d, res:%s\n", sizeof (res),res);
    return res;
}


void removeAll(LineList *head,char *comp_line){
    LineList *move = head;
    while (move->next != NULL){
        if(strcmp(move->next->line, comp_line) == 0){
            LineList *tmp = move->next;
            move->next = tmp->next;
            free(tmp);
            tmp = NULL;
        } else{
            move = move->next;
        }
    }
}

void removeRepeation(LineList *first){
    LineList *tmp = first;
    LineList *move = first;
    while (tmp != NULL){
        while (move->next != NULL){
            if(strcmp(tmp->line,move->next->line) == 0){
                LineList *p = move->next;
                move->next = p->next;
                free(p);p = NULL;
            }else{
                move = move->next;
            }
        }
        tmp = tmp->next;
        move = tmp;
    }
}

int main(){
    start = clock();

    char f1_line[MAX_LINE_SIZE];
    char f2_line[MAX_LINE_SIZE];
    if ((file1 = fopen(f1_path,"r")) == NULL || (file2 = fopen(f2_path,"r")) == NULL ){
        printf("file open error!");
        return -1;
    }

    //printf("13123 %d",sizeof (LineList));

    //LineList *head = (LineList *)(malloc(sizeof(LineList)));
    LineList *head = (LineList *)(malloc(sizeof (LineList)));
    if(head == NULL) return -1;
    LineList *move = head;

    while ( fgets(f1_line,sizeof (char )* MAX_LINE_SIZE,file1)){
        LineList *tmp = (LineList *)(malloc(sizeof (LineList)));
        if(tmp == NULL) return -1;
        tmp->line = (char *)(malloc(strlen(f1_line) + 1));    //直接分配strlen的空间可能会导致'\0'的丢失
        if(tmp->line == NULL) return -1;
        tmp->next = NULL;

        //去空行
        char *p = NULL;
//        p = strchr(f1_line,',');
//        if(p == NULL) continue;
//        strcpy(tmp->line,p+1);
        strtok(f1_line,",");
        p = strtok(NULL,"");
        strcpy(tmp->line,"");

        move->next = tmp;
        move = tmp;
    }

    while ( fgets(f2_line,sizeof (char )* MAX_LINE_SIZE,file2)){
        char *p = NULL;
        p = strchr(f2_line,',');
        if (p == NULL) continue;
        removeAll(head,p + 1);
//        strtok(f2_line,",");
//        removeAll(head, strtok(NULL,""));
    }

    removeRepeation(head->next);
    //输出到标准输出
    move = head;
    while (move->next != NULL) {
        move = move->next;
        printf("%s",move->line);
        //printf("len:%d  %s", strlen(move->line),move->line);
    }
    fclose(file1);
    fclose(file2);

    finish = clock();
    double total_time = (double)(finish - start)/CLOCKS_PER_SEC;
    printf("total time:%.4f sec",total_time);
    return 0;
}