#include "Service.h"
#include "Validators.h"

#include <cassert>

Car& Service::find_car(int licence_plate) {
    return repo.find(licence_plate);
}

void Service::undo() {
    if (undo_states.empty()) {
        throw UndoException("Nothing to undo!\n");
    }
    auto& state = undo_states.back();
    state->do_undo();
    undo_states.pop_back();
}

void Service::add_car(int licence_plate, const string& make, const string& model, const string& type) {
    Car new_car(licence_plate, make, model, type);
    Validator::validate(new_car);
    repo.store(new_car);
    undo_states.push_back(std::make_unique<UndoAdd>(repo, licence_plate));
}

void Service::remove_car(int licence_plate) {
    Car removed_car = repo.find(licence_plate);
    repo.remove(licence_plate);
    undo_states.push_back(std::make_unique<UndoRemove>(repo, removed_car));
}

void Service::modify_car(int licence_plate, const string& new_value, int type) {
    Car& car = repo.find(licence_plate);
    switch (type) {
        case 1:
            undo_states.push_back(std::make_unique<UndoModify>(car, car.get_make(), type));
            car.set_make(new_value);
            break;
        case 2:
            undo_states.push_back(std::make_unique<UndoModify>(car, car.get_model(), type));
            car.set_model(new_value);
            break;
        case 3:
            undo_states.push_back(std::make_unique<UndoModify>(car, car.get_type(), type));
            car.set_type(new_value);
            break;
        default:
            break;
    }
}

vector<Car> Service::get_filtered(const string &filter_string, int type) {
    vector<Car> filtered_list;
    vector<Car> &car_list = repo.get_all();
    if (type == 1) {
        std::copy_if(car_list.begin(), car_list.end(), std::inserter(filtered_list, filtered_list.end()),
                     [&](const Car& c){ return c.get_make() == filter_string; });
    }
    else if (type == 2) {
        std::copy_if(car_list.begin(), car_list.end(), std::inserter(filtered_list, filtered_list.end()),
                     [&](const Car& c){ return c.get_type() == filter_string; });
    }
    return filtered_list;
}

bool Service::sort(int sort_type) {
    if (sort_type == 1)
        sort_list(compare_licence_plates);
    else if (sort_type == 2)
        sort_list(compare_types);
    else if (sort_type == 3)
        sort_list(compare_make_model);
    else
        return false;
    return true;
}

int Service::compare_licence_plates(Car& p, Car& q) {
    return p.get_licence_plate() - q.get_licence_plate();
}

int Service::compare_types(Car& p, Car& q) {
    return p.get_type() > q.get_type();
}

int Service::compare_make_model(Car& p, Car& q) {
    string p_full_product_name = p.get_make() + p.get_model();
    string q_full_product_name = q.get_make() + q.get_model();
    return p_full_product_name > q_full_product_name;
}

void Service::sort_list(int(*compare)(Car& p, Car& q)) {
    bool sorted = false;
    vector<Car> &car_list = repo.get_all();
    int len = static_cast<int>(car_list.size());
    while (!sorted) {
        sorted = true;
        for (int j = 0; j < len-1; j++) {
            if (compare(car_list[j], car_list[j+1]) > 0) {
//                std::cout << "sorting " << car_list[j].get_licence_plate() << " " << car_list[j+1].get_licence_plate();
                Car swap = car_list[j];
                car_list[j] = car_list[j+1];
                car_list[j+1] = swap;
                sorted = false;
            }
        }
    }
}

void Service::add_to_wash_list(int licence_plate) {
    Car& car = find_car(licence_plate);
    washlist.add_to_list(car);
}

bool Service::wash_list_priority() {
    return washlist.has_priority_cars();
}

/***************************************TESTS***************************************/

void test_add_car() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "d", "e", "f");
    test_service.add_car(8, "a", "b", "c");

    assert(test_service.get_all().size() == 2);

    try {
        test_service.add_car(-11, "", "", "");
        assert(false);
    }
    catch(ValidationException &e) {
        assert(true);
        assert(!e.get_errors().empty());
    }
}

void test_remove_car() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "d", "e", "f");
    test_service.add_car(8, "a", "b", "c");

    assert(test_service.get_all().size() == 2);
    test_service.remove_car(16);
    assert(test_service.get_all().size() == 1);
}

