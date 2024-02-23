#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

//new
struct Node
{
    char *data;
    struct Node *next;
};

struct _StrList
{
    struct Node *head;
    size_t size;
};

struct Node* create_node(const char *str) {
    struct Node* new_N = malloc(sizeof(struct Node));
    if (new_N == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_N->data = strdup(str);
    new_N->next = NULL;
    return new_N;
}


StrList* StrList_alloc() {
    StrList* new_list = malloc(sizeof(StrList));
    if (new_list == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}

void StrList_free(StrList* StrList){
    if (StrList == NULL) return;
    
    struct Node *temp = StrList->head;
    struct Node *next = NULL;
    StrList->head = NULL;
    
    while (temp != NULL)
    {
        next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }
    StrList->size = 0;
}


size_t StrList_size(const StrList* StrList) {
    return StrList != NULL ? StrList->size : 0;
}

void StrList_insertLast(StrList* StrList, const char* data){
    if (StrList->head == NULL) StrList->head = create_node(data);
    else
    {
        struct Node *temp = StrList->head;
        struct Node *new_N = create_node(data);

        while (temp->next != NULL) temp = temp->next;
        temp->next = new_N;
    }
    StrList->size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (StrList == NULL) return; 

    else if (index < 0) return; 
    struct Node *new_N = create_node(data);

    if (new_N == NULL) return;

    else if (index == 0) 
    {
        new_N->next = StrList->head;
        StrList->head = new_N;
    } else {
        struct Node *temp = StrList->head;
        int count = 0;

        while (temp != NULL && count < index - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL) {
            free(new_N->data);
            free(new_N);
            return;
        }
        new_N->next = temp->next;
        temp->next = new_N;
    }
    StrList->size++;
}


char* StrList_firstData(const StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL) return NULL;

    char* data = strdup(StrList->head->data);
    if (data == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return data;
}


void StrList_print(const StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL) {
        printf("\n");
        return;
    }

    char* buffer = (char*)malloc(StrList_printLen(StrList) + StrList_size(StrList));
    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    buffer[0] = '\0';
    struct Node* temp = StrList->head;

    while (temp != NULL) {
        strcat(buffer, temp->data);
        strcat(buffer, " ");
        temp = temp->next;
    }

    printf("%s\n", buffer);
    free(buffer);
}


void StrList_printAt(const StrList* Strlist, int index) {
    if (Strlist == NULL || index < 0) {
        printf("\n");
        return;
    }

    struct Node* temp = Strlist->head;
    int count = 0;

    while (temp != NULL && count < index) {
        temp = temp->next;
        count++;
    }

    if (count == index && temp != NULL) printf("%s\n", temp->data);
    else  printf("\n");
}


int StrList_printLen(const StrList* Strlist) {
    if (Strlist == NULL) return 0;

    int totalLength = 0;
    struct Node* temp = Strlist->head;

    while (temp != NULL) {
        totalLength += strlen(temp->data);
        temp = temp->next;
    }

    return totalLength;
}


int StrList_count(StrList* StrList, const char* data) {
    if (StrList == NULL) return 0;

    int count = 0;
    struct Node* temp = StrList->head;

    while (temp != NULL) {
        if (strcmp(temp->data, data) == 0) count++;
        temp = temp->next;
    }

    return count;
}


void StrList_remove(StrList* StrList, const char* data) {
    if (StrList == NULL) return;

    struct Node* temp = StrList->head;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->data, data) == 0) {
            if (prev == NULL) {
                StrList->head = temp->next;
                free(temp->data);
                free(temp);
                temp = StrList->head;
            } else {
                prev->next = temp->next;
                free(temp->data);
                free(temp);
                temp = prev->next;
            }
            StrList->size--;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}


void StrList_removeAt(StrList* StrList, int index) {
    if (StrList == NULL || StrList->head == NULL || index < 0) return;

    if (index == 0) {
        struct Node* temp1 = StrList->head;
        StrList->head = temp1->next;
        free(temp1->data);
        free(temp1);
    } else {
        struct Node* temp2 = StrList->head;
        int count = 0;

        while (temp2 != NULL && count < index - 1) {
            temp2 = temp2->next;
            count++;
        }

        if (temp2 == NULL || temp2->next == NULL) return;

        struct Node* temp1 = temp2->next;
        temp2->next = temp1->next;
        free(temp1->data);
        free(temp1);
    }
    StrList->size--;
}


int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {
    if (StrList1 == NULL || StrList2 == NULL) return 0;

    else if (StrList_size(StrList1) != StrList_size(StrList2)) return 0;
    else
    {
        struct Node* temp1 = StrList1->head;
        struct Node* temp2 = StrList2->head;

        while (temp1 != NULL && temp2 != NULL) 
        {
            if (strcmp(temp1->data, temp2->data) != 0) return 0;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return (temp1 == NULL && temp2 == NULL);
    }
}


StrList* StrList_clone(const StrList* StrList) {
    if (StrList == NULL || StrList_size(StrList) <= 0) return NULL;

    struct _StrList * cloned_list = StrList_alloc();
    if (cloned_list == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    struct Node* temp = StrList->head;
    struct Node* tail = NULL;

    while (temp != NULL) {
        char* data_copy = strdup(temp->data);
        if (data_copy == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        struct Node* new_N = create_node(data_copy);
        if (new_N == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        if (tail == NULL) cloned_list->head = new_N;
        else tail->next = new_N;
        
        tail = new_N;
        temp = temp->next;
    }

    cloned_list->size = StrList_size(StrList);
    return cloned_list;
}


void StrList_reverse(StrList* StrList) {
    if (StrList == NULL || StrList_size(StrList) <= 1) return;

    struct Node* prev = NULL;
    struct Node* temp = StrList->head;
    struct Node* next = NULL;

    while (temp != NULL) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    StrList->head = prev;
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList_size(StrList) <= 1) return;

    struct Node* sorted = NULL;
    while (StrList->head != NULL) {
        struct Node* temp1 = StrList->head;
        StrList->head = StrList->head->next;

        if (sorted == NULL || strcmp(temp1->data, sorted->data) <= 0) {
            temp1->next = sorted;
            sorted = temp1;
        } 
        else 
        {
            struct Node* temp2 = sorted;
            
            while (temp2->next != NULL && strcmp(temp1->data, temp2->next->data) > 0) temp2 = temp2->next;
            
            temp1->next = temp2->next;
            temp2->next = temp1;
        }
    }
    StrList->head = sorted;
}


int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList_size(StrList) <= 1) return 1;
    else
    {
        struct Node* temp = StrList->head;
        while (temp->next != NULL) {
            if (strcmp(temp->data, temp->next->data) > 0) return 0; 
        
            temp = temp->next;
        }
        return 1;
    }
}

void buildList(StrList* StrList, int length, char* str){
    int count = 0;

    for (int i = 0; i < length; i++)
    {
        char* substring;
        while (str[count] != ' ' && count < strlen(str)) count++;
        
        substring = (char*)malloc(count+1);
        strncpy(substring, str, count);
        substring[count] = '\0';
        
        StrList_insertLast(StrList, substring);        
        count++;
        str += count;
        count = 0;
        free(substring);
    }
}
