reset
set title 'Merge Sort'
set ylabel 'time(sec)'
set xlabel 'input size'
set term png enhanced font 'Verdana,10'
set output 'merge-perf.png'

plot [10000:60000][:0.05]'merge-perf.txt' using 1:2 with linespoints linewidth 2 title 'Avg', \
'' using 1:3 with linespoints linewidth 2 title 'Worst'