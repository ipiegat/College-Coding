#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// TODO:
void push(stack *s, node *new_node)
{
    if (s == NULL) {
        printf("Stack is empty\n");
        return;
    }

    new_node->next = s->top;
    s->top = new_node;
}

// TODO:
node* pop(stack *s)
{
    if (s == NULL || s->top == NULL) {
        return NULL;
    }

    node *temp = s->top;
    s->top = s->top->next;
    temp->next = NULL;
    return temp;
}

// TODO:
int empty(stack *s)
{
    return (s == NULL || s->top == NULL);
}

// TODO:
void clear_stack(stack *s)
{
    while (!empty(s)) {
        node *temp = pop(s);
        free(temp);
    }
}
