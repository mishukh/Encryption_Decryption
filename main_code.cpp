
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// CipherLibrary class definition
class CipherLibrary {
private:
    // Mathematical helper functions
    long long mod(long long a, long long b);
    long long gcd(long long a, long long b);
    long long inverseMod(long long a, long long b);
    long long inverseModSupport(long long a, long long b, long long x0 = 0, long long x1 = 1);
    
    // Matrix operations for Hill cipher
    long long determinant(std::vector<std::vector<float>> matrix, int order);
    std::vector<std::vector<float>> inverseModMatrix(std::vector<std::vector<float>> matrix, int order);

public:
    // Classical cipher implementations
    void caesarCipher();
    void vigenereCipher();
    void affineCipher();
    void hillCipher();
    void playfairCipher();
    void transpositionCipher();
    
    // Constructor and destructor
    CipherLibrary() {}
    ~CipherLibrary() {}
};

// Mathematical helper functions
long long CipherLibrary::mod(long long a, long long b) {
    if (a >= 0) {
        return a % b;
    } else {
        return (-1 * (a / b) + 1) * b + a; 
    }
}

long long CipherLibrary::gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, mod(a, b));
    }
}

long long CipherLibrary::inverseModSupport(long long a, long long b, long long x0, long long x1) {
    if (a > b && b != 0) {
        long long d = x1;
        x1 = (-1 * x1) * (a / b) + x0;
        x0 = d;
    }
    
    if (b == 0) {
        return x0;
    } else {
        return inverseModSupport(b, mod(a, b), x0, x1);
    }
}

long long CipherLibrary::inverseMod(long long a, long long b) {
    long long t = inverseModSupport(a, b);
    
    if (mod(a * t, b) == 1) {
        return t;
    } else {
        t = (1 - (b * t)) / a;
        return t;
    }
}

// Matrix operations for Hill cipher
long long CipherLibrary::determinant(vector<vector<float>> mat, int order) {
    float ratio;
    
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if (j > i) { // Elementary row operations
                ratio = mat[j][i] / mat[i][i];
                for (int k = 0; k < order; k++) {
                    mat[j][k] -= ratio * mat[i][k];
                }
            }
        }
    }
    
    float det = 1;
    for (int i = 0; i < order; i++) {
        det *= mat[i][i];
    }
    
    if (isnan(det)) {
        return 0;
    } else {
        return (long long)nearbyintf(det);
    }
}

vector<vector<float>> CipherLibrary::inverseModMatrix(vector<vector<float>> mat, int order) {
    vector<vector<float>> inv(order, vector<float>(order));
    
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if (i == j) {
                inv[i][j] = 1;
            } else {
                inv[i][j] = 0;
            }
        }
    }

    // Ordering of rows
    for (int i = order - 1; i > 0; i--) {
        if (mat[i-1][0] < mat[i][0]) {
            for (int j = 0; j < order; j++) {
                int d = mat[i][j];
                mat[i][j] = mat[i-1][j];
                mat[i-1][j] = d;
                d = inv[i][j];
                inv[i][j] = inv[i-1][j];
                inv[i-1][j] = d;
            }
        }
    }
    
    // Row operations
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if (j != i) {
                float d = mat[j][i] / mat[i][i];
                for (int k = 0; k < order; k++) {
                    mat[j][k] -= (mat[i][k] * d);
                    inv[j][k] -= (inv[i][k] * d);
                }
            }
        }
    }
    
    long long de = determinant(mat, order);
    long long inv_de = inverseMod(de, 26);
    
    // Doing the modulus work
    for (int i = 0; i < order; i++) {
        float d = mat[i][i];
        for (int j = 0; j < order; j++) {
            inv[i][j] = (float)de * inv[i][j] / d;
            inv[i][j] = mod(inv_de * (long long)inv[i][j], 26);
        }
    }
    
    return inv;
}

