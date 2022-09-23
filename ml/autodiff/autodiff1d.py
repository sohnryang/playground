import torch

x = torch.ones(1)
a = torch.randn(1, requires_grad=True)
b = torch.randn(1, requires_grad=True)
y = torch.zeros(1, requires_grad=True)
z = a * x + b
loss = torch.nn.functional.mse_loss(z, y, reduction="none")

print(f"a={a}")
print(f"b={b}")
print(f"z={z}")
print(f"y={y}")
print(f"loss={loss}")

loss.backward()
print(f"gradient of a={a.grad}")
print(f"gradient of b={b.grad}")
