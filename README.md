# graphics6.837
graphic course of MIT-my answers

## assignment0
```text
Render an IFS by iterating the transform on random input points from the unit square. 
```
```cpp
for "lots" of random points (x0, y0)
       for k=0 to num_iters 
           pick a random transform fi
           (xk+1, yk+1) = fi(xk, yk)
       display a dot at (xk, yk)
```
