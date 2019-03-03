reset
set title 'Worst case'
set ylabel 'time(sec)'
set xlabel 'input size'
set term png enhanced font 'Verdana,10'
set output 'worst-perf.png'

plot [10000:60000][:26]'worst-perf.txt' using 1:2 with linespoints linewidth 2 title 'Insertion', \
'' using 1:3 with linespoints linewidth 2 title 'Quick', \
'' using 1:4 with linespoints linewidth 2 title 'Merge'