# Automatic Differentiation with PyTorch

## 1D case: `autodiff1d.py`
다음과 같이 변수를 놓을 때,

$$
z = ax + b, l = \mathrm{MSE}(z, y) = (z - y)^2
$$

Backpropagation은 다음과 같다.

$$
\begin{align}
  \frac{\partial l}{\partial a} &= \frac{\partial}{\partial a}(ax + b - y)^2 = 2x(ax + b - y) \\
  \frac{\partial l}{\partial b} &= \frac{\partial}{\partial b}(ax + b - y)^2 = 2(ax + b - y)
\end{align}
$$

## 2D case: `autodiff2d.py`
다음과 같이 변수를 놓자.

$$
z = Ax + b, l = \mathrm{MSE}(z, y) = (z - y)^2
$$

여기서는 행렬이 나오기 때문에, 좀 더 명시적으로 작성하면 다음과 같다.

$$
\begin{pmatrix}
  z_1 \\
  z_2
\end{pmatrix} = \begin{pmatrix}
  a_{11} & a_{12} \\
  a_{21} & a_{22}
\end{pmatrix} \begin{pmatrix}
  x_1 \\
  x_2
\end{pmatrix} + \begin{pmatrix}
  b_1 \\
  b_2
\end{pmatrix}
$$
