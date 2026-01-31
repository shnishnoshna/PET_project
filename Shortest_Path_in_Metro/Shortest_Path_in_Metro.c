#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

enum {name_length=50, total_links=50, max_path_station=100};

typedef struct tag_station {
    char name[name_length];                 // название станции метро
    struct tag_station* links[total_links]; // связи станции метро с другими соседними станциями
    short count_links;                      // общее количество связей
    char fl_reserved;                     // зарезервированная переменная (полезна при реализации алгоритма поиска маршрута)
    struct tag_station *parent;
} STATION ;

typedef struct queue{
    STATION *st;
    struct queue *prev;
    struct queue *next;
} QUEUE ;

typedef struct{
    size_t size_list;
    QUEUE *head;
    QUEUE *tail;
} LIST ;


void set_station_links(STATION* st, int count_links, ...)
{
    va_list arg;
    va_start(arg, count_links);
    while(count_links--){
        st->links[st->count_links++] = va_arg(arg, STATION*);
    }
    va_end(arg);
}

QUEUE *push_back(LIST *list, STATION *st)
{
    QUEUE *obj = malloc(sizeof(QUEUE));
    obj->next = NULL;
    if(list->head == NULL && list->tail == NULL){
        list->head = obj;
        list->tail = obj;
        obj->prev = NULL;
        obj->st = st;
    }
    else {
        obj->prev = list->tail;
        (*list->tail).next = obj;
        list->tail = obj;
        obj->st = st;
    }
    obj->st->fl_reserved = 1;
    list->size_list++;
    return obj;
}

QUEUE *del_front_obj(LIST *list)
{
    if(list->head == NULL && list->tail == NULL)
        return 0;
    QUEUE *tmp = list->head;
    list->head = list->head->next;
    if(list->head != NULL)
        list->head->prev = NULL;
    if(tmp == list->tail)
        list->tail = NULL;
    free(tmp);
    list->size_list--;
    return list->head;
}

void fl_reserved_cleaner(STATION *st[], int count)
{
    for(int i = 0; i < count; ++i)
        st[i]->fl_reserved = 0;
}

void find_path(STATION *from, STATION *to, STATION *path[], int *count_st)
{
    STATION *clean_st[max_path_station];
    int clean_st_count = 0;
    bool path_go = false;
    LIST list;
    list.head = push_back(&list, from);
    list.head->st->parent = NULL;
    while(list.head != NULL){
        if(list.head->st == to){
            clean_st[clean_st_count++] = list.head->st;
            list.head->st->fl_reserved = 1;
            del_front_obj(&list);
            path_go = true;
            break;
        }
        for(int i = 0; i < list.head->st->count_links; ++i){
            if(list.head->st->links[i]->fl_reserved == 0){
                list.head->st->links[i]->fl_reserved = 1;
                list.head->st->links[i]->parent = list.head->st;
                list.tail = push_back(&list, list.head->st->links[i]);
            }
        }
        clean_st[clean_st_count++] = list.head->st;
        //printf("%d %s = Parent[%s]\n", *count_st, list.head->st->name, list.head->st->parent->name);
        del_front_obj(&list);
    }
    if(path_go == true){
        STATION *tmp = to;
        while(tmp != NULL){
            (*count_st)++;
            tmp = tmp->parent;
        }
        tmp = to;
        for(int i = *count_st - 1; i >= 0; --i){
            path[i] = tmp;
            tmp = tmp->parent;
            //printf("%s\n", path[i]);
        }
    }
    fl_reserved_cleaner(clean_st, clean_st_count);
}

int main()
{
    STATION* path[max_path_station];
    int count_st = 0;
    
    STATION st[10] = {
        {"St #1", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #2", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #3", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #4", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #5", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #6", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #7", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #8", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #9", .count_links=0, .fl_reserved=0, .parent = 0},
        {"St #10", .count_links=0, .fl_reserved=0, .parent = 0},
    };
    
    set_station_links(&st[0], 2, &st[1], &st[2]);
    set_station_links(&st[1], 3, &st[0], &st[3], &st[4]);
    set_station_links(&st[2], 2, &st[0], &st[5]);
    set_station_links(&st[3], 2, &st[1], &st[5]);
    set_station_links(&st[4], 2, &st[1], &st[7]);
    set_station_links(&st[5], 4, &st[2], &st[3], &st[6], &st[8]);
    set_station_links(&st[6], 2, &st[5], &st[8]);
    set_station_links(&st[7], 2, &st[4], &st[8]);
    set_station_links(&st[8], 4, &st[5], &st[6], &st[7], &st[9]);
    set_station_links(&st[9], 1, &st[8]);

    puts("Select start and end stations...\n----------------");

    int st_start;
    int st_end;
    puts("Station_Start:");
    scanf("%d", &st_start);
    puts("Station_End:");
    scanf("%d", &st_end);

    find_path(&st[st_start - 1], &st[st_end - 1], path, &count_st);

    for(int i = 0; i < count_st; ++i){
        printf("[%s]", path[i]->name);
    }
    putchar('\n');
    
    return 0;

}
