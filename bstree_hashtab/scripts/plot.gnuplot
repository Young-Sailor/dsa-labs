#!/usr/bin/gnuplot
set termoption enhanced
set terminal png size 1280,720 font "Arial, 16"
set output "plot.png"
set style line 1 lc rgb "0xFD91FF" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x91B9FF" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "The number of elements in the dictionary"
set ylabel "Element adding time, seconds" rotate by 90
set xtics 20000
set ytics 0.00005
set mxtics
set format x "%6.0f"
set format y "%f"
plot "plotdata.dat" using 1:2 title "BSTree" with linespoints ls 1, \
"plotdata.dat" using 1:3 title "Hashtab" with linespoints ls 2