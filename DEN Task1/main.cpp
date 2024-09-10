#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "json.hpp"
#include <algorithm>
#include <map>
#include <utility>
using namespace std;
class Location 
{
    public:
    string name;
    double latitude;
    double longitude;
    Location()
    {

    }
    Location (string locname,double lat,double lon):name(locname),latitude(lat),longitude(lon)
    {

    }
    static vector<Location> Locations;
    void AddLocation(const Location& loc) 
    {
        Locations.push_back(loc);
    }
     static void RemoveLocation(const string& locname) 
    {
        auto it=find_if(Locations.begin(),Locations.end(),[&](const Location& loc){return loc.name==locname;});
        if(it != Locations.end())
        {
            Locations.erase(it);
            cout<<"Location "<< locname <<" removed successfully."<<endl;
        }
        else
        {
            cout<<"Location "<< locname <<" not found."<<endl;
        }
    }
    static void ListLocations()
    {
        if(Locations.empty())
        {
            cout<<"No locations available."<<endl;
        }
        else
        {
            for(const auto& loc : Locations) 
            {
                cout<<"Name: "<<loc.name<<"; Latitude: "<<loc.latitude<<"; Longitude: "<<loc.longitude<<endl;
            }
        }
    }
};
vector<Location> Location::Locations;
class WeatherVariable 
{
    private:
    map<string, double> variables;

    public:
    WeatherVariable() 
    {
        variables["Temperature"] = 25.0;
        variables["Humidity"] = 60.0;
    }

