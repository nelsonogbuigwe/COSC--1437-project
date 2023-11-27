#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;

void sp() {
    std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Pause for 0.5 seconds
}

// Spaceship class representing different types of spaceships
class Spaceship {
protected:
    int fuel_capacity;
    int crew_capacity;
    int current_fuel;
    int current_crew;
    int current_money;
    float fuel_efficiency; // Changed fuel efficiency to float

public:
    // Constructor initializing spaceship properties
    Spaceship(int fuel, int crew, float efficiency, int money) : fuel_capacity(fuel), crew_capacity(crew), current_fuel(fuel), current_crew(crew), current_money(money), fuel_efficiency(efficiency) {}

    // Virtual destructor for polymorphism
    virtual ~Spaceship() {}

    // Method to refuel the spaceship
    void fueling(int amount) {
        current_fuel += amount;
        if (current_fuel > fuel_capacity) {
            current_fuel = fuel_capacity;
        }
    }

    void upgrade(float eff, int capp, int pop) {
        fuel_efficiency += eff;
        fuel_capacity += capp;
        crew_capacity += pop;
    }

    void getPaid(int amount) {
        current_money += amount;
    }

    // Method to add crew members
    void disembark(int crewAdded) {
        current_crew += crewAdded;
        if (current_crew > crew_capacity) {
            current_crew = crew_capacity;
        }
    }

    // Getters for spaceship properties
    int getFuel() const { return current_fuel; }
    int getCrew() const { return current_crew; }
    int getMoney() const { return current_money; }
    int getFuelCapacity() const { return fuel_capacity; }
    int getCrewCapacity() const { return crew_capacity; }
    float getFuelEfficiency() const { return fuel_efficiency; }

    virtual string getDescription() const = 0;

    // Method to simulate exploration and fuel consumption
    void explore(int fuelRequired) {
        float fuelConsumed = fuelRequired * fuel_efficiency;
        if (current_fuel >= fuelConsumed) {
            current_fuel -= fuelConsumed;
            sp();
        } else {
            cout << "Not enough fuel to explore this planet!" << endl;
        }
    }

};

// Stealth Ship with fuel efficiency 0.5
class StealthShip : public Spaceship {
public:
    StealthShip() : Spaceship(350, 23, 0.5, 60) {}

    string getDescription() const override {
        return "Stealth Ship: This ship has an advanced cloaking device for evading enemies. \nFuel Capacity: " + to_string(getFuelCapacity()) + "\nCrew Capacity: " + to_string(getCrewCapacity()) + "\nFuel Efficiency: 0.5\n";
    }
};

// Jet Ship with fuel efficiency 0.8
class JetShip : public Spaceship {
public:
    JetShip() : Spaceship(500, 15, 0.8, 60) {}

    string getDescription() const override {
        return "Jet Ship: Equipped with high-speed warp drives for faster travel between planets. \nFuel Capacity: " + to_string(getFuelCapacity()) + "\nCrew Capacity: " + to_string(getCrewCapacity()) + "\nFuel Efficiency: 0.8 \n";
    }
};

// Travel Ship with fuel efficiency 1.0
class TravelShip : public Spaceship {
public:
    TravelShip() : Spaceship(700, 30, 1.35, 70) {}

    string getDescription() const override {
        return "Travel Ship: Utilizes advanced scanners to attract additional resources from planets. \nFuel Capacity: " + to_string(getFuelCapacity()) + "\nCrew Capacity: " + to_string(getCrewCapacity()) + "\nFuel Efficiency: 1.0 \n";
    }
};

// Planet class representing different planets
class Planet {
private:
    string name;
    string description;
    int fuel_required;
    int hostility_level;
    bool uniqueEventTriggered;

public:
    // Constructor initializing planet properties
    Planet(const string &planetName, const string &planetDescription, int fuelRequired, int hostilityLevel) : name(
            planetName), description(planetDescription), fuel_required(fuelRequired), hostility_level(hostilityLevel),
                                                                                                              uniqueEventTriggered(
                                                                                                                      false) {}

