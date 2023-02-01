
#define MIN     0
#define MAX     1
#define ODD     2
#define EVEN    3
#define MINMAX  4
#define ODDEVEN 5

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "memory.h"
#include "buffer.h"

int *inputBuffer = NULL;
int *outputBuffer = NULL;

// two functions provided to you (defined in io.h and io.c) are:

// int get_value(void);
//       this function generates a single value
//       you use it to obtain this value and put it into an input buffer

// int submit_result(int[]);
//       you use this function to submit the data processing results
//       for validation (your results are checked inside this function)


int reading() {

    int operation_ID = get_value();
    if(operation_ID == -1){
        return -1;
    }
    else {
        int number_of_points = get_value();
        inputBuffer = (int *) my_malloc((number_of_points + 2) * sizeof(int));

        for (int j = 0; j < number_of_points + 2; j++) {
            inputBuffer[j] = 0;
        }
        inputBuffer[0] = operation_ID;
        inputBuffer[1] = number_of_points;

        for (int i = 0; i < number_of_points; i++) {
            inputBuffer[i + 2] = get_value();
        }
        // printing the input buffer contents
        printf("inputBuffer elements \n");
        for (int j = 0; j < number_of_points + 2; j++) {

            printf("%d ", inputBuffer[j]);
        }
        printf("\n");
        return number_of_points;
    }
    }
    
void transferringTOlocal(int* localBuffer) {

    // freeing memory borrowed from reading, and transferring the contents of the input buffer to local buffer
    for (int i=0;i<inputBuffer[1]+2;i++)
    {
        localBuffer[i] = inputBuffer[i];
    }
    my_free(inputBuffer);
}

void processing(int *localBuffer) {
    // printing local buffer prior the operations performed

    printf("local buffer elements \n");
    for (int j = 0; j < localBuffer[1]+2; j++) {

        printf("%d ", localBuffer[j]);
    }
    printf("\n");

    // Declaration of local variables
    int Max = localBuffer[2];
    int Min = localBuffer[2];
    int odd = 0;
    int even = 0;

    // Operation ID
    int x = localBuffer[0];

    switch (x) {
        // Minimum value
        case MIN:
            for (int r = 0; r < localBuffer[1]; r++) {
                if (Min > localBuffer[r+2]) {

                    Min = localBuffer[r+2];
                }
                localBuffer[2] = Min;
            }
            break;

            // Max value
        case MAX:
            for (int f = 0; f < localBuffer[1]; f++) {
                if (Max < localBuffer[f+2]) {

                    Max = localBuffer[f+2];
                }
                localBuffer[2] = Max;
            }
            break;

            // odd determinant
        case ODD:
            for(int t = 0; t<localBuffer[1];t++){
                if ((localBuffer[t+2] % 2)== 1){
                    odd++;
                }
            }
            localBuffer[2] = odd;
            break;

            // even determinant
        case EVEN:
            for(int y = 0; y<localBuffer[1];y++){
                if ((localBuffer[y+2] % 2) == 0){
                    even++;
                }
                localBuffer[2] = even;
            }
            break;

            // min and max determinant
        case MINMAX:
            for (int r = 0; r < localBuffer[1]; r++) {
                if (Min > localBuffer[r+2]) {

                    Min = localBuffer[r+2];
                }
            }
            for (int q = 0; q < localBuffer[1]; q++) {
                if (Max < localBuffer[q+2]) {

                    Max = localBuffer[q+2];
                }
            }
            localBuffer[2] = Min;
            localBuffer[3] = Max;
            break;

            // Odd and even determination
        case ODDEVEN:
            for(int t = 0; t<localBuffer[1];t++){
                if ((localBuffer[t+2] % 2) == 1){
                    odd = odd + 1;
                }
            }

            for(int y = 0; y<localBuffer[1];y++){
                if ((localBuffer[y+2] % 2) == 0){
                    even = even + 1;
                }
            }

            localBuffer[2] = odd;
            localBuffer[3] = even;
            break;

        default:
            printf("the operation ID is not in the range of 0-5");
            break;
    }
}

void transferringFROMlocal(int *localBuffer) {

    int x = sizeof*localBuffer;
    // allocate memory to output buffer, output buffer have max 5 elements
    outputBuffer = (int *)my_malloc(x*sizeof(int));
    for (int i = 0; i <4; i++) {
        outputBuffer[i] = localBuffer[i];
    }
}

void submitting() {

    // ensuring the correct format for the output buffer's second value depending on the operation ID
    int x = outputBuffer[0];

    switch (x) {
        case 0:
            outputBuffer[1] = 1;
            break;
        case 1:
            outputBuffer[1] = 1;
            break;
        case 2:
            outputBuffer[1] = 1;
            break;
        case 3:
            outputBuffer[1] = 1;
            break;
        case 4:
            outputBuffer[1] = 2;
            break;
        case 5:
            outputBuffer[1] = 2;
            break;
        default:
            printf("No ID matched");
            break;
    }

    // printing output buffer with specified conditions
    printf("Output buffer elements \n");
    if(outputBuffer[0] == 1 || outputBuffer[0] == 0 || outputBuffer [0] == 2 || outputBuffer[0] == 3)
        for (int j = 0; j < 3; j++) {

            printf("%d ", outputBuffer[j]);
        }
    else {
        for (int j = 0; j < 4; j++) {

            printf("%d ", outputBuffer[j]);
        }
    }
    printf("\n");

    // Confirming the results
    printf("%d \n", submit_results(outputBuffer));
    printf("\n");
    my_free(outputBuffer);
}


