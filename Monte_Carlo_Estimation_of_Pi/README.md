<h1>Description</h1>
Create plots to visualize a monte carlo estimation of PI. 

plot.sh is a shell script that utilizes the program monte_carlo.c, which was provided. 
The purpose of monte_carlo.c is to estimate PI.
monte_carlo.c is a program that randomly creates coordinate points ranging from [0,1] on the x-axis and
[0,1] on the y-axis. Then it analyses whether each point is in the circle x^2 + y^2 = 1. The number of points
that are in the circle is divided by the total number of points times 4. This gives an estimation for PI.
The more points that the program uses, the more accurate its estimation of PI gets. At around 4000 points,
the estimation for PI gets very accurate. 

In plot.sh I rebuilt the monte_carlo executable 5 times. 

plot.sh creates two plots, saved in "figure2.pdf" and "figure3.pdf". The first plot is all the points created by one
monte_carlo executable. The points are color coded either blue or red based on whether or not they are in the cirle
x^2 + y^2 = 1. The second plot graphs the error between the PI estimate and actual PI along the y-axis and the
number of points along the x-axis. All 5 executables are graphed. 

The Makefile was provided. It creates a monte_carlo executable.

<h1>Usage</h1>
To use plot.sh, one must download plot.sh, monte_carlo.c, and the Makefile. Then, running plot.sh in the same 
working directory is sufficient to run the program. 

In plot.sh I rebuilt the monte_carlo executable 5 times. Between each rebuild, I used the 'sleep' command
to make the processor wait 1.1 seconds. This is because monte_carlo.c uses a seed to randomly generate 
coordinate points. The seed resets every 1 second, so I had to make sure the processor waited. If I did not
do this, the points of 2 different executables could be the same. 

<h2>Example</h2>
To run the shell script, simply use 

chmod +x plot.sh
./plot.sh

To view the resulting plots, check your current working directory for figure2.pdf and figure3.pdf. 

<h1>Author</h1>
Githika Annapureddy