    // Getter for uniqueEventTriggered flag
    bool isUniqueEventTriggered() const { return uniqueEventTriggered; }

    // Getters for planet properties
    string getName() const { return name; }

    string getDescription() const { return description; }

    int getFuelRequired() const { return fuel_required; }

    int getHostilityLevel() const { return hostility_level; }

    // Method to simulate planet exploration
    // Method to simulate planet exploration and trigger unique event
    void simulateExplorationEvent(Spaceship *current_ship) {
        if (!uniqueEventTriggered) {
            uniqueEventTriggered = true;
            sp();sp();
            if (name == "Terra Nova") {
                cout << "You discovered ancient ruins that provide advanced technology. Fuel +20, Crew +5." << endl;
                // Update spaceship attributes accordingly
                current_ship->fueling(20);
                current_ship->disembark(5);
            } else if (name == "Aurora Prime") {
                cout
                        << "You encountered a friendly alien race willing to trade valuable resources for fuel. Fuel -10, Crew +2."
                        << endl;
                // Update spaceship attributes accordingly
                current_ship->fueling(-10);
                current_ship->disembark(2);
            } else if (name == "Nebula Serenity") {
                cout
                        << "You witnessed a rare atmospheric phenomenon and gained insights into efficient fuel utilization. Fuel Efficiency +0.1."
                        << endl;
                // Update spaceship attributes accordingly
                current_ship->upgrade(0.2, 25, 0);
            } else if (name == "Phoenix Rebirth") {
                cout
                        << "You tap into geothermal energy sources, enhancing your ship's power systems. Fuel +15, Fuel Efficiency +0.05, Crew Capacity +11, fuel capacity +15"
                        << endl;
                // Update spaceship attributes accordingly
                current_ship->fueling(15);
                current_ship->upgrade(-0.2, 15, 11);
            } else if (name == "Galactic Haven") {
                cout << "You are welcomed by advanced civilizations, offering rare technologies. Fuel -5, Money +30."
                     << endl;
                // Update spaceship attributes accordingly
                current_ship->fueling(-5);
                current_ship->getPaid(30);
            } else if (name == "Asteria Minor") {
                cout << "Your crew discovers hidden ancient ruins, providing valuable artifacts. Crew +3, Money +20."
                     << endl;
                // Update spaceship attributes accordingly
                current_ship->disembark(3);
                current_ship->getPaid(20);
            } else if (name == "Celestial Odyssey") {
                cout << "You unveil rare artifacts with mysterious powers. Fuel +10, Crew +5." << endl;
                // Update spaceship attributes accordingly
                current_ship->disembark(5);
                current_ship->fueling(23);
                current_ship->upgrade(-0.2, 60, 0);
            } else if (name == "Elysium Fields") {
                cout
                        << "Your crew experiences a rejuvenating atmosphere, improving their morale. Crew +5, Fuel Efficiency +0.1."
                        << endl;
                // Update spaceship attributes accordingly
                current_ship->disembark(5);
                current_ship->fueling(60);
                current_ship->upgrade(-0.2, 60, 0);
            }
        } else {
            cout << "You've already explored this planet!" << endl;
        }
    };

// Abstract class representing different types of random events
    class RandomEvent {
    public:
        virtual ~RandomEvent() {}

        virtual void executeEvent(Spaceship *current_ship) = 0;
    };

    class SolarFlareRandomEvent : public RandomEvent {
    public:
        void executeEvent(Spaceship *current_ship) override {
            sp();
            cout << "A solar flare disrupts your spaceship's systems!" << endl;
            sp();
            int outcome = rand() % 2;

            if (outcome == 0) {
                cout << "You managed to mitigate the effects, but lost some fuel." << endl;
                current_ship->fueling(-15); // Adjust fuel amount after the event
            } else {
                cout << "The flare caused significant damage. You lost fuel and crew members." << endl;
                current_ship->fueling(-25); // More fuel lost
                current_ship->disembark(-2); // Crew members lost
            }
        }
    };

