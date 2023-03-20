#include <fstream>
#include "WashList.h"

void WashList::new_wl(vector<Car> &repo_list, int n) {
    if (static_cast<int>(repo_list.size()) < n)
        throw ListException("There are not enough cars in the repository\n");
    clear_list();
    for (int i = 0; i < n; i++) {
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, static_cast<int>(repo_list.size()-1));

        auto random_car = repo_list[dist(mt)];
        if (exists(random_car)) i--;
        else add_to_list(random_car);
    }
    notify();
}

void WashList::add_to_list(const Car &new_car) {
    if(!exists(new_car)) {
        car_list.push_back(new_car);
        notify();
    }
    else throw ListException("Car already exists\n");
}

vector<Car> &WashList::get_all() {
    return car_list;
}

void WashList::clear_list() {
    car_list.clear();
    notify();
}

void WashList::export_csv(string filename) {
    filename = filename + ".csv";
    char delimiter = ',';
    std::ofstream fout(filename);
    fout << "Licence plate,Make,Model,Type\n";
    for (const auto& car : car_list) {
        fout << car.get_licence_plate() << delimiter << car.get_make() << delimiter
             << car.get_model() << delimiter << car.get_type() << '\n';
    }
    std::cout << "Successfully exported to " << filename << '\n';
}

bool WashList::exists(const Car &car) {
    int licence_plate = car.get_licence_plate();
    auto found_car = std::find_if(this->car_list.begin(), this->car_list.end(),
                                  [&](const Car& c){ return c.get_licence_plate() == licence_plate; });
    if (found_car != this->car_list.end())
        return true;
    return false;
}

bool WashList::has_priority_cars() {
    return std::any_of(this->car_list.begin(), this->car_list.end(),
                       [&](const Car& c) { return c.get_licence_plate() % 10 == 0; });
}

/***************************************TESTS***************************************/

void test_generate() {
    CarRepository test_repo;
    Car test_car1(64, "h", "i", "j");
    Car test_car2(128, "k", "l", "m");
    Car test_car3(256, "n", "o", "p");
    test_repo.store(test_car1);
    test_repo.store(test_car2);
    test_repo.store(test_car3);
    WashList wl;
    wl.new_wl(test_repo.get_all(), 2);
    assert(wl.get_all().size() == 2);
    wl.clear_list();
    assert(wl.get_all().empty());
    try {
        wl.new_wl(test_repo.get_all(), 4);
        assert(false);
    }
    catch(ListException &e) {
        assert(true);
    }
}

void test_add() {
    CarRepository test_repo;
    Car test_car1(64, "h", "i", "j");
    Car test_car2(128, "k", "l", "m");
    Car test_car3(256, "n", "o", "p");
    test_repo.store(test_car1);
    test_repo.store(test_car2);
    test_repo.store(test_car3);
    WashList wl;
    wl.new_wl(test_repo.get_all(), 0);
    assert(wl.get_all().empty());
    wl.add_to_list(test_car1);
    wl.add_to_list(test_car2);
    try {
        wl.add_to_list(test_car2);
    }
    catch(ListException &e) {
        assert(true);
        assert(e.get_error() == "Car already exists\n");
    }
    wl.add_to_list(test_car3);
    assert(wl.get_all().size() == 3);
}

void test_export() {
    CarRepository test_repo;
    Car test_car1(64, "h", "i", "j");
    Car test_car2(128, "k", "l", "m");
    Car test_car3(256, "n", "o", "p");
    test_repo.store(test_car1);
    test_repo.store(test_car2);
    test_repo.store(test_car3);
    WashList wl;
    wl.new_wl(test_repo.get_all(), 0);
    assert(wl.get_all().empty());
    wl.add_to_list(test_car1);
    wl.add_to_list(test_car2);
    wl.add_to_list(test_car3);

    wl.export_csv("test_file");
    std::ifstream fin("test_file.csv");
    string line;
    getline(fin >> std::ws, line);
    assert(line == "Licence plate,Make,Model,Type");
}

void test_priority() {
    CarRepository test_repo;
    Car test_car1(64, "h", "i", "j");
    Car test_car2(120, "k", "l", "m");
    test_repo.store(test_car1);
    test_repo.store(test_car2);
    WashList wl;
    wl.new_wl(test_repo.get_all(), 0);
    assert(wl.has_priority_cars() == false);
    wl.add_to_list(test_car1);
    assert(wl.has_priority_cars() == false);
    wl.add_to_list(test_car2);
    assert(wl.has_priority_cars() == true);
}

void test_wash_list() {
    test_generate();
    test_add();
    test_export();
    test_priority();
}
