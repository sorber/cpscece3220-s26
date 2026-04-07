#include <stdio.h>
#include <stdlib.h>

#define NUM_VALUES 100

int main() {
    int *values[NUM_VALUES];

    for (int i=0; i < NUM_VALUES; i++) {
        values[i] = malloc(sizeof(int));
        *(values[i]) = i;
    }

    //check to see if the values are intact and free the odd values
    for (int i=0; i < NUM_VALUES; i++) {
        if (*(values[i]) != i) {
            printf("ERROR: values[%d] != %d (%d)\n", i, i, *(values[i]));
        }

        //free the odd numbered values
        if (i % 2) {
            free(values[i]);
            values[i] = NULL;
        }
    }

    //same but free the remaining values
    for (int i=0; i < NUM_VALUES; i++) {
        if (values[i] && *(values[i]) != i) {
            printf("ERROR: values[%d] != %d (%d)\n", i, i, *(values[i]));
        }

        //free the odd numbered values
        if (values[i]) {
            free(values[i]);
            values[i] = NULL;
        }
    }

    return EXIT_SUCCESS;
}