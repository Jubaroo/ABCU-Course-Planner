//============================================================================
// Name        : ABCUCoursePlanner.cpp
// Author      : Jarrod Schantz
// Version     : 1.0
// Description : Course planning system for ABCU Computer Science Department
//               Uses Binary Search Tree for efficient course management
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

//============================================================================
// Course Structure Definition
//============================================================================

/**
 * Structure to hold course information
 * Contains course number, title, and list of prerequisites
 */
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    // Default constructor
    Course() = default;

    // Parameterized constructor
    Course(const string &number, string title) {
        courseNumber = number;
        courseTitle = std::move(title);
    }
};

//============================================================================
// Binary Search Tree Node Structure
//============================================================================

/**
 * Internal structure for tree node
 * Each node contains a course and pointers to left and right children
 */
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Constructor with course
    explicit Node(Course aCourse) : Node() {
        course = std::move(aCourse);
    }
};

//============================================================================
// Binary Search Tree Class Definition
//============================================================================

/**
 * Binary Search Tree class for managing courses
 * Provides efficient insertion, search, and in-order traversal
 */
class BinarySearchTree final {
    Node* root;

    static void addNode(Node* node, const Course& course);

    static void inOrder(const Node* node);

    static void deleteRecursive(const Node* node);

public:
    BinarySearchTree();

    ~BinarySearchTree();
    void InOrder() const;
    void Insert(const Course& course);
    [[nodiscard]] Course Search(const string& courseNumber) const;
};

/**
 * Default constructor
 * Initializes root to nullptr creating an empty tree
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 * Recursively deletes all nodes to prevent memory leaks
 */
BinarySearchTree::~BinarySearchTree() {
    deleteRecursive(root);
}

// Helper function to delete all nodes
// Deletes children first, then parent
void BinarySearchTree::deleteRecursive(const Node* node) {
    if (node != nullptr) {
        deleteRecursive(node->left);
        deleteRecursive(node->right);
        delete node;
    }
}

/**
 * Insert a course into the tree
 *
 * @param course The course to insert
 */
void BinarySearchTree::Insert(const Course& course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        addNode(root, course);
    }
}

/**
 * Recursive helper to add a course to the correct position in tree
 *
 * @param node Current node in traversal
 * @param course Course to add
 */
void BinarySearchTree::addNode(Node* node, const Course& course) {
    // Compare course numbers to determine placement
    if (course.courseNumber < node->course.courseNumber) {
        // Add to left subtree
        if (node->left == nullptr) {
            node->left = new Node(course);
        } else {
            addNode(node->left, course);
        }
    } else {
        // Add to right subtree
        if (node->right == nullptr) {
            node->right = new Node(course);
        } else {
            addNode(node->right, course);
        }
    }
}

/**
 * Public method to traverse tree in order
 */
void BinarySearchTree::InOrder() const {
    inOrder(root);
}

/**
 * Recursive in-order traversal
 * Visits nodes in sorted order: left -> root -> right
 *
 * @param node Current node being visited
 */
void BinarySearchTree::inOrder(const Node* node) {
    if (node != nullptr) {
        // Traverse left subtree
        inOrder(node->left);

        // Print current node
        cout << node->course.courseNumber << ", "
             << node->course.courseTitle << endl;

        // Traverse right subtree
        inOrder(node->right);
    }
}

/**
 * Search for a course by course number
 * Iteratively traverses tree based on comparisons
 *
 * @param courseNumber The course number to search for
 * @return The course if found, empty course otherwise
 */
Course BinarySearchTree::Search(const string& courseNumber) const {
    Node* current = root;

    // Traverse tree until found or reach end
    while (current != nullptr) {
        // Found matching course
        if (current->course.courseNumber == courseNumber) {
            return current->course;
        }

        // Search left subtree if target is smaller
        if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        // Search right subtree if target is larger
        else {
            current = current->right;
        }
    }

    // Course not found, return empty course
    Course course;
    return course;
}

//============================================================================
// Utility Functions
//============================================================================

/**
 * Split a string by a delimiter
 *
 * @param str The string to split
 * @param delimiter The character to split on
 * @return Vector of string tokens
 */
vector<string> tokenize(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        // Trim whitespace from token
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);
        tokens.push_back(token);
    }

    return tokens;
}

/**
 * Load courses from a file into the BST
 * Performs two-pass validation to ensure data integrity
 *
 * @param filename Path to the course data file
 * @param bst Pointer to the binary search tree
 * @return true if load successful, false otherwise
 */
