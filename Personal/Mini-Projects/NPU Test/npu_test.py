import numpy as np
import onnx
import onnxruntime as ort        # ← the correct import!
from onnx import helper, TensorProto
import time

def make_matmul_model(dim):
    A = helper.make_tensor_value_info('A', TensorProto.FLOAT, [dim,dim])
    B = helper.make_tensor_value_info('B', TensorProto.FLOAT, [dim,dim])
    Y = helper.make_tensor_value_info('Y', TensorProto.FLOAT, [dim,dim])
    node = helper.make_node('MatMul', ['A','B'], ['Y'])
    graph = helper.make_graph([node], 'matmul', [A,B],[Y])
    return helper.make_model(graph)

dim = 2048
model = make_matmul_model(dim)
onnx.save(model, 'matmul.onnx')

sess = ort.InferenceSession('matmul.onnx',
    providers=['DmlExecutionProvider','CPUExecutionProvider'])

A = np.random.randn(dim,dim).astype(np.float32)
B = np.random.randn(dim,dim).astype(np.float32)

for _ in range(5):
    sess.run(['Y'], {'A':A,'B':B})

times = []
for _ in range(20):
    t0 = time.time()
    sess.run(['Y'], {'A':A,'B':B})
    times.append(time.time()-t0)

avg = sum(times)/len(times)
flops = 2 * dim**3
tops = flops/(avg * 1e12)
print(f'Avg inference: {avg*1000:.3f} ms → {tops*1000:.1f} TOPS')