// Caesar Cipher implementation
void CipherLibrary::caesarCipher() {
    cout << "\n------------ CAESAR CIPHER ------------" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice: ";
    
    int cryptChoice;
    cin >> cryptChoice;
    
    if (cryptChoice == 1) {
        cout << "\n-------Encryption-------" << endl;
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "Enter shift key (0-25): ";
        int shift;
        cin >> shift;
        shift = mod(shift, 26);
        
        for (int i = 0; i < message.length(); i++) {
            if (message[i] == ' ') {
                continue;
            }
            
            if (message[i] + shift <= 'z') {
                message[i] += shift;
            } else {
                message[i] = 'a' + shift - ('z' - message[i]) - 1;
            }
        }
        
        cout << "\nEncrypted text: " << message << endl;
    } else if (cryptChoice == 2) {
        cout << "\n-------Decryption-------" << endl;
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "1. Decrypt with specific shift" << endl;
        cout << "2. Show all possible decryptions" << endl;
        cout << "Enter choice: ";
        
        int decryptChoice;
        cin >> decryptChoice;
        
        if (decryptChoice == 1) {
            cout << "Enter shift key (0-25): ";
            int shift;
            cin >> shift;
            shift = mod(shift, 26);
            
            for (int i = 0; i < message.length(); i++) {
                if (message[i] == ' ') {
                    continue;
                }
                
                if (message[i] - shift >= 'a') {
                    message[i] -= shift;
                } else {
                    message[i] = 'z' - shift + (message[i] - 'a') + 1;
                }
            }
            
            cout << "\nDecrypted text: " << message << endl;
        } else if (decryptChoice == 2) {
            cout << "\nAll possible decryptions:" << endl;
            string original = message;
            
            cout << "Shift 0: " << message << endl;
            
            for (int shift = 1; shift <= 25; shift++) {
                message = original;
                
                for (int i = 0; i < message.length(); i++) {
                    if (message[i] == ' ') {
                        continue;
                    }
                    
                    if (message[i] - 1 >= 'a') {
                        message[i] -= 1;
                    } else {
                        message[i] = 'z';
                    }
                }
                
                cout << "Shift " << shift << ": " << message << endl;
                original = message;
            }
        }
    }
}

// Vigenere Cipher implementation
void CipherLibrary::vigenereCipher() {
    cout << "\n------------ VIGENERE CIPHER ------------" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice: ";
    
    int cryptChoice;
    cin >> cryptChoice;
    
    if (cryptChoice == 1) {
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "Enter Key [lowercase letters]: ";
        string key;
        getline(cin, key);
        
        int j = 0;
        for (int i = 0; i < message.length(); i++) {
            if (message[i] == ' ') {
                continue;
            }
            
            if (j == key.length()) {
                j = 0;
            }
            
            int shift = key[j++] - 'a';
            
            if (message[i] + shift <= 'z') {
                message[i] += shift;
            } else {
                message[i] = 'a' + shift - ('z' - message[i]) - 1;
            }
        }
        
        cout << "\nEncrypted text: " << message << endl;
    } else if (cryptChoice == 2) {
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "Enter Key [lowercase letters]: ";
        string key;
        getline(cin, key);
        
        int j = 0;
        for (int i = 0; i < message.length(); i++) {
            if (message[i] == ' ') {
                continue;
            }
            
            if (j == key.length()) {
                j = 0;
            }
            
            int shift = key[j++] - 'a';
            
            if (message[i] - shift >= 'a') {
                message[i] -= shift;
            } else {
                message[i] = 'z' - shift + (message[i] - 'a') + 1;
            }
        }
        
        cout << "\nDecrypted text: " << message << endl;
    }
}

// Affine Cipher implementation
void CipherLibrary::affineCipher() {
    cout << "\n------------ AFFINE CIPHER ------------" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice: ";
    
    int cryptChoice;
    cin >> cryptChoice;
    
    if (cryptChoice == 1) {
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "Enter parameters for the form aX+b" << endl;
        
        int a = 1;
        do {
            cout << "Enter a [must be coprime with 26]: ";
            cin >> a;
        } while (gcd(a, 26) != 1);
        
        int b;
        cout << "Enter b: ";
        cin >> b;
        
        for (int i = 0; i < message.length(); i++) {
            if (message[i] == ' ') {
                continue;
            }
            
            int shift = a * (message[i] - 'a') + b;
            shift = mod(shift, 26);
            
            message[i] = 'a' + shift;
        }
        
        cout << "\nEncrypted text: " << message << endl;
    } else if (cryptChoice == 2) {
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "Enter parameters for the form aX+b" << endl;
        
        int a = 1;
        do {
            cout << "Enter a [must be coprime with 26]: ";
            cin >> a;
        } while (gcd(a, 26) != 1);
        
        int b;
        cout << "Enter b: ";
        cin >> b;
        
        int a_inv = mod(inverseMod(a, 26), 26);
        
        for (int i = 0; i < message.length(); i++) {
            if (message[i] == ' ') {
                continue;
            }
            
            int shift = a_inv * (message[i] - 'a' - b);
            shift = mod(shift, 26);
            
            message[i] = 'a' + shift;
        }
        
        cout << "\nDecrypted text: " << message << endl;
    }
}

