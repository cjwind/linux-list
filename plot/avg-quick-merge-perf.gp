reset
set title 'Avg case'
set ylabel 'time(sec)'
set xlabel 'input size'
set term png enhanced font 'Verdana,10'
set output 'avg-quick-merge-perf.png'

plot [10000:60000][:0.055]'avg-quick-merge-perf.txt' using 1:2 with linespoints linewidth 2 title 'Quick', \
'' using 1:3 with linespoints linewidth 2 title 'Merge'