#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

// Define the Course structure
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Function to load courses from a file into the map
void loadCourses(std::map<std::string, Course>& courses) {
    std::string filename = "CS 300 ABCU_Advising_Program_Input.csv"; // Predefined filename
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Course course;
        std::getline(ss, course.courseNumber, ',');
        std::getline(ss, course.courseTitle, ',');

        std::string prerequisite;
        while (std::getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courses[course.courseNumber] = course;
    }
    std::cout << "Data structure loaded successfully.\n";
}

// Function to display the menu
void displayMenu() {
    std::cout << "\n1. Load Data Structure.\n";
    std::cout << "2. Print Course List.\n";
    std::cout << "3. Print Course.\n";
    std::cout << "9. Exit\n";
    std::cout << "What would you like to do? ";
}

// Function to print the list of courses
void printCourseList(const std::map<std::string, Course>& courses) {
    std::cout << "\nHere is a sample schedule:\n";
    for (const auto& pair : courses) {
        std::cout << pair.first << ", " << pair.second.courseTitle << std::endl;
    }
}

// Function to print information about a specific course
void printCourseInformation(const std::string& courseNumber, const std::map<std::string, Course>& courses) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
        if (!course.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                std::cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cerr << "Course not found!\n";
    }
}

// Function to handle user input and perform corresponding actions
void handleUserChoice(int choice, std::map<std::string, Course>& courses) {
    switch (choice) {
    case 1:
        loadCourses(courses);
        break;
    case 2:
        printCourseList(courses);
        break;
    case 3: {
        std::string courseNumber;
        std::cout << "What course do you want to know about? ";
        std::cin >> courseNumber;
        // Convert input to uppercase to match course numbers
        std::transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
        printCourseInformation(courseNumber, courses);
        break;
    }
    case 9:
        std::cout << "Thank you for using the course planner!\n";
        break;
    default:
        std::cerr << choice << " is not a valid option.\n";
        break;
    }
}

// Main function
int main() {
    std::cout << "Welcome to the course planner.\n";
    std::map<std::string, Course> courses;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        handleUserChoice(choice, courses);
    } while (choice != 9);

    return 0;
}


