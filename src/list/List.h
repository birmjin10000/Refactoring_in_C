#ifndef _LIST_H_
#define _LIST_H_

#define List_ForEach(cursor, head) \
    for (cursor = (head)->next; cursor != (head); cursor = cursor->next)

typedef struct _List{
    void* data;
    struct _List* next;
    struct _List* prev;
} List;

void List_Init(List* list);
void List_Append(List* new, List* head);

#endif // _LIST_H_
