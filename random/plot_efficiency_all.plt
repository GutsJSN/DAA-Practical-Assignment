set datafile separator "\t"
set title "Time/Comparison Efficiency Analysis (All Algorithms)"
set xlabel "Array Size"
set ylabel "Time per Comparison (nanoseconds)"
set grid
set key outside right top
set logscale y

# Use distinct line styles, point types, and colors for better visibility
plot "sorting_efficiency_random.txt" using 1:2 with linespoints pt 7 ps 1.5 lw 2 lc rgb "red" title "Bubble Sort", \
     "sorting_efficiency_random.txt" using 1:3 with linespoints pt 9 ps 1.5 lw 2 lc rgb "blue" title "Insertion Sort", \
     "sorting_efficiency_random.txt" using 1:4 with linespoints pt 5 ps 1.5 lw 2 lc rgb "green" title "Merge Sort", \
     "sorting_efficiency_random.txt" using 1:5 with linespoints pt 11 ps 1.5 lw 2 lc rgb "purple" title "Quick Sort (First)", \
     "sorting_efficiency_random.txt" using 1:6 with linespoints pt 13 ps 1.5 lw 2 lc rgb "orange" title "Quick Sort (Random)", \
     "sorting_efficiency_random.txt" using 1:7 with linespoints pt 2 ps 1.5 lw 2 lc rgb "cyan" title "Quick Sort (Median)", \
     "sorting_efficiency_random.txt" using 1:8 with linespoints pt 4 ps 1.5 lw 2 lc rgb "brown" title "Heap Sort", \
     "sorting_efficiency_random.txt" using 1:9 with linespoints pt 6 ps 1.5 lw 2 lc rgb "black" title "Radix Sort"

# Save the plot as a PNG file
set terminal png size 1200,800
set output "sorting_efficiency_analysis_all.png"
replot
