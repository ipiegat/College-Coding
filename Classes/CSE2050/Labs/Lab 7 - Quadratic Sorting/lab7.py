# Task # 1. Read lab manual for details.
def sort_matrix_by_row(matrix):

    # Use selection sort to solve this problem,
    for matrices in matrix:
        for i in range(len(matrices) - 1):
            min_idx = i
            for j in range(i + 1, len(matrices)):
                if matrices[j] < matrices[min_idx]:
                    min_idx = j

            matrices[i], matrices[min_idx] = matrices[min_idx], matrices[i]

    return matrix


# Task # 2. Read lab manual for details.
# We have the following rectangles records in a list of dictionaries.
rectangles = [
    {"ID": "Rect1", "Length": 40, "Breadth": 25, "Color": "red"},
    {"ID": "Rect2", "Length": 30, "Breadth": 20, "Color": "blue"},
    {"ID": "Rect3", "Length": 70, "Breadth": 45, "Color": "green"},
    {"ID": "Rect4", "Length": 20, "Breadth": 10, "Color": "purple"},
]


def sort_rectangles(title):
    # Using insertion sort to solve this problem.

    for i in range(1, len(rectangles)):
        dict = rectangles[i]
        j = i - 1

        # Compare key with each element on the left of it until an element smaller than it is found
        # For descending order, change key<array[j] to key>array[j].
        while j >= 0 and dict[title] < rectangles[j][title]:
            rectangles[j + 1] = rectangles[j]
            j = j - 1

        # Place key at after the element just smaller than it.
        rectangles[j + 1] = dict

    # sort by title.
    # return rectangles.
    return rectangles
