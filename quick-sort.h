#include "list.h"
#include "common.h"

static struct listitem *find_pivot(struct list_head *head)
{
    struct listitem *first = NULL, *last = NULL, *mid = NULL;

    first = list_first_entry(head, struct listitem, list);
    last = list_last_entry(head, struct listitem, list);

    struct list_head *node = NULL;
    int count = 0;
    list_for_each (node, head) {
        count++;
    }

    int i = 0;
    int mid_idx = count / 2 - 1;
    list_for_each_entry (mid, head, list) {
        if (i == mid_idx) {
            break;
        }
        i++;
    }

    struct listitem *big = NULL, *small = NULL;

    if (cmpint(&first->i, &last->i) > 0) {
        big = first;
        small = last;
    } else {
        big = last;
        small = first;
    }

    if (cmpint(&mid->i, &big->i) > 0) {
        return big;
    }

    if (cmpint(&mid->i, &small->i) > 0) {
        return mid;
    }

    return small;
}

static void list_qsort(struct list_head *head)
{
    struct list_head list_less, list_greater;
    struct listitem *pivot;
    struct listitem *item = NULL, *is = NULL;

    if (list_empty(head) || list_is_singular(head))
        return;

    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = find_pivot(head);
    list_del(&pivot->list);

    list_for_each_entry_safe (item, is, head, list) {
        if (cmpint(&item->i, &pivot->i) < 0)
            list_move_tail(&item->list, &list_less);
        else
            list_move(&item->list, &list_greater);
    }

    list_qsort(&list_less);
    list_qsort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}