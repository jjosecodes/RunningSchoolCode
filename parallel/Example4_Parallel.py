from concurrent.futures import ThreadPoolExecutor

# Function to compute factorial
def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)

# Parallel execution
with ThreadPoolExecutor(max_workers=4) as executor:
    results = list(executor.map(factorial, range(10)))

print("Results:", results)

