# Overview

This project is a relatively simple console-based to-do list application written in C++, where my goal was to practice working with file handling, user input validation, classes, and data structures while reinforcing my knowledge of C++ fundamentals. This software allows users to add tasks, view tasks, remove tasks, mark them completed, and save the tasks and their status to a file (done automatcally).

I have always wanted to learn C++ because it is most often used in areas such as automotive engineering and robotics, where embedded systems are needed. I have always had a passion for robotics and automobiles, and my dream job is to work for Ford Motor Company as a Software Engineer. As my coursework at school does not teach C++ as a main language, I decided to learn the basics on my own and practice some other programming skills while doing it, resulting in this software program. 

[Software Demo Video](https://youtu.be/K6f6u6wJ-XM)

# Development Environment

- **IDE:** Visual Studio Code  
- **Compiler:** g++ (MinGW)  
- **Language:** C++  
- **Libraries Used:**  
  - `<iostream>` for input and output  
  - `<vector>` for storing tasks dynamically  
  - `<fstream>` for reading and writing to a file  
  - `<string>` for handling descriptions and names
  - `<limits>` for input validation 
- **Development Machine:** Apple MacBook Pro (M3 Pro)
- **Operating System:** macOS Sequoia (version 15.3.2) 

# Useful Websites

- [Microsoft C++ Documentation](https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170)
- [W3 Schools - C++ Tutorial](https://www.w3schools.com/cpp/default.asp)
- [Codecademy - C++ Tutorial](https://www.codecademy.com/learn/learn-c-plus-plus)

# Future Work

- **Enhance task persistence** – Adding a JSON or database-based approach instead of simple text file storage.  
- **Add task due dates and priorities** – Allow users to set deadlines and importance levels for better task management.  
- **Improve UI experience** – Implement colored text and formatting to make the command-line interface more user-friendly.  
- **Build a GUI version** – Convert the program into a desktop application using a GUI framework like Qt or wxWidgets.  