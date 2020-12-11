import numpy as np

file = open("input.txt")                    # Open file
content = file.read()                       # Read contents to string
file.close()                                # Close file
list = content.split("\n")                  # Split to list of strings
list.remove("")                             # Remove blank line from the end

for i in range(len(list)):                  # Convert string list to int list
    list[i] = int(list[i])

list.append(0)                              # Add outlet
list.append(max(list) + 3)                  # Add device

list.sort()                                 # Sort
diffList = np.diff(list)                    # List of differences between consecutive values

ones = np.count_nonzero(diffList == 1)      # Count 1 jolt differences
threes = np.count_nonzero(diffList == 3)    # Count 3 jolt differences

print (ones, "*", threes, "=", ones * threes)
