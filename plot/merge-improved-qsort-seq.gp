reset
set title 'Sequential Input (Improved Quick Sort)'
set ylabel 'time(sec)'
set xlabel 'input size'
set term png enhanced font 'Verdana,10'
set output 'merge-improved-qsort-seq.png'

plot [10000:60000][:0.03]'merge-improved-qsort-seq.txt' using 1:2 with linespoints linewidth 2 title 'Quick', \
'' using 1:3 with linespoints linewidth 2 title 'Merge'