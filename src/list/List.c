#include "List.h"

void List_Init(List* list) {
    list->next = list;
    list->prev = list;
}

static void __List_Append(List* new, List* prev, List* next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

void List_Append(List* new, List* head) {
    __List_Append(new, head->prev, head);
}

