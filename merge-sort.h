#include "list.h"
#include "common.h"

static void merge(struct list_head *list1, struct list_head *list2)
{
    struct list_head merged;
    struct listitem *item1 = NULL, *item2 = NULL;
    int cmp = 0;

    INIT_LIST_HEAD(&merged);

    while (!list_empty(list1) && !list_empty(list2)) {
        item1 = list_first_entry(list1, struct listitem, list);
        item2 = list_first_entry(list2, struct listitem, list);

        cmp = cmpint(&item1->i, &item2->i);

        if (cmp < 0) {
            list_move_tail(&item1->list, &merged);
        } else if (cmp > 0) {
            list_move_tail(&item2->list, &merged);
        } else {
            list_move_tail(&item1->list, &merged);
            list_move_tail(&item2->list, &merged);
        }
    }

    if (!list_empty(list1)) {
        list_splice_tail_init(list1, &merged);
    }

    if (!list_empty(list2)) {
        list_splice_tail(list2, &merged);
    }

    list_splice_tail(&merged, list1);
}

static void list_mergesort(struct list_head *head)
{
    if (list_empty(head) || list_is_singular(head)) {
        return;
    }

    struct list_head list;
    INIT_LIST_HEAD(&list);

    struct list_head *node = NULL;
    int count = 0;
    list_for_each (node, head) {
        count++;
    }

    int i = 0;
    int mid = count / 2 - 1;
    list_for_each (node, head) {
        if (i == mid) {
            break;
        }
        i++;
    }

    list_cut_position(&list, head, node);

    list_mergesort(head);
    list_mergesort(&list);

    merge(head, &list);
}