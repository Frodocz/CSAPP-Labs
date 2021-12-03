/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) return;
    /* How about freeing the list elements and the strings? */
    list_ele_t *cur = q->head, *next = NULL;
    while (cur) {
        /* Free the value string of the current node */
        free(cur->value);

        /* Keep track of the next node */
        next = cur->next;

        /* Free the current node */
        free(cur);

        /* Move to next node */
        cur = next;
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (!q) {
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    int len = strlen(s);
    newh->value = malloc(len + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    newh->value[len] = '\0';
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (!q->tail) {
        q->tail = newh;
    }
    ++q->size;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    if (!q) {
        return false;
    }
    /* q is not NULL or empty, we'll insert the new node after the tail of queue */
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    int len = strlen(s);
    newt->value = malloc(len + 1);
    if (!newt->value) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);
    newt->value[len] = '\0';
    newt->next = NULL;
    /* Remember: It should operate in O(1) time */
    if (q->tail) {
        q->tail->next = newt;
    } else {
        q->head = newt;
    }
    q->tail = newt;
    ++q->size;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    /* Return false if queue is NULL or empty. */ 
    if (!q || !q->head) {
        return false;
    }
    if (sp) {
        int len = strlen(q->head->value);
        if (len >= bufsize - 1) {
            len = bufsize - 1;
        }
        strncpy(sp, q->head->value, len);
        sp[len] = '\0';
    }
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    --q->size;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !q->head) return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q && q->head) {
        list_ele_t *tmp_head = q->head, *tmp_tail = q->tail;
        list_ele_t *prev = NULL, *cur = q->head, *next;
        while (cur) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        q->head = tmp_tail;
        q->tail = tmp_head;
    }
}

