#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

Graph *Graph_alloc() {
    Graph *g = malloc(sizeof(Graph));
    
    assert(g != NULL);

    g->n = 0;
    g->first = NULL;
    g->last = NULL;

    return g;
}

void Graph_free() {

}

void Graph_insertVertex(Graph *g, void *value) {
    assert(g != NULL);

    Vertex *new = malloc(sizeof(Vertex));

    assert(new != NULL);

    new->n = 0;
    new->first = NULL;
    new->last = NULL;
    new->next = NULL;
    new->value = value;
    new->label = g->n;

    if (g->n == 0)
        g->first = new;
    else
        g->last->next = new;

    g->last = new;
    g->n++;
}

Vertex *Graph_find(Graph *g, int label) {
    assert(g != NULL);
    assert(label >= 0);

    Vertex *v = g->first;

    while (v) {
        if (v->label == label)
            return v;

        v = v->next;
    }

    return NULL;
}

Vertex *Graph_findByValue(Graph *g, void *value, int (*cmp)(void*,void*)) {
    assert(g != NULL);
    assert(value != NULL);
    assert(cmp != NULL);

    Vertex *v = g->first;

    while (v) {
        if (cmp(v->value, value) == 0)
            return v;

        v = v->next;
    }

    return NULL;
}

void Graph_insertEdge(Graph *g, int label1, int label2, void *value) {
    assert(g != NULL);
    assert(label1 >= 0);
    assert(label2 >= 0);

    Vertex *v1 = Graph_find(g, label1);
    Vertex *v2 = Graph_find(g, label2);
    assert(v1 != NULL);
    assert(v2 != NULL);

    Edge *new = malloc(sizeof(Edge));
    assert(new != NULL);

    new->next = NULL;
    new->value = value;
    new->label = v1->n;
    new->tail = v1;
    new->head = v2;

    if (v1->n == 0)
        v1->first = new;
    else
        v1->last->next = new;

    v1->last = new;
    v1->n++;
}

void Graph_print(Graph *g) {
    assert(g != NULL);

    Vertex *v = g->first;
    while (v) {
        printf("[%d]\u2192", v->label);

        Edge *e = v->first;
        while (e) {
            printf("(%d)\u2192", e->head->label);
            e = e->next;
        }
        printf("\n \u2193\n");

        v = v->next;
    }
}

void *Graph_removeVertex(Graph *g, int label) {
    assert(g != NULL);
    assert(label >= 0);

    Vertex *v1 = NULL, *v2 = NULL;

    v2 = Graph_find(g, label);
    assert(v2 != NULL);

    v1 = g->first;
    while (v1) {
        Graph_removeEdge(g, v1->label, v2->label);
        v1 = v1->next;
    }

    Vertex *v = NULL, *ant = NULL;
    void   *value = NULL;
    
    v = g->first;
    while (v) {
        if (v->label == label) {
            if (ant)
                ant->next = v->next;
            else
                g->first = v->next;

            value = v->value;
            free(v);
            g->n--;
            break;
        }

        ant = v;
        v = v->next;
    }

    return value;
}

void *Graph_removeEdge(Graph *g, int label1, int label2) {
    assert(g != NULL);
    assert(label1 >= 0);
    assert(label2 >= 0);

    Vertex *v1 = Graph_find(g, label1);
    assert(v1 != NULL);

    Vertex *v2 = Graph_find(g, label2);
    assert(v2 != NULL);

    Edge *ant = NULL;
    void *value = NULL;
    
    Edge *e = v1->first;
    while (e) {
        if (e->head->label == label2) {
            if (ant)
                ant->next = e->next;
            else
                v1->first = e->next;

            value = e->head->value;
            free(e);
            v1->n--;
            break;
        }
        ant = e;
        e = e->next;
    }

    return value;
}