void test_find_car() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "d", "e", "f");
    test_service.add_car(8, "a", "b", "c");

    assert(test_service.find_car(16).get_make() == "d");
}

void test_modify_car() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "d", "e", "f");
    test_service.add_car(8, "a", "b", "c");

    test_service.modify_car(16, "h", 1);
    test_service.modify_car(16, "g", 2);
    test_service.modify_car(16, "f", 3);
    test_service.modify_car(16, "e", 0);

    assert(test_service.find_car(16).get_make() == "h");
    assert(test_service.find_car(16).get_model() == "g");
    assert(test_service.find_car(16).get_type() == "f");
}

void test_sort_cars() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "ddd", "lll", "hwe");
    test_service.add_car(8, "aaa", "ddd", "asd");
    test_service.add_car(11, "bbb", "aaa", "sss");
    test_service.add_car(1, "aaa", "bbb", "hhh");

    test_service.sort(1);
    assert(test_service.get_all()[0].get_licence_plate() == 1);
    assert(test_service.get_all()[3].get_licence_plate() == 16);
    test_service.sort(2);
    assert(test_service.get_all()[0].get_licence_plate() == 8);
    assert(test_service.get_all()[3].get_licence_plate() == 11);
    test_service.sort(3);
    assert(test_service.get_all()[0].get_licence_plate() == 1);
    assert(test_service.get_all()[1].get_licence_plate() == 8);
    assert(test_service.get_all()[2].get_licence_plate() == 11);
    assert(test_service.get_all()[3].get_licence_plate() == 16);
    assert(test_service.sort(5) == false);
}

void test_filter_cars() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "ddd", "lll", "hwe");
    test_service.add_car(8, "aaa", "ddd", "asd");
    test_service.add_car(11, "bbb", "aaa", "sss");
    test_service.add_car(1, "aaa", "bbb", "hhh");

    vector<Car> filtered1 = test_service.get_filtered("aaa", 1);
    vector<Car> filtered2 = test_service.get_filtered("asd", 2);
    assert(filtered1.size() == 2);
    assert(filtered2.size() == 1);
}

void test_wl() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "d", "e", "f");
    test_service.add_car(8, "a", "b", "c");

    test_service.new_wash_list(1);
    assert(test_service.get_all_wash_list().size() == 1);
    test_service.clear_wash_list();
    assert(test_service.get_all_wash_list().empty());
    test_service.add_to_wash_list(8);
    assert(test_service.get_all_wash_list().size() == 1);

    test_service.export_csv("test_file");
    std::ifstream fin("test_file.csv");
    string line;
    getline(fin >> std::ws, line);
    assert(line == "Licence plate,Make,Model,Type");

    assert(test_service.wash_list_priority() == false);
    test_service.add_car(160, "f", "g", "h");
    test_service.add_to_wash_list(160);
    assert(test_service.wash_list_priority() == true);
}

void test_undo() {
    CarRepository test_repo;
    Validator v;
    Service test_service(test_repo, v);

    test_service.add_car(16, "d", "e", "f");
    test_service.add_car(8, "a", "b", "c");
    assert(test_service.get_all().size() == 2);

    test_service.remove_car(16);
    test_service.remove_car(8);
    assert(test_service.get_all().empty());
    test_service.undo();
    assert(test_service.get_all().size() == 1);
    test_service.undo();
    assert(test_service.get_all().size() == 2);

    test_service.modify_car(16, "h", 1);
    test_service.modify_car(16, "g", 2);
    test_service.modify_car(16, "f", 3);
    assert(test_service.find_car(16).get_make() == "h");
    assert(test_service.find_car(16).get_model() == "g");
    assert(test_service.find_car(16).get_type() == "f");
    test_service.undo();
    test_service.undo();
    test_service.undo();
    assert(test_service.find_car(16).get_make() == "d");
    assert(test_service.find_car(16).get_model() == "e");
    assert(test_service.find_car(16).get_type() == "f");
    test_service.undo();
    test_service.undo();
    assert(test_service.get_all().empty());

    try {
        test_service.undo();
        assert(false);
    }
    catch (UndoException& e) {
        assert(true);
    }
}

void test_service() {
    test_add_car();
    test_remove_car();
    test_find_car();
    test_modify_car();
    test_sort_cars();
    test_filter_cars();
    test_wl();
    test_undo();
}