    class AlienDiplomacyRandomEvent : public RandomEvent {
    public:
        void executeEvent(Spaceship *current_ship) override {
            sp();
            cout << "You encounter a peaceful alien species interested in diplomacy!" << endl;
            sp();
            cout << "Options:" << endl;
            cout << "1. Engage in diplomacy" << endl;
            cout << "2. Ignore them" << endl;

            int choice;
            cin >> choice;

            if (choice == 1) {
                int diplomacyOutcome = rand() % 2;

                if (diplomacyOutcome == 0) {
                    sp();
                    cout << "Diplomacy successful! The aliens offer resources in exchange for information." << endl;
                    current_ship->fueling(15); // Adjust resources gained from successful diplomacy
                } else {
                    sp();
                    cout << "Your diplomacy attempt failed. The aliens leave without interaction." << endl;
                }
            } else if (choice == 2) {
                sp();
                cout << "You chose to ignore the aliens. No further interaction occurs." << endl;
            } else {
                cout << "Invalid choice!" << endl;
            }
        }
    };

// Derived class representing a random event where the crew encounters a stranger
    class StrangerRandomEvent : public RandomEvent {
    public:
        void executeEvent(Spaceship *current_ship) override {
            cout << "While exploring, the crew encounters a stranger walking in the desert." << endl;
            sp();
            cout << "The stranger seems to have important information." << endl;

            cout << "Options:" << endl;
            cout << "1. Approach the stranger" << endl;
            cout << "2. Ignore the stranger" << endl;

            int choice;
            cin >> choice;

            if (choice == 1) {
                sp();
                cout << "You chose to approach the stranger." << endl;
                sp();
                cout << "The stranger warns you about a nearby dangerous area, saving your crew!" << endl;
            } else if (choice == 2) {
                sp();
                cout << "You chose to ignore the stranger." << endl;
                sp();
                cout << "As you ignore the stranger, your crew wanders into a dangerous area and suffers casualties."
                     << endl;
                current_ship->disembark(-2); // Losing 2 crew members
            } else {
                cout << "Invalid choice!" << endl;
            }
        }
    };

// Derived class representing a random event where the spaceship is ambushed by bandits
    class BanditRandomEvent : public RandomEvent {
    public:
        void executeEvent(Spaceship *current_ship) override {
            sp();
            cout << "Your spaceship is ambushed by bandits!" << endl;
            sp();
            cout << "You have to defend your crew." << endl;

            int outcome = rand() % 2;

            if (outcome == 0) {
                sp();
                cout << "You managed to fight off the bandits, but you lost some fuel." << endl;
                current_ship->fueling(-10); // Losing some fuel
            } else {
                sp();
                cout << "You suffered losses. Bandits took advantage and you lost 2 crew members and some fuel."
                     << endl;
                current_ship->disembark(-2); // Losing 2 crew members
                current_ship->fueling(-20); // Losing more fuel
            }
        }
    };

// Define a new class for the MysteriousArtefactRandomEvent
    class MysteriousArtefactRandomEvent : public RandomEvent {
    public:
        void executeEvent(Spaceship *current_ship) override {
            int choice;
            sp();
            cout << "You found a mysterious artefact! What do you want to do?" << endl;
            sp();
            cout << "1. Examine it closely" << endl;
            cout << "2. Leave it alone" << endl;
            cin >> choice;

            if (choice == 1) {
                sp();
                cout << "The artefact emits a strange energy and grants you extra fuel!" << endl;
                current_ship->fueling(100); // Add extra fuel if examined closely
            } else {
                sp();
                cout
                        << "You decide to leave the artefact undisturbed. Its sassy and wants attention. You'll be punished. by losing a member (-1) and fuel(-15)"
                        << endl;
                current_ship->fueling(-15);
                current_ship->disembark(-1);
            }
        }
    };

// Game class managing game logic and interactions
class Game {
    private:
        vector<Spaceship *> spaceships;
        vector<Planet *> planets;
        vector<bool> exploredPlanets;
        Spaceship *current_ship;
        int currentPlanetIndex;
        RandomEvent *currentEvent;

