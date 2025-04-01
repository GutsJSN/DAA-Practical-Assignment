# DAA Practical Assignment

## Data Generation and Experimental Setup

### Machine Specifications
- **CPU:** 12 × 13th Gen Intel® Core™ i5-1335U
- **RAM:** 16 GB
- **Operating System:** Linux Ubuntu 22.04
- **Compiler:** GCC with optimization level `-O2`

### Timing Mechanism
- Used C’s `<time.h>` library with `clock()` function to measure CPU time.
- Time was calculated as:
  ```c
  ((double)(end - start)) / CLOCKS_PER_SEC * 1000000000.0
  ```
- All times are reported in nanoseconds for better readability and comparison.

### Experiment Repetition
- Each algorithm was run **5 times** for each input size.
- The **median time** of these 5 runs was used for the final report to filter outliers.

### Reported Times
- The time reported is **only the execution time** of the sorting algorithm itself.
- Time for array generation and memory allocation was excluded from measurements.

### Input Selection
- Array sizes ranged from **1000 to 10000** elements, with increments of **1000**.
- Three types of input arrays were used:
  1. **Sorted arrays** (elements in ascending order: 1, 2, 3, ...)
  2. **Reverse-sorted arrays** (elements in descending order: n, n-1, n-2, ...)
  3. **Randomly shuffled arrays**

### Consistency Across Algorithms
- The **same input arrays** were used for all sorting algorithms.
- For each size and type, identical copies of arrays were created to ensure fair comparison.
- **Bubble sort and insertion sort** were only tested on arrays up to **5000 elements** due to their quadratic time complexity.

### Special Considerations
- For **quicksort**, three different pivot selection strategies were tested:
  1. **First element** as pivot
  2. **Random element** as pivot
  3. **Median-of-three** as pivot
- Results were written to a **tab-separated file** for easy plotting with **gnuplot**.

