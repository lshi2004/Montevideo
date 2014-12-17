/*
 ============================================================================
 Name        : PL1.c
 Author      : HC1
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct LL_element {
    int value;
    struct LL_element *next;
};
int is_palindrom_solution (int number)
{
    int is_palindrom = 0;
    int reversed = 0;
    unsigned int copy = number;

    if (number >= 0) {
        while (number != 0) {
            reversed = reversed * 10 + number % 10;
            number /= 10;
        }
        if (reversed == copy) {
            is_palindrom = 1;
        }
    }

    return is_palindrom;
}


int palindrom_main(void) {
    printf("!!!Hello World!!!\n"); /* prints !!!Hello World!!! */

    printf("is palindrom %d  \n", is_palindrom_solution(37473));

    printf("is palindrom %d  \n", is_palindrom_solution(47473));
    return EXIT_SUCCESS;
}




void LL_print_list(struct LL_element *ll) {
    for (; ll; ll = ll->next) {
        printf("\n %d ", ll->value);
    }
}

int LL_insert_front(struct LL_element **ll, int value) {
    struct LL_element *ptr = NULL;

    if (!ll) {
        return -1;
    }

    ptr = malloc(sizeof(struct LL_element));
    if (!ptr) {
        return -1;
    }

    ptr->value = value;

    if (*ll) {
        ptr->next = (*ll);
    } else {
        ptr->next = NULL;
    }

    *ll = ptr;
    return 0;
}

struct LL_element *LL_lookup(struct LL_element *ll, int value) {
    for (; ll; ll = ll->next) {
        if (ll->value == value) {
            return ll;
        }
    }

    return NULL;
}

struct LL_element *LL_remove(struct LL_element **head, int value) {
    struct LL_element *prev = NULL;
    struct LL_element *ll;

    if (!head) {
        return NULL;
    }

    ll = *head;

    for (; ll; prev = ll, ll = ll->next) {
        if (ll->value == value) {
            if (prev) { //middle
                prev->next = ll->next;
            } else { // head
                *head = ll->next;
            }
            return ll;
        }
    }

    return NULL;
}

int LL_sort (struct LL_element **head)
{

    if (head == NULL || *head == NULL) {
        return 0;
    }

    return 0;
}


int main() {
    int i = 0;
    struct LL_element *head = NULL;
    struct LL_element *ptr = NULL;

    for (i = 0; i < 10; i++) {
        LL_insert_front(&head, i);
    }

    LL_print_list(head);


    printf("Hello New World \n\n");

    ptr = LL_lookup(head, 5);
    if (ptr) {
        printf("Found node %d \n", ptr->value);
    }

    ptr = LL_lookup(head, 9);
    if (ptr) {
        printf("Found node %d \n", ptr->value);
    }

    ptr = LL_lookup(head, 0);
    if (ptr) {
        printf("Found node %d \n", ptr->value);
    }

    printf("World Hello \n");

    ptr = LL_remove(&head, 9);
    if (ptr) {
        printf("Removing node %d \n", ptr->value);
        free(ptr);
    } else {
        printf("Empty Removing node %p \n", ptr);
    }

    printf("World Hello 2 %s \n", __FUNCTION__);

    LL_print_list(head);

    ptr = LL_remove(&head, 0);
    if (ptr) {
        printf("Removing node %d \n", ptr->value);
        free(ptr);
    } else {
        printf("Empty Removing node %p \n", ptr);
    }

    printf("World Hello 2 %s \n", __FUNCTION__);

    LL_print_list(head);


    return 0;
}


