#include "WashListGUI.h"

void WashListGUI::init_GUI() {
    /* main */
    auto* layout = new QHBoxLayout;
    this->setLayout(layout);
    this->setWindowTitle("Wash list");

    /* left half */
    auto* left_widget = new QWidget;
    auto* left_layout = new QVBoxLayout;
    left_widget->setLayout(left_layout);

    wl_new_button = new QPushButton("New List");
    left_layout->addWidget(wl_new_button);
    wl_add_button = new QPushButton("Add Car");
    left_layout->addWidget(wl_add_button);
    wl_priority_button = new QPushButton("Check Priority");
    left_layout->addWidget(wl_priority_button);
    wl_clear_button = new QPushButton("Clear List");
    left_layout->addWidget(wl_clear_button);
    wl_export_button = new QPushButton("Export CSV");
    left_layout->addWidget(wl_export_button);

    /* right half */
    auto* right_widget = new QWidget;
    auto* right_layout = new QGridLayout;
    right_widget->setLayout(right_layout);
    q_wash_list = new QListView;
    model = new WashListModel(this, wl.get_all());
    q_wash_list->setModel(model);
    right_layout->addWidget(q_wash_list, 0, 0, 1, 0);

    /* finish init */
//    refresh_wash_list(srv.get_all_wash_list());
    layout->addWidget(left_widget);
    layout->addWidget(right_widget);

}

void WashListGUI::connect_buttons() {
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
    QObject::connect(wl_priority_button, &QPushButton::clicked, this, [&](){
        auto* msgbox = new QMessageBox;
        if (srv.wash_list_priority()) {
            msgbox->setText(QString::fromStdString("There are priority cars in the list"));
        }
        else {
            msgbox->setText(QString::fromStdString("There are no priority cars in the list"));
        }
        msgbox->exec();
    });
    QObject::connect(wl_export_button, &QPushButton::clicked, this, [&](){
        bool ok;
        string filename = QInputDialog::getText(this, tr("Export"),
                                                tr("Filename:"), QLineEdit::Normal,
                                                "out", &ok).toStdString();
        if (ok) {
            srv.export_csv(filename);
        }
    });
}

void WashListGUI::refresh_wash_list(const vector<Car>& car_list) {
    model->setCars(car_list);
}
