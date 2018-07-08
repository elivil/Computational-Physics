Interesting things to note:
If the right-hand wall is moved at constant speed away from the other wall, gas adiabatically expands, and its energy decreases. If it's
moved towards the other wall, gas is adiabatically compressed, and its energy increases. 

For adiabatical process P*V^(gamma)=const or T*V^(gamma-1)=const. Gamma=2*(dof/2+1)/dof where dof is the number of degrees of freedom which 
is 1 for one-dimensional gas. Hence gamma=3, and T*V^2=const. Because the internal energy is proportional to T, it will be proportional to 
V^(-2) in this situation. This is shown on the plot of energy vs time (and hence volume) for expanding gas - wallmovesaway-energy.png.

In the case of heavy mass in the centre and light masses on sides of it, we observe oscillations of the central mass about the centre. 
The frequency can be predicted for small oscillations from adiabatic properties. 

Force on the central mass is (P1-P2)*A, where P1 and P2 pressures from two sides, A is the area. Assume that in the beginning when the heavy 
mass is in the centre, the pressures on both sides are equal to P, volumes of both sides are equal to V. When the central mass moved by x, 
the volume V2 increased by A*x, whereas the volume V1 decreased by A*x. Because in the adiabatic process P*V^(gamma)=const, we can determine
P1 and P2:

P1=P*(V/V1)^(gamma)=P*[V/(V-Ax)]^(gamma)=P*[1+gamma*Ax/V] (used approximation Ax<<V)
P2=P*(V/V2)^(gamma)=P*[V/(V+Ax)]^(gamma)=P*[1-gamma*Ax/V] (used approximation Ax<<V)

Then 

F=(P1-P2)*A= -2P*gamma*A^2*x/V

Hence, F is proportional to -x, and k=2PA^2*gamma/V.
Hence, period T=2pi*sqrt(mV/[2PA^2*gamma]) where m is mass of the central mass.

