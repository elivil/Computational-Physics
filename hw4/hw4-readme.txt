HW4 Subtractive cancellation

A) The code is in suma.cc. As requested in the specification, the sums are calculated with single precision (float data type). The output is written
into the file suma.dat. The code works up from N=1 to N=1,000,000 in factors of 10. The plot was made using gnuplot and is in the file sumaplot.png.

B) The code is in sumb.cc. Since the precision is not specified, the sums are calculated with double precision. The output is written into the file
sumb.dat. The code works up from N=1 to N=1,000,000 in factors of 10. The plot was made using gnuplot and is in the file sumbplot.png. As we can see,
the downward sum is more precise since the sum goes from smaller terms to larger terms thus reducing the roundoff error.

C) Sqrt(x^2+1) - x = (x^2+1-x^2)/(Sqrt(x^2+1)+x) = 1/(Sqrt(x^2+1)+x)
   1 - Sin(x) = (1-(Sin(x))^2)/(1+Sin(x)) = (Cos(x))^2/(1+Sin(x))
   The expressions on RHS do not have subtractive cancellation errors.