    public:
        // Constructor initializing game state
        Game() : current_ship(nullptr), currentPlanetIndex(0), currentEvent(nullptr) {

            // Initialize spaceships
            spaceships.push_back(new StealthShip());
            spaceships.push_back(new JetShip());
            spaceships.push_back(new TravelShip());

            // Initialize planets
            planets.push_back(new Planet("Terra Nova", "A lush green planet with abundant resources", 30, 2));
            planets.push_back(new Planet("Aurora Prime", "An icy world with valuable mineral deposits", 40, 3));
            planets.push_back(new Planet("Nebula Serenity", "A gas giant with peculiar atmospheric phenomena", 50, 4));
            planets.push_back(new Planet("Phoenix Rebirth", "A volcanic planet with geothermal energy sources", 35, 5));
            planets.push_back(new Planet("Galactic Haven", "A peaceful planet with advanced civilizations", 45, 2));
            planets.push_back(new Planet("Asteria Minor", "A small rocky planet with hidden ancient ruins", 25, 3));
            planets.push_back(
                    new Planet("Celestial Odyssey", "A planet shrouded in mystery with rare artifacts", 55, 4));
            planets.push_back(
                    new Planet("Elysium Fields", "A paradise-like planet with stunning natural beauty", 60, 2));

            for (size_t i = 0; i < planets.size(); ++i) {
                exploredPlanets.push_back(false);
            }

        }

        // Method for player to choose a spaceship
        void chooseShip() {
            int choice;
            do {
                cout << "Choose your spaceship:" << endl;
                sp();
                cout << endl;
                for (int i = 0; i < spaceships.size(); ++i) {
                    cout << i + 1 << ". " << spaceships[i]->getDescription() << endl;
                }
                cin >> choice;
            } while (choice < 1 || choice > 3);

            current_ship = spaceships[choice - 1];
            cout << "You've chosen: " << current_ship->getDescription() << endl;
        }

        void displayGameStatus(Spaceship *current_ship) {
            cout << endl;
            sp();
            cout << "----- GAME STATUS -----" << endl;
            cout << "Current Planet: " << planets[currentPlanetIndex]->getName() << endl;
            cout << "-----------------------" << endl;
            sp();
            cout << "Ship Type --> " << current_ship->getDescription() << endl;
            cout << "Fuel Efficiency: " << current_ship->getFuelEfficiency() << endl;
            cout << "-----------------------" << endl;
            sp();
            cout << "Money: " << current_ship->getMoney() << endl;
            cout << "Fuel: " << current_ship->getFuel() << endl;
            cout << "Crew: " << current_ship->getCrew() << endl;
            sp();
            cout << "-----------------------" << endl;
            cout << endl;

            int exploredCount = 0;
            for (bool explored: exploredPlanets) {
                if (explored) {
                    exploredCount++;
                }
            }
            cout << "Planets Explored: " << exploredCount << "/" << planets.size() << endl;

            int planetsLeft = planets.size() - exploredCount;
            cout << "Planets Left to Explore: " << planetsLeft << endl;
            sp();

            cout << "Remaining Planets:" << endl;
            for (size_t i = 0; i < exploredPlanets.size(); ++i) {
                if (!exploredPlanets[i]) {
                    cout << "- " << planets[i]->getName();
                }
            }
            cout << "-----------------------" << endl;
        }

    // Inside the Game class

