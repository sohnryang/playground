import numpy as np
import tvm
import tvm.testing
from tvm import te

tgt = tvm.target.Target(target="llvm", host="llvm -mcpu=apple-m1")

n, m, h = te.var("n"), te.var("m"), te.var("h")
A = te.placeholder((n, m), name="A")
B = te.placeholder((m, h), name="B")
k = te.reduce_axis((0, m), name="k")
C = te.compute((n, h), lambda y, x: te.sum(A[y, k] * B[k, x], axis=k), name="C")
s = te.create_schedule(C.op)  # type: ignore
matmult = tvm.build(s, [A, B, C], tgt, name="matmult")

dev = tvm.device(tgt.kind.name, 0)
a = tvm.nd.array(np.random.uniform(size=(1024, 1024)).astype(A.dtype), dev)
b = tvm.nd.array(np.random.uniform(size=(1024, 1024)).astype(B.dtype), dev)
c = tvm.nd.array(np.zeros((1024, 1024), dtype=C.dtype), dev)  # type: ignore
matmult(a, b, c)
tvm.testing.assert_allclose(c.numpy(), a.numpy() @ b.numpy(), 1e-5, 1e-5)
