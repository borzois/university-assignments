#ifndef LAB6_7_UNDO_H
#define LAB6_7_UNDO_H

#include <utility>

#include "CarRepository.h"

class UndoException {
private:
    string error;
public:
    /* Constructor */
    explicit UndoException(string error) : error{std::move(error)} {};

    /**
     * Returneaza mesajul de eroare
     * @return string - error message
     */
    string get_error() { return this->error; }
};

class UndoAction {
public:
    virtual void do_undo() = 0;

    virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
private:
    CarRepository& repo;
    int added_car_plate;

public:
    /* Constructor */
    UndoAdd(CarRepository& repo, int& car) : repo { repo }, added_car_plate { car } {};

    /**
     * Sterge din lista
     */
    void do_undo() override;
};

class UndoRemove : public UndoAction {
private:
    CarRepository& repo;
    Car removed_car;

public:
    /* Constructor */
    UndoRemove(CarRepository& repo, const Car& car) : repo { repo }, removed_car { car } {};

    /*
     * Adauga inapoi in lista masina stearsa
     */
    void do_undo() override;
};

class UndoModify : public UndoAction {
private:
    Car& modified_car;
    string old_value;
    int type;

public:
    /* Constructor */
    UndoModify(Car& car, string old_value, int type) : modified_car { car }, old_value { std::move(old_value) }, type { type } {};

    /**
     * Modifica valoarea inapoi la cea initiala
     */
    void do_undo() override;
};

#endif //LAB6_7_UNDO_H
