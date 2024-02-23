import numpy as np

def fft(a):
    """Compute the Fast Fourier Transform of array `a`."""
    n = len(a)
    if n <= 1:
        return a
    even = fft(a[0::2])
    odd = fft(a[1::2])
    t = [np.exp(-2j * np.pi * k / n) * odd[k % (n//2)] for k in range(n//2)]
    return [even[k] + t[k] for k in range(n//2)] + [even[k] - t[k] for k in range(n//2)]

def ifft(a):
    """Compute the Inverse Fast Fourier Transform of array `a`."""
    n = len(a)
    if n <= 1:
        return a
    even = ifft(a[0::2])
    odd = ifft(a[1::2])
    t = [np.exp(2j * np.pi * k / n) * odd[k % (n//2)] for k in range(n//2)]
    return [(even[k] + t[k]) / 2 for k in range(n//2)] + [(even[k] - t[k]) / 2 for k in range(n//2)]

def fft_multiply(x, y):
    """Multiply two polynomials `x` and `y` using FFT."""
    # Determine the size for the result (next power of 2)
    n = 1
    while n < max(len(x), len(y)) * 2:
        n *= 2
    x += [0] * (n - len(x))
    y += [0] * (n - len(y))
    
    # Compute FFTs
    fft_x = fft(x)
    fft_y = fft(y)
    
    # Point-wise multiplication
    fft_z = [fft_x[i] * fft_y[i] for i in range(n)]
    
    # Compute the inverse FFT
    z = ifft(fft_z)
    
    # Round and take real part
    result = [int(round(num.real)) for num in z]
    return result

# Example usage

x = []  # Coefficients for the polynomial 1 + 2x + 3x^2
y = []  # Coefficients for the polynomial 4 + 5x + 6x^2

for i in range(10000):
    x.append(i)
    y.append(i)

result = fft_multiply(x, y)
print(result)
