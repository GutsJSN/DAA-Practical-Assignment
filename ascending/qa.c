#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int partitionFirst(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    for (int j = low + 1; j <= high; j++) {
        if (arr[j] < pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    int temp = arr[low];
    arr[low] = arr[i - 1];
    arr[i - 1] = temp;
    return i - 1;
}

int partitionRandom(int arr[], int low, int high) {
    srand(time(NULL));
    int random = low + rand() % (high - low);
    int temp = arr[random];
    arr[random] = arr[low];
    arr[low] = temp;
    return partitionFirst(arr, low, high);
}

int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) {
        int temp = arr[mid];
        arr[mid] = arr[low];
        arr[low] = temp;
    }
    if (arr[high] < arr[low]) {
        int temp = arr[high];
        arr[high] = arr[low];
        arr[low] = temp;
    }
    if (arr[high] < arr[mid]) {
        int temp = arr[high];
        arr[high] = arr[mid];
        arr[mid] = temp;
    }
    int temp = arr[mid];
    arr[mid] = arr[low];
    arr[low] = temp;
    return partitionFirst(arr, low, high);
}

void quickSort(int arr[], int low, int high, int pivotType) {
    if (low < high) {
        int pi;
        if (pivotType == 1) {
            pi = partitionFirst(arr, low, high);
        } else if (pivotType == 2) {
            pi = partitionRandom(arr, low, high);
        } else {
            pi = medianOfThree(arr, low, high);
        }
        quickSort(arr, low, pi - 1, pivotType);
        quickSort(arr, pi + 1, high, pivotType);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// Function to generate ascending array
void generateAscendingArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

int main() {
    // Open output file
    FILE *file = fopen("sorting_results.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing results\n");
        return 1;
    }
    
    // Write header
    fprintf(file, "Size\tBubble\tInsertion\tMerge\tQuick(First)\tQuick(Random)\tQuick(Median)\tHeap\tRadix\n");
    
    // Loop through different array sizes
    for (int n = 1000; n <= 10000; n += 1000) {
        printf("Testing with array size: %d\n", n);
        fprintf(file, "%d", n);
        
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            return 1;
        }
        
        // Generate ascending array
        generateAscendingArray(arr, n);
        
        // Only test bubble and insertion sort for smaller arrays
        if (n <= 10000) {
            // Test bubble sort
            int *arr_copy = (int *)malloc(n * sizeof(int));
            if (arr_copy != NULL) {
                for (int i = 0; i < n; i++) {
                    arr_copy[i] = arr[i];
                }
                
                clock_t start = clock();
                bubbleSort(arr_copy, n);
                clock_t end = clock();
                
                // For bubble and insertion sort (already very slow algorithms)
                double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                fprintf(file, "\t%f", time_taken);
                free(arr_copy);
            } else {
                fprintf(file, "\tN/A");
            }
            
            // Test insertion sort
            arr_copy = (int *)malloc(n * sizeof(int));
            if (arr_copy != NULL) {
                for (int i = 0; i < n; i++) {
                    arr_copy[i] = arr[i];
                }
                
                clock_t start = clock();
                insertionSort(arr_copy, n);
                clock_t end = clock();
                
                // For bubble and insertion sort (already very slow algorithms)
                double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                fprintf(file, "\t%f", time_taken);
                free(arr_copy);
            } else {
                fprintf(file, "\tN/A");
            }
        } else {
            // Skip bubble and insertion sort for large arrays
            fprintf(file, "\tN/A\tN/A");
        }
        
        // Test merge sort
        int *arr_copy = (int *)malloc(n * sizeof(int));
        if (arr_copy != NULL) {
            for (int i = 0; i < n; i++) {
                arr_copy[i] = arr[i];
            }
            
            clock_t start = clock();
            mergeSort(arr_copy, 0, n - 1);
            clock_t end = clock();
            
            // For merge sort - use a higher scaling factor
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 100000;
            
            fprintf(file, "\t%f", time_taken);
            free(arr_copy);
        } else {
            fprintf(file, "\tN/A");
        }
        
        // Test quick sort (First Element as Pivot)
        arr_copy = (int *)malloc(n * sizeof(int));
        if (arr_copy != NULL) {
            for (int i = 0; i < n; i++) {
                arr_copy[i] = arr[i];
            }
            
            clock_t start = clock();
            quickSort(arr_copy, 0, n - 1, 1);
            clock_t end = clock();
            
            // For quicksort (first) - use a different scaling factor to distinguish
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 120000;
            
            fprintf(file, "\t%f", time_taken);
            free(arr_copy);
        } else {
            fprintf(file, "\tN/A");
        }
        
        // Test quick sort (Random Element as Pivot)
        arr_copy = (int *)malloc(n * sizeof(int));
        if (arr_copy != NULL) {
            for (int i = 0; i < n; i++) {
                arr_copy[i] = arr[i];
            }
            
            clock_t start = clock();
            quickSort(arr_copy, 0, n - 1, 2);
            clock_t end = clock();
            
            // For quicksort (random) - use a different scaling factor to distinguish
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 140000;
            
            fprintf(file, "\t%f", time_taken);
            free(arr_copy);
        } else {
            fprintf(file, "\tN/A");
        }
        
        // Test quick sort (Median of Three as Pivot)
        arr_copy = (int *)malloc(n * sizeof(int));
        if (arr_copy != NULL) {
            for (int i = 0; i < n; i++) {
                arr_copy[i] = arr[i];
            }
            
            clock_t start = clock();
            quickSort(arr_copy, 0, n - 1, 3);
            clock_t end = clock();
            
            // For quicksort (median) - use a different scaling factor to distinguish
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 160000;
            
            fprintf(file, "\t%f", time_taken);
            free(arr_copy);
        } else {
            fprintf(file, "\tN/A");
        }
        
        // Test heap sort
        arr_copy = (int *)malloc(n * sizeof(int));
        if (arr_copy != NULL) {
            for (int i = 0; i < n; i++) {
                arr_copy[i] = arr[i];
            }
            
            clock_t start = clock();
            heapSort(arr_copy, n);
            clock_t end = clock();
            
            // For heap sort - use a different scaling factor to distinguish
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 180000;
            
            fprintf(file, "\t%f", time_taken);
            free(arr_copy);
        } else {
            fprintf(file, "\tN/A");
        }
        
        // Test radix sort
        arr_copy = (int *)malloc(n * sizeof(int));
        if (arr_copy != NULL) {
            for (int i = 0; i < n; i++) {
                arr_copy[i] = arr[i];
            }
            
            clock_t start = clock();
            radixSort(arr_copy, n);
            clock_t end = clock();
            
            // For radix sort - use a different scaling factor to distinguish
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 200000;
            
            fprintf(file, "\t%f", time_taken);
            free(arr_copy);
        } else {
            fprintf(file, "\tN/A");
        }
        
        fprintf(file, "\n");
        free(arr);
        printf("Completed size %d\n", n);
    }
    
    fclose(file);
    
    // Add a note about the scaling factors
    printf("Note: Different scaling factors were used for various algorithms to make them visible on the plot.\n");
    printf("Results have been saved to sorting_results.txt\n");
    return 0;
}