    void buyFuel() {
        int fuelPrice = 5; // Set the price of fuel (adjust as needed)
        int maxFuelToBuy = 50; // Set the maximum amount of fuel a player can buy at once

        int fuelToBuy;
        cout << "Fuel Price: " << fuelPrice << " credits per unit" << endl;
        cout << "How much fuel do you want to buy? (Max: " << maxFuelToBuy << " units): ";
        cin >> fuelToBuy;

        // Check if the player has enough money and if the entered amount is within limits
        if (current_ship->getMoney() >= fuelPrice * fuelToBuy && fuelToBuy > 0 && fuelToBuy <= maxFuelToBuy) {
            int cost = fuelPrice * fuelToBuy;
            current_ship->fueling(fuelToBuy);
            current_ship->getPaid(-cost);
            cout << "You've bought " << fuelToBuy << " units of fuel for " << cost << " credits." << endl;
        } else {
            cout << "Invalid input or insufficient funds!" << endl;
        }
    }

    void buyCrew() {
        int crewPrice = 10; // Set the price of hiring a crew member (adjust as needed)
        int maxCrewToBuy = 5; // Set the maximum number of crew members a player can hire at once

        int crewToBuy;
        cout << "Crew Member Price: " << crewPrice << " credits per crew member" << endl;
        cout << "How many crew members do you want to hire? (Max: " << maxCrewToBuy << " members): ";
        cin >> crewToBuy;

        // Check if the player has enough money and if the entered amount is within limits
        if (current_ship->getMoney() >= crewPrice * crewToBuy && crewToBuy > 0 && crewToBuy <= maxCrewToBuy) {
            int cost = crewPrice * crewToBuy;
            current_ship->disembark(crewToBuy);
            current_ship->getPaid(-cost);
            cout << "You've hired " << crewToBuy << " crew members for " << cost << " credits." << endl;
        } else {
            cout << "Invalid input or insufficient funds!" << endl;
        }
    }


    // Function to save the game state in CSV format
        void saveGame(const string &filename) {
            ofstream file(filename);

            if (file.is_open()) {
                // Save player resources on separate lines
                file << current_ship->getFuel() << endl;
                file << current_ship->getCrew() << endl;
                file << current_ship->getMoney() << endl;

                // Save current planet index on a new line
                file << currentPlanetIndex << endl;

                // Save explored planets status on separate lines
                for (bool explored: exploredPlanets) {
                    file << (explored ? "1" : "0") << endl;
                }

                // Save current ship type index on a new line
                int shipTypeIndex = -1;
                for (size_t i = 0; i < spaceships.size(); ++i) {
                    if (current_ship == spaceships[i]) {
                        shipTypeIndex = static_cast<int>(i);
                        break;
                    }
                }
                file << shipTypeIndex << endl;

                file.close();
                sp();
                cout << "Game state saved successfully to " << filename << "!" << endl;
            } else {
                cout << "Unable to open file for saving!" << endl;
            }
        }

// Function to load the game state from a CSV file
        void loadGame(const string &filename) {
            ifstream file(filename);

            if (file.is_open()) {

                string line;
                // Read current fuel and crew count of the spaceship
                getline(file, line);
                int savedFuel = stoi(line);
                getline(file, line);
                int savedCrew = stoi(line);
                getline(file, line);
                int savedMoney = stoi(line);

                // Set the loaded fuel and crew count to the spaceship
                current_ship->fueling(savedFuel - current_ship->getFuel()); // Adding the difference to update fuel
                current_ship->disembark(savedCrew - current_ship->getCrew()); // Adding the difference to update crew
                current_ship->getPaid(savedMoney - current_ship->getMoney()); // Adding the difference to update fuel

                // Read current planet index
                getline(file, line);
                currentPlanetIndex = stoi(line);

                // Read explored planets status
                int index = 0;
                while (getline(file, line)) {
                    if (index >= exploredPlanets.size()) {
                        break;
                    }
                    exploredPlanets[index++] = (line == "1");
                }

                int shipTypeIndex;
                // Read and set current ship type
                getline(file, line);
                shipTypeIndex = stoi(line);

                if (shipTypeIndex >= 0 && shipTypeIndex < static_cast<int>(spaceships.size())) {
                    current_ship = spaceships[shipTypeIndex];
                }

                file.close();
                sp();
                cout << "Game state loaded successfully from " << filename << "!" << endl;

                // Display game status after loading
                displayGameStatus(current_ship);
                cout << "Continue playing from here!" << endl;
            } else {
                cout << "File does not exist. I recommend starting a new game." << endl;
            }
        }