bool loadCourses(const string& filename, BinarySearchTree* bst) {
    ifstream file(filename);

    // Check if file opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    cout << "Loading course data from " << filename << "..." << endl;

    vector<Course> courses;
    vector<string> validCourseNumbers;
    string line;
    int lineNumber = 0;

    // First pass: Read and validate basic structure
    while (getline(file, line)) {
        lineNumber++;

        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Parse line into tokens
        vector<string> tokens = tokenize(line, ',');

        // Validate minimum number of fields
        if (tokens.size() < 2) {
            cout << "Error: Line " << lineNumber << " has insufficient data" << endl;
            cout << "Each line must have at least course number and title" << endl;
            file.close();
            return false;
        }

        // Create course object
        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        // Add prerequisites (if any) - skip empty strings
        for (size_t i = 2; i < tokens.size(); i++) {
            // Only add non-empty prerequisites
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        // Store course and track valid course numbers
        courses.push_back(course);
        validCourseNumbers.push_back(course.courseNumber);
    }

    file.close();

    // Second pass: Validate prerequisites exist
    for (const auto& course : courses) {
        for (const auto& prereq : course.prerequisites) {
            // Skip empty prerequisites
            if (prereq.empty()) {
                continue;
            }

            // Check if prerequisite exists in course list
            if (ranges::find(validCourseNumbers, prereq)
                == validCourseNumbers.end()) {
                cout << "Error: Prerequisite " << prereq << " for course "
                     << course.courseNumber << " does not exist" << endl;
                return false;
            }
        }
    }

    // All validation passed - load into BST
    for (const auto& course : courses) {
        bst->Insert(course);
    }

    cout << "Successfully loaded " << courses.size() << " courses." << endl;
    return true;
}

/**
 * Display the main menu
 */
void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "Welcome to the course planner." << endl;
    cout << "========================================" << endl;
    cout << "  1. Load Data Structure" << endl;
    cout << "  2. Print Course List" << endl;
    cout << "  3. Print Course" << endl;
    cout << "\n  9. Exit" << endl;
    cout << "========================================" << endl;
    cout << "What would you like to do? ";
}

/**
 * Print information for a specific course including prerequisites
 *
 * @param bst Pointer to the binary search tree
 * @param courseNumber Course number to search for
 */
void printCourse(const BinarySearchTree* bst, string courseNumber) {
    // Extract only the course number (first token before comma or space)
    const size_t commaPos = courseNumber.find(',');
    const size_t spacePos = courseNumber.find(' ');

    if (const size_t endPos = min(commaPos, spacePos); endPos != string::npos) {
        courseNumber = courseNumber.substr(0, endPos);
    }

    // Trim whitespace
    courseNumber.erase(0, courseNumber.find_first_not_of(" \t\r\n"));
    courseNumber.erase(courseNumber.find_last_not_of(" \t\r\n") + 1);

    // Convert to uppercase for case-insensitive search
    ranges::transform(courseNumber,
                      courseNumber.begin(), ::toupper);

    const Course course = bst->Search(courseNumber);

    // Check if course was found
    if (course.courseNumber.empty()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    // Print course information
    cout << course.courseNumber << "," << course.courseTitle << endl;

    // Print prerequisites
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

//============================================================================
// Main Function
//============================================================================

/**
 * Main program entry point
 * Provides menu-driven interface for course management
 */
int main() {
    auto* bst = new BinarySearchTree();
    string filename;
    string courseNumber;
    int choice = 0;
    bool dataLoaded = false;

    cout << "\nABCU Course Planner" << endl;

    // Main program loop
    while (choice != 9) {
        displayMenu();

        // Get user input with error checking
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number." << endl;
            continue;
        }

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                // Load data structure
                cout << "Enter the file name: ";
                getline(cin, filename);

                if (loadCourses(filename, bst)) {
                    dataLoaded = true;
                }
                break;

            case 2:
                // Print course list
                if (!dataLoaded) {
                    cout << "\nError: No data loaded. Please load data first (Option 1)." << endl;
                } else {
                    cout << "\nHere is a sample schedule:\n" << endl;
                    bst->InOrder();
                }
                break;

            case 3:
                // Print course information
                if (!dataLoaded) {
                    cout << "\nError: No data loaded. Please load data first (Option 1)." << endl;
                } else {
                    cout << "What course do you want to know about? (Enter course number): ";
                    getline(cin, courseNumber);
                    cout << endl;
                    printCourse(bst, courseNumber);
                }
                break;

            case 9:
                // Exit program
                cout << "\nThank you for using the course planner!" << endl;
                break;

            default:
                // Invalid option
                cout << "\n" << choice << " is not a valid option." << endl;
                break;
        }
    }

    // Clean up memory
    delete bst;

    return 0;
}