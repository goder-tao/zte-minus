
/* 改进:
 *  1、采用双层水平分割表，二层每个节点连接一棵hash树,树采取从小层向大层递增的结构以保证节点利用率
 *
 *
 *
 *
 * */


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
#define MAX_LINE_SIZE 1000
#define DEVISION_TREE_FIRST_LEVEL 20
#define DEVISION_TREE_LEVEL_COUNT 1

#define DEBUG true
#define PRINT_RES true
#define DEVISION1_COUNT 401
#define DEVISION2_COUNT 3


const int prime_number[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,
                            73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,
                            179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,
                            283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,
                            419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,
                            547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,
                            661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,
                            811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,
                            947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,
                            1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,    //200
                            1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,
                            1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,
                            1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,
                            1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,
                            1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,
                            1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,
                            2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,
                            2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,
                            2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,
                            2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,    //400
                            2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,
                            2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,
                            3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,
                            3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,
                            3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571,
                            3581,3583,3593,3607,3613,3617,3623,3631,3637,3643,3659,3671,3673,3677,3691,3697,3701,3709,3719,3727,
                            3733,3739,3761,3767,3769,3779,3793,3797,3803,3821,3823,3833,3847,3851,3853,3863,3877,3881,3889,3907,
                            98953,98963,98981,98993,98999,99013,99017,99023,99041,99053,99079,99083,99089,99103,99109,99119,99131,99133,99137,99139,
                            99149,99173,99181,99191,99223,99233,99241,99251,99257,99259,99277,99289,99317,99347,99349,99367,99371,99377,99391,99397,
                            99401,99409,99431,99439,99469,99487,99497,99523,99527,99529,99551,99559,99563,99571,99577,99581,99607,99611,99623,99643,    //600
                            99661,99667,99679,99689,99707,99709,99713,99719,99721,99733,99761,99767,99787,99793,99809,99817,99823,99829,99833,
                            1213,1217,1223,10069,10079,10091,25999,32609,50069,99961,99971,99989,99991
};


/*
 * struct definition
 */
typedef struct TreeLevel{
    int16_t level = -1;   //为新增一层提供支持
    int store = 0;  //当前存储的节点数
    struct Node * Nodes = nullptr;
    struct TreeLevel *next_level = nullptr;  //下一个spec
}SpecTreeLevel;

typedef struct Node{
    char * spec = nullptr;
    bool occupied = false;
}SpecNode;

typedef struct Tree{
    struct TreeLevel * head = nullptr;
}SpecMapTree;

struct HashDevision2{
    struct Tree * root = nullptr;
};

struct HashDevision1{
    struct HashDevision2 * devision2 = nullptr;
};

/*
 * function definition
 */

unsigned int  BKDRHashCode(char * str);
SpecMapTree * createTree(int first_level,int level_count,bool reverse);
bool line2Specs(char *specs[],char * line);
bool insertFirstNodeOfNewLevel(SpecTreeLevel *Level,char *spec, unsigned int hash_code,int level,bool reverse);
bool insertNodeOfLevel(SpecTreeLevel *Level,char *spec,unsigned int index);
void trim(char des[],char * str,int head,int tail);
void printTime(clock_t finish_t,char *type);
HashDevision1 * createDevision1();
void use_rate(HashDevision1 * devision1,char * use_res);
void insertDevision1(HashDevision1 * devision1,char * line);
void deleteDevision1(HashDevision1 * devision1,char * line);
void printDevision1(HashDevision1 * devision1);
void insertSpecMapTreeOfDevision(SpecMapTree * root,char * line,unsigned int hash_code);


/*
 * global var definition
 */
char f1_path[] = "/home/web/ztedatabase/3/input1.csv";
char f2_path[] = "/home/web/ztedatabase/3/input2.csv";
char mem_path[] = "/home/web/ztedatabase/mem";
char command[100];
FILE *file1,*file2,*mem;
clock_t  start,finish_insert,finish_delete,finish_print;
int total_mem = 0,start_mem = 0,insert_mem = 0;

