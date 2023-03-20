#include "gui.h"

void GUI::init_GUI() {
    /* main */
    auto* layout = new QHBoxLayout;
    this->setLayout(layout);
    this->setWindowTitle("Cars");

    /* left half */
    auto* left_widget = new QWidget;
    auto* left_layout = new QVBoxLayout;
    left_widget->setLayout(left_layout);

    auto* form = new QGroupBox;
    auto* form_layout = new QGridLayout;
    form->setLayout(form_layout);

    auto* plate_label = new QLabel("Licence Plate:");
    auto* make_label = new QLabel("Make:");
    auto* model_label = new QLabel("Model:");
    auto* type_label = new QLabel("Type:");
    form_layout->addWidget(plate_label, 0, 0);
    form_layout->addWidget(make_label, 1, 0);
    form_layout->addWidget(model_label, 2, 0);
    form_layout->addWidget(type_label, 3, 0);

    q_licence_plate_edit = new QLineEdit;
    q_make_edit = new QLineEdit;
    q_model_edit = new QLineEdit;
    q_type_edit = new QLineEdit;
    form_layout->addWidget(q_licence_plate_edit, 0, 1);
    form_layout->addWidget(q_make_edit, 1, 1);
    form_layout->addWidget(q_model_edit, 2, 1);
    form_layout->addWidget(q_type_edit, 3, 1);

    q_add_button = new QPushButton("Add Car");
    q_add_button->setShortcut(QKeySequence(Qt::Key_Return));
    form_layout->addWidget(q_add_button, 4, 0);

    left_layout->addWidget(form);

    auto* wl_group = new QGroupBox;
    auto* wl_layout = new QGridLayout;
    wl_group->setLayout(wl_layout);

    q_list1_button = new QPushButton("List View");
    q_list2_button = new QPushButton("Image View");
    wl_new_button = new QPushButton("New List");
    wl_add_button = new QPushButton("Add Car");
    wl_clear_button = new QPushButton("Clear List");
    wl_layout->addWidget(q_list1_button, 0, 0, 1, 3);
    wl_layout->addWidget(q_list2_button, 0, 3, 1, 3);
    wl_layout->addWidget(wl_new_button, 1, 0, 1, 2);
    wl_layout->addWidget(wl_add_button, 1, 2, 1, 2);
    wl_layout->addWidget(wl_clear_button, 1, 4, 1, 2);

    left_layout->addWidget(wl_group);


    /* right half */
    auto* right_widget = new QWidget;
    right_layout = new QGridLayout;
    right_widget->setLayout(right_layout);
    q_car_list = new QListWidget;
    right_layout->addWidget(q_car_list, 0, 0, 1, 0);

    auto* manage_label = new QLabel("Manage..");
    right_layout->addWidget(manage_label, 1, 0);

    q_remove_button = new QPushButton("Remove Car");
    q_remove_button->setShortcut(QKeySequence(Qt::Key_Backspace));
    right_layout->addWidget(q_remove_button, 1, 1);

    q_modify_button = new QPushButton("Modify Car");
    right_layout->addWidget(q_modify_button, 1, 2);

    q_find_button = new QPushButton("Find Car");
    right_layout->addWidget(q_find_button, 1, 3);

    /* sort */
    auto* sort_label = new QLabel("Sort..");
    right_layout->addWidget(sort_label, 2, 0);

    q_sort_plate = new QPushButton("By Plate");
    q_sort_type = new QPushButton("By Type");
    q_sort_model = new QPushButton("By Model");

    right_layout->addWidget(q_sort_plate, 2, 1);
    right_layout->addWidget(q_sort_type, 2, 2);
    right_layout->addWidget(q_sort_model, 2, 3);

    /* filter */
    auto* filter_label = new QLabel("Filter..");
    right_layout->addWidget(filter_label, 3, 0);

    q_filter = new QPushButton("Filter");
    right_layout->addWidget(q_filter, 3, 1);


    /* new buttons (right) */
    new_widget = new QWidget;
    new_layout = new QVBoxLayout;
    new_widget->setLayout(new_layout);

    /* finish init */
    layout->addWidget(left_widget);
    layout->addWidget(right_widget);
    //layout->addWidget(new_widget);

    /* menu bar */
    auto* menubar = new QMenuBar;
    auto* edit_menu = menubar->addMenu(tr("&Edit"));

    undo_act = new QAction(tr("&Undo"), this);
    undo_act->setShortcut(QKeySequence("Ctrl+Z"));

    edit_menu->addAction(undo_act);
}

