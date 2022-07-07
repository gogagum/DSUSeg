import numpy as np
import test_cpp_functions

arr = np.array([1, 2, 3])
arr2d = np.array([[1, 2, 3]])

test_cpp_functions.print_dims(arr)    # prints "3, "
test_cpp_functions.print_dims(arr2d)  # prints "1, 3, "
