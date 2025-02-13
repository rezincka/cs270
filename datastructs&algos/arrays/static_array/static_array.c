#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity; 
} Array;

void array_init(Array *arr, size_t initial_capacity) {
    arr->data = (int *)malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
}

void array_append(Array *arr, int value) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int *)realloc(arr->data, arr->capacity * sizeof(int));
        if (arr->data == NULL) {
            fprintf(stderr, "Memory allocation error!\n");
            exit(EXIT_FAILURE);
        }
    }
    arr->data[arr->size++] = value;
}

void array_print(Array *arr) {
    for (size_t i = 0; i < arr->size; i++) {
        printf("arr[%zu] = %d\n", i, arr->data[i]);
    }
}

void array_free(Array *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

int main() {
    Array arr;
    
    array_init(&arr, 4);
    
    array_append(&arr, 10);
    array_append(&arr, 20);
    array_append(&arr, 30);
    array_append(&arr, 40);
    array_append(&arr, 50);
    
    array_print(&arr);
    
    array_free(&arr);
    
    return 0;
}