void GUI::connect_buttons() {
    QObject::connect(q_add_button, &QPushButton::clicked, this, &GUI::add_car_GUI);
    QObject::connect(q_remove_button, &QPushButton::clicked, this, &GUI::remove_car_GUI);
    QObject::connect(q_modify_button, &QPushButton::clicked, this, &GUI::modify_car_GUI);
    QObject::connect(q_find_button, &QPushButton::clicked, this, &GUI::find_car_GUI);
    //QObject::connect(q_list_button, &QPushButton::clicked, this, &GUI::wash_list_GUI);
    QObject::connect(q_list1_button, &QPushButton::clicked, this, [&](){
        auto wl1 = new WashListGUI {srv, srv.get_wash_list()};
        wl1->show();
    });
    QObject::connect(q_list2_button, &QPushButton::clicked, this, [&](){
        auto wl2 = new WashListReadOnlyGUI {srv.get_wash_list()};
        wl2->show();
    });
    QObject::connect(q_filter, &QPushButton::clicked, this, &GUI::filter_GUI);

    QObject::connect(q_sort_plate, &QPushButton::clicked, this, [&](){
        srv.sort(1);
        refresh_list(srv.get_all());
    });
    QObject::connect(q_sort_type, &QPushButton::clicked, this, [&](){
        srv.sort(2);
        refresh_list(srv.get_all());
    });
    QObject::connect(q_sort_model, &QPushButton::clicked, this, [&](){
        srv.sort(3);
        refresh_list(srv.get_all());
    });
    QObject::connect(undo_act, &QAction::triggered, this, [&](){
        try {
            srv.undo();
            refresh_list(srv.get_all());
        }
        catch (UndoException &e) {
            auto* msgbox = new QMessageBox;
            msgbox->setText(QString::fromStdString("Could not undo"));
            msgbox->exec();
        }
    });
    QObject::connect(wl_new_button, &QPushButton::clicked, this, [&](){
        bool ok;
        int cars = QInputDialog::getInt(this, tr("New List"),
                                        tr("Cars to add:"), 0, 0, static_cast<int>(srv.get_all().size()), 1, &ok);
        if (ok) {
            try {
                srv.new_wash_list(cars);
            }
            catch (ListException &e) {
                std::cout << e.get_error();
            }
        }
    });
    QObject::connect(wl_add_button, &QPushButton::clicked, this, [&](){
        bool ok;
        int licence = QInputDialog::getText(this, tr("Add car"),
                                            tr("Licence plate:"), QLineEdit::Normal,
                                            "12345", &ok).toInt();
        if (ok) {
            try {
                srv.add_to_wash_list(licence);
            }
            catch (RepoException &e) {
                std::cout << e.get_error();
                auto* msgbox = new QMessageBox;
                msgbox->setText(QString::fromStdString("Could not find car"));
                msgbox->exec();
            }
        }
    });
    QObject::connect(wl_clear_button, &QPushButton::clicked, this, [&](){
        srv.clear_wash_list();
    });
}

void GUI::refresh_list(const vector<Car>& car_list) {
    q_car_list->clear();
    for (auto& car : car_list) {
        QString car_str = QString::fromStdString(std::to_string(car.get_licence_plate()) + " - " + car.get_make() + " " + car.get_model() + " - "
                              + car.get_type());
        q_car_list->addItem(car_str);
    }
}

void GUI::refresh_wash_table(const vector<Car>& car_list) {
    q_wash_table->clear();
    int row = 0;
    for (auto& car : car_list) {
//        QString car_str = QString::fromStdString(std::to_string(car.get_licence_plate()) + " - " + car.get_make() + " " + car.get_model() + " - "
//                              + car.get_type());
//        q_wash_list->addItem(car_str);

        q_wash_table->setItem(row, 0, new QTableWidgetItem(QString::number(car.get_licence_plate())));
        q_wash_table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(car.get_make())));
        q_wash_table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(car.get_model())));
        q_wash_table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(car.get_type())));
        row++;
    }
}

