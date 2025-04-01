set datafile separator "\t"
set title "QuickSort Variants Performance Comparison (Random Arrays)"
set xlabel "Array Size"
set ylabel "Time (nanoseconds)"
set grid
set key left top
set format y "%.0f"

# Use different line styles and colors
plot "sorting_results_random.txt" using 1:5 with linespoints pt 7 ps 1.5 lw 2 title "Quick Sort (First Element)", \
     "sorting_results_random.txt" using 1:6 with linespoints pt 9 ps 1.5 lw 2 title "Quick Sort (Random Element)", \
     "sorting_results_random.txt" using 1:7 with linespoints pt 5 ps 1.5 lw 2 title "Quick Sort (Median-of-Three)"

# Save the plot as PNG
set terminal png size 1200,800 enhanced font "Arial,12"
set output "quicksort_random_comparison.png"
replot