        // Method to explore a planet
        void explorePlanet() {
            if (exploredPlanets[currentPlanetIndex]) {
                cout << "You've already explored this planet!" << endl;
                return;
            }

            // Check if the planet can be explored in the current order
            if (currentPlanetIndex != 0 && !exploredPlanets[currentPlanetIndex - 1]) {
                cout << "You must explore planets in order!" << endl;
                return;
            }

            // Display exploration process and planet description
            cout << "Exploring........ " << endl;
            sp();
            cout << "WELCOME TO " << planets[currentPlanetIndex]->getName() << "!! ....." << endl;
            sp();
            cout << planets[currentPlanetIndex]->getDescription() << endl;

            // Award the player upon visiting a planet
            int fuelAwarded = 20; // Adjust this value as needed
            int moneyAwarded = 50; // Adjust this value as needed
            int crewAwarded = +2; // Adjust this value as needed

            // Award fuel, money, and crew
            current_ship->fueling(fuelAwarded);

            current_ship->getPaid(moneyAwarded);

            current_ship->disembark(crewAwarded);

            // Update explored status of the current planet
            exploredPlanets[currentPlanetIndex] = true;

            // Trigger unique event for the planet
            planets[currentPlanetIndex]->simulateExplorationEvent(current_ship);

            // Exploration of the planet happens automatically

            int fuelRequired = planets[currentPlanetIndex]->getFuelRequired();
            current_ship->explore(fuelRequired);

            if (currentEvent != nullptr) {
                currentEvent->executeEvent(current_ship);
                delete currentEvent;
                currentEvent = nullptr;
            }

            // Move to the next planet or loop back to the first one
            if (currentPlanetIndex == planets.size() - 1) {
                currentPlanetIndex = 0; // Loop back to the first planet
            } else {
                ++currentPlanetIndex; // Move to the next planet
            }
        }


        // Method to trigger a random event during planet exploration
        void triggerRandomEvent() {
            int eventsCount = rand() % 4 + 1; // Generate a random number between 1 and 4

            for (int i = 0; i < eventsCount; ++i) {
                sp();
                int eventType = rand() % 6; // Update based on the number of events (including the new one)
                cout << endl;
                if (eventType == 0) {
                    cout << "Random Event Occurred: Stranger Encounter!" << endl;
                    currentEvent = new StrangerRandomEvent();
                    currentEvent->executeEvent(current_ship);
                } else if (eventType == 1) {
                    cout << "Random Event Occurred: Bandit Ambush!" << endl;
                    currentEvent = new BanditRandomEvent();
                    currentEvent->executeEvent(current_ship);
                } else if (eventType == 2) {
                    cout << "Random Event Occurred: Mysterious Artefact!" << endl;
                    currentEvent = new MysteriousArtefactRandomEvent();
                    currentEvent->executeEvent(current_ship);
                } else if (eventType == 3) {
                    cout << "Random Event Occurred: Solar Flare!" << endl;
                    currentEvent = new SolarFlareRandomEvent();
                    currentEvent->executeEvent(current_ship);;
                } else if (eventType == 4) {
                    cout << "Random Event Occurred: Alien Diplomacy!" << endl;
                    currentEvent = new AlienDiplomacyRandomEvent();
                    currentEvent->executeEvent(current_ship);
                }
                // Add more conditions for other events if available
            }
        }

