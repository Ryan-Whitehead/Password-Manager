#include "pwManager.hpp"


int main(){
    int choice;
    std::string site, username, password;
    PwManager manager;

    manager.startMenu();

    do {
        manager.displayMenu();
        std::cin >> choice;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
        std::string generated;
    switch(choice){
        case 1:
            manager.displayHelper("Enter site name");
            std::cin >> site;
            manager.displayHelper("Enter username: ");
            std::cin >> username;
            manager.displayHelper("Enter password (or type 'generate' to create one): ");
                std::cin >> password;
                
                if (password == "generate") {
                    password = manager.generatePassword();
                    if (!password.empty()) {
                        manager.displayHelper("Generated password: " + password);
                    }
                }
                manager.savePassword(site, username, password);
                break;
        case 2:
            manager.loadPasswords();
            break;
        case 3:
            generated = manager.generatePassword();
            if (!generated.empty()){
                manager.displayHelper("Generated password: " + generated);
            }
            break;
        case 4:
            manager.displayHelper("[System] Exiting...");

            break;
        default: 
            manager.displayHelper("\n [System] Invalid Choice. Please try again");
            break;
    }
    } while (choice != 4);
}