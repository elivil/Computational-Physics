HW8

The drivers for interpolation are in neville.cc and cubspline.cc. I had to make some (small - mostly array indexing) adjustments to the subroutines 
polint.cc, spline.cc, splint.cc, so to compile and check the drivers make sure to use these modified subroutines.

The results of the interpolation are drawn in neville-plot.png, neville-error.png and spline-plot.png. 
Based on Neville's algorithm, the resonance energy = 75 MeV, FWHM = 58 MeV.
Based on cubic spline algorithm, the resonance energy = 76 MeV, FWHM = 58 MeV.