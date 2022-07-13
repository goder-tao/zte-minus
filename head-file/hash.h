//
// Created by tao on 2021/4/12.
//
#ifndef ZTE_HASH_H
#define ZTE_HASH_H
#endif //ZTE_HASH_H

typedef struct entry {
    void * key;             // 键（void指针可以表示任意类似）
    void * value;           // 值
    struct entry * next;    // 冲突链表
}*Entry;


// 哈希结构
typedef struct hashMap *HashMap;
#define newHashMap() NEW(struct hashMap)

// 哈希函数类型（函数指针）
typedef int(*HashCode)(HashMap, void * key);

// 判等函数类型
typedef bool(*Equal)(void * key1, void * key2);

// 添加键函数类型
typedef void(*Put)(HashMap hashMap, void * key, void * value);

// 获取键对应值的函数类型
typedef void * (*Get)(HashMap hashMap, void * key);

// 删除键的函数类型
typedef bool(*Remove)(HashMap hashMap, void * key);

// 清空Map的函数类型
typedef void(*Clear)(HashMap hashMap);

// 判断键值是否存在的函数类型
typedef bool(*Exists)(HashMap hashMap, void * key);

typedef struct hashMap {
    int size;           // 当前大小
    int listSize;       // 有效空间大小
    HashCode hashCode;  // 哈希函数
    Equal equal;        // 判等函数
    Entry list;         // 存储区域
    Put put;            // 添加键的函数
    Get get;            // 获取键对应值的函数
    Remove remove;      // 删除键
    Clear clear;        // 清空Map
    Exists exists;      // 判断键是否存在
    bool autoAssign;	// 设定是否根据当前数据量动态调整内存大小，默认开启
}*HashMap;