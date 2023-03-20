#ifndef LAB6_7_CAR_H
#define LAB6_7_CAR_H

#include <string>
#include <iostream>
#include <utility>
using std::string;

class Car {
private:
    int licence_plate{}; /* numarul de inmatriculare */
    string make;       /* producatorul */
    string model;      /* modelul */
    string type;       /* tipul */
public:
    /* Getters */
    int get_licence_plate() const;
    string get_make() const;
    string get_model() const;
    string get_type() const;

    /* Setters */
    void set_licence_plate(int value);
    void set_make(string value);
    void set_model(string value);
    void set_type(string value);

    /* Constructors */
    Car() = default;
    Car(int licence_plate, string make, string model, string type) : licence_plate{licence_plate}, make{std::move(make)}, model{std::move(model)}, type{std::move(type)}{};
    Car(const Car & ot) = default;
};

void test_domain();

#endif //LAB6_7_CAR_H
