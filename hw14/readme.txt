HW 14

Part A: 
Compiling and running lineq.c one obtains the solution vector x=(1,1,1).


Part B: 
Code to solve the Hilbert equation is in hilbert.cc. Running it, one correctly obtains x=(1,0,0,...,0).


Part C: 
Code to solve 1st-order auto-regressive process (using dgesv) is in ar-dgesv.cc. Code to solve the same problem using dposv is in ar-dposv.cc. Timing them 
gives that dposv runs faster by about 0.1-0.15 s.
