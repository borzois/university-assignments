#include "Car.h"

#include <cassert>
#include <utility>

int Car::get_licence_plate() const {
    return this->licence_plate;
}

string Car::get_make() const {
    return this->make;
}

string Car::get_model() const {
    return this->model;
}

string Car::get_type() const {
    return this->type;
}


void Car::set_licence_plate(int value) {
    this->licence_plate = value;
}

void Car::set_make(string value) {
    this->make = std::move(value);
}

void Car::set_model(string value) {
    this->model = std::move(value);
}

void Car::set_type(string value) {
    this->type = std::move(value);
}


/***************************************TESTS***************************************/


void test_getters_setters() {
    Car car1 {16, "abc", "def", "ghi"};
    car1.set_licence_plate(32);
    car1.set_make("xyz");
    car1.set_model("uvw");
    car1.set_type("rst");
    assert(car1.get_licence_plate() == 32);
    assert(car1.get_make() == "xyz");
    assert(car1.get_model() == "uvw");
    assert(car1.get_type() == "rst");
}

void test_domain() { test_getters_setters(); }