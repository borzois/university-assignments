#ifndef LAB6_7_VALIDATORS_H
#define LAB6_7_VALIDATORS_H

#include "Car.h"

#include <string>
#include <utility>
#include <vector>

class ValidationException {
private:
    std::vector<std::string> errors;
public:
    explicit ValidationException(std::vector<std::string>  e) : errors{std::move( e )} { };

    /**
     * Returneza cocnatenarea erorilor
     * @return string erorare
     */
    string get_errors() {
        std::string message;
        for (const auto& error : errors) {
            message += error + "\n";
        }
        return message;
    }
};

class Validator {
public:
    /**
     * Valideaza obiectul Car
     * @param car obiectul validat
     */
    static void validate(const Car& car) {
        std::vector<std::string> errors;
        if (car.get_licence_plate() < 0)
            errors.emplace_back("Licence plate number must be a positive number");
        if (car.get_make().length() < 1)
            errors.emplace_back("Make must be at least 1 character long");
        if (car.get_model().length() < 1)
            errors.emplace_back("Model must be at least 1 character long");
        if (car.get_type().length() < 1)
            errors.emplace_back("Type must be at least 1 character long");

        if (!errors.empty())
            throw ValidationException(errors);
    }
};

#endif //LAB6_7_VALIDATORS_H
