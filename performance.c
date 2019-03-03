#include "common.h"
#include "list.h"
#include "merge-sort.h"
#include "quick-sort.h"
#include "insert-sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define INPUT_SIZE 256
#define RANDOM_INPUT

static uint16_t values[INPUT_SIZE];

void performance(struct list_head *list, void (*sort)(struct list_head *))
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    sort(list);
    gettimeofday(&stop, NULL);
    unsigned long int sec = (stop.tv_usec < start.tv_usec)
                                ? stop.tv_sec - start.tv_sec - 1
                                : stop.tv_sec - start.tv_sec;
    unsigned long int usec = (stop.tv_usec < start.tv_usec)
                                 ? (1000000 + stop.tv_usec - start.tv_usec)
                                 : (stop.tv_usec - start.tv_usec);
    printf("%lu.%06lu sec\n", sec, usec);
}

int main()
{
    struct list_head insert_sort_list, quick_sort_list, merge_sort_list;
    struct listitem *item = NULL, *is = NULL;

    INIT_LIST_HEAD(&insert_sort_list);
    INIT_LIST_HEAD(&quick_sort_list);
    INIT_LIST_HEAD(&merge_sort_list);

#ifdef RANDOM_INPUT
    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));
#else
    sequential_array(values, (uint16_t) ARRAY_SIZE(values));
#endif

    for (size_t i = 0; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        item->i = values[ARRAY_SIZE(values) - i - 1];
        list_add_tail(&item->list, &insert_sort_list);

        item = (struct listitem *) malloc(sizeof(*item));
        item->i = values[i];
        list_add_tail(&item->list, &quick_sort_list);

        item = (struct listitem *) malloc(sizeof(*item));
        item->i = values[i];
        list_add_tail(&item->list, &merge_sort_list);
    }

    printf("input size = %d (", INPUT_SIZE);
#ifdef RANDOM_INPUT
    printf("random input)\n");
#else
    printf("squential input)\n");
#endif
    printf("insert sort:\t");
    performance(&insert_sort_list, list_insertsort);
    printf("quick sort:\t");
    performance(&quick_sort_list, list_qsort);
    printf("merge sort:\t");
    performance(&merge_sort_list, list_mergesort);

    list_for_each_entry_safe (item, is, &insert_sort_list, list) {
        list_del(&item->list);
        free(item);
    }

    list_for_each_entry_safe (item, is, &quick_sort_list, list) {
        list_del(&item->list);
        free(item);
    }

    list_for_each_entry_safe (item, is, &merge_sort_list, list) {
        list_del(&item->list);
        free(item);
    }

    return 0;
}