from numba import jit, prange

# Function to compute the sum of squares
@jit(nopython=True, parallel=True)
def sum_of_squares(n):
    total = 0
    for i in prange(n):
        total += i * i
    return total

# Call the function
result = sum_of_squares(1000000)
print("Sum of squares:", result)

