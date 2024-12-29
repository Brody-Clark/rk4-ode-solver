# rk4-ode-solver
A command line First Order Oridinary Differential Equation Solver using RK4 written in C++. It parses user-defined ODEs using [ExprTk](https://github.com/ArashPartow/exprtk) and prints results to console with the option to print to a text file.

## Overview

### Numerical Integration

Numerical integration is a technique used to approximate the solutions of ODEs. Unlike analytical methods, which seek exact solutions, numerical methods provide approximate solutions by discretizing the problem. This approach is particularly useful for complex ODEs that cannot be solved analytically.

### Solving First-Order Differential Equations

This application is specifically designed to solve first-order differential equations of the form:

$$
\frac{dy}{dx} = f(x, y)
$$

A first-order differential equation involves the first derivative of a function. The RK4 method is particularly well-suited for these types of equations due to its balance of computational efficiency and accuracy.

### The Runge-Kutta 4th Order (RK4) Algorithm

The Runge-Kutta 4th Order method is one of the most widely used numerical integration techniques. It is known for its accuracy and stability. The RK4 algorithm calculates the solution of an ODE by taking the weighted average of four estimates of the derivative:

1. **k1**: The slope at the beginning of the interval.
2. **k2**: The slope at the midpoint of the interval, using k1 to estimate the value of the function.
3. **k3**: Another slope at the midpoint, but using k2 to estimate the function value.
4. **k4**: The slope at the end of the interval, using k3 to estimate the function value.

The formula for the RK4 method is as follows:

$$
y_{n+1} = y_n + \frac{1}{6} (k_1 + 2k_2 + 2k_3 + k_4) \cdot h
$$

Where:
$$ y_n \text{ is the current value of the function.}$$
$$ h \text{ is the step size.}$$
$$ k_1 = f(t_n, y_n)$$
$$ k_2 = f(t_n + \frac{h}{2}, y_n + \frac{h}{2} k_1)$$
$$ k_3 = f(t_n + \frac{h}{2}, y_n + \frac{h}{2} k_2)$$
$$ k_4 = f(t_n + h, y_n + h k_3)$$

By combining these estimates, the RK4 method provides a highly accurate approximation of the solution to the ODE.

## How to Use This Project

### Building the Project

1. Clone the repository:
   ```sh
   git clone https://github.com/Brody-Clark/rk4-ode_solver.git
   ```
2. Run from Visual Studio