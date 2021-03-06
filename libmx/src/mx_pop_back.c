#include "libmx.h"

void mx_pop_back(t_list **head) {
    t_list *tmp = NULL;
    if (!head || !*head) {
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        tmp = *head;
        while (tmp && tmp->next->next) {
            tmp = tmp->next;
        }
        free(tmp->next);
        tmp->next = NULL;
    }
}
