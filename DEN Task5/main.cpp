#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Player {
public:
    string name;
    int health;
    vector<string> inventory;

    Player(string playerName) {
        name = playerName;
        health = 100; // Set initial health points
    }

    void addItem(string item) {
        inventory.push_back(item);
        cout << item << " has been added to your inventory." << endl;
    }

    void displayInventory() {
        cout << "Your Inventory: ";
        if (inventory.empty()) {
            cout << "Empty" << endl;
        } else {
            for (const auto& item : inventory) {
                cout << item << " ";
            }
            cout << endl;
        }
    }
};

void introduction();
void forestPath(Player& player);
void encounterCreature(Player& player);
void findTreasure(Player& player);
void solvePuzzle(Player& player);
void chooseAction(Player& player);
void exploreClearing(Player& player);
void displayHealth(Player& player);
void checkGameOver(Player& player);
void escapeForest(Player& player);

int main() {
    string playerName;

    cout << "Enter your name: ";
    getline(cin, playerName);
    Player player(playerName); // Create a player object

    introduction(); // Start the game
    forestPath(player); // Navigate the forest
    return 0;
}

// Function to display the introduction
void introduction() {
    cout << "Welcome to 'Mystery of the Forgotten Forest'!" << endl;
    cout << "You wake up in a mysterious, foggy forest with no memory of how you got there." << endl;
    cout << "Your goal is to escape the forest, but beware... not everything is as it seems." << endl;
}

// Function to navigate the forest path
void forestPath(Player& player) {
    cout << "\nYou stand at a fork in the path." << endl;
    cout << "Do you want to go left, right, explore the clearing, or try to escape? (left/right/clearing/escape) ";

    string choice;
    cin >> choice;

    if (choice == "left") {
        encounterCreature(player);
    } else if (choice == "right") {
        findTreasure(player);
    } else if (choice == "clearing") {
        exploreClearing(player);
    } else if (choice == "escape") {
        escapeForest(player); // New option to escape
    } else {
        cout << "Invalid choice. Please type 'left', 'right', 'clearing', or 'escape'." << endl;
        forestPath(player); // Retry if input is invalid
    }
}

// Function to handle the encounter with a creature
void encounterCreature(Player& player) {
    cout << "\nYou encounter a fierce-looking creature!" << endl;
    displayHealth(player);

    // Ask the player what to do
    while (true) {
        cout << "Do you want to (fight) it, (run) away, or (check inventory)? ";
        
        string choice;
        cin >> choice;

        if (choice == "fight") {
            cout << "You bravely fight the creature!" << endl;
            player.health -= 20; // Decrease health points
            cout << "You take damage! Your health is now: " << player.health << endl;
            checkGameOver(player); // Check for game over

            cout << "You managed to defeat it!" << endl;
            forestPath(player); // Go back to the forest path
            break; // Exit the loop
        } else if (choice == "run") {
            cout << "You run away safely, but you've lost your chance to face the creature." << endl;
            forestPath(player); // Go back to the forest path
            break; // Exit the loop
        } else if (choice == "check") {
            player.displayInventory();
            // Prompt to continue
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get(); // Wait for user input to continue
            // Loop back to ask again
        } else {
            cout << "Invalid choice. Please type 'fight', 'run', or 'check'." << endl;
        }
    }
}

// Function to find treasure
void findTreasure(Player& player) {
    cout << "\nYou find a treasure chest hidden behind some bushes!" << endl;
    cout << "Do you want to open it or leave it? (open/leave) ";
    
    string choice;
    cin >> choice;

    if (choice == "open") {
        cout << "You open the chest and find a magic potion!" << endl;
        player.addItem("Magic Potion");
        forestPath(player); // Go back to the forest path
    } else if (choice == "leave") {
        cout << "You decide to leave the treasure behind, continuing your journey." << endl;
        forestPath(player); // Go back to the forest path
    } else {
        cout << "Invalid choice. Please type 'open' or 'leave'." << endl;
        findTreasure(player); // Retry if input is invalid
    }
}

// Function to explore the clearing
void exploreClearing(Player& player) {
    cout << "\nYou enter a sunny clearing filled with flowers." << endl;
    cout << "There is a mysterious stone in the center. Do you want to (inspect) it or (leave)? ";

    string choice;
    cin >> choice;

    if (choice == "inspect") {
        cout << "You discover a riddle inscribed on the stone!" << endl;
        solvePuzzle(player); // Start solving a puzzle
    } else if (choice == "leave") {
        cout << "You leave the clearing, returning to the forest path." << endl;
        forestPath(player); // Go back to the forest path
    } else {
        cout << "Invalid choice. Please type 'inspect' or 'leave'." << endl;
        exploreClearing(player); // Retry if input is invalid
    }
}

// Function to solve a puzzle
void solvePuzzle(Player& player) {
    cout << "To escape the forest, you must solve this riddle:" << endl;
    cout << "'I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?'" << endl;
    cout << "Type your answer: ";

    string answer;
    cin >> answer;

    if (answer == "echo") {
        cout << "Correct! The stone glows, and a path opens before you." << endl;
        player.addItem("Forest Key"); // Player receives a key
        forestPath(player); // Go back to the forest path
    } else {
        cout << "Incorrect. The stone remains silent." << endl;
        exploreClearing(player); // Retry the clearing exploration
    }
}

// Function to display player health
void displayHealth(Player& player) {
    cout << "Your current health: " << player.health << endl;
}

// Function to check if the player is out of health
void checkGameOver(Player& player) {
    if (player.health <= 0) {
        cout << "You have lost all your health. Game Over!" << endl;
        exit(0); // End the game
    }
}

// Function to handle escaping the forest
void escapeForest(Player& player) {
    cout << "\nYou come across a large gate leading out of the forest." << endl;
    if (find(player.inventory.begin(), player.inventory.end(), "Forest Key") != player.inventory.end()) {
        cout << "You use the Forest Key to unlock the gate." << endl;
        cout << "Congratulations! You have successfully escaped the Forgotten Forest!" << endl;
        exit(0); // End the game successfully
    } else {
        cout << "The gate is locked. You need the Forest Key to escape." << endl;
        forestPath(player); // Return to the forest path
    }
}
