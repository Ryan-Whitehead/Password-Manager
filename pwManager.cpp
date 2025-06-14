#include "pwManager.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

/**
 * @brief a constructor for password Manager class
 * @par choice 
 */
PwManager::PwManager() : siteAndPwd("", " "){
    // Constructor initializes member variables
}
//check if file exists in Linux specific system
bool PwManager::fileExists(const std::string& filename){
    return access(filename.c_str(), F_OK) == 0;
}
// SHA-256 hashing
std::string PwManager::sha256_hash(const std::string& password){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::string salted = password + salt;
SHA256(reinterpret_cast<const unsigned char*>(salted.data()), salted.size(), hash);

std::stringstream ss;

 for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    return ss.str();

}

void PwManager::startMenu(){
    displayHelper("=== Password Manager Login ===");
    displayHelper("Enter username");
    std::cin >> username;

    std::string userFile = username + ".txt";
    if (fileExists(userFile)) {
        if (!authenticateUser()) {
            std::cerr << "Authentication failed!" << std::endl;
            exit(1);
        }
    } else {
        createNewUser();
    }
    displayHelper("Login successful! Welcome, " + username + "!");
}

void PwManager::createNewUser(){
    std::string password;
    displayHelper("New user detected. Create a master password: ");
    std::cin >> password;

    masterPasswordHash = sha256_hash(password);
    std::ofstream userFile(username + ".txt");
     if (userFile) {
        userFile << masterPasswordHash << std::endl;
        std::cout << "Account created successfully!" << std::endl;
    } else {
        std::cerr << "Error creating user file!" << std::endl;
        exit(1);
    }
}

bool PwManager::authenticateUser(){
    const int MAX_ATTEMPTS = 3;
    const int DELAY_SECONDS = 2;
    static int failedAttempts = 0;
    //Bruteforce lockout check
    if (failedAttempts >= MAX_ATTEMPTS){
        std::cerr << "Account locked. Too many failed attempts. \n";
        exit(1);
    }
    std::string password;
    displayHelper("Enter master password for " + username + ": ");
    std::cin >> password;

    std::ifstream userFile(username + ".txt");
    if (userFile){
        std::string storedHash;
        userFile >> storedHash;
        if (sha256_hash(password) == storedHash){
            failedAttempts = 0;
            return true;
        }
    }
    // Failed attempt handling
    failedAttempts++;
    std::cerr << "Invalid password! Attempts remaining: " 
              << (MAX_ATTEMPTS - failedAttempts) << "\n";
    
    // Time delay
    sleep(DELAY_SECONDS);

    return false;

}
void PwManager::displayHelper(const std::string& msg){
    std::cout << msg <<std::endl;
    
}
void PwManager::startMenu(){
    displayHelper("Provide your username: \n");
}
void PwManager::displayMenu(){
    displayHelper("\nPassword Manager");
    displayHelper(" 1. Add Password");
    displayHelper(" 2. View Passwords");
    displayHelper(" 3. Generate a password");
    displayHelper(" 4. Exit");
    displayHelper("Enter your choice: ");
}
void PwManager::savePassword(const std::string& site, const std::string& password){
    //Creates an object of file and opens a file (aka a text file), app adds to the file if it exists
    std::ofstream file("passwords.txt", std::ios::app);
    if(file.is_open()){
        file << site << " " << password << "\n";
        file.close();
        displayHelper("Password saved successfully!");
    }
    else {
        std::cerr << "Error: unable to open file for writing \n";
    }
}

void PwManager::loadPasswords(){
    std::ifstream file("passwords.txt");
    if (file.is_open()){
        std::string site, password;
        displayHelper("\nSaved Passwords: ");
        while(file >> site >> password){
            std::cout << "Site: " << site << ", password: " << password << "\n";
        }
        file.close();
    }
    else {
        std::cerr << "\n[System] no passwords saved yet. \n";
    }

}

void PwManager::generatePasswordMenu(){
    displayHelper("Choose which characters you'd like to include");
    displayHelper("1. Lowercase - LC");
    displayHelper("2. Uppercase - UC");
    displayHelper("3. digits - DG");
    displayHelper("4. special characters - SC");
    displayHelper("5. All - Al");
    displayHelper("6. Done");
    displayHelper("7. Exit");
    displayHelper("Option(s): ");
}
int PwManager::pwdLength(){
    int passwordLength;
    displayHelper("How long would you like your password to be?");
    std::cin >> passwordLength;
    return passwordLength;
}

std::string PwManager::generatePassword(){
    int choice;
    std::string password;
    int passwordLength = pwdLength();
    if (passwordLength < 4 || passwordLength > 50){
        displayHelper("Password length must be between 4 and 50 characters");
        passwordLength = pwdLength();
    }
    possibleChars.clear();

    do {
        generatePasswordMenu();
        std::cin >> choice;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (choice >= 1 && choice <= 5){
            possibleKeys(choice);
        }
    }while (choice != 6 && choice != 7);

    if (choice == 6 & !possibleChars.empty()){
        
    }
        std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<> distribution(0, possibleChars.size() - 1);
            
            // Generate the password
            password.clear();
            for (int i = 0; i < passwordLength; ++i) {
                password += possibleChars[distribution(generator)];
            }
            
            return password;
}

void PwManager::possibleKeys(const int& choice){
    switch(choice){
        case 1: 
            possibleChars.append(lowercase);
            generatePasswordMenu();
        case 2:
            possibleChars.append(uppercase);
            generatePasswordMenu();        
            
        case 3: 
            possibleChars.append(digits);
            generatePasswordMenu();
        case 4:
            possibleChars.append(symbols);
            generatePasswordMenu();

        case 5:
        possibleChars.append(lowercase);
        possibleChars.append(uppercase);
        possibleChars.append(digits);
        possibleChars.append(symbols);
        break;
        case 6:
            break;
    }
}