from multiprocessing import Pool

# Function to compute square
def square(x):
    return x * x

if __name__ == "__main__":
    # Create a pool of workers
    with Pool(processes=4) as pool:
        # Map the function to the input data
        results = pool.map(square, range(10))

    print("Results:", results)

