#include <iostream>
#include <thread>
#include <chrono>
#include "kinosaal.hpp"

std::vector<Kinosaal> kinoSaele;
std::vector<std::string> kinoNames;

void addKinosaal()
{
    system("cls");
    std::string kinoName;
    int rows;
    int cols;

    std::cout << "Namen des Saals eingeben: ";
    std::cin.clear();
    std::cin.sync();
    std::getline(std::cin, kinoName);

    std::cin.clear();
    std::cin.sync();
    fflush(stdout);
    fflush(stdin);
    std::cout << "Reihen: ";
    std::cin >> rows;


    fflush(stdout);
    fflush(stdin);
    std::cout << "Sitze in einer Reihe: ";
    std::cin >> cols;

    Kinosaal newSaal(rows, cols);
    kinoSaele.push_back(newSaal);
    kinoNames.push_back(kinoName);
}

void removeSaal()
{
    int choice;
    char secQuestion;

    std::cout << "ID des Saals: ";
    std::cin >> choice;

    std::cout << "Wollen sie diesen Saal löschen? (Y/N)\n";
    std::cout << "> ";
    std::cin >> secQuestion;

    if(!(secQuestion == 'Y' || secQuestion == 'y'))
    {
        return;
    }

    kinoSaele.erase(kinoSaele.begin()+(choice-1));
    kinoNames.erase(kinoNames.begin()+(choice-1));
}

bool showSaele(bool reservMode)
{
    system("cls");
    if(kinoNames.size() != kinoSaele.size())
    {
        std::cout << "[ERROR] The size of two vectors dont match, deleting all Data" << std::endl;
        kinoSaele.clear();
        kinoNames.clear();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return false;
    }

    if(kinoNames.empty())
    {
        std::cout << "[ERROR] Es gibt keine Eingetragenen Kinosaele, bitte fügen sie welche hinzu" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return false;
    }

    std::cout << "{ID    Name   INFO}" << std::endl;
    for(int i = 0; i < kinoNames.size(); i++)
    {
        std::cout << i + 1 << "      " << kinoNames[i] << "   [Reihen: " << kinoSaele[i].getRows() << " | Sitze in R.: " << kinoSaele[i].getCols() << "] " << std::endl;
    }
    if(!reservMode) {
        std::cout << "\nThis will be closed in 7 seconds!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(7));
    }
    return true;
}

void kinosaeleMenu()
{
    int running = true;
    int choice;

    while(running)
    {
        choice = 0;
        system("cls");
        std::cout << "Funktion auswählen:\n" << std::endl;
        std::cout << "  1. Kinosaal hinzufügen" << std::endl;
        std::cout << "  2. Kinosaal entfernen" << std::endl;
        std::cout << "  3. Kinosäle anzeigen" << std::endl;
        std::cout << "  4. Zurück\n" << std::endl;
        std::cout << "Auswahl: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addKinosaal();
                break;
            case 2:
                removeSaal();
                break;
            case 3:
                showSaele(false);
                break;
            case 4:
                running = false;
                return;
                break;
            default:
//                std::cout << "Funktion nicht verfügbar!" << std::endl;
                break;
        }
    }
}

void tryReservSeat()
{
    system("cls");
    bool success = showSaele(true);
    int saal;
    int XX, YY;

    if(!success)
    {
        std::cout << "[ERROR] Reservieren fehlgeschlagen!" << std::endl;
        return;
    }
    std::cout << "Waehlen sie einen Saal zum Reservieren: ";
    std::cin >> saal;

    system("cls");
    if(saal > kinoSaele.size()) return;

    kinoSaele[saal-1].printGrid();
    fflush(stdout);

    std::cout << "Waehlen sie einen Platz aus in diesem Format \"XX YY\"" << std::endl;
    std::cout << "> ";
    std::cin >> XX >> YY;

    if(XX > kinoSaele[saal-1].getRows() - 1 || YY > kinoSaele[saal-1].getCols() - 1 || XX < 0 || YY < 0)
    {
        std::cout << "[ERROR]" << " Out of bounds" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    } else {
        success = kinoSaele[saal-1].reservSeat(XX, YY);

        if(!success)
        {
            std::cout << "[ERROR] Saal ist schon reserviert!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

    //std::cout << "XX: " << XX << std::endl;
    //std::cout << "YY: " << YY << std::endl;




}

int main() {
    bool running = true;
    int choice = 0;

    while(running) {
        system("cls");
        std::cout << "Funktion auswählen:\n" << std::endl;
        std::cout << "  1.Kinosäle" << std::endl;
        std::cout << "  2.Reservieren" << std::endl;
        std::cout << "  3.Exit\n" << std::endl;

        std::cout << "Auswahl: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                kinosaeleMenu();
                break;
            case 2:
                tryReservSeat();
                break;
            case 3:
                running = false;
                break;
            default:
//                std::cout << "Funktion nicht verfügbar!";
                break;
        }
    }
    return 0;
}

