#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;
enum class DomeniuStudiu {
    INGINERIE_MECANICA = 1,
    INGINERIE_SOFTWARE = 2,
    TEHNOLOGIE_ALIMENTARA = 3,
    URBANISM_ARHITECTURA = 4,
    MEDICINA_VETERINARA = 5
};

class Student {
private:
    string prenume;
    string nume;
    string email;
    string dataInscriere;
    string dataNasterii;

public:
    Student(string prenume, string nume,string email, string dataInscriere, string dataNasterii)
        : prenume(prenume), nume(nume), email(email), dataInscriere(dataInscriere), dataNasterii(dataNasterii) {}

   string getEmail() const {
        return email;
    }
};

class Facultate {
private:
   string nume;
    string abreviere;
    vector<Student> studenti;
    DomeniuStudiu domeniuStudiu;

public:
    Facultate(string nume, string abreviere, DomeniuStudiu domeniuStudiu)
        : nume(nume), abreviere(abreviere), domeniuStudiu(domeniuStudiu) {}

    void adaugaStudent(const Student& student) {
        studenti.push_back(student);
    }

   string getNume() const {
        return nume;
    }

    vector<Student> getStudenti() const {
        return studenti;
    }

    DomeniuStudiu getDomeniuStudiu() const {
        return domeniuStudiu;
    }
};

class Universitate {
private:
    vector<Facultate> facultati;

public:
    void creeazaFacultate(string nume, string abreviere, DomeniuStudiu domeniuStudiu) {
        Facultate facultate(nume, abreviere, domeniuStudiu);
        facultati.push_back(facultate);
    }

    bool asignareStudentLaFacultate(const string& emailStudent, const string& numeFacultate) {
        for (auto& facultate : facultati) {
            if (facultate.getNume() == numeFacultate) {
                Student student(emailStudent, "", "", "", "");
                facultate.adaugaStudent(student);
                return true;
            }
        }
        return false;
    }

    string cautareFacultateDupaEmailStudent(const string& emailStudent) {
        for (const auto& facultate : facultati) {
            for (const auto& student : facultate.getStudenti()) {
                if (student.getEmail() == emailStudent) {
                    return facultate.getNume();
                }
            }
        }
        return "Studentul nu a fost gasit";
    }

    void afisareFacultatiUniversitate() {
        for (const auto& facultate : facultati) {
            cout << facultate.getNume() << endl;
        }
    }

    void afisareToateFacultatileDinDomeniu(DomeniuStudiu domeniuStudiu) {
        for (const auto& facultate : facultati) {
            if (facultate.getDomeniuStudiu() == domeniuStudiu) {
                cout << facultate.getNume() << endl;
            }
        }
    }

    void salvareStare(const string& numeFisier) {
        ofstream fisier(numeFisier);
        if (fisier.is_open()) {
            for (const auto& facultate : facultati) {
                fisier << facultate.getNume() << "," << static_cast<int>(facultate.getDomeniuStudiu()) << ",";
                for (const auto& student : facultate.getStudenti()) {
                    fisier << student.getEmail() << ",";
                }
                fisier << endl;
            }
            fisier.close();
            cout << "Starea a fost salvata cu succes." << endl;
        }
        else {
            cerr << "Nu se poate deschide fisierul." << endl;
        } // Aici a fost adăugat semnul de închidere al acoladelor
    }
    void incarcareStare(const string& numeFisier) {
        facultati.clear();
        ifstream fisier(numeFisier);
        if (fisier.is_open()) {
            string linie;
            while (getline(fisier, linie)) {
                istringstream iss(linie);
                string numeFacultate, emailStudent;
                int domeniuStudiuInt;
                iss >> numeFacultate >> domeniuStudiuInt;
                DomeniuStudiu domeniuStudiu = static_cast<DomeniuStudiu>(domeniuStudiuInt);
                creeazaFacultate(numeFacultate, "", domeniuStudiu);
                while (getline(iss, emailStudent, ',')) {
                    if (!emailStudent.empty())
                        asignareStudentLaFacultate(emailStudent, numeFacultate);
                }
            }
            fisier.close();
            cout<< "Starea a fost incarcata cu succes." << endl;
        }
        else {
            cerr << "Nu se poate deschide fisierul." << endl;
        }
    }
};

