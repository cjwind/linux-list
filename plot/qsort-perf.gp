reset
set title 'Quick Sort'
set ylabel 'time(sec)'
set xlabel 'input size'
set term png enhanced font 'Verdana,10'
set output 'qsort-perf.png'

plot [10000:60000][:26]'qsort-perf.txt' using 1:2 with linespoints linewidth 2 title 'Avg', \
'' using 1:3 with linespoints linewidth 2 title 'Worst'