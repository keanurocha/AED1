#include <stdio.h>

#define MAX_SIZE 1001

int find_max_index(int arr[], int size) {
    if (size <= 0) return -1;
    int max_val = -1;
    int max_idx = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_idx = i;
        }
    }
    return max_idx;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int stack[MAX_SIZE];
        int stack_size = 0;

        int queue[MAX_SIZE];
        int queue_front = 0;
        int queue_rear = 0;

        int pq[MAX_SIZE];
        int pq_size = 0;

        int is_stack = 1;
        int is_queue = 1;
        int is_priority_queue = 1;

        for (int i = 0; i < n; i++) {
            int command, value;
            scanf("%d %d", &command, &value);

            if (command == 1) {
                if (is_stack) stack[stack_size++] = value;
                if (is_queue) queue[queue_rear++] = value;
                if (is_priority_queue) pq[pq_size++] = value;
            } else {
                if (is_stack) {
                    if (stack_size == 0 || stack[--stack_size] != value) {
                        is_stack = 0;
                    }
                }
                
                if (is_queue) {
                    if (queue_front >= queue_rear || queue[queue_front++] != value) {
                        is_queue = 0;
                    }
                }

                if (is_priority_queue) {
                    if (pq_size == 0) {
                        is_priority_queue = 0;
                    } else {
                        int max_idx = find_max_index(pq, pq_size);
                        if (max_idx == -1 || pq[max_idx] != value) {
                            is_priority_queue = 0;
                        } else {
                           pq[max_idx] = pq[--pq_size];
                        }
                    }
                }
            }
        }
        
        int possibilities = is_stack + is_queue + is_priority_queue;

        if (possibilities == 0) {
            printf("impossible\n");
        } else if (possibilities > 1) {
            printf("not sure\n");
        } else {
            if (is_stack) {
                printf("stack\n");
            } else if (is_queue) {
                printf("queue\n");
            } else {
                printf("priority queue\n");
            }
        }
    }
    return 0;
}