void GUI::refresh_buttons(QVBoxLayout* layout, const vector<Car>& car_list) {
    while (!layout->isEmpty()) {
        auto* child = layout->takeAt(0);
        if ( child->widget() != nullptr ) {
            delete child->widget();
        }
        delete child;
    }

    vector<string> unique_type_list;
    /* get unique */
    for (auto& car : car_list) {
        auto type = car.get_type();
        bool add = true;
        for (auto& unique_type : unique_type_list) {
            if (unique_type == type) {
                add = false;
                break;
            }
        }
        if (add)
            unique_type_list.push_back(type);
    }
    for (auto& e : unique_type_list) std::cout << e;

    /* make buttons */
    for (auto& type : unique_type_list) {
        auto* new_button = new QPushButton(QString::fromStdString(type));
        QObject::connect(new_button, &QPushButton::clicked, this, [&, type](){
            auto* msgbox = new QMessageBox;
            msgbox->setText(QString::number(get_freq(srv.get_all(), type)));
            msgbox->exec();
        });
        layout->addWidget(new_button);
    }
}

int GUI::get_freq(const vector<Car>& car_list, const string& type) {
    int count = 0;
    for (auto& car : car_list) {
        auto t = car.get_type();
        std::cout << "looking for " << type << ":" << t << '\n';
        if (type == t) {
            count++;
        }
    }
    return count;
}

void GUI::add_car_GUI() {
    auto licence_plate = q_licence_plate_edit->text().toInt();
    auto make = q_make_edit->text().toStdString();
    auto model = q_model_edit->text().toStdString();
    auto type = q_type_edit->text().toStdString();

    q_licence_plate_edit->clear();
    q_make_edit->clear();
    q_model_edit->clear();
    q_type_edit->clear();

    try {
        srv.add_car(licence_plate, make, model, type);
        refresh_list(srv.get_all());
        refresh_buttons(new_layout, srv.get_all());
    }
    catch (ValidationException &e) {
        std::cout << e.get_errors();
    }
    catch (RepoException &e) {
        std::cout << e.get_error();
    }
}

void GUI::remove_car_GUI() {
    if (q_car_list->currentItem() != nullptr) {
        auto selected = q_car_list->currentItem()->text().toStdString();
        auto licence = std::stoi(selected.substr(0, selected.find(' ')));
        try {
            srv.remove_car(licence);
            refresh_list(srv.get_all());
            refresh_buttons(new_layout, srv.get_all());
        }
        catch (RepoException &e) {
            std::cout << e.get_error();
        }
    }
}

void GUI::find_car_GUI() {
    bool ok;
    int licence = QInputDialog::getText(this, tr("Find car"),
                                        tr("Licence plate:"), QLineEdit::Normal,
                                        "12345", &ok).toInt();
    if (ok) {
        try {
            auto& found = srv.find_car(licence);
            auto* msgbox = new QMessageBox;
            msgbox->setWindowTitle("Car found");
            msgbox->setText(QString::fromStdString(std::to_string(found.get_licence_plate()) + " - " + found.get_make()
                                + " " + found.get_model() + " - " + found.get_type()));
            msgbox->exec();
        }
        catch (RepoException &e) {
            std::cout << e.get_error();
            auto* msgbox = new QMessageBox;
            msgbox->setText(QString::fromStdString("Could not find car"));
            msgbox->exec();
        }
    }
}

