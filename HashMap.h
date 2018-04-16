/*
 * Copyright (c) 2016-2017, Evercoin. All Rights Reserved.
 */

#ifndef HASHMAP_HEADER
#define HASHMAP_HEADER

#include <stdbool.h>

typedef struct hashmap_item *Item;
typedef struct hashmap *HashMap;

struct hashmap_item {
    Item next;
    char *key;
    void *value;
};

struct hashmap {
    Item * buckets;
    size_t size;
    size_t count;
};

HashMap HMConstruct(size_t size);
void * HMGet(HashMap hm, char *key);
void HMPut(HashMap hm, char *key, void *value);
void HMPutIfAbsent(HashMap hm, char *key, void *value);
void HMPutAll(HashMap hm, HashMap copy);
void HMIterotor(HashMap hm, void func(void *, void *));
size_t HMSize(HashMap hm);
bool HMIsEmpty(HashMap hm);
void HMRemove(HashMap hm, char *key);
void HMClear(HashMap hm);
void HMFree(HashMap hm);

#endif