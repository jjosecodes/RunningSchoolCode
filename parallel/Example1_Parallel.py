from joblib import Parallel, delayed
import math

# Function to compute square root
def compute_sqrt(x):
    return math.sqrt(x)

# Parallel execution
results = Parallel(n_jobs=4)(delayed(compute_sqrt)(i) for i in range(10))

print("Results:", results)