// Hill Cipher implementation
void CipherLibrary::hillCipher() {
    cout << "\n------------ HILL CIPHER ------------" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice: ";
    
    int cryptChoice;
    cin >> cryptChoice;
    
    if (cryptChoice == 1) {
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "Enter matrix size (order): ";
        int order;
        cin >> order;
        
        vector<vector<float>> matrix(order, vector<float>(order));
        
        do {
            cout << "Enter the matrix [determinant must be coprime with 26]:" << endl;
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    cin >> matrix[i][j];
                }
            }
        } while (gcd(abs(determinant(matrix, order)), 26) != 1);
        
        // Pad message if needed
        while (message.length() % order != 0) {
            message += 'x';
        }
        
        string result;
        
        for (int k = 0; k < message.length(); k += order) {
            string block = message.substr(k, order);
            vector<int> cipherValues(order, 0);
            
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    cipherValues[i] += (block[j] - 'a') * matrix[j][i];
                    cipherValues[i] %= 26;
                }
                result += (cipherValues[i] + 'a');
            }
        }
        
        cout << "\nEncrypted text: " << result << endl;
    } else if (cryptChoice == 2) {
        cout << "Enter Message [all lowercase letters]: ";
        string message;
        cin.ignore();
        getline(cin, message);
        
        cout << "Enter matrix size (order): ";
        int order;
        cin >> order;
        
        vector<vector<float>> matrix(order, vector<float>(order));
        
        do {
            cout << "Enter the matrix [determinant must be coprime with 26]:" << endl;
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    cin >> matrix[i][j];
                }
            }
        } while (gcd(abs(determinant(matrix, order)), 26) != 1);
        
        vector<vector<float>> inverseMatrix = inverseModMatrix(matrix, order);
        string result;
        
        for (int k = 0; k < message.length(); k += order) {
            string block = message.substr(k, order);
            vector<int> plainValues(order, 0);
            
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    plainValues[i] += (block[j] - 'a') * inverseMatrix[j][i];
                    plainValues[i] %= 26;
                }
                result += (plainValues[i] + 'a');
            }
        }
        
        cout << "\nDecrypted text: " << result << endl;
    }
}

// Playfair Cipher implementation
void CipherLibrary::playfairCipher() {
    cout << "\n------------ PLAYFAIR CIPHER ------------" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice: ";
    
    int cryptChoice;
    cin >> cryptChoice;
    
    cout << "Enter Message [all lowercase letters]: ";
    string message;
    cin.ignore();
    getline(cin, message);
    
    cout << "Enter Key [all lowercase letters]: ";
    string key;
    getline(cin, key);
    
    // Create the 5x5 Playfair matrix
    vector<vector<int>> playfairMatrix(5, vector<int>(5));
    vector<int> letterUsed(26, 0);
    
    letterUsed['j' - 'a'] = 1; // J and I are treated the same
    
    int keyIndex = 0;
    int alphabetIndex = 0;
    
    // Fill matrix with key first
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyIndex < key.length()) {
                while (keyIndex < key.length() && letterUsed[key[keyIndex] - 'a'] != 0) {
                    keyIndex++;
                }
                
                if (keyIndex < key.length()) {
                    playfairMatrix[i][j] = key[keyIndex];
                    letterUsed[key[keyIndex] - 'a'] = 1;
                    keyIndex++;
                } else {
                    // Fill with remaining alphabet
                    while (letterUsed[alphabetIndex] != 0) {
                        alphabetIndex++;
                    }
                    
                    playfairMatrix[i][j] = 'a' + alphabetIndex;
                    letterUsed[alphabetIndex] = 1;
                    alphabetIndex++;
                }
            } else {
                // Fill with remaining alphabet
                while (letterUsed[alphabetIndex] != 0) {
                    alphabetIndex++;
                }
                
                playfairMatrix[i][j] = 'a' + alphabetIndex;
                letterUsed[alphabetIndex] = 1;
                alphabetIndex++;
            }
        }
    }
    
    if (cryptChoice == 1) { // Encryption
        string result;
        
        // Prepare message (separate same letters and handle odd length)
        for (int i = 0; i < message.length(); i += 2) {
            if (i + 1 == message.length()) {
                message.insert(i + 1, "x");
            }
            
            if (message[i] == message[i + 1]) {
                if (message[i] == 'x') {
                    message.insert(i + 1, "q");
                } else {
                    message.insert(i + 1, "x");
                }
                i -= 2; // Re-process this pair
            }
        }
        
        // Encrypt each pair
        for (int i = 0; i < message.length(); i += 2) {
            pair<int, int> pos1, pos2;
            
            // Find positions in the matrix
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 5; col++) {
                    if (playfairMatrix[row][col] == message[i]) {
                        pos1 = make_pair(row, col);
                    } else if (playfairMatrix[row][col] == message[i + 1]) {
                        pos2 = make_pair(row, col);
                    }
                }
            }
            
            // Apply rules
            if (pos1.first == pos2.first) { // Same row
                result += playfairMatrix[pos1.first][(pos1.second + 1) % 5];
                result += playfairMatrix[pos2.first][(pos2.second + 1) % 5];
            } else if (pos1.second == pos2.second) { // Same column
                result += playfairMatrix[(pos1.first + 1) % 5][pos1.second];
                result += playfairMatrix[(pos2.first + 1) % 5][pos2.second];
            } else { // Rectangle
                result += playfairMatrix[pos1.first][pos2.second];
                result += playfairMatrix[pos2.first][pos1.second];
            }
        }
        
        cout << "\nEncrypted text: " << result << endl;
    } else if (cryptChoice == 2) { // Decryption
        string result;
        
        // Decrypt each pair
        for (int i = 0; i < message.length(); i += 2) {
            pair<int, int> pos1, pos2;
            
            // Find positions in the matrix
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 5; col++) {
                    if (playfairMatrix[row][col] == message[i]) {
                        pos1 = make_pair(row, col);
                    } else if (playfairMatrix[row][col] == message[i + 1]) {
                        pos2 = make_pair(row, col);
                    }
                }
            }
            
            // Apply reverse rules
            if (pos1.first == pos2.first) { // Same row
                result += playfairMatrix[pos1.first][(pos1.second + 4) % 5]; // +4 is equivalent to -1 mod 5
                result += playfairMatrix[pos2.first][(pos2.second + 4) % 5];
            } else if (pos1.second == pos2.second) { // Same column
                result += playfairMatrix[(pos1.first + 4) % 5][pos1.second];
                result += playfairMatrix[(pos2.first + 4) % 5][pos2.second];
            } else { // Rectangle
                result += playfairMatrix[pos1.first][pos2.second];
                result += playfairMatrix[pos2.first][pos1.second];
            }
        }
        
        cout << "\nDecrypted text: " << result << endl;
    }
}