int main() {
    Universitate universitateTUM;
    while (true) {
        cout << "\n1.--Creeaza o noua facultate--" << endl;
        cout << "2.--Creeaza si asigna un student la o facultate--" << endl;
        cout << "3.--Cauta la ce facultate apartine un student dupa email--" << endl;
        cout << "4.--Afiseaza facultatile universitatii--" << endl;
        cout << "5.--Afiseaza toate facultatile dintr-un domeniu--" << endl;
       cout << "6.--Salveaza starea--" << endl;
       cout << "7.--Incarca starea--" << endl;
       cout << "8.--Iesire--" << endl;

        int optiune;
        cout << "Introduceti optiunea: ";
       cin >> optiune;

        switch (optiune) {
        case 1: {
           string nume, abreviere;
            int domeniuStudiuInt;
           cout << "Introduceti numele facultatii: ";
            cin >> nume;
            cout << "Introduceti abrevierea facultatii: ";
            cin >> abreviere;
            cout << "Introduceti domeniul de studiu (1 - INGINERIE_MECANICA, 2 - INGINERIE_SOFTWARE, 3 - TEHNOLOGIE_ALIMENTARA, 4 - URBANISM_ARHITECTURA, 5 - MEDICINA_VETERINARA): ";
           cin >> domeniuStudiuInt;
            DomeniuStudiu domeniuStudiu = static_cast<DomeniuStudiu>(domeniuStudiuInt);
            universitateTUM.creeazaFacultate(nume, abreviere, domeniuStudiu);
            break;
        }
        case 2: {
            string emailStudent, numeFacultate;
            cout << "Introduceti emailul studentului: ";
            cin >> emailStudent;
            cout << "Introduceti numele facultatii pentru asignarea studentului: ";
           cin >> numeFacultate;
            bool succes = universitateTUM.asignareStudentLaFacultate(emailStudent, numeFacultate);
            if (succes) {
                cout << "Studentul a fost asignat cu succes la facultate." << endl;
            }
            else {
                cout << "Facultatea nu a fost gasita." <<endl;
            }
            break;
        }
        case 3: {
            string emailStudent;
            cout << "Introduceti emailul studentului: ";
            cin >> emailStudent;
            string facultate = universitateTUM.cautareFacultateDupaEmailStudent(emailStudent);
            cout << "Studentul apartine facultatii " << facultate << "." << endl;
            break;
        }
        case 4:
            cout << "Facultatile universitatii:" << endl;
            universitateTUM.afisareFacultatiUniversitate();
            break;
        case 5: {
            int domeniuStudiuInt;
           cout << "Introduceti domeniul de studiu (1 - INGINERIE_MECANICA, 2 - INGINERIE_SOFTWARE, 3 - TEHNOLOGIE_ALIMENTARA, 4 - URBANISM_ARHITECTURA, 5 - MEDICINA_VETERINARA): ";
            cin >> domeniuStudiuInt;
            DomeniuStudiu domeniuStudiu = static_cast<DomeniuStudiu>(domeniuStudiuInt);
            cout << "Facultati din domeniul " << domeniuStudiuInt << ":" <<endl;
            universitateTUM.afisareToateFacultatileDinDomeniu(domeniuStudiu);
            break;
        }
        case 6: {
           string numeFisier;
            cout << "Introduceti numele fisierului pentru salvarea starii: ";
            cin >> numeFisier;
            universitateTUM.salvareStare(numeFisier);
            break;
        }
        case 7: {
            string numeFisier;
           cout << "Introduceti numele fisierului pentru incarcarea starii: ";
            cin >> numeFisier;
            universitateTUM.incarcareStare(numeFisier);
            break;
        }
        case 8:
            cout << "EXIT" << endl;
            return 0;
        }
    }

    return 0;
}