void GUI::modify_car_GUI() {
    if (q_car_list->currentItem() == nullptr) return;

    /* main */
    auto* dialog = new QDialog;
    dialog->setModal(true);
    auto* main_layout = new QVBoxLayout;
    dialog->setLayout(main_layout);

    /* form */
    auto* form_widget = new QWidget;
    auto* form_layout = new QGridLayout;
    form_widget->setLayout(form_layout);

    auto* label = new QLabel("New Value:");
    auto* value_edit = new QLineEdit;

    form_layout->addWidget(label, 0, 0);
    form_layout->addWidget(value_edit, 0, 1);

    /* radio */
    auto* radio_widget = new QWidget;
    auto* radio_layout = new QHBoxLayout;
    radio_widget->setLayout(radio_layout);

    radio_make = new QRadioButton("Make");
    radio_model = new QRadioButton("Model");
    radio_type = new QRadioButton("Type");
    radio_layout->addWidget(radio_make);
    radio_layout->addWidget(radio_model);
    radio_layout->addWidget(radio_type);

    /* buttons */
    auto* button_widget = new QWidget;
    auto* button_layout = new QHBoxLayout;

    button_widget->setLayout(button_layout);
    modify_accept_button = new QPushButton("Modify");
    modify_cancel_button = new QPushButton("Cancel");

    button_layout->addWidget(modify_accept_button);
    button_layout->addWidget(modify_cancel_button);

    main_layout->addWidget(form_widget);
    main_layout->addWidget(radio_widget);
    main_layout->addWidget(button_widget);

    dialog->show();

    QObject::connect(modify_accept_button, &QPushButton::clicked, this, [&, value_edit, dialog](){
        auto selected = q_car_list->currentItem()->text().toStdString();
        auto licence = std::stoi(selected.substr(0, selected.find(' ')));
        int type {0};
        if (radio_make->isChecked()) {
            type = 1;
        }
        else if (radio_model->isChecked()) {
            type = 2;
        }
        else if (radio_type->isChecked()) {
            type = 3;
        }

        std::cout << licence << ' ' << value_edit->text().toStdString() << ' ' << type;

        if (!value_edit->text().isEmpty()) {
            srv.modify_car(licence, value_edit->text().toStdString(), type);
            refresh_list(srv.get_all());
            refresh_buttons(new_layout, srv.get_all());
        }
        dialog->accept();
    });

    QObject::connect(modify_cancel_button, &QPushButton::clicked, this, [dialog](){
        dialog->reject();
    });
}

void GUI::filter_GUI() {
    /* main */
    auto* dialog = new QDialog;
    dialog->setModal(true);
    auto* main_layout = new QVBoxLayout;
    dialog->setLayout(main_layout);

    /* form */
    auto* form_widget = new QWidget;
    auto* form_layout = new QGridLayout;
    form_widget->setLayout(form_layout);

    auto* label = new QLabel("Search:");
    auto* value_edit = new QLineEdit;

    form_layout->addWidget(label, 0, 0);
    form_layout->addWidget(value_edit, 0, 1);

    /* radio */
    auto* radio_widget = new QWidget;
    auto* radio_layout = new QHBoxLayout;
    radio_widget->setLayout(radio_layout);

    radio_make = new QRadioButton("Make");
    radio_type = new QRadioButton("Type");
    radio_layout->addWidget(radio_make);
    radio_layout->addWidget(radio_type);

    /* buttons */
    auto* button_widget = new QWidget;
    auto* button_layout = new QHBoxLayout;

    button_widget->setLayout(button_layout);
    modify_accept_button = new QPushButton("Filter");
    modify_cancel_button = new QPushButton("Cancel");

    button_layout->addWidget(modify_accept_button);
    button_layout->addWidget(modify_cancel_button);

    main_layout->addWidget(form_widget);
    main_layout->addWidget(radio_widget);
    main_layout->addWidget(button_widget);

    dialog->show();

    QObject::connect(modify_accept_button, &QPushButton::clicked, this, [&, value_edit, dialog](){
        int type {0};
        if (radio_make->isChecked()) {
            type = 1;
        }
        else if (radio_type->isChecked()) {
            type = 2;
        }

        std::cout << value_edit->text().toStdString() << ' ' << type;

        if (!value_edit->text().isEmpty()) {
            refresh_list(srv.get_filtered(value_edit->text().toStdString(), type));
            refresh_buttons(new_layout, srv.get_all());

            q_remove_filter = new QPushButton("Clear");
            right_layout->addWidget(q_remove_filter, 3, 2);
            QObject::connect(q_remove_filter, &QPushButton::clicked, this, [&](){
                refresh_list(srv.get_all());
                delete q_remove_filter;
            });
        }
        dialog->accept();
    });

    QObject::connect(modify_cancel_button, &QPushButton::clicked, this, [dialog](){
        dialog->reject();
    });
}

