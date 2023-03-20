#include <QtWidgets>
#include <QApplication>
#include <iostream>

#include "ui.h"
#include "qtui.h"
#include "gui.h"

// Creați o aplicație care permite:
//   gestiunea unei liste de mașini.
//     Mașina: nrInmatriculare, producător, model, tip
//     adăugare, ștergere, modificare și afișare mașini
//   căutare mașina
//   filtrare mașini după: producător, tip
//   sortare mașini după: nrInmatriculare, tip, producator + model

void tests() {
    test_domain();
    test_repo();
    test_service();
    test_wash_list();
    std::cout << "All tests passed\n";
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CarRepository repo;
    Validator v;
    Service srv{repo, v};
    GUI gui{srv};

    tests();
    gui.show();

    return a.exec();
}