void insertDevision1(HashDevision1 * devision1,char * line){
    if(devision1 == nullptr || line == nullptr){return;}
    unsigned int hash_code = BKDRHashCode(line);
    int devision1_index = hash_code % DEVISION1_COUNT;
    int devision2_index = hash_code % DEVISION2_COUNT;

    if(devision1[devision1_index].devision2[devision2_index].root == nullptr){//null tree
        do{
            devision1[devision1_index].devision2[devision2_index].root = createTree(DEVISION_TREE_FIRST_LEVEL,DEVISION_TREE_LEVEL_COUNT,false);
        } while (devision1[devision1_index].devision2[devision2_index].root == nullptr);
    }
    insertSpecMapTreeOfDevision(devision1[devision1_index].devision2[devision2_index].root,line,hash_code);
}
void deleteDevision1(HashDevision1 * devision1,char * line){
    if (devision1 == nullptr || line == nullptr) return;
    unsigned int hash_code = BKDRHashCode(line);
    int devision1_index = hash_code % DEVISION1_COUNT,devision2_index = hash_code % DEVISION2_COUNT;
    int level_index;
    SpecTreeLevel * move;
    if(devision1[devision1_index].devision2[devision2_index].root != nullptr){
       move = devision1[devision1_index].devision2[devision2_index].root->head;
        while (move->next_level != nullptr){
            level_index = hash_code % prime_number[move->next_level->level];
            if(move->next_level->Nodes[level_index].occupied && strcmp(move->next_level->Nodes[level_index].spec,line) == 0){
                //find
                move->next_level->store--;
                move->next_level->Nodes[level_index].occupied = false;
                if(move->next_level->store == 0){
                    SpecTreeLevel * tmp_level = move->next_level;
                    move->next_level = tmp_level->next_level;
                    free(tmp_level->Nodes);
                    tmp_level->Nodes = nullptr;
                    free(tmp_level);
                    tmp_level = nullptr;
                }
                return;
            }
            move = move->next_level;
        }
    }else{//no tree
        return;
    }
}
void printDevision1(HashDevision1 * devision1){
    SpecTreeLevel * move;
    for(int i = 0; i < DEVISION1_COUNT; i++){
        for(int j = 0; j < DEVISION2_COUNT; j++){
            if(devision1[i].devision2[j].root != nullptr){
                move = devision1[i].devision2[j].root->head;
                while (move->next_level != nullptr){
                    for(int k = 0; k < prime_number[move->next_level->level]; k++){
                        if(move->next_level->Nodes[k].occupied){
                            printf("%s\n",move->next_level->Nodes[k].spec);
                        }
                    }
                    move = move->next_level;
                }
            }
        }
    }
}

void insertSpecMapTreeOfDevision(SpecMapTree * root,char * line,unsigned int hash_code){
    if(root == nullptr || root->head == nullptr) return;
    SpecTreeLevel * move = root->head;
    int index;
    while (move->next_level != nullptr){
        index = hash_code % prime_number[move->next_level->level];
        if(move->next_level->Nodes[index].occupied && strcmp(move->next_level->Nodes[index].spec,line) == 0){//exist
            return;
        } else if(!move->next_level->Nodes[index].occupied){
            insertNodeOfLevel(move->next_level,line,hash_code % prime_number[move->next_level->level]);
            move->next_level->store++;
            move->next_level->Nodes[index].occupied = true;
            return;
        }
        move = move->next_level;
    }
    //move->next_level = NULL
    SpecTreeLevel * tmp_level = nullptr;
    do{
        tmp_level = (SpecTreeLevel *) malloc(sizeof (SpecTreeLevel));
    } while (tmp_level == nullptr);
    insertFirstNodeOfNewLevel(tmp_level,line,hash_code,move->level, false);
    tmp_level->store++;
    tmp_level->Nodes[hash_code % prime_number[tmp_level->level]].occupied = true;
    move->next_level = tmp_level;
}

HashDevision1 * createDevision1(){
    HashDevision1 * devision1 = nullptr;
    do{
        devision1 = (HashDevision1 *) malloc(sizeof (HashDevision1) * DEVISION1_COUNT);
    } while (devision1 == nullptr);
    for(int i = 0; i < DEVISION1_COUNT; i++){
        do{
            devision1[i].devision2 = (HashDevision2 *) malloc(sizeof (HashDevision2) * DEVISION2_COUNT);
        } while (devision1[i].devision2 == nullptr);
    }
    return devision1;
}

