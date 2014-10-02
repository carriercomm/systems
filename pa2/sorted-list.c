#include <string.h>
#include "sorted-list.h"

// Declare function in advance.
int SLTraverse(SortedList *list, void *func, void *data);

ListNode *LNCreate(void *data) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));

    if (node) {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

// Destroys a list node struct. Should only be called after the node
// has been safely removed from the list.
void LNDestroy(ListNode *node, DestructFuncT destruct) {
    destruct(node->data);
    free(node);
}

SortedList *SLCreate(CompareFuncT cf, DestructFuncT df) {
    SortedList *list = (SortedList *) malloc(sizeof(SortedList));

    if (list) {
        list->head = NULL;
        list->comparator = cf;
        list->destructor = df;
    }

    return list;
}

void SLDestroy(SortedList *list) {
    ListNode *current = list->head;
    while (current) {
        ListNode *tmp = current;
        current = current->next;
        LNDestroy(tmp, list->destructor);
    }
    free(list);
}

int SLInsert(SortedList *list, void *newObj) {
    // Check if we've been passed a null pointer.
    if (!newObj) {
        return 0;
    } else if (!list->head) {
        ListNode *head = LNCreate(newObj);
        list->head = head;
        return 1;
    }

    ListNode *current = list->head, *prev = NULL;
    CompareFuncT compare = list->comparator;
    while (current) {
        int comparison = compare(newObj, current->data);
        if (comparison > 0) {
            ListNode *node = LNCreate(newObj);
            if (!prev) {
                node->next = list->head;
                list->head = node;
            } else {
                prev->next = node;
                node->next = current;
            }
            return 1;
        } else if (!comparison) {
            return 0;
        }
        prev = current;
        current = current->next;
    }

    ListNode *node = LNCreate(newObj);
    prev->next = node;
    return 1;
}

int SLRemove(SortedList *list, void *newObj) {
    if (!newObj) {
        return 0;
    }

    ListNode *current = list->head, *prev = NULL;
    CompareFuncT compare = list->comparator;
    while (current) {
        if (compare(newObj, current->data) == 0) {
            if (!prev) {
                list->head = list->head->next;
                LNDestroy(current, list->destructor);
            } else {
                prev->next = current->next;
                LNDestroy(current, list->destructor);
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    return 0;
}

SortedListIterator *SLCreateIterator(SortedList *list) {
    SortedListIterator *iterator = (SortedListIterator *) malloc(sizeof(SortedListIterator));

    if (iterator) {
        iterator->list = list;
        iterator->current = (ListNode *) malloc(sizeof(ListNode));
    }

    return iterator;
}

void SLDestroyIterator(SortedListIterator *iter) {
    free(iter);
}

void *SLGetItem(SortedListIterator *iter) {
    return iter->current->data;
}

void *SLNextItem(SortedListIterator *iter) {

}