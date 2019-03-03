reset
set title 'Insert Sort'
set ylabel 'time(sec)'
set xlabel 'input size'
set term png enhanced font 'Verdana,10'
set output 'insert-perf.png'

plot [10000:60000][:14]'insert-perf.txt' using 1:2 with linespoints linewidth 2 title 'Avg', \
'' using 1:3 with linespoints linewidth 2 title 'Worst'