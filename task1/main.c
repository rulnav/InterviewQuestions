#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000000000
#define BOOL uint8_t
#define TRUE 1
#define FALSE 0
#define COUNT_SORT_BASE 256

void countSort(uint32_t *arr, uint32_t *output, uint32_t n, int64_t exp)
{
    // output array
    int32_t i, count[COUNT_SORT_BASE] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % COUNT_SORT_BASE]++;
 
    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (i = 1; i < COUNT_SORT_BASE; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % COUNT_SORT_BASE] - 1] = arr[i];
        count[(arr[i] / exp) % COUNT_SORT_BASE]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(uint32_t *arr, uint32_t arr_size)
{
    uint32_t *temp_arr = (uint32_t *)malloc(arr_size * sizeof(uint32_t));
    //Count sort for every digit, exp is 10^i, where i is the current digit number
    //0xFFFFFFFF is the maximum value for uint32_t
    for (int64_t exp = 1; 0xFFFFFFFF / exp > 0; exp *= COUNT_SORT_BASE){
        printf("CountSort\n");
        countSort(arr, temp_arr, arr_size, exp);
    }
    free(temp_arr);
}

int main() {
    FILE *file;
    file = fopen("full-test.bin","rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    uint32_t *buffer = (uint32_t *)malloc(BUFFER_SIZE * sizeof(uint32_t));
    if (!buffer) {
        perror("Error allocating memory!");
        return 1;
    }

    size_t bytes_read = fread((void *)buffer, sizeof(uint32_t), BUFFER_SIZE, file);
    if (bytes_read < BUFFER_SIZE){
        perror("Error reading file");
        return 1;
    }
    fclose(file);

    radixSort(buffer, BUFFER_SIZE);

    int unique_numbers = 1;
    int numbers_that_occur_only_once = (buffer[0]!=buffer[1]);
    // printf("%u ", buffer[0]);
    for(int i = 1; i < BUFFER_SIZE-1; ++i){
        // printf("%u ", buffer[i]); 
        if(buffer[i] != buffer[i-1]){
            unique_numbers++;
            if(buffer[i] != buffer[i+1]){
                numbers_that_occur_only_once++;
            }
        }
    }
    // printf("%u \n", buffer[BUFFER_SIZE-1]);
    if(buffer[BUFFER_SIZE-1]!=buffer[BUFFER_SIZE-2]){
        unique_numbers++;
        numbers_that_occur_only_once++;
    }
    free(buffer);

    printf("Unique numbers in binary file is: %u\n", unique_numbers);
    printf("Count of numbers seen only once is: %d\n", numbers_that_occur_only_once); 

    return 0;
}

// void bruteSolution(uint32_t *arr, uint32_t arr_size){
//     uint32_t *unique_num_arr = (uint32_t *)malloc(arr_size * sizeof(uint32_t));
//     uint32_t *occurance_count_arr = (uint32_t *)calloc(arr_size, sizeof(uint32_t));
//     uint32_t unique_num_arr_size = 0;
//     int32_t count_only_once = 0;
//     for(int i = 0; i < arr_size; ++i){
//         // if (!(i % 100000)) printf("%d\n",i);
//         BOOL is_unique = TRUE;
//         for(int j = 0; j < unique_num_arr_size; ++j){
//             if (unique_num_arr[j] == arr[i]) {
//                 is_unique = FALSE;
//                 count_only_once-=( (++occurance_count_arr[j]) == 2 );
//                 break;
//             }
//         }
//         if(is_unique){
//             unique_num_arr[unique_num_arr_size] = arr[i];
//             occurance_count_arr[unique_num_arr_size] = 1;
//             ++count_only_once;
//             ++unique_num_arr_size;
//         }
//         printf("%u ", arr[i]); 
//     }
//     free(unique_num_arr);
//     free(occurance_count_arr);
//
//     printf("Unique numbers in binary file is: %u\n", unique_num_arr_size);
//     printf("Count of numbers seen only once is: %d\n", count_only_once); 
// }
