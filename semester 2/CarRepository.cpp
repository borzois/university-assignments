#include "CarRepository.h"

#include <cassert>

void CarRepository::store(const Car &new_car) {
    for (auto &car : car_list) {
        if (car.get_licence_plate() == new_car.get_licence_plate())
            throw RepoException("Car already exists\n");
    }
    this->car_list.push_back(new_car);
}

vector<Car> &CarRepository::get_all() {
    return this->car_list;
}

Car &CarRepository::find(int licence_plate) {
    auto found_car = std::find_if(this->car_list.begin(), this->car_list.end(),
                                  [&](const Car& c){ return c.get_licence_plate() == licence_plate; });
    if (found_car != this->car_list.end())
        return *found_car;

    throw RepoException("Could not find car\n");
}

void CarRepository::remove(const int licence_plate) {
    auto iterator = std::find_if(this->car_list.begin(), this->car_list.end(),
                                 [&](const Car& c){ return c.get_licence_plate() == licence_plate; });

    if (iterator != this->car_list.end())
        this->car_list.erase(iterator);

    else
        throw RepoException("Could not find car\n");
}

/***************************************TESTS***************************************/


void test_add_repo() {
    CarRepository test_repo;
    Car test_car1(64, "h", "i", "j");
    Car test_car2(128, "k", "l", "m");
    Car test_car3(256, "n", "o", "p");
    test_repo.store(test_car1);
    test_repo.store(test_car2);
    test_repo.store(test_car3);
    assert(test_repo.get_all().size() == 3);
    try {
        test_repo.store(test_car1);
        assert(false);
    }
    catch(RepoException &e) {
        assert(true);
    }
}

void test_remove_repo() {
    CarRepository test_repo;
    Car test_car1(64, "h", "i", "j");
    Car test_car2(128, "k", "l", "m");
    Car test_car3(256, "n", "o", "p");
    test_repo.store(test_car1);
    test_repo.store(test_car2);
    test_repo.store(test_car3);
    assert(test_repo.get_all().size() == 3);
    test_repo.remove(64);
    assert(test_repo.get_all().size() == 2);
    try {
        test_repo.remove(8);
        assert(false);
    }
    catch(RepoException &e) {
        assert(true);
    }
}

void test_find_repo() {
    CarRepository test_repo;
    Car test_car1(64, "h", "i", "j");
    Car test_car2(128, "k", "l", "m");
    Car test_car3(256, "n", "o", "p");
    test_repo.store(test_car1);
    test_repo.store(test_car2);
    test_repo.store(test_car3);

    Car found = test_repo.find(64);
    assert(found.get_make() == "h");
    try {
        test_repo.find(8);
        assert(false);
    }
    catch(RepoException &e) {
        assert(true);
        assert(e.get_error() == "Could not find car\n");
    }
}

void test_repo() {
    test_add_repo();
    test_remove_repo();
    test_find_repo();
}