void printTime(clock_t finish_t,char * type){
    double total_time = (double)(finish_t - start)/CLOCKS_PER_SEC;
    printf("%s time:%.4f sec\n",type,total_time);
}


void trim(char des[],char * str,int head,int tail){
    int i = head+1,j = tail-1,k = 1;
    des[0] = '\"';
    while ( i<=j && isspace(*(str+i))) i++;
    while ( i<j && isspace(*(str+j))) j--;
    if(i==head+1 && j == tail-1){
        strncpy(des,str+head,tail-head+1);
        des[tail-head+1] = '\0';
    }else{
        for(; k < (j-i)+2;k++)
            des[k] = *(str+i+k-1);
        des[k] = '\"';
        des[k+1] = '\0';
    }
}



bool insertNodeOfLevel(SpecTreeLevel *Level,char *spec,unsigned int index){
    do{
        Level->Nodes[index].spec = (char *) malloc(sizeof (char) * strlen(spec) + 1);
    }while (Level->Nodes[index].spec == nullptr);
    strcpy(Level->Nodes[index].spec,spec);
    //可以先赋值，但是不能先确认，后面可能会有错误导致当前的操作无效
    return true;
}


bool insertFirstNodeOfNewLevel(SpecTreeLevel *Level,char *spec,unsigned  int hash_code,int level,bool reverse){
    if(level < 0) return false;
    if(reverse) {
        Level->level = level - 1;
    } else{
        Level->level = level + 1;
    }
    if(Level->level < 0){
        //printf("level < 0 error!\n");
        return false;
    }
    do{
        Level->Nodes = (SpecNode *) malloc(sizeof (SpecNode) * prime_number[Level->level]);
    }while (Level->Nodes == nullptr);
    return insertNodeOfLevel(Level,spec,hash_code % prime_number[Level->level]);
}


unsigned int BKDRHashCode(char* str)
{
    int i = 0;
//BKDRHash
    unsigned int seed = 31;    // 31 131 1313 13131 131313 etc.. 37
    //long double seed1;
    unsigned int key = 0;

    while (*(str+i))
    {
        key = key * seed + (*(str+i));
        i++;
    }

    return ( key & 0x7fffffff);
}


bool line2Specs(char *specs[],char *line){
    if(line == nullptr) return false;
    int head = 0,tail = 1,lenght = strlen(line),index = 0;
    while (tail < lenght-1 && index < 2){
        if(*(line+tail) == ',' && *(line+tail-1) == '\"' && *(line+tail+1) == '\"'){
            trim(specs[index],line,head,tail-1);
            head = tail+1;
            tail += 2;
            index++;
        } else{
            tail++;
        }
    }
    if(tail == lenght-1){//something wrong
        return false;
    }
    trim(specs[index],line,head,lenght-2);
    strcat(specs[0],",");
    strcat(specs[0],specs[1]);
    strcat(specs[0],",");
    strcat(specs[0],specs[2]);
    return true;
}



SpecMapTree * createTree(int first_level,int level_count,bool reverse){
    SpecMapTree * Tree;
    do{
        Tree = (SpecMapTree *) malloc(sizeof (SpecMapTree));
    }while (Tree == nullptr);
    do{
        Tree->head = (SpecTreeLevel *) malloc(sizeof (SpecTreeLevel));
    } while (Tree->head == nullptr);

    SpecTreeLevel * level_move = Tree->head;
    if(reverse){//大层向小层递减结构
        for(int i = first_level; i >= first_level - level_count + 1 && i >= 0; i--){
            SpecTreeLevel *tmp_level = nullptr;
            do{
                tmp_level = (SpecTreeLevel *) malloc(sizeof (SpecTreeLevel));
            } while (tmp_level == nullptr);

            tmp_level->level = i;
            do{
                tmp_level->Nodes = (SpecNode *) malloc(sizeof (SpecNode) * prime_number[tmp_level->level]);
            } while (tmp_level->Nodes == nullptr);
            level_move->next_level = tmp_level;
            level_move = level_move->next_level;
        }
    } else{//小层向大层递增结构
        for(int i = first_level ; i < first_level + level_count; i++){
            SpecTreeLevel * tmp_level;
            do{
                tmp_level = (SpecTreeLevel *) malloc(sizeof (SpecTreeLevel));
            }while (tmp_level == nullptr);

            tmp_level->level = i;
            do{
                tmp_level->Nodes = (SpecNode *) malloc(sizeof (SpecNode) * prime_number[tmp_level->level]);
            }while (tmp_level->Nodes == nullptr);
            level_move->next_level = tmp_level;
            level_move = level_move->next_level;
        }
    }
    return Tree;
}

