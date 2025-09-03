
#Example: Parallel Execution with Time Measurement
#This example calculates the square of numbers in parallel using concurrent
#futures and measures the execution time for both sequential and parallel approaches.


import concurrent.futures
import time

# Function to compute the square of a number (simulating a time-consuming task)
def compute_square(n):
    time.sleep(0.1)  # Simulate a delay
    return n * n

# Sequential execution
def sequential_execution(numbers):
    results = []
    for num in numbers:
        results.append(compute_square(num))
    return results

# Parallel execution using ThreadPoolExecutor
def parallel_execution(numbers):
    with concurrent.futures.ThreadPoolExecutor() as executor:
        results = list(executor.map(compute_square, numbers))
    return results

if __name__ == "__main__":
    # List of numbers to process
    numbers = list(range(10))

    # Measure time for sequential execution
    start_time = time.time()
    sequential_results = sequential_execution(numbers)
    sequential_time = time.time() - start_time
    print(f"Sequential Results: {sequential_results}")
    print(f"Sequential Execution Time: {sequential_time:.2f} seconds")

    # Measure time for parallel execution
    start_time = time.time()
    parallel_results = parallel_execution(numbers)
    parallel_time = time.time() - start_time
    print(f"Parallel Results: {parallel_results}")
    print(f"Parallel Execution Time: {parallel_time:.2f} seconds")

#Explanation:

#Sequential Execution:

#The sequential_execution function processes each number one by one.
#A delay of 0.1 seconds is added to simulate a time-consuming task.

#Parallel Execution:

#The parallel_execution function uses ThreadPoolExecutor to execute tasks in parallel.
#The executor.map method applies the compute_square function to each number in the list concurrently.

#Time Measurement:

#The time.time() function is used to measure the start and end times for both sequential and parallel executions.

