#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;


void dynamic_array_init(DynamicArray *arr, size_t initial_capacity) {
    arr->size = 0;
    arr->capacity = initial_capacity;
    arr->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!arr->data) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
}


void dynamic_array_resize(DynamicArray *arr, size_t new_capacity) {
    arr->capacity = new_capacity;
    arr->data = (int *)realloc(arr->data, new_capacity * sizeof(int));
    if (!arr->data) {
        fprintf(stderr, "Memory reallocation error\n");
        exit(EXIT_FAILURE);
    }
}


void dynamic_array_push_back(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        size_t new_capacity = (arr->capacity == 0) ? 1 : arr->capacity * 2;
        dynamic_array_resize(arr, new_capacity);
    }
    arr->data[arr->size++] = value;
}

void dynamic_array_pop_back(DynamicArray *arr) {
    if (arr->size > 0) {
        arr->size--;
    }
}

int dynamic_array_get(DynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        fprintf(stderr, "Error: array index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return arr->data[index];
}

void dynamic_array_set(DynamicArray *arr, size_t index, int value) {
    if (index >= arr->size) {
        fprintf(stderr, "Error: array index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    arr->data[index] = value;
}

void dynamic_array_free(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void dynamic_array_print(DynamicArray *arr) {
    printf("Array (size: %zu, capacity: %zu): ", arr->size, arr->capacity);
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

int main() {
    DynamicArray arr;
    dynamic_array_init(&arr, 2);

    dynamic_array_push_back(&arr, 10);
    dynamic_array_push_back(&arr, 20);
    dynamic_array_push_back(&arr, 30);

    dynamic_array_print(&arr);

    printf("Element at index 1: %d\n", dynamic_array_get(&arr, 1));

    dynamic_array_set(&arr, 1, 50);
    printf("After modifying the second element:\n");
    dynamic_array_print(&arr);

    dynamic_array_pop_back(&arr);
    printf("After removing the last element:\n");
    dynamic_array_print(&arr);

    dynamic_array_free(&arr);
    return 0;
}
