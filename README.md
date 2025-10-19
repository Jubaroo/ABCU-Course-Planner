# ABCU Course Planner

A command-line course management system for the ABCU Computer Science Department that uses a Binary Search Tree data structure for efficient course organization and retrieval.

## Overview

This application was developed as part of CS-300 (Data Structures and Algorithms) at Southern New Hampshire University. It demonstrates the practical application of Binary Search Trees for managing course information, including course numbers, titles, and prerequisite relationships.

## Features

- **Efficient Data Structure**: Implements a Binary Search Tree for O(log n) search complexity
- **Course Management**: Load, store, and retrieve course information
- **Prerequisite Validation**: Two-pass validation system ensures all prerequisites exist in the course catalog
- **Sorted Display**: In-order traversal displays courses in alphanumeric order
- **Case-Insensitive Search**: Find courses regardless of input case
- **Data Integrity**: Validates course data structure and relationships before loading
- **User-Friendly Interface**: Menu-driven command-line interface

## Technical Details

### Data Structures
- **Binary Search Tree**: Primary data structure for course storage and retrieval
- **Vector**: Used for storing prerequisites and temporary data during file parsing
- **Custom Node Structure**: Contains course data and pointers to left/right children

### Design Patterns
- **Object-Oriented Design**: Course and Node structures with clear encapsulation
- **Recursive Algorithms**: Tree traversal and node insertion
- **Memory Management**: Proper cleanup with recursive deletion in destructor

### Algorithms
- **Insertion**: Recursive BST insertion maintaining sorted order
- **Search**: Iterative search through tree with O(log n) average complexity
- **Traversal**: In-order traversal for sorted course listing
- **Validation**: Two-pass file parsing for data integrity

## How to Use

### Compilation
```bash
g++ -std=c++20 ABCUCoursePlanner.cpp -o ABCUCoursePlanner
```

### Running the Program
```bash
./ABCUCoursePlanner
```

### Menu Options

1. **Load Data Structure**: Load course data from a CSV file
2. **Print Course List**: Display all courses in alphanumeric order
3. **Print Course**: Search for and display a specific course with prerequisites
9. **Exit**: Close the application

### Input File Format

The program expects a CSV file with the following format:
```
CourseNumber,CourseTitle,Prerequisite1,Prerequisite2,...
```

**Example:**
```
CSCI100,Introduction to Computer Science
CSCI101,Introduction to Programming in C++,CSCI100
CSCI200,Data Structures,CSCI101
MATH201,Discrete Mathematics
CSCI300,Introduction to Algorithms,CSCI200,MATH201
```

**Requirements:**
- Each line must have at least a course number and title
- Prerequisites are optional but must reference valid courses
- Course numbers should be unique
- Empty lines are skipped

## Performance Analysis

### Time Complexity
- **Insertion**: O(log n) average case, O(n) worst case
- **Search**: O(log n) average case, O(n) worst case
- **In-Order Traversal**: O(n)
- **File Loading**: O(n*m) where n is courses and m is average prerequisites

### Space Complexity
- **Tree Storage**: O(n) where n is the number of courses
- **Additional Storage**: O(k) for k prerequisites per course

## Code Structure
```
ABCUCoursePlanner.cpp
├── Course Structure
│   ├── courseNumber
│   ├── courseTitle
│   └── prerequisites vector
├── Node Structure
│   ├── Course data
│   ├── Left child pointer
│   └── Right child pointer
├── BinarySearchTree Class
│   ├── Insert()
│   ├── Search()
│   ├── InOrder()
│   └── Helper methods
└── Utility Functions
    ├── loadCourses()
    ├── tokenize()
    ├── displayMenu()
    └── printCourse()
```

## Error Handling

The application includes robust error handling for:
- File not found errors
- Malformed CSV data
- Missing prerequisites
- Invalid course numbers
- Insufficient data in file
- Invalid user input

## Sample Output
```
ABCU Course Planner

========================================
Welcome to the course planner.
========================================
  1. Load Data Structure
  2. Print Course List
  3. Print Course

  9. Exit
========================================
What would you like to do? 1
Enter the file name: courses.csv
Loading course data from courses.csv...
Successfully loaded 7 courses.

What would you like to do? 3
What course do you want to know about? CSCI300

CSCI300, Introduction to Algorithms
Prerequisites: CSCI200, MATH201
```

## Key Learning Outcomes

This project demonstrates:
- Implementation of Binary Search Tree from scratch
- Understanding of tree traversal algorithms
- File I/O and data parsing in C++
- Data validation and error handling
- Algorithm efficiency analysis
- Memory management in C++
- Object-oriented programming principles

## Technologies Used

- **Language**: C++ (C++20 standard)
- **Concepts**: Data Structures, Algorithms, Object-Oriented Programming
- **Tools**: Standard Template Library (STL)

## Author

**Jarrod Schantz**  
Southern New Hampshire University  
CS-300: Data Structures and Algorithms

## License

This project was created for educational purposes as part of coursework at SNHU.

## Acknowledgments

- Southern New Hampshire University CS-300 course materials
- ABCU Computer Science Department (fictional client)
