#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H

#include "Service.h"

class UI {
private:
    Service& srv;
public:
    explicit UI(Service& srv) : srv{srv} {};
    UI(const UI& ot) = delete;
    void run();

    /* Menus */
    static void menu();
    static void manage_menu();
    static void modify_menu();
    static void filter_menu();
    static void sort_menu();
    static void wash_list_menu();

    /* UI Functions */
    void add_ui();
    void remove_ui();
    void modify_ui();

    void find_ui();
    void filter_ui();
    void sort_ui();

    void wash_list_ui();

    void undo_ui();
    /* Print Functions */
    static void print_all(const vector<Car>& list);
    static void print_car(const Car& c);

};

#endif //LAB6_7_UI_H
