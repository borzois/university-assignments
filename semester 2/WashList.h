#ifndef LAB6_7_WASHLIST_H
#define LAB6_7_WASHLIST_H

#include <utility>
#include <vector>
#include <random>
#include <chrono>
#include "Car.h"
#include "CarRepository.h"
#include "Observer.h"

using std::vector;

class ListException {
private:
    string error;
public:
    /* Constructor */
    explicit ListException(string error) : error{std::move(error)} {};

    /**
     * Returneaza mesajul de eroare
     * @return string - error message
     */
    string get_error() { return this->error; }
};

class WashList : public Observable {
private:
    vector<Car> car_list;

    bool exists(const Car& car);
public:
    /* Constructors */
    WashList() = default;
    WashList(const WashList& ot) = delete;

    /**
     * Sterege toate masinile din lista
     */
    void clear_list();

    /**
     * Adauga o masina noua in lista
     * @param new_car masina de adaugat
     */
    void add_to_list(const Car& new_car);

    /**
     * Returneaza lista
     * @return car list
     */
    vector<Car>& get_all();

    /**
     * Exporteaza lista ca csv
     * @param filename fisierul (fara extensie)
     */
    void export_csv(string filename);

    /**
     * Returneaza daca exista masini cu numere de inmatriculare care se termina in 0
     * @return true daca exista, false altfel
     */
    bool has_priority_cars();
    void new_wl(vector<Car>& repo_list, int n); /* n - number of cars to randomly populate with */

};

void test_wash_list();

#endif //LAB6_7_WASHLIST_H
