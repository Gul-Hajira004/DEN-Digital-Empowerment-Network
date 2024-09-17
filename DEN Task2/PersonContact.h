#include <vector>
#include <string>
using namespace std;

class PersonContact
{
    private:
        string contactName;
        long phoneNo;

    public:
        PersonContact();
        PersonContact(string n, long p);
        static void AddPerson(vector<PersonContact>& contactList);
        static void ShowAll(const vector<PersonContact>& contactList);
        void printDetails() const;
        static void RemovePerson(vector<PersonContact>& contactList);
};
