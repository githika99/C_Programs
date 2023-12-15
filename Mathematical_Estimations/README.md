<h1>Description</h1>
This project is comprised of the files: e.c, bbp.c, euler.c, madhava.c, viete.c, newton.c, mathlib-test.c, Makefile, and mathlib.h, which was provided. 

e.c is comprised of the functions e() and e\_terms(). e() estimates the value for the mathematical constant e. It does this using the Taylor Series of the equation 1/k!. So, as 1/k! is added to a total sum, and as k approaches infinity, the total sum approaches the vale of e. In my program, once the estimation is within epsilon (provided to be 1e-14) of the true value, it stops running. e() returns this estimation.

e\_terms() returns the number of terms used in the Taylor series to reach this estimation. In my program, this number is 23. 

bbp.c is comprised of the functions pi\_bbp() and pi\_bbp\_terms(). pi\_bbp() estimates the value of pi. It does this using the Taylor series for the equation (16^(-k) times (4/(8k + 1) - 2/(8k + 4) - 1/(8k + 5) - 1/(8k + 6))). As each term is added to a total sum, and as k approaches infinity, the total sum approaches the value of pi. In my program, once the estimation is within epsilon (provided to be 1e-14) of the true value, it stops running. pi\_bbp() returns this estimation.

pi\_bbp\_terms() returns the number of terms used in the Taylor series to reach this estimation. In my program, this number is 11.

euler.c is comprised of the functions pi\_euler() and pi\_euler\_terms(). pi\_euler() estimates the value for pi. It does this using the Taylor Series of the equation 1/(k^)2.As each term is added to a total sum, and as k approaches infinity, the total sum gets larger . Then, the square root of the total sum is multiplied by the square root of 6. This yields an approximation of pi.  In my program, once the estimation is within epsilon (provided to be 1e-14) of the true value, it stops running. pi\_euler() returns this estimation.

pi\_euler\_terms() returns the number of terms used in the Taylor series to reach this estimation. In my program, this number is 10000000.

madhava.c is comprised of the functions pi\_madhava() and pi\_madhava\_terms(). pi\_madhava() estimates the value of pi. It does this using the Taylor series for the equation ((-3) ^ (-k) )/(2k + 1). As each term is added to a total sum, and as k approaches infinity, the total sum approaches the value of pi divided by 12 squared. So the total sum is multiplied by 12 squared. In my program, once the estimation is within epsilon (provided to be 1e-14) of the true value, it stops running. pi\_madhava() returns this estimation.

pi\_madhava\_terms() returns the number of terms used in the Taylor series to reach this estimation. In my program, this number is 27.

viete.c is comprised of the functions pi\_viete() and pi\_viete\_terms(). pi\_viete() estimates the value of pi. It does this mutiplying the square root of (2 times the previous value) to the total sum. The previous value starts off as 0. As each term is added to a total sum, and as k approaches infinity, the total sum approaches the value of 2/pi. So, the total sum is divided by 2 and then the sum is made equal to one over the sum. In my program, once the estimation is within epsilon (provided to be 1e-14) of the true value, it stops running. pi\viete() returns this estimation.

pi\_viete\_terms() returns the number of terms used in the Taylor series to reach this estimation. In my program, this number is 23.

newton.c is comprised of the functions sqrt\_newton(double x) and sqrt\_newton\_iters(). sqrt\_newton(double x) takes a value x as its parameter and then finds the square root of that number through the Newton-Raphson method. This method tests if the difference between each guess is less than epsilon in order to break the loop. Each guess is found through finding the derivative of the line passing through the previous guess and x. The guess starts off as 1.0. sqrt\_newton(double x) returns this guess.

sqrt\_newton\_iters() returns the number of iterations through a loop it took for sqrt\_newton() to return the final guess value. This number changes based on the given x, but ranges from 1 to 7 for most positive numbers. 

mathlib-test.c has one main function that tests the various other programs. 

mathlib.h is a header file that contains all of the functions in all of the other programs. This file simply needs to be included at the beginning of all the ohter files so that all the files can use the functions of each other. It also contains the value of epsilon that is used by the other programs. Finally, it contains a function to find the absolute value of two doubles so that the absolute value function from the math library does not need to be used.

Makefile creates the executable mathlib-test. It does not create executables for the other files, since their purpose is not to be executed, but rather their functions are meant to be called in mathlib-test.c. 

<h1>Usage</h1>

In order to use the files, they first must all be downloaded in the same directory. Then, the command 'make' should be entered. This creates the executable mathlib-test. This can be executed using './mathlib-test'. Several exentions can be used to test specific programs. '-a' runs all the tests. '-e' runs the test for e.c. '-v' runs the test for viete.c. '-r' runs the test for euler.c. '-b' runs the test for bbp.c. '-m' runs the test for madhava.c. '-n' runs the test for newton.c. Adding '-s' after any of the other extentions causes the number of terms or iterations it took for that test to also be printed. 

<h2>Example</h2>
$ make
$ ./mathlib-test -a -s

This should print out all the test cases and the number of terms that each test required.

<h1>Author</h1>
Githika Annapureddy

