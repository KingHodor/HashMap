/*
 * Copyright (c) 2016-2017, Evercoin. All Rights Reserved.
 */

#include <stdio.h>
#include "HashMap.h"

void func(void *value, void *key) {
    printf("value: %s - key: %s\n", (char *) value, (char *) key);
}

void test1() {

    HashMap hm;
    char *ret;

    char *key1 = "key 1";
    char *key2 = "key 2";
    char *key3 = "key 3";
    char *key4 = "key 4";

    hm = HMConstruct(2);

    printf("HM is empty: %d\n", HMIsEmpty(hm));

    HMPut(hm, key1, "value 1");
    HMPut(hm, key2, "value 2");
    HMPut(hm, key3, "value 3");
    HMPut(hm, key4, "value 4");

    HMIterotor(hm, func);
    printf("\n");

    HMRemove(hm, key1);
    HMRemove(hm, key3);

    ret = HMGet(hm, key2);
    HMIterotor(hm, func);
    printf("%s\n", ret);

    printf("\n");
    HashMap copy;
    copy = HMConstruct(2);
    char *copy_key1 = "copy key 1";
    char *copy_key2 = "copy key 2";
    HMPut(copy, copy_key1, "copy value 1");
    HMPut(copy, copy_key2, "copy value 2");

    HMPutAll(hm, copy);
    HMIterotor(hm, func);

    printf("Hashmap size :%d\n", (int) HMSize(hm));
    printf("HM is empty: %d\n", HMIsEmpty(hm));

    HMPut(hm, key4, "value 5");
    ret = HMGet(hm, key4);
    printf("%s\n", ret);

    HMPutIfAbsent(hm, key4, "value 6");
    ret = HMGet(hm, key4);
    printf("%s\n", ret);

    HMFree(hm);


}

int main() {
    test1();
    return 0;
}