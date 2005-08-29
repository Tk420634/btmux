/*
 * Doubly Linked List
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dllist.h"

/* Create the List */
dllist *dllist_create_list() {

    dllist *temp;

    temp = malloc(sizeof(dllist));
    if (temp == NULL) {
        return NULL;
    }

    memset(temp, 0, sizeof(temp));
    temp->head = NULL;
    temp->tail = NULL;
    temp->size = 0;

    return temp;
}

/* Create a node */
dllist_node *dllist_create_node(void *data) {

    dllist_node *temp;

    temp = malloc(sizeof(dllist_node));
    if (temp == NULL) {
        return NULL;
    }

    memset(temp, 0, sizeof(dllist_node));
    temp->prev = NULL;
    temp->next = NULL;
    temp->data = data;

    return temp;
}

/* Destroy the List - Won't destroy unless the list is empty */
int dllist_destroy_list(dllist *dllist) {

    /* Check the size */
    if (dllist->size != 0) {
        return 0;
    } else {
        free(dllist);
        return 1;
    }

}

/* Destroy a Node - Returns the data in the node */
void *dllist_destroy_node(dllist_node *node) {
    
    void *data;

    data = node->data;
    free(node);

    return data;

}

/* Insert a given node after a node */
void dllist_insert_after(dllist *dllist, dllist_node *node, dllist_node *newnode) {

    newnode->prev = node;
    newnode->next = node->next;
    if (node->next == NULL) {
        dllist->tail = newnode;
    } else {
        (node->next)->prev = newnode;
    }
    node->next = newnode;

    /* Increment */
    dllist->size++;

    return;
}

/* Insert a given node before a node */
void dllist_insert_before(dllist *dllist, dllist_node *node, dllist_node *newnode) {

    newnode->prev = node->prev;
    newnode->next = node;
    if (node->prev == NULL) {
        dllist->head = newnode;
    } else {
        (node->prev)->next = newnode;
    }
    node->prev = newnode;

    /* Increment */
    dllist->size++;

    return;
}

/* Insert a node at the beginning */
void dllist_insert_beginning(dllist *dllist, dllist_node *newnode) {

    /* If there is no head it means empty list */
    if (dllist->head == NULL) {
        dllist->head = newnode;
        dllist->tail = newnode;
        newnode->prev = NULL;
        newnode->next = NULL;

        /* Increment */
        dllist->size++;

    } else {
        dllist_insert_before(dllist, dllist->head, newnode);
    }

    return;
}

/* Insert a node at the end of the list */
void dllist_insert_end(dllist *dllist, dllist_node *newnode) {

    /* If there is no tail means empty list */
    if (dllist->tail == NULL) {
        dllist_insert_beginning(dllist, newnode);
    } else {
        dllist_insert_after(dllist, dllist->tail, newnode);
    }

    return;

}

/* Remove a node from the list - returns the data */
void *dllist_remove(dllist *dllist, dllist_node *node) {

    void *data;

    /* We're checking if this first node */
    if (node->prev == NULL) {
        dllist->head = node->next;
    } else {
        (node->prev)->next = node->next;
    }

    /* Check if end of list */
    if (node->next == NULL) {
        dllist->tail = node->prev;
    } else {
        (node->next)->prev = node->prev;
    }

    /* Destroy Node */
    data = dllist_destroy_node(node);

    /* De-Increment */
    dllist->size--;

    return data;

}

/* Utility functions */

/* Get Head node */
dllist_node *dllist_head(dllist *dllist) {
    return dllist->head;
}

/* Get Tail Node */
dllist_node *dllist_tail(dllist *dllist) {
    return dllist->tail;
}

/* Gets next node */
dllist_node *dllist_next(dllist_node *node) {
    return node->next;
}   

/* Gets previous node */
dllist_node *dllist_prev(dllist_node *node) {
    return node->prev;
}

/* Get the size of the list */
int dllist_size(dllist *dllist) {
    return dllist->size;
}