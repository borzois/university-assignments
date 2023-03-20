#include "ui.h"
#include "iostream"

using std::cin;
using std::cout;

void UI::menu() {
    cout << "x----------------------------x\n";
    cout << "|=======| Car rental |=======|\n";
    cout << "|----------------------------|\n";
    cout << "| [1] Manage cars            |\n";
    cout << "| [2] Search for car         |\n";
    cout << "| [3] Filter cars            |\n";
    cout << "| [4] Sort cars              |\n";
    cout << "| [5] Manage wash list       |\n";
    cout << "| [6] Undo                   |\n";
    cout << "| [0] Exit                   |\n";
    cout << "x----------------------------x\n";
}

void UI::manage_menu() {
    cout << "x----------------------------x\n";
    cout << "| [1] Add a new car          |\n";
    cout << "| [2] Remove a car           |\n";
    cout << "| [3] Modifiy a car          |\n";
    cout << "| [4] Show all cars          |\n";
    cout << "x----------------------------x\n";
}

void UI::modify_menu() {
    cout << "x----------------------------x\n";
    cout << "| [1] Modify make            |\n";
    cout << "| [2] Modify model           |\n";
    cout << "| [3] Modify type            |\n";
    cout << "| [0] Go back                |\n";
    cout << "x----------------------------x\n";
}

void UI::filter_menu() {
    cout << "x----------------------------x\n";
    cout << "| [1] Filter by make         |\n";
    cout << "| [2] Filter by type         |\n";
    cout << "x----------------------------x\n";
}

void UI::sort_menu() {
    cout << "x----------------------------x\n";
    cout << "| [1] Sort by licence plate  |\n";
    cout << "| [2] Sort by type           |\n";
    cout << "| [3] Sort by make and model |\n";
    cout << "x----------------------------x\n";
}

void UI::wash_list_menu() {
    cout << "x----------------------------x\n";
    cout << "| [1] New list               |\n";
    cout << "| [2] Add car                |\n";
    cout << "| [3] Clear list             |\n";
    cout << "| [4] Check for priority     |\n";
    cout << "| [5] Export as CSV          |\n";
    cout << "| [0] Go back                |\n";
    cout << "x----------------------------x\n";
}

void UI::print_car(const Car &c) {
    cout << "  " << c.get_licence_plate() << " : " << c.get_make() << " " << c.get_model() << " - "
         << c.get_type() << "\n";
}

void UI::run() {
    int option1 {0}, option2 {0};
    bool running {true};
    while (running) {
        vector<Car> list = srv.get_all();
        menu();
        cin >> option1;
        switch (option1) {
            case 1:
                manage_menu();
                cin >> option2;
                switch (option2) {
                    case 1:
                        add_ui();
                        break;
                    case 2:
                        remove_ui();
                        break;
                    case 3:
                        modify_ui();
                        break;
                    case 4:
                        print_all(list);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                find_ui();
                break;
            case 3:
                filter_ui();
                break;
            case 4:
                sort_ui();
                break;
            case 5:
                wash_list_ui();
                break;
            case 6:
                undo_ui();
                break;
            case 0:
                running = false;
                break;
            default:
                break;
        }
    }
}

void UI::add_ui() {
    int licence;
    string make, model, type;

    cout << "Licence plate: ";
    cin >> licence;
    cout << "Make: ";
    getline(cin >> std::ws, make);
    cout << "Model: ";
    getline(cin >> std::ws, model);
    cout << "Type: ";
    getline(cin >> std::ws, type);

    try {
        srv.add_car(licence, make, model, type);
        cout << "Car added successfully\n";
    }
    catch (ValidationException &e) {
        std::cout << e.get_errors();
    }
    catch (RepoException &e) {
        std::cout << e.get_error();
    }
}

void UI::remove_ui() {
    int licence;

    cout << "Licence plate to delete: ";
    cin >> licence;
    try {
        srv.remove_car(licence);
    }
    catch (RepoException &e) {
        std::cout << e.get_error();
    }
}

void UI::modify_ui() {
    int licence;

    cout << "Licence plate to modify: ";
    cin >> licence;
    try {
        Car &found_car = srv.find_car(licence);

        bool modifying = true;
        int option3 {0};
        while (modifying) {
            modify_menu();
            print_car(found_car);
            cin >> option3;
            if (option3 == 1 || option3 == 2 || option3 == 3) {
                string new_value;

                cout << "New value: ";
                getline(cin >> std::ws, new_value);
                srv.modify_car(licence, new_value, option3);
            }
            else if (option3 == 0)
                modifying = false;
            else
                cout << "Not a valid command\n";
        }
    }
    catch (RepoException &e) {
        std::cout << e.get_error();
    }
}

void UI::find_ui() {
    int licence;

    cout << "Licence plate to find: ";
    cin >> licence;
    try {
        Car& found_car = srv.find_car(licence);
        print_car(found_car);
    }
    catch (RepoException &e) {
        std::cout << e.get_error();
    }
}

void UI::filter_ui() {
    int filter_type;
    string filter_string;
    filter_menu();

    cout << "Filter by: ";
    cin >> filter_type;
    while (!(filter_type == 1 || filter_type == 2)) {
        cout << "Not a valid command\n";
        cout << "Filter by: ";
        cin >> filter_type;
    }

    cout << "Filter: ";
    getline(cin >> std::ws, filter_string);

    print_all(srv.get_filtered(filter_string, filter_type));
}

void UI::sort_ui() {
    int sort_type;
    sort_menu();

    cout << "Sort by: ";
    cin >> sort_type;

    if (srv.sort(sort_type))
        cout << "Car list sorted\n";
    else
        cout << "Could not sort list\n";
}

void UI::wash_list_ui() {
    bool managing_list = true;
    int option3 {0};
    int licence_plate;
    int random_cars;
    string filename;

    while (managing_list) {
        print_all(srv.get_all_wash_list());
        wash_list_menu();
        cin >> option3;
        switch (option3) {
            case 1:
                cout << "Number of cars to add randomly: ";
                cin >> random_cars;
                try {
                    srv.new_wash_list(random_cars);
                }
                catch (ListException &e) {
                    cout << e.get_error();
                }
                break;
            case 2:
                cout << "Licence plate to add: ";
                cin >> licence_plate;
                try {
                    srv.add_to_wash_list(licence_plate);
                }
                catch (ListException &e) {
                    cout << e.get_error();
                }
                break;
            case 3:
                srv.clear_wash_list();
                break;
            case 4:
                if(srv.wash_list_priority())
                    cout << "There are priority cars in the list";
                else
                    cout << "There are no priority cars in the list";
                break;
            case 5:
                cout << "Filename: ";
                getline(cin >> std::ws, filename);
                srv.export_csv(filename);
                break;
            case 0:
                managing_list = false;
                break;
            default:
                cout << "Not a valid command\n";
                break;
        }
    }
}

void UI::undo_ui() {
    try {
        srv.undo();
        cout << "Undo succesful\n";
    }
    catch (UndoException &e) {
        cout << e.get_error();
    }
}

void UI::print_all(const vector<Car>& list) {
    if (!list.empty()) {
        cout << "\n";
        cout << "x---------------------------------x\n";
        cout << "|=======|      Cars:      |=======|\n";
        cout << "x---------------------------------x\n";
        for (const auto &car: list) {
            print_car(car);
        }
        cout << "x---------------------------------x\n\n";
    }
    else
        cout << "There are currently no cars available\n";
}