    // Define a new variable or overwrite an existing one
    void DefineVariable(const string& key, double value) 
    {
        variables[key] = value;
        cout << "Variable '" << key << "' defined successfully!" << endl;
    }

void UpdateVariable(const string& key) 
{
    auto it = variables.find(key);
    if (it != variables.end())
    {
        double value;
        cout << "Enter the new value for " << key << ": ";
        cin >> value;
        variables[key] = value;
        cout << key << " updated successfully!" << endl;
    }
    else
    {
        cout << "Variable '" << key << "' not found." << endl;
    }
}


void DisplayVariables() const 
{
    cout << "Currently defined variables:\n";
    for (const auto& var : variables) 
    {
        cout << var.first << ": " << var.second << endl;
    }
    if (variables.empty()) 
    {
        cout << "No variables defined yet." << endl;
    }
}

};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) 
{
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}
class WeatherForecastingSystem 
{
    public:
    string fetchWeatherData(double latitude, double longitude) 
    {
        CURL* curl;
        CURLcode res;
        string readBuffer;
        curl = curl_easy_init();
        if (curl) 
        {
            string url = "https://api.open-meteo.com/v1/forecast?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) + "&current_weather=true";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) 
            {
                cerr << "API request failed: " << curl_easy_strerror(res) << endl;
                return "";
            }
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }
    void displayWeatherData(double latitude,double longitude)
    {
        string data=fetchWeatherData(latitude,longitude);
        cout<<"Weather Data for ("<<latitude<<", "<<longitude<<"):"<<data<<endl;
    }
    void exportToCSV(const string& filename, const vector<string>& weatherData) 
    {
        ofstream file(filename);
        if (file) 
        {
            file << "Location,Latitude,Longitude,Temperature,Humidity\n"; 
            for (const auto& data : weatherData)
                file << data << "\n";
            cout << "Data exported to " << filename << " (CSV)." << endl;
        } 
        else 
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
    void exportToJSON(const string& filename, const vector<pair<string, map<string, double>>>& weatherData) 
    {
        nlohmann::json jsonData;
        for (const auto& entry : weatherData)
            jsonData[entry.first] = entry.second;

        ofstream file(filename);
        if (file) 
        {
            file << jsonData.dump(4); 
            cout << "Data exported to " << filename << " (JSON)." << endl;
        } 
        else 
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
};
class HistoricalWeatherSystem
{
    private:
    string apiKey;

    public:
    HistoricalWeatherSystem(const string& key) : apiKey(key) {}

    string fetchHistoricalWeatherData(const string& location)
    {
        return "{\"location\": \"" + location + "\",\"temperature\":26.0,\"wind_speed\":4.0}";
    }

    void displayHistoricalData(const string& location)
    {
        string data = fetchHistoricalWeatherData(location);
        cout << "Historical Weather Data for " << location << ": " << data << endl;
    }

    void exportHistoricalDataToCSV(const string& filename, const vector<string>& historicalData) 
    {
        ofstream file(filename);
        if (file.is_open()) 
        {
            file << "Location,Latitude,Longitude,Date,Temperature,Humidity\n"; 
            for (const auto& data : historicalData) 
            {
                file << data << "\n"; 
            }
            file.close();
            cout << "Historical data exported to " << filename << " successfully." << endl;
        } 
        else 
        {
            cerr << "Could not open the file for writing." << endl;
        }
    }

    void exportHistoricalDataToJSON(const string& filename, const vector<pair<string, map<string, double>>>& historicalData) 
    {
        nlohmann::json jsonData;
        for (const auto& entry : historicalData)
        {
            jsonData[entry.first] = entry.second; 
        }
        ofstream file(filename);
        if (file.is_open()) 
        {
            file << jsonData.dump(4); 
            file.close();
            cout << "Historical data exported to " << filename << " successfully." << endl;
        } 
        else 
        {
            cerr << "Could not open the file for writing." << endl;
        }
    }
};
void DisplayMenu() 
{
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Manage Locations" << endl;
    cout << "2. Manage Weather Variables" << endl;
    cout << "3. Fetch and Export Weather Data" << endl;
    cout << "4. Fetch and Export Historical Weather Data" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void DisplayLocationMenu() 
{
    cout << "\n--- Manage Locations ---" << endl;
    cout << "1. Add a Location" << endl;
    cout << "2. Remove a Location" << endl;
    cout << "3. List all Locations" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void DisplayWeatherMenu() 
{
    cout << "\n--- Manage Weather Variables ---" << endl;
    cout << "1. Define a Weather Variable" << endl;
    cout << "2. Update a Weather Variable" << endl;
    cout << "3. List all Weather Variables" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Location loc1("Islamabad", 33.6844, 73.0479);
    Location loc2("Karachi", 24.8607, 67.0011);
    loc1.AddLocation(loc1);
    loc1.AddLocation(loc2);
     WeatherVariable weatherVar;
    WeatherForecastingSystem weatherSystem;
    HistoricalWeatherSystem historicalSystem("YOUR_API_KEY");

    char mainChoice;
    do {
        DisplayMenu();
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
            case '1': {
                char locChoice;
                do {
                    DisplayLocationMenu();
                    cin >> locChoice;
                    cin.ignore();

                    switch (locChoice) {
                        case '1': {
                            string locName;
                            double latitude, longitude;
                            cout << "Enter the name of the location: ";
                            getline(cin, locName);
                            cout << "Enter the latitude: ";
                            cin >> latitude;
                            cout << "Enter the longitude: ";
                            cin >> longitude;
                            cin.ignore();
                            Location newLoc(locName, latitude, longitude);
                            newLoc.AddLocation(newLoc);
                            cout << "\nLocation added successfully!" << endl;
                            break;
                        }
                        case '2': {
                            string locNameToDelete;
                            cout << "Enter the name of the location you want to delete: ";
                            getline(cin, locNameToDelete);
                            Location::RemoveLocation(locNameToDelete);
                            break;
                        }
                        case '3': {
                            Location::ListLocations();
                            break;
                        }
                    }
                } while (locChoice != '4');
                break;
            }
            case '2': {
                char weatherChoice;
                do {
                    DisplayWeatherMenu();
                    cin >> weatherChoice;
                    cin.ignore();

                    switch (weatherChoice) {
                        case '1': {
                            string key;
                            double value;
                            cout << "Enter the weather variable name: ";
                            getline(cin, key);
                            cout << "Enter the value: ";
                            cin >> value;
                            cin.ignore();

                            weatherVar.DefineVariable(key, value);
                            cout << "Variable defined successfully!" << endl;
                            break;
                        }
                        case '2': {
                            string key;
                            cout << "Enter the weather variable name to update: ";
                            getline(cin, key);

                            weatherVar.UpdateVariable(key);
                            break;
                        }

                        case '3': {

                            weatherVar.DisplayVariables();
                            break;
                        }
                    }
                } while (weatherChoice != '4');
                break;
            }
            case '3': {
                weatherSystem.displayWeatherData(loc1.latitude, loc1.longitude);

                vector<string> weatherData = {
                    "Islamabad,33.6844,73.0479,30.0,10.0",  
                    "Karachi,24.8607,67.0011,32.0,8.0"
                };
                weatherSystem.exportToCSV("weather_forecast.csv", weatherData);
                cout << "CSV export completed.\n";

                vector<pair<string, map<string, double>>> jsonData = {
                    {"Islamabad", {{"Latitude", 33.6844}, {"Longitude", 73.0479}, {"Temperature", 30.0}, {"Humidity", 10.0}}},
                    {"Karachi", {{"Latitude", 24.8607}, {"Longitude", 67.0011}, {"Temperature", 32.0}, {"Humidity", 8.0}}}
                };
                weatherSystem.exportToJSON("weather_forecast.json", jsonData);
                cout << "JSON export completed.\n";

                break;
            }
            case '4': {
                historicalSystem.displayHistoricalData("Islamabad");
                historicalSystem.displayHistoricalData("Karachi");


                vector<string> historicalData = {
                    "Islamabad,33.6844,73.0479,2023-01-01,26.0,60.0",
                    "Karachi,24.8607,67.0011,2023-01-01,28.0,65.0"
                };
                historicalSystem.exportHistoricalDataToCSV("historical_data.csv", historicalData);
                cout << "Historical data export to CSV completed.\n";


                vector<pair<string, map<string, double>>> historicalJsonData = {
                    {"Islamabad", {{"Latitude", 33.6844}, {"Longitude", 73.0479}, {"Date", 20230101}, {"Temperature", 26.0}, {"Humidity", 60.0}}},
                    {"Karachi", {{"Latitude", 24.8607}, {"Longitude", 67.0011}, {"Date", 20230101}, {"Temperature", 28.0}, {"Humidity", 65.0}}}
                };

                historicalSystem.exportHistoricalDataToJSON("historical_data.json", historicalJsonData);
                cout << "Historical data export to JSON completed.\n";
            }
        }
    } while (mainChoice != '5');

    return 0;
}