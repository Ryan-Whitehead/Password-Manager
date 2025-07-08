#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>
#include <openssl/sha.h>
#include <unistd.h>

class PwManager{
    private:
        std::string username;
        std::string masterPasswordHash;
        const std::string salt = "FixedSaltForDemo";
        std::string possibleChars = "";
        std::string lowercase = "abcdefghijklmnopqrstuvwyz";
        std::string uppercase = "ABCDEFGIJKLMNOPQRSTUVWYZ";
        std::string digits = "0123456789";
        std::string symbols = "!@#$%^&*()-_+ ={}<>?";
        std::pair<std::string, std::string> siteAndPwd;
        std::string sha256_hash(const std::string& password);
        bool fileExists(const std::string& filename);
    public:
        PwManager();
        void startMenu();
        void createNewUser();
        bool authenticateUser();
        void failedLogin();
        void displayMenu();
        void displayHelper(const std::string& msg);
        void savePassword(const std::string& site, const std::string& username, const std::string& password);
        void loadPasswords();
        std::string generatePassword();
        int pwdLength();
        void generatePasswordMenu();
        void possibleKeys(const int& choice);
        void searchPasswordByWebsite();
        void viewAllPasswords();
        bool linearSearch(const std::string& targetSite, std::string& foundPassword);


};