set terminal svg size 950,720 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

# Key means label...
set xlabel 'Количество элементов в дереве'
set ylabel 'Время поиска элемента, с'
set title 'Зависимость высоты дерева от количества добавленных в него узлов'
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set border lw 2
set grid
set key top left
set tics out
set yrange [0:0.00001]
set xrange [0:210000]
set xtics 20000
set mxtics
set format y "%10f"
plot  "data.txt" using 1:2 title 'AVL tree' with linespoints ls 3