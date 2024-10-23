import random

# Generate a list of 5 million random integers
large_unsorted_data = [random.randint(1, 1000000) for _ in range(5000000)]

# Write the unsorted data to a text file
with open("large_unsorted_data_5m.txt", "w") as file:
    file.write("\n".join(map(str, large_unsorted_data)))

print("File 'large_unsorted_data_5m.txt' created successfully!")