        // Method representing the main game loop
        void mainGameLoop() {
            int choice;
            do {
                cout << endl;
                cout << "1. Explore planet" << endl;
                sp();
                cout << "2. Display Game Status" << endl;
                sp();
                cout << "3. Save game" << endl;
                sp();
                cout << "4. Load game" << endl;
                sp();
                cout << "5. Exit" << endl;
                sp();
                cout << endl;
                cin >> choice;

                switch (choice) {
                    case 1:
                        explorePlanet();
                        triggerRandomEvent();
                        break;
                    case 2:
                        displayGameStatus(current_ship);
                        break;
                    case 3: {
                        string savefile;
                        cout << "Enter the filename to save to: ";
                        cin >> savefile;
                        saveGame(savefile);
                        break;
                    }

                    case 4: {
                        string loadfile;
                        cout << "Enter the filename to load: ";
                        cin >> loadfile;
                        loadGame(loadfile);
                        break;
                    }
                    case 5:
                        cout << "Exiting the game." << endl;
                        break;
                    case 6:
                        buyFuel();
                        break;
                    case 7:
                        buyCrew();
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                }

                // Check for game over conditions
                bool allPlanetsExplored = true;
                for (bool explored: exploredPlanets) {
                    if (!explored) {
                        allPlanetsExplored = false;
                        break;
                    }
                }

                if (allPlanetsExplored) {
                    cout << "Congratulations! You've explored all planets. You win!" << endl;
                    break;
                }

                // Check for lose conditions
                if (current_ship->getCrew() <= 0 || current_ship->getFuel() <= 29) {
                    cout << "Game Over! You're out of crew or fuel. Better luck next time!" << endl;
                    cout << endl;
                    displayGameStatus(current_ship);
                    break;
                }
            } while (choice != 6);
        }


        // Destructor to free memory
        ~Game() {
            for (auto &ship: spaceships) {
                delete ship;
            }
            for (auto &planet: planets) {
                delete planet;
            }
        }
    };
};

// Main function running the game
int main() {
    std::cout << "  _______  _______  _______  _______  _______  _______  _______" << std::endl;
    std::cout << " |   |   ||   |   ||   |   ||   |   ||   |   ||   |   ||   |   |" << std::endl;
    std::cout << " |   |___||   |___||   |___||   |___||   |___||   |___||   |___|" << std::endl;
    std::cout << " |_______||_______||_______||_______||_______||_______||_______|" << std::endl;
    std::cout << "  _|___|____|___|____|___|____|___|____|___|____|___|____|___|_" << std::endl;
    std::cout << " |___|_____|___|____|___|____|___|____|___|____|___|____|___|_|" << std::endl;
    cout << endl;
    sp();

    cout << "!!!WELCOME TO THE SPACE ODYSSEY!!!" << endl;
    cout << "__________________________________" << endl;
    cout << " - You will travel across 8 planets. During each trip events will occur:\n   accidents and spells of good fortune\n   Use your limited resources and wits to survive!!!" << endl;
    cout << " - You will choose a spaceship with certain properties and resources that you will use throughout the game" << endl;
    cout << " - You will have two chances to buy goods. Use them well" << endl;
    cout << endl;
    sp();

    std::cout << "    /\\   " << std::endl;
    std::cout << "   /  \\  " << std::endl;
    std::cout << "  /    \\ " << std::endl;
    std::cout << " |      |" << std::endl;
    std::cout << " |      |" << std::endl;
    std::cout << " |______|" << std::endl;
    cout << endl;

    srand(static_cast<unsigned int>(time(nullptr))); // Seed for randomization
    Planet::Game game;
    game.chooseShip(); // Player chooses a spaceship
    game.mainGameLoop(); // Main game loop
    return 0;
};
//end