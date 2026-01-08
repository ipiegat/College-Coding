# Simple test cases provided for your own tests
from lab7 import sort_matrix_by_row, sort_rectangles


def test(got, expected):
    if got == expected:
        prefix = " PASSED "
    else:
        prefix = "  FAILED "
    print("%s got: %s expected: %s" % (prefix, repr(got), repr(expected)))


def test_task1():
    print()
    print("Testing Task 1: Sorting matrix in rows")
    test(
        sort_matrix_by_row([[5, 8, 1], [6, 7, 3], [5, 4, 9]]),
        [[1, 5, 8], [3, 6, 7], [4, 5, 9]],
    )

    test(
        sort_matrix_by_row([[75, 28, 12], [63, 37, 23], [84, 15, 49]]),
        [[12, 28, 75], [23, 37, 63], [15, 49, 84]],
    )

    test(
        sort_matrix_by_row(
            [
                ["chair", "table", "house"],
                ["square", "rectangle", "triangle"],
                ["motor cycle", "car", "truck"],
            ]
        ),
        [
            ["chair", "house", "table"],
            ["rectangle", "square", "triangle"],
            ["car", "motor cycle", "truck"],
        ],
    )


def test_task2():
    print()
    print("Testing Task 2: sort_rectangle")

    test(
        sort_rectangles("Color"),
        [
            {"ID": "Rect2", "Length": 30, "Breadth": 20, "Color": "blue"},
            {"ID": "Rect3", "Length": 70, "Breadth": 45, "Color": "green"},
            {"ID": "Rect4", "Length": 20, "Breadth": 10, "Color": "purple"},
            {"ID": "Rect1", "Length": 40, "Breadth": 25, "Color": "red"},
        ],
    )
    print("============================================================")
    test(
        sort_rectangles("Length"),
        [
            {"ID": "Rect4", "Length": 20, "Breadth": 10, "Color": "purple"},
            {"ID": "Rect2", "Length": 30, "Breadth": 20, "Color": "blue"},
            {"ID": "Rect1", "Length": 40, "Breadth": 25, "Color": "red"},
            {"ID": "Rect3", "Length": 70, "Breadth": 45, "Color": "green"},
        ],
    )
    print("============================================================")
    test(
        sort_rectangles("Breadth"),
        [
            {"ID": "Rect4", "Length": 20, "Breadth": 10, "Color": "purple"},
            {"ID": "Rect2", "Length": 30, "Breadth": 20, "Color": "blue"},
            {"ID": "Rect1", "Length": 40, "Breadth": 25, "Color": "red"},
            {"ID": "Rect3", "Length": 70, "Breadth": 45, "Color": "green"},
        ],
    )


test_task1()
test_task2()
