#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <sstream>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class RequestHandler
{
public:
    virtual string processRequest() = 0;
};

class GetRequestHandler : public RequestHandler
{
public:
    string processRequest() override
    {
        return "Processing GET request";
    }
};

class SimpleHttpServer
{
private:
    int serverSocket; 
    struct sockaddr_in serverAddress; 
    int option = 1; 
    int addressLength = sizeof(serverAddress); 

public:
    SimpleHttpServer(int portNumber)
    {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY; 
        serverAddress.sin_port = htons(portNumber); 
        bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
        listen(serverSocket, 3);
    }

    void start()
    {
        while (true)
        {
            int clientSocket = accept(serverSocket, (struct sockaddr*)&serverAddress, (socklen_t*)&addressLength);
            thread(&SimpleHttpServer::handleClientConnection, this, clientSocket).detach();
        }
    }

    void handleClientConnection(int clientSocket)
    {
        char requestBuffer[1024] = {0}; 
        read(clientSocket, requestBuffer, 1024); 
        string clientRequest(requestBuffer);
        cout << "Client request received: " << clientRequest << endl;

        GetRequestHandler getRequest;
        string response = getRequest.processRequest();
        string htmlContent = loadHtmlFile("index.html");

        string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + htmlContent;
        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);
        close(clientSocket); 
    }

    string loadHtmlFile(const string &fileName)
    {
        ifstream htmlFile(fileName);
        stringstream fileBuffer; 
        fileBuffer << htmlFile.rdbuf(); 
        return fileBuffer.str(); 
    }

    ~SimpleHttpServer()
    {
        close(serverSocket); 
    }
};

int main()
{
    int userChoice;
    do
    {
        cout << endl << "OPTIONS MENU" << endl;
        cout << "1. Launch HTTP Server" << endl;
        cout << "2. Exit\n" << endl;
        cout << "Select an option: ";
        cin >> userChoice;

        if (userChoice == 1)
        {
            int portNumber;
            cout << "Enter the port number (e.g., 8080): ";
            cin >> portNumber;

            SimpleHttpServer server(portNumber);
            cout << "HTTP Server is starting on port " << portNumber << endl;
            server.start();
        }
        else if (userChoice == 2)
        {
            cout << "Exiting the application. Thank you!" << endl;
        }
        else
        {
            cout << "Invalid selection. Please choose again.\n";
        }
    } while (userChoice != 2);

    return 0;
}
