set terminal png
set output "test.png"

set ylabel "Relative Humidity %"
set yrange [20:100]
set ytics nomirror tc lt 2
set y2label "Degrees Celsius"
set y2range [20:30]
set y2tics nomirror tc lt 2
set xlabel "Minutes"

plot "test.txt" using ($0/2):2 with lines title "Relative Humidity", \
     "test.txt" using ($0/2):3 with lines title "Temperature" axes x1y2
