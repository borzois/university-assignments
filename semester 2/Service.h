#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H

#include <utility>
#include <memory>
#include <fstream>

#include "CarRepository.h"
#include "WashList.h"
#include "Validators.h"
#include "Undo.h"

class Service {
private:
    CarRepository& repo;
    WashList washlist;

    vector<std::unique_ptr<UndoAction>> undo_states;

    /* Functii de comparare */
    static int compare_types(Car &p, Car &q);
    static int compare_licence_plates(Car &p, Car &q);
    static int compare_make_model(Car &p, Car &q);
public:
    /* Constructors */
    explicit Service(CarRepository& repo, Validator& validator) : repo{repo} {};
    Service(const Service& ot) = delete;

    /**
     * Adauga o noua masina in repo
     * @param licence_plate numarul de inmatriculare
     * @param make producatorul
     * @param model modelul
     * @param type tipul
     */
    void add_car(int licence_plate, const string& make, const string& model, const string& type);

    /**
     * Sterge o masina dupa numarul de inmatriculare
     * @param licence_plate numarul de inmatriculare
     */
    void remove_car(int licence_plate);

    /**
     * Modifica atributul ales al unei masini: 1 - producatorul, 2 - modelul, 3 - tipul
     * @param licence_plate numarul de inmatriculare
     * @param new_value stringul care va inlocui atributul
     * @param type tipul modificarii
     */
    void modify_car(int licence_plate, const string& new_value, int type);

    /**
     * Returneaza lista de masini
     * @return lista de masini
     */
    vector<Car>& get_all() { return repo.get_all(); }

    /**
     * Cauta o masina dupa numarul de inmatriculare
     * @param licence_plate numarul de inmatriculare
     * @return obiect, referinta - masina
     */
    Car &find_car(int licence_plate);

    /**
     * Fitlreaza lista de masini dupa un string
     * @param filter_string stringul cautat
     * @param type tipul filtrarii
     * @return lista de masini filtrata
     */
    vector<Car> get_filtered(const string& filter_string, int type);

    /**
     * Sorteaza dupa tipul ales
     * @param sort_type tipul sortarii
     * @return true daca sortarea a fost efectuata, false altfel
     */
    bool sort(int sort_type);

    /**
     * Bubble sort
     * @param compare functia de comparare
     */
    void sort_list(int (*compare)(Car &, Car &));

    /**
     * Initializeaza wash list
     * @param n numarul de masini introduse random
     */
    void new_wash_list(int n) { washlist.new_wl(repo.get_all(), n); }

    /**
     * Returneaza lista masinilor din wash list
     * @return car list
     */
    vector<Car> get_all_wash_list() { return washlist.get_all(); }

    /**
     * Adauga masina in wash list dupa numarul de inmatriculare
     * @param licence_plate
     */
    void add_to_wash_list(int licence_plate);

    /**
     * Sterge toate masinile din wash list
     */
    void clear_wash_list() { washlist.clear_list(); }

    /**
     * Determina daca exista masini cu prioritate in lista
     * @return
     */
    bool wash_list_priority();

    /**
     * Exporteaza masinile din wash list in format csv
     * @param filename numele fisierului
     */
    void export_csv(string filename) { washlist.export_csv(std::move(filename)); }

    /**
     * Aduce repo la starea precedenta
     * Arunca exceptie daca nu mai sunt operatiuni in lista de undo
     */
    void undo();

    WashList& get_wash_list() { return this->washlist; };
};

void test_service();

#endif //LAB6_7_SERVICE_H
