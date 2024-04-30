#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    Node *current;
    int size;
    int data_size;
    void (*free_data)(void *data);
} List;

void Lista_new(List *lista, int data_size, void (*free_data)(void *)) {
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    lista->size = 0;
    lista->data_size = data_size;
    lista->free_data = free_data;
}
void Lista_delete(List *lista) {
    Node *current = lista->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        if (lista->free_data != NULL) {
            lista->free_data(current->data);
        }
        free(current->data);
        free(current);
        current = next;
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    lista->size = 0;
}

int Lista_isEmpty(List *lista) {
    return lista->size == 0;
}

int Lista_size(List *lista) {
    return lista->size;
}

void Lista_pushFront(List *lista, void *valor) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = malloc(lista->data_size);
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(new_node->data, valor, lista->data_size);
    new_node->next = lista->head;
    lista->head = new_node;
    if (lista->size == 0) {
        lista->tail = new_node;
    }
    lista->size++;
}
void Lista_pushBack(List *lista, void *valor) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = malloc(lista->data_size);
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(new_node->data, valor, lista->data_size);
    new_node->next = NULL;

    if (lista->size == 0) {
        lista->head = new_node;
    } else {
        lista->tail->next = new_node;
    }
    lista->tail = new_node;
    lista->size++;
}

int Lista_search(List *lista, void *chave, void *dest, int (*cmp)(void *, void *)) {
    Node *current = lista->head;

    while (current != NULL) {
        if (cmp(current->data, chave) == 0) {
            memcpy(dest, current->data, lista->data_size);
            return 1; // Retorna 1 se a chave foi encontrada
        }
        current = current->next;
    }

    return 0; // Retorna 0 se a chave não foi encontrada
}

void Lista_first(List *lista) {
    lista->current = lista->head;
}
void Lista_last(List *lista) {
    lista->current = lista->tail;
}

int Lista_next(List *lista) {
    if (lista->current != NULL) {
        lista->current = lista->current->next;
        return 1; // Retorna 1 se há um próximo nó
    } else {
        return 0; // Retorna 0 se não há um próximo nó
    }
}

void Lista_current(List *lista, void *dest) {
    if (lista->current != NULL) {
        memcpy(dest, lista->current->data, lista->data_size);
    } else {
        fprintf(stderr, "No current node\n");
        exit(EXIT_FAILURE);
    }
}
void Lista_remove(List *lista, void *chave, int (*cmp)(void *, void *)) {
    Node *current = lista->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (cmp(current->data, chave) == 0) {
            if (prev == NULL) { // Se o nó a ser removido for o primeiro
                lista->head = current->next;
                if (lista->head == NULL) { // Se a lista ficar vazia após a remoção
                    lista->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next == NULL) { // Se o nó a ser removido for o último
                    lista->tail = prev;
                }
            }

            if (lista->free_data != NULL) {
                lista->free_data(current->data);
            }
            free(current->data);
            free(current);
            lista->size--;
            return; // Sai da função após remover o nó
        }
        prev = current;
        current = current->next;
    }
}
void Lista_insertAfter(List *lista, void *dado) {
    if (lista->current != NULL) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        new_node->data = malloc(lista->data_size);
        if (new_node->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        memcpy(new_node->data, dado, lista->data_size);
        new_node->next = lista->current->next;

        lista->current->next = new_node;

        if (lista->current == lista->tail) {
            lista->tail = new_node;
        }
        lista->size++;
    } else {
        fprintf(stderr, "No current node\n");
        exit(EXIT_FAILURE);
    }
}

int cmp_int(void *a, void *b) {
    int *num_a = (int *)a;
    int *num_b = (int *)b;
    if (*num_a == *num_b) {
        return 0; // Chaves iguais
    } else if (*num_a < *num_b) {
        return -1; // Chave 'a' menor que chave 'b'
    } else {
        return 1; // Chave 'a' maior que chave 'b'
    }
}
int main() {
    // Seu código principal aqui...
    return 0;
}
