#!/bin/bash
#perl script.pl pi pi 500 10000 500 8 > plot0
#echo "execucio base feta"
#perl script.pl pi pi1 500 10000 500 8 > plot1
#echo "execucio 1 feta"
#perl script.pl pi pi3 500 10000 500 8 > plot3
#echo "execucio 3 feta"
gnuplot <<- EOF
        set xlabel "Decimals"
        set ylabel "Time(s)"
        set term png
        set output "plot.png"
        plot "plot0" title "Original" with pointslines, "plot1" title "O1" with pointslines, "plot3" title "O3" with pointslines  
EOF
perl converteix.pl plot0 > cplot0
perl converteix.pl plot1 > cplot1
perl converteix.pl plot3 > cplot3
gnuplot <<- EOF
        set xlabel "Decimals"
        set ylabel "Time(s)/Decimals"
        set term png
        set output "cplot.png"
        plot "cplot0" title "Original" with pointslines, "cplot1" title "O1" with pointslines, "cplot3" title "O3" with pointslines  
EOF
