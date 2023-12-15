#!/bin/bash

make clean && make monte_carlo #rebuilds the monte_carlo executable
./monte_carlo -n 16384 > /tmp/monte_carlo1.dat #places the data into a .dat file
sleep 1.1
make clean && make monte_carlo #rebuilds the monte_carlo executable
./monte_carlo -n 16384 > /tmp/monte_carlo2.dat #places the data into a .dat file
sleep 1.1
make clean && make monte_carlo #rebuilds the monte_carlo executable
./monte_carlo -n 16384 > /tmp/monte_carlo3.dat #places the data into a .dat file
sleep 1.1
make clean && make monte_carlo #rebuilds the monte_carlo executable
./monte_carlo -n 16384 > /tmp/monte_carlo4.dat #places the data into a .dat file
sleep 1.1
make clean && make monte_carlo #rebuilds the monte_carlo executable
./monte_carlo -n 16384  > /tmp/monte_carlo5.dat #places the data into a .dat file

#figure 2
gnuplot <<END
set terminal pdf
set output "figure2.pdf"
#set title "Figure 2"
set xlabel "x"
set ylabel "y"
set xrange[0:1]
set yrange[0:1]
set size square

f(x) = sqrt(1 - (x * x))

set key autotitle columnhead
set palette defined (0 "red", 1 "blue")
unset key
unset colorbox
plot f(x) linecolor 0,  "/tmp/monte_carlo1.dat" using 3:4:5 with points palette ps .1  pt 7

#plot f(x) linecolor 0,  "/tmp/monte_carlo1.dat" using 3:4:5 with points palette ps .1  pt 7, "/tmp/monte_carlo2.dat" using 3:4:5 with points palette ps .1  pt 7, "/tmp/monte_carlo3.dat" using 3:4:5 with points palette ps .1  pt 7, "/tmp/monte_carlo4.dat" using 3:4:5 with points palette ps .1  pt 7, "/tmp/monte_carlo5.dat" using 3:4:5 with points palette ps .1  pt 7

END


#extracting PI estimates for each run
#subtract PI from it
#put it back into the value
awk '{$2=($2 - 3.1415926535); print ;}' /tmp/monte_carlo1.dat > /tmp/changed_monte_carlo.dat
mv /tmp/changed_monte_carlo.dat /tmp/monte_carlo1.dat && > /tmp/changed_monte_carlo.dat
awk '{$2=($2 - 3.1415926535); print ;}' /tmp/monte_carlo2.dat > /tmp/changed_monte_carlo.dat
mv /tmp/changed_monte_carlo.dat /tmp/monte_carlo2.dat && > /tmp/changed_monte_carlo.dat
awk '{$2=($2 - 3.1415926535); print ;}' /tmp/monte_carlo3.dat > /tmp/changed_monte_carlo.dat
mv /tmp/changed_monte_carlo.dat /tmp/monte_carlo3.dat && > /tmp/changed_monte_carlo.dat
awk '{$2=($2 - 3.1415926535); print ;}' /tmp/monte_carlo4.dat > /tmp/changed_monte_carlo.dat
mv /tmp/changed_monte_carlo.dat /tmp/monte_carlo4.dat && > /tmp/changed_monte_carlo.dat
awk '{$2=($2 - 3.1415926535); print ;}' /tmp/monte_carlo5.dat > /tmp/changed_monte_carlo.dat
mv /tmp/changed_monte_carlo.dat /tmp/monte_carlo5.dat && > /tmp/changed_monte_carlo.dat






#figure 3
gnuplot <<END
set terminal pdf
set output "figure3.pdf"
set title "Monte Carle Error Estimation"
set ylabel "Error"
set xrange[1:16384]
set yrange[-1:1]
set logscale x 4
unset key
set grid xtics ytics
set grid

plot "/tmp/monte_carlo1.dat" using 1:2 with lines, "/tmp/monte_carlo2.dat" using 1:2 with lines, "/tmp/monte_carlo3.dat" using 1:2 with lines, "/tmp/monte_carlo4.dat" using 1:2 with lines, "/tmp/monte_carlo5.dat" using 1:2 with lines

END

