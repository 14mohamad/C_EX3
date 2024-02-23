#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

#define Max_Size_Str 100

void buildList(StrList* StrList, int length, char* str);

int main() {
    int num;
    StrList* strlist = StrList_alloc();

    while (1) {
        scanf("%d", &num);

        if (num == 0) {
            break;
        }

        switch (num) {
            case 1: {
                int length;
                scanf("%d", &length);

                char* str = (char*)malloc((Max_Size_Str + 1) * length);
                scanf(" %[^\n]", str);

                buildList(strlist, length, str);

                free(str);
                break;
            }
            case 2: {
                int index;
                scanf("%d", &index);

                char* str = (char*)malloc(Max_Size_Str + 1);
                scanf(" %s", str);

                StrList_insertAt(strlist, str, index);

                free(str);
                break;
            }
            case 3: {
                StrList_print(strlist);
                break;
            }
            case 4: {
                printf("%zu\n", StrList_size(strlist));
                break;
            }
            case 5: {
                int index;
                scanf("%d", &index);

                StrList_printAt(strlist, index);
                break;
            }
            case 6: {
                printf("%d\n", StrList_printLen(strlist));
                break;
            }
            case 7: {
                char* str = (char*)malloc(Max_Size_Str + 1);
                scanf(" %s", str);

                printf("%d\n", StrList_count(strlist, str));

                free(str);
                break;
            }
            case 8: {
                char* str = (char*)malloc(Max_Size_Str + 1);
                scanf(" %s", str);

                StrList_remove(strlist, str);

                free(str);
                break;
            }
            case 9: {
                int index;
                scanf("%d", &index);

                StrList_removeAt(strlist, index);
                break;
            }
            case 10: {
                StrList_reverse(strlist);
                break;
            }
            case 11: {
                StrList_free(strlist);
                break;
            }
            case 12: {
                StrList_sort(strlist);
                break;
            }
            case 13: {
                if (StrList_isSorted(strlist)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
            }
            default:
                break;
        }
    }

    StrList_free(strlist);
    free(strlist);

    return 0;
}