void use_rate(HashDevision1 * devision1,char * use_res){
    int sum_node = 0,storage = 0;
    SpecTreeLevel * move;
    for(int i = 0; i < DEVISION1_COUNT; i++){
        for(int j = 0; j < DEVISION2_COUNT; j++){
            if(devision1[i].devision2[j].root != nullptr){
                move = devision1[i].devision2[j].root->head;
                while (move->next_level != nullptr){
                    sum_node += prime_number[move->next_level->level];
                    storage += move->next_level->store;
                    move = move->next_level;
                }
            }
        }
    }
    sprintf(use_res,"sum node: %d, used node: %d, use rate: %.2f\n",sum_node,storage,(double )storage/sum_node * 100);
}



int main(){
    start = clock();
    char f_line[MAX_LINE_SIZE] = "";


    if(DEBUG){
        strcat(command,"free -m | grep Mem | awk '{print $2,$3}' > ");
        strcat(command,mem_path);
        system(command);

        mem = fopen(mem_path,"r");
        fgets(f_line,sizeof (char) * MAX_LINE_SIZE,mem);
        fclose(mem);
        total_mem = (atoi(strtok(f_line," ")));
        start_mem = (atoi(strtok(NULL," ")));
    }

    char *p;
    char use_res[MAX_LINE_SIZE];

    char *specs[3] = {nullptr,nullptr,nullptr};
    specs[0] = (char *) malloc(sizeof (char) * MAX_LINE_SIZE);
    specs[1] = (char *) malloc(sizeof (char) * MAX_LINE_SIZE);
    specs[2] = (char *) malloc(sizeof (char) * MAX_LINE_SIZE);

    HashDevision1 * devision1 = createDevision1();

    if(specs[0] == nullptr || specs[1] == nullptr || specs[2] == nullptr){
        return -1;
    }

    if ((file1 = fopen(f1_path,"r")) == nullptr || (file2 = fopen(f2_path,"r")) == nullptr ){
        printf("file open error!");
        return -1;
    }


    while (fgets(f_line,sizeof (char) * MAX_LINE_SIZE,file1)){
        p = strchr(f_line,',');
        if(p == nullptr || strcmp(p,"") == 0 ||strcmp(p+1,"\n") == 0 || strcmp(p+1,"\0") == 0) continue;
        if(line2Specs(specs,p+1)) {
            insertDevision1(devision1,specs[0]);
        }
    }


    finish_insert = clock();
    use_rate(devision1,use_res);

    if(DEBUG){
        system(command);
        mem = fopen(mem_path,"r");
        fgets(f_line,sizeof (char) * MAX_LINE_SIZE,mem);
        fclose(mem);
        total_mem = (atoi(strtok(f_line," ")));
        insert_mem = (atoi(strtok(NULL," ")));
    }

    while (fgets(f_line,sizeof (char) * MAX_LINE_SIZE,file2)){
        p = strchr(f_line,',');
        if(p == nullptr || strcmp(p,"") == 0 ||strcmp(p+1,"\n") == 0 || strcmp(p+1,"\0") == 0) continue;
        if(line2Specs(specs,p+1)){
            deleteDevision1(devision1,specs[0]);
        }
    }

    finish_delete = clock();

    if(PRINT_RES)
        printDevision1(devision1);

    finish_print = clock();

    if(DEBUG){
        printf("%s",use_res);
        printf("menmory used: %dM\n",insert_mem - start_mem);
        printTime(finish_insert,"insert");
        printTime(finish_delete,"delete");
        printTime(finish_print,"print");
    }

    fclose(file1);
    fclose(file2);


    return 0;
}