// Transposition Cipher implementation
void CipherLibrary::transpositionCipher() {
    cout << "\n------------ TRANSPOSITION CIPHER ------------" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice: ";
    
    int cryptChoice;
    cin >> cryptChoice;
    
    cout << "Enter Message [all lowercase letters]: ";
    string message;
    cin.ignore();
    getline(cin, message);
    
    cout << "Enter Key [numeric]: ";
    int key;
    cin >> key;
    
    if (cryptChoice == 1) { // Encryption
        vector<string> columns(key);
        
        // Distribute message into columns
        for (int i = 0; i < key; i++) {
            int position = i;
            while (position < message.length()) {
                columns[i] += message[position];
                position += key;
            }
        }
        
        // Combine columns to get ciphertext
        string result;
        for (int i = 0; i < key; i++) {
            result += columns[i];
        }
        
        cout << "\nEncrypted text: " << result << endl;
    } else if (cryptChoice == 2) { // Decryption
        // Calculate dimensions
        int rows = ceil((float)message.length() / key);
        int unshaded = rows * key - message.length();
        
        vector<string> result(rows);
        int col = 0, row = 0;
        
        // Reconstruct the transposition grid
        for (int i = 0; i < message.length(); i++) {
            result[col] += message[i];
            col++;
            
            if (col == rows || (col == rows - 1 && row >= key - unshaded)) {
                col = 0;
                row++;
            }
        }
        
        // Read the grid row by row
        string plaintext;
        for (int i = 0; i < rows; i++) {
            plaintext += result[i];
        }
        
        cout << "\nDecrypted text: " << plaintext << endl;
    }
}

// Display functions for the main program
void displayHeader() {
    cout << "=================================================" << endl;
    cout << "           CLASSICAL ENCRYPTION ALGORITHMS        " << endl;
    cout << "=================================================" << endl;
    cout << "This program implements various classical ciphers" << endl;
    cout << "for educational purposes and text encryption." << endl;
}

void displayMenu() {
    cout << "\n-------------------------------------------------" << endl;
    cout << "                 CIPHER MENU                     " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "1. Caesar Cipher (Shift Cipher)" << endl;
    cout << "2. Affine Cipher" << endl;
    cout << "3. Vigenere Cipher" << endl;
    cout << "4. Hill Cipher" << endl;
    cout << "5. Transposition Cipher" << endl;
    cout << "6. Playfair Cipher" << endl;
    cout << "7. Exit Program" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter your choice (1-7): ";
}

// Main function
int main() {
    CipherLibrary cipherLib;
    int choice = 0;
    
    displayHeader();
    
   
        displayMenu();
        cin >> choice;
        
        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number." << endl;
            
        }
        
        switch (choice) {
            case 1:
                cipherLib.caesarCipher();
                break;
            case 2:
                cipherLib.affineCipher();
                break;
            case 3:
                cipherLib.vigenereCipher();
                break;
            case 4:
                cipherLib.hillCipher();
                break;
            case 5:
                cipherLib.transpositionCipher();
                break;
            case 6:
                cipherLib.playfairCipher();
                break;
            case 7:
                cout << "\nThank you for using Classical Encryption Algorithms." << endl;
                return 0;
            default:
                cout << "\nInvalid choice. Please select a number between 1 and 7." << endl;
        
    }
    
    return 0;
}
