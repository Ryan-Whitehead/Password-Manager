# Linux Password Manager

A simple command-line password manager written in C++ that allows users to store, generate, and manage passwords securely.
Features

    User authentication with master password

    Secure password storage

    Password generation with customizable options:

        Length selection

        Character type selection (lowercase, uppercase, digits, symbols)

    Password storage associated with website/service names

    Basic file-based storage system

Requirements

    C++ compiler (supporting C++11 or later)

    OpenSSL library (for SHA-256 hashing)

    Unix-like system (uses unistd.h)

Installation

    Clone the repository:
    git clone [repository-url]
cd password-manager

Compile the program:
    make

Run the program:
    ./main


Usage

    Upon first run, you'll be prompted to create a master password

    After authentication, you can:

        Store new passwords (option 1)

        View stored passwords (option 2)

        Generate new passwords (option 3)

        Exit the program (option 4)

Security Notes

    Uses SHA-256 hashing for master password storage

    Includes a fixed salt (for demonstration purposes - not recommended for production)

    Passwords are stored in plaintext in individual user files

    For real-world use, additional security measures should be implemented:

        Random salts for each user

        Encryption of stored passwords

        More secure file permissions

Limitations

    Basic file-based storage (not suitable for large numbers of passwords)

    No password editing or deletion functionality

    No search functionality

    Minimal error handling

License

This project is open-source and available for free use. No warranty is provided.
Future Improvements

Planned enhancements include:

    Adding search functionality for passwords

    Implementing individual password files per user

    Adding password modification and deletion options
