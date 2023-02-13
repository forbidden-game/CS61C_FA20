#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if (head == NULL || head -> next == NULL) {
        return 0;
    }
    node *p = head;
    node *q = head -> next;

    while (q != NULL && q -> next != NULL) {
        if (p == q)
        {
            return 1;
        }
        q = q -> next -> next;
        p = p -> next;
    }
    
    return 0;
}