//void GUI::wash_list_new_GUI() {
//    /* main */
//    auto* layout = new QHBoxLayout;
//    auto* window = new QWidget;
//    window->setLayout(layout);
//    window->setWindowTitle("Wash list");
//
//    /* left half */
//    auto* left_widget = new QWidget;
//    auto* left_layout = new QVBoxLayout;
//    left_widget->setLayout(left_layout);
//
//    wl_new_button = new QPushButton("New List");
//    left_layout->addWidget(wl_new_button);
//    wl_add_button = new QPushButton("Add Car");
//    left_layout->addWidget(wl_add_button);
//    wl_priority_button = new QPushButton("Check Priority");
//    left_layout->addWidget(wl_priority_button);
//    wl_clear_button = new QPushButton("Clear List");
//    left_layout->addWidget(wl_clear_button);
//    wl_export_button = new QPushButton("Export CSV");
//    left_layout->addWidget(wl_export_button);
//
//    /* right half */
//    auto* right_widget = new QWidget;
//    right_layout = new QGridLayout;
//    right_widget->setLayout(right_layout);
//    q_wash_table = new QTableWidget(10, 4);
//
//    QStringList labels;
//    labels << "Licence plate" << "Make" << "Model" << "Type";
//
//    right_layout->addWidget(q_wash_table, 0, 0, 1, 0);
//
//    /* finish init */
//    refresh_wash_table(srv.get_all_wash_list());
//    q_wash_table->setHorizontalHeaderLabels(labels);
//    layout->addWidget(left_widget);
//    layout->addWidget(right_widget);
//
//
//    /* connect */
//    QObject::connect(wl_new_button, &QPushButton::clicked, this, [&](){
//        bool ok;
//        int cars = QInputDialog::getInt(this, tr("New List"),
//                                        tr("Cars to add:"), 0, 0, static_cast<int>(srv.get_all().size()), 1, &ok);
//        if (ok) {
//            try {
//                srv.new_wash_list(cars);
//            }
//            catch (ListException &e) {
//                std::cout << e.get_error();
//            }
//            refresh_wash_table(srv.get_all_wash_list());
//        }
//    });
//    QObject::connect(wl_add_button, &QPushButton::clicked, this, [&](){
//        bool ok;
//        int licence = QInputDialog::getText(this, tr("Add car"),
//                                            tr("Licence plate:"), QLineEdit::Normal,
//                                            "12345", &ok).toInt();
//        if (ok) {
//            try {
//                srv.add_to_wash_list(licence);
//            }
//            catch (RepoException &e) {
//                std::cout << e.get_error();
//                auto* msgbox = new QMessageBox;
//                msgbox->setText(QString::fromStdString("Could not find car"));
//                msgbox->exec();
//            }
//            refresh_wash_table(srv.get_all_wash_list());
//        }
//    });
//    QObject::connect(wl_clear_button, &QPushButton::clicked, this, [&](){
//        srv.clear_wash_list();
//        refresh_wash_table(srv.get_all_wash_list());
//    });
//    QObject::connect(wl_priority_button, &QPushButton::clicked, this, [&](){
//        auto* msgbox = new QMessageBox;
//        if (srv.wash_list_priority()) {
//            msgbox->setText(QString::fromStdString("There are priority cars in the list"));
//        }
//        else {
//            msgbox->setText(QString::fromStdString("There are no priority cars in the list"));
//        }
//        msgbox->exec();
//    });
//    QObject::connect(wl_export_button, &QPushButton::clicked, this, [&](){
//        bool ok;
//        string filename = QInputDialog::getText(this, tr("Export"),
//                                                tr("Filename:"), QLineEdit::Normal,
//                                                "out", &ok).toStdString();
//        if (ok) {
//            srv.export_csv(filename);
//        }
//    });
//
//    window->show();
//}

/* Simulare
 * 3-4 func
 * Qslider, Qcheckbox (Qtassistant ok)
 */