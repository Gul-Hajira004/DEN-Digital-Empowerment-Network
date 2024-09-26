#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class InvalidInputError
{
public:
    void message()
    {
        cout << endl << "=> Invalid Input. Please try again!" << endl;
    }
};

void readFromFile(const string &fileName, string &data)
{
    ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        cerr << "=> Unable to open file: " << fileName << endl;
        return;
    }
    ostringstream buffer;
    buffer << inputFile.rdbuf();
    data = buffer.str();
    inputFile.close();
}

void writeToFile(const string &fileName, const string &data)
{
    ofstream outputFile(fileName);
    if (!outputFile.is_open())
    {
        cerr << "=> Unable to write to file: " << fileName << endl;
        return;
    }
    outputFile << data;
    outputFile.close();
}

void encodeString(const string &input, string &encoded)
{
    int length = input.length();
    for (int i = 0; i < length; i++)
    {
        int count = 1;
        while (i + 1 < length && input[i] == input[i + 1])
        {
            count++;
            i++;
        }
        encoded += input[i];
        encoded += to_string(count);
    }
}

void decodeString(const string &encodedInput, string &decoded)
{
    for (int i = 0; i < encodedInput.length(); i++)
    {
        char currentChar = encodedInput[i];
        i++;
        string countStr;
        while (i < encodedInput.length() && isdigit(encodedInput[i]))
        {
            countStr += encodedInput[i];
            i++;
        }
        if (countStr.empty())
        {
            cerr << "=> Invalid format detected! No count found for character: '" << currentChar << "'" << endl;
            return;
        }
        int count = stoi(countStr);
        decoded.append(count, currentChar);
        i--;
    }
}

bool checkFileType(const string &fileName)
{
    if (fileName.length() < 4)
        return false;
    return fileName.substr(fileName.length() - 4) == ".txt";
}

int main()
{
    string sourceFile = "data.txt";
    string compressedFile = "output_compressed.txt";
    string decompressedFile = "output_decompressed.txt";
    int userChoice;

    do
    {
        try
        {
            cout << endl << "===== MENU =====" << endl;
            cout << "1. Compress File" << endl;
            cout << "2. Decompress File" << endl;
            cout << "3. Exit" << endl;
            cout << "Choose an option: ";
            cin >> userChoice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                throw InvalidInputError();
            }

            string fileContent;
            readFromFile(sourceFile, fileContent);

            if (!checkFileType(sourceFile))
            {
                cout << "=> Error: Unsupported file type. Please use a .txt file." << endl;
                continue;
            }

            if (fileContent.empty())
            {
                cout << "=> Error: The source file is empty!" << endl;
                continue;
            }

            if (userChoice == 1)
            {
                string compressedData;
                encodeString(fileContent, compressedData);
                writeToFile(compressedFile, compressedData);
                cout << endl << "=> Compression Successful!" << endl;
            }
            else if (userChoice == 2)
            {
                string encodedData;
                readFromFile(compressedFile, encodedData);
                if (encodedData.empty())
                {
                    cout << "=> Error: Compressed file is empty. Cannot proceed with decompression." << endl;
                }
                else
                {
                    string decompressedData;
                    decodeString(encodedData, decompressedData);
                    writeToFile(decompressedFile, decompressedData);
                    cout << endl << "=> Decompression Successful!" << endl;
                }
            }
        }
        catch (InvalidInputError &error)
        {
            error.message();
        }

    } while (userChoice != 3);

    cout << endl << "=> Exiting program. Thank you!" << endl;
    return 0;
}
