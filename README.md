#  Classical Encryption Algorithms

A comprehensive C++ implementation of various classical encryption algorithms for educational purposes and text encryption.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Implemented Ciphers](#implemented-ciphers)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Examples](#examples)
- [Mathematical Background](#mathematical-background)
- [Contributing](#contributing)

##  Overview

This project provides a complete library of classical encryption algorithms implemented in C++. It's designed for educational purposes to help understand the fundamentals of cryptography and how various historical ciphers work.

##  Features

- **6 Classical Cipher Implementations**
- **Interactive Menu System**
- **Both Encryption and Decryption Support**
- **Input Validation and Error Handling**
- **Mathematical Helper Functions**
- **Matrix Operations for Advanced Ciphers**
- **Brute Force Decryption Options**

##  Implemented Ciphers

### 1. Caesar Cipher (Shift Cipher)
- **Type**: Substitution cipher
- **Key**: Single integer (0-25)
- **Features**: 
  - Encrypt/decrypt with specific shift
  - Show all possible decryptions (brute force)

### 2. Affine Cipher
- **Type**: Mathematical substitution cipher
- **Key**: Two integers (a, b) where gcd(a, 26) = 1
- **Formula**: `E(x) = (ax + b) mod 26`

### 3. Vigenère Cipher
- **Type**: Polyalphabetic substitution cipher
- **Key**: String of letters
- **Features**: Repeating key pattern for enhanced security

### 4. Hill Cipher
- **Type**: Polygraphic substitution cipher
- **Key**: n×n matrix with determinant coprime to 26
- **Features**: Matrix-based encryption using linear algebra

### 5. Playfair Cipher
- **Type**: Digraph substitution cipher
- **Key**: String used to generate 5×5 matrix
- **Features**: Encrypts pairs of letters using position rules

### 6. Transposition Cipher
- **Type**: Transposition cipher
- **Key**: Integer for column count
- **Features**: Rearranges character positions rather than substituting

##  Getting Started

### Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- C++11 or later standard support

### Installation

1. **Clone the repository**
```bash
git clone https://github.com/yourusername/classical-encryption-algorithms.git
cd classical-encryption-algorithms
```

2. **Compile the program**
```bash
g++ -std=c++11 -o cipher_program main.cpp
```

3. **Run the program**
```bash
./cipher_program
```

##  Usage

The program features an interactive menu system:

```
=================================================
           CLASSICAL ENCRYPTION ALGORITHMS        
=================================================

-------------------------------------------------
                 CIPHER MENU                     
-------------------------------------------------
1. Caesar Cipher (Shift Cipher)
2. Affine Cipher
3. Vigenère Cipher
4. Hill Cipher
5. Transposition Cipher
6. Playfair Cipher
7. Exit Program
-------------------------------------------------
```

### Input Requirements

- **Messages**: All lowercase letters
- **Keys**: Vary by cipher type (integers, strings, matrices)
- **Spaces**: Preserved in output where applicable

##  Examples

### Caesar Cipher
```
Input: "hello world"
Key: 3
Output: "khoor zruog"
```

### Vigenère Cipher
```
Input: "attackatdawn"
Key: "lemon"
Output: "lxfopvefrnhr"
```

### Affine Cipher
```
Input: "affinecipher"
Key: a=5, b=8
Output: "ihhwvcswbsct"
```

##  Mathematical Background

### Key Mathematical Functions

- **Modular Arithmetic**: Custom `mod()` function for proper negative number handling
- **Greatest Common Divisor**: Euclidean algorithm implementation
- **Modular Inverse**: Extended Euclidean algorithm
- **Matrix Operations**: Determinant calculation and matrix inversion for Hill cipher

##  Code Structure

```
CipherLibrary Class
├── Mathematical Helpers
│   ├── mod()
│   ├── gcd()
│   ├── inverseMod()
│   └── Matrix operations
├── Cipher Implementations
│   ├── caesarCipher()
│   ├── affineCipher()
│   ├── vigenereCipher()
│   ├── hillCipher()
│   ├── playfairCipher()
│   └── transpositionCipher()
└── User Interface
    ├── displayHeader()
    ├── displayMenu()
    └── main()
```

##  Contributing

Contributions are welcome! Here are some ways you can help:

1. **Bug Reports**: Found a bug? Please open an issue
2. **Feature Requests**: Ideas for new ciphers or improvements
3. **Code Improvements**: Optimization, better error handling, or documentation
4. **Additional Ciphers**: Implementation of other classical ciphers

### Development Guidelines

- Follow existing code style and naming conventions
- Include comments for complex mathematical operations
- Test all encryption/decryption pairs
- Ensure input validation for all user inputs

##  Acknowledgments

- Historical cryptographers who developed these ciphers
- Educational institutions promoting cryptography education
- Open source community for best practices and inspiration

---

** If you found this project helpful, please consider giving it a star!**
