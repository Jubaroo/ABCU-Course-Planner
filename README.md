# ABCU Course Planner

A command-line course management system for the ABCU Computer Science Department that uses a Binary Search Tree data structure for efficient course organization and retrieval.

## Overview

This application was developed as part of CS-300 (Data Structures and Algorithms) at Southern New Hampshire University. It demonstrates the practical application of Binary Search Trees for managing course information, including course numbers, titles, and prerequisite relationships.

## Project Components

This repository contains two key deliverables from CS-300:

1. **[Data Structure Analysis](CS%20300%20Project%20One.docx)** - Runtime and memory analysis comparing vectors, hash tables, and binary search trees, with recommendation for optimal data structure selection
2. **[Working Implementation](ABCUCoursePlanner.cpp)** - Complete C++ application implementing the Binary Search Tree solution

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
- **File Loading**: O(n log n) average case

### Space Complexity
- **Tree Storage**: O(n) where n is the number of courses
- **Additional Storage**: O(k) for k prerequisites per course

### Data Structure Comparison

Based on the analysis in Project One, the Binary Search Tree was selected over vectors and hash tables because:

- **Vectors**: Required O(n log n) sorting for every display operation
- **Hash Tables**: Excellent O(1) search but O(n log n) to display sorted list
- **BST**: Balanced performance with O(log n) search and O(n) sorted traversal

The BST provides the optimal balance for this application's primary use cases: searching for courses and displaying sorted course lists.

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

## Project Reflection

### What was the problem you were solving in the projects for this course?

The primary problem I was solving was creating an efficient course management system for the ABCU Computer Science Department. The system needed to store course information, manage prerequisites, and provide quick access to course data. This required selecting and implementing an appropriate data structure that could handle insertion, searching, and sorted display operations efficiently. The key challenge was balancing performance with maintainability while ensuring data integrity through prerequisite validation.

### How did you approach the problem? Consider why data structures are important to understand.

I approached the problem by first analyzing different data structures (vectors, hash tables, and binary search trees) to determine which would best meet the requirements. Understanding data structures was crucial because each has different time complexities for various operations. I ultimately chose a Binary Search Tree because it provides O(log n) search time and maintains sorted order naturally through in-order traversal, which was essential for displaying courses alphabetically. This decision demonstrates how proper data structure selection directly impacts both performance and code simplicity.

### How did you overcome any roadblocks you encountered while going through the activities or project?

One significant roadblock was implementing the prerequisite validation system. Initially, I attempted single-pass validation, but this caused issues when prerequisites were listed before the courses they referenced. I overcame this by implementing a two-pass approach: first loading all courses to build a complete list of valid course numbers, then validating prerequisites against this list. Another challenge was managing memory properly with the BST. I solved this by implementing a recursive destructor to ensure all nodes were properly deleted, preventing memory leaks.

### How has your work on this project expanded your approach to designing software and developing programs?

This project expanded my approach by emphasizing the importance of planning before coding. Analyzing the runtime and memory complexity of different data structures before implementation helped me make informed decisions rather than defaulting to familiar solutions. I learned to consider not just whether code works, but whether it works efficiently. The project also taught me to think about scalability—designing a system that could handle growing amounts of data without significant performance degradation. This analytical approach will be valuable in all future software development work.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

This project significantly improved my approach to writing maintainable code. I focused on clear documentation with detailed comments explaining the purpose and functionality of each method. I separated concerns by keeping the data structure implementation distinct from the user interface logic, making the code more modular and easier to modify. The use of helper functions for specific tasks (like tokenizing strings and converting to lowercase) made the code more readable and reusable. Additionally, implementing proper error handling throughout the program ensures it fails gracefully and provides useful feedback, making it more robust and easier to debug. These practices have become fundamental to how I approach all programming tasks.

## Key Learning Outcomes

This project demonstrates:
- Implementation of Binary Search Tree from scratch
- Understanding of tree traversal algorithms
- File I/O and data parsing in C++
- Data validation and error handling
- Algorithm efficiency analysis and comparison
- Memory management in C++
- Object-oriented programming principles
- Strategic data structure selection based on requirements

## Technologies Used

- **Language**: C++ (C++20 standard)
- **Concepts**: Data Structures, Algorithms, Object-Oriented Programming
- **Tools**: Standard Template Library (STL)

## Author

**Jarrod Schantz**  
Southern New Hampshire University  
CS-300: Data Structures and Algorithms  
Email: jschantz1985@gmail.com

## Acknowledgments

Developed as part of the CS-300 Data Structures and Algorithms course at Southern New Hampshire University.
