#include "PersonContact.h"
#include <iostream>
using namespace std;

int main()
{
    vector<PersonContact> contactList = {
        PersonContact("John", 30218574567),
        PersonContact("Alas", 3984758066543),
        PersonContact("Tom", 3024349058957),
        PersonContact("Jemmy",9834763894653489)
    };

    int option;
    do
    {
        PersonContact p;
        cout << endl << "\t\t==== CONTACT MANAGEMENT SYSTEM ====" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. View All Contacts" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore();

        if (option == 1)
        {
            p.AddPerson(contactList);
        }
        else if (option == 2)
        {
            p.ShowAll(contactList);
        }
        else if (option == 3)
        {
            p.RemovePerson(contactList);
        }
        else if (option == 4)
        {
            cout << "Exiting... Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid option. Try again!" << endl;
        }

    } while (option != 4);

    return 0;
}
