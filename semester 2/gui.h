#ifndef LAB10_11_GUI_H
#define LAB10_11_GUI_H

#include <QtWidgets>
#include <QApplication>

#include "Service.h"
#include "WashListGUI.h"

class GUI : public QWidget {
private:

    Service& srv;

    QListWidget* q_car_list;
    QTableWidget* q_wash_table;

    QPushButton* q_add_button;
    QPushButton* q_remove_button;
    QPushButton* q_modify_button;
    QPushButton* q_find_button;
    QPushButton* q_list1_button;
    QPushButton* q_list2_button;

    QPushButton* q_sort_plate;
    QPushButton* q_sort_type;
    QPushButton* q_sort_model;

    QPushButton* q_filter;
    QPushButton* q_remove_filter;
    QPushButton* modify_accept_button;
    QPushButton* modify_cancel_button;

    QLineEdit* q_licence_plate_edit;
    QLineEdit* q_make_edit;
    QLineEdit* q_model_edit;
    QLineEdit* q_type_edit;

    QRadioButton* radio_make;
    QRadioButton* radio_model;
    QRadioButton* radio_type;

    QWidget* new_widget;
    QVBoxLayout* new_layout;
    QGridLayout* right_layout;

    QAction* undo_act;

    QPushButton* wl_new_button;
    QPushButton* wl_add_button;
    QPushButton* wl_clear_button;

    void init_GUI();

    void add_car_GUI();
    void remove_car_GUI();
    void modify_car_GUI();
    void find_car_GUI();
    void filter_GUI();

    void wash_list_new_GUI();

    void connect_buttons();
    void refresh_list(const vector<Car>& car_list);
    void refresh_wash_list(const vector<Car>& car_list);
    void refresh_wash_table(const vector<Car>& car_list);
    void refresh_buttons(QVBoxLayout* layout, const vector<Car>& car_list);

    static int get_freq(const vector<Car>& car_list, const string& type);

public:

    GUI(Service& srv) : srv { srv } {
        init_GUI();
        connect_buttons();
        refresh_list(srv.get_all());
    };
};


#endif //LAB10_11_GUI_H
