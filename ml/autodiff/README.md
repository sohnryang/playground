# Automatic Differentiation with PyTorch

## 1D case: `autodiff1d.py`
다음과 같이 변수를 놓을 때,

```math
z = ax + b, l = \mathrm{MSE}(z, y) = (z - y)^2
```

Backpropagation은 다음과 같다.

```math
\begin{align}
  \frac{\partial l}{\partial a} &= \frac{\partial}{\partial a}(ax + b - y)^2 = 2x(ax + b - y)
  \frac{\partial l}{\partial b} &= \frac{\partial}{\partial b}(ax + b - y)^2 = 2(ax + b - y)
\end{align}
```
