#include "PersonContact.h"
#include <iostream>
using namespace std;

PersonContact::PersonContact()
{
    contactName = " ";
    phoneNo = 0;
}

PersonContact::PersonContact(string n, long p)
{
    contactName = n;
    phoneNo = p;
}

void PersonContact::AddPerson(vector<PersonContact>& contactList)
{
    string nameInput;
    long phoneInput;
    cout << endl << "=> Enter Contact Name: ";
    getline(cin, nameInput);
    cout << "=> Enter Phone Number: ";
    cin >> phoneInput;
    contactList.emplace_back(nameInput, phoneInput);
    cout << endl << "=> CONTACT ADDED!" << endl;
}

void PersonContact::ShowAll(const vector<PersonContact>& contactList)
{
    if (contactList.empty())
    {
        cout << endl << "=> NO CONTACTS TO SHOW." << endl;
        return;
    }
    cout << endl << "=> CONTACTS:" << endl;
    for (const auto& contact : contactList)
    {
        contact.printDetails();
    }
}

void PersonContact::printDetails() const
{
    cout << endl << "Contact Name: " << contactName << endl;
    cout << "Phone Number: " << phoneNo << endl;
}

void PersonContact::RemovePerson(vector<PersonContact>& contactList)
{
    if (contactList.empty())
    {
        cout << endl << "=> NO CONTACTS TO REMOVE." << endl;
        return;
    }
    string nameToRemove;
    cout << endl << "=> Enter Contact Name to Remove: ";
    getline(cin, nameToRemove);
    bool isDeleted = false;
    for (size_t i = 0; i < contactList.size(); i++)
    {
        if (contactList[i].contactName == nameToRemove)
        {
            contactList.erase(contactList.begin() + i);
            isDeleted = true;
            cout << endl << "=> CONTACT REMOVED!" << endl;
            break;
        }
    }
    if (!isDeleted)
    {
        cout << endl << "=> CONTACT NOT FOUND!" << endl;
    }
}
