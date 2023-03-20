#ifndef LAB6_7_CARREPOSITORY_H
#define LAB6_7_CARREPOSITORY_H

#include <utility>
#include <vector>
#include <algorithm>
#include "Car.h"

using std::vector;

class RepoException {
private:
    string error;
public:
    /* Constructor */
    explicit RepoException(string error) : error{std::move(error)} {};

    /**
     * Returneaza mesajul de eroare
     * @return string - error message
     */
    string get_error() { return this->error; }
};

class CarRepository {
private:
    vector<Car> car_list;

public:
    /* Constructors */
    CarRepository() = default;
    CarRepository(const CarRepository& ot) = delete;


    /**
     * Adauga un nou obiect in lista de masini
     * @param new_car masina de adaugat
     */
    void store(const Car& new_car);

    /**
     * Returneaza lista de masini
     * @return lista de masini
     */
    vector<Car>& get_all();

    /**
     * Cauta o masina in lista dupa numarul de inmatriculare
     * @param licence_plate numarul de inmatriculare
     * @return obiect, referinta - masina
     */
    Car& find(int licence_plate);

    /**
     * Sterge o masina din lista dupa numarul de inmatriculare
     * @param licence_plate numarul de inmatriculare
     */
    void remove(int licence_plate);
};

void test_repo();

#endif //LAB6_7_CARREPOSITORY_H
