/*
 * Copyright (c) 2016-2017, Evercoin. All Rights Reserved.
 */

#include <stdlib.h>
#include <string.h>
#include "HashMap.h"

static int hash(void *ptr, int size) {
    return (int) (((long) ptr) % size);
}

static void rehash(HashMap hm) {
    Item *current, *buckets;
    Item item, next;
    size_t s, size;
    int i, index;

    current = hm->buckets;
    s = hm->size;
    size = s << 1;

    buckets = calloc(size, sizeof(Item));

    for (i = 0; i < s; i++) {
        for (item = current[i]; item != NULL; item = next) {
            index = hash(item->key, size);
            next = item->next;
            item->next = buckets[index];
            buckets[index] = item;
        }
    }

    free(hm->buckets);
    hm->buckets = buckets;
    hm->size = size;
}

HashMap HMConstruct(size_t size) {
    HashMap hm = (HashMap) malloc(sizeof(struct hashmap));
    hm->buckets = calloc(size, sizeof(Item));
    hm->size = size;
    hm->count = 0;
    return hm;
}

void *HMGet(HashMap hm, char *key) {
    int index = hash(key, hm->size);
    Item item;

    for (item = hm->buckets[index]; item != NULL; item = item->next) {
        if ((strcmp(item->key, key)) == 0)
            return item->value;
    }

    return NULL;
}

void HMPut(HashMap hm, char *key, void *value) {
    Item item;
    Item *p;
    int index = hash(key, hm->size);

    p = &(hm->buckets[index]);

    for (item = *p; item != NULL; item = item->next) {
        if ((strcmp(item->key, key)) == 0) {/* key already exists */
            item->value = value;
            return;
        }
    }

    item = *p;
    Item newItem = (Item) malloc(sizeof(struct hashmap_item));
    newItem->key = key;
    newItem->value = value;
    (*p) = newItem;
    (*p)->next = item;

    if (++hm->count >= hm->size * 3 / 4)
        rehash(hm);
}

void HMPutAll(HashMap hm, HashMap copy) {
    int i;
    Item item;

    for (i = 0; i < copy->size; i++) {
        for (item = copy->buckets[i]; item != NULL; item = item->next) {
            HMPut(hm, item->key, item->value);
        }
    }
}

void HMIterotor(HashMap hm, void func(void *, void *)) {
    int i;
    Item item;

    for (i = 0; i < hm->size; i++) {
        for (item = hm->buckets[i]; item != NULL; item = item->next) {
            (*func)(item->value, item->key);
        }
    }
}

size_t HMSize(HashMap hm) {
    return hm->count;
}

bool HMIsEmpty(HashMap hm) {
    return hm->count == 0 ? true : false;
}

void HMRemove(HashMap hm, char *key) {
    int index = hash(key, hm->size);
    Item item, next;

    item = hm->buckets[index];

    if (item == NULL)
        return;

    if (item->next == NULL) {
        free(item);
        hm->buckets[index] = NULL;
        hm->count--;
        return;
    }

    while (item != NULL) {
        next = item->next;
        if (next != NULL && (strcmp(next->key, key)) == 0) {
            item->next = next->next;
            hm->count--;
            free(next);
            return;
        }
        item = next;
    }
}

void HMFree(HashMap hm) {
    int i;
    Item item, next;

    for (i = 0; i < hm->size; i++) {
        for (item = hm->buckets[i]; item != NULL;) {
            next = item->next;
            free(item);
            item = next;
        }
    }

    free(hm->buckets);
    free(hm);
}