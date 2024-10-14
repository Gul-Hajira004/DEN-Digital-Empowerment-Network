## DEN INTERNSHIP TASKS AND PROJECTS OVERVIEW
This repository contains the projects and tasks completed during my six-week internship at Digital Empowerment Network, focusing on implementing various systems and tools in C++.
### TASK 1: Weather Forecast And History System
---
### *OBJECTIVE*:
Provides a  Weather Forecast And History System for managing locations, weather variables, and historical data, including functionalities for fetching, displaying, and exporting weather information.
+ *DESCRIPTION*:
  - A comprehensive weather forecasting and historical data retrieval tool developed in C++.
  - Integrates with APIs to fetch real-time weather data and retrieve historical weather records for multiple locations.
  - Utilizes libcurl for API requests and nlohmann/json for handling JSON data.
  - Allows users to define weather variables, manage locations, and export data in both CSV and JSON formats.
+ *KEY STEPS* :
  - Defining a Location class with attributes for name, latitude, and longitude, and managing a static list of locations.
  - Implementing functions to add, remove, and list locations using the Location class.
  - Defining a WeatherVariable class to handle weather-related variables, including functionality for defining, updating, and displaying these variables.
  - Using curl for fetching real-time weather data from an API and displaying it.
  - Implementing WeatherForecastingSystem for exporting weather data to CSV and JSON formats.
  - Creating a HistoricalWeatherSystem to simulate fetching historical weather data and exporting it to CSV and JSON formats.
  - Providing a menu-driven interface for user interaction, including managing locations, weather variables, and exporting data.
+ *TECHNOLOGIES USED*: C++, libcurl Library, nlohmann/json Library, fstream, API
+ *OUTCOME*: Accurate weather forecasting, seamless data exports, and a robust interface for managing weather variables and locations.
--- ---
  ### TASK 2: Contact Management System
---
### *OBJECTIVE*:
Implement a simple system to manage contacts demonstrating basic object-oriented programming concepts like classes, vectors, and user input handling.
+ *DESCRIPTION*:
  - C++ program that allows users to add, view, anddelete contacts.
  - Each contact should have a name and a phone number.
+ *KEY STEPS* :
  - Defining a Contact class with appropriate attributes.
  - Using vectors to store contact objects.
  - Implementing functions for adding, viewing, and deleting contacts.
  - Providing a menu-driven interface for user interaction.
+ *TECHNOLOGIES USED*: C++,OOP,Standard Template Library (STL).
+ *OUTCOME*: The system provides a simple, interactive way to manage contacts, demonstrating core OOP principles and dynamic data handling with C++.
--- ---
### TASK 3: Simple File Compression Algorithm
---
### *OBJECTIVE*:
Develop a basic file compression and decompression tool.
+ *DESCRIPTION*:
  - Create a C++ program that reads a file, compresses its content using a simple algorithm (e.g., Run-Length Encoding).
  - Writes the compressed data to a new file.
  - Also, implement decompression.
+ *KEY STEPS* :
  - Reading and writing files.
  - Implementing the Run-Length Encoding algorithm.
  - Handling edge cases (e.g., different file types, empty files)
  - Creating functions for both compression and decompression.
+ *TECHNOLOGIES USED*: C++,OOP,Standard Template Library (STL),File Handling,Error Handling.
+ *OUTCOME*: The code implements a file compression and decompression utility that reads a text file, compresses its content using run-length encoding, and allows users to decompress the compressed file, handling errors and file operations appropriately.
--- ---
### TASK 4: Multi-Threaded Web Server
---
### *OBJECTIVE*:
Develop a basic web server that can handle multiple client requests simultaneously.
+ *DESCRIPTION*:
  - Create a C++ program that listens for HTTP requests and serves static HTML files.
  - Use multi-threading to handle multiple clients concurrently.
+ *KEY STEPS* :
  - Setting up socket programming to handle HTTP requests and responses.
  - Implementing multi-threading using the C++ Standard Library&#39;s thread support.
  - Serving static HTML files from a specified directory.
  - Handling concurrent client connections.
+ *TECHNOLOGIES USED*: C++,Socket Programming,Multithreading,HTTP Protocol,Cross-Platform Compatibility,OOP,File Handling,Standard Library
+ *OUTCOME*: The code implements a simple multi-threaded HTTP server in C++ that listens for incoming client requests on a specified port, serves static HTML files, and handles multiple connections concurrently, providing a basic demonstration of socket programming and object-oriented design.
--- ---
### TASK 5: Text-Based Adventure Game
---
### *OBJECTIVE*:
Design an interactive text-based adventure game where players navigate through different scenarios, make decisions, and progress based on their choices.
+ *DESCRIPTION*:
  - The game allows players to explore a mysterious forest filled with creatures, treasures, and puzzles.
  - Players must make decisions that affect their health and inventory, ultimately aiming to escape the forest.
+ *KEY STEPS* :
  - Creating a player class to manage attributes such as health and inventory.
  - Implementing game mechanics to handle encounters, treasure finding, and puzzle solving.
  - Using conditional statements and loops to manage game flow and player choices.
  - Validating user input to ensure valid game actions.
  - Displaying health and inventory management to enhance user experience.
+ *TECHNOLOGIES USED*: C++,OOP,Standard Library (STL)
+ *OUTCOME*: The code implements a complete text-based adventure game in C++ that engages players in decision-making and exploration, featuring various encounters and challenges. It serves as an example of basic game design principles, user interaction, and object-oriented programming.
--- ---

