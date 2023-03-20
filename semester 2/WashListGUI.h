#ifndef LAB10_11_WASHLISTGUI_H
#define LAB10_11_WASHLISTGUI_H

#include <QWidget>
#include <QtWidgets>
#include "Service.h"

class WashListModel;

class WashListGUI : public QWidget, public Observer {
private:
    Service& srv;
    WashList& wl;

    QPushButton* wl_new_button;
    QPushButton* wl_add_button;
    QPushButton* wl_clear_button;
    QPushButton* wl_priority_button;
    QPushButton* wl_export_button;

    QListView* q_wash_list;
    WashListModel* model;

    void init_GUI();
    void connect_buttons();
    void refresh_wash_list(const vector<Car>& car_list);

    void update() override {
        refresh_wash_list(wl.get_all());
        std::cout << "updating";
    }

public:
    WashListGUI(Service& srv, WashList& wl) : srv { srv }, wl { wl } {
        wl.addObserver(this); // subscribe to wl
        init_GUI();
        connect_buttons();
    };
    ~WashListGUI() {
        wl.removeObserver(this);
    }
};


class WashListReadOnlyGUI : public QWidget, public Observer {
private:
    WashList& wl;

    void paintEvent(QPaintEvent*) override {
        QPainter p{ this };
        for (auto& car : wl.get_all()) {
            auto licence = car.get_licence_plate();
            /* pseudo random consistent */
            auto x = (licence * licence * 129) % 400;
            auto y = (x * 63 + 31) % 400;
            auto rec = QRect(x, y, 60, 60);

            QImage img("img/b_1.JPG");
            Q_ASSERT(!img.isNull());
            p.drawImage(rec, img);
            p.drawText(rec, QString::number(car.get_licence_plate()));
        }
    }
    void update() override {
        repaint();
        std::cout << "updating readonly\n";
    }

public:
    WashListReadOnlyGUI(WashList& wl) : wl { wl } {
        wl.addObserver(this); // subscribe to washlist
    };
    ~WashListReadOnlyGUI() {
        wl.removeObserver(this);
    }
};


class WashListModel : public QAbstractListModel {
private:
    vector<Car>& cars;
public:
    WashListModel(QObject* parent, vector<Car>& cars) : QAbstractListModel(parent), cars { cars } {};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        std::cout<<"rowcount\n";
        return static_cast<int>(cars.size());
    };

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            auto car =  cars[index.row()];
            std::cout<<"trying to display" <<car.get_licence_plate()<<"\n";
            return QString::fromStdString(std::to_string(car.get_licence_plate()) + " - " + car.get_make() + " " + car.get_model() + " - "
                                          + car.get_type());
        }
        return QVariant();
    };

    void setCars(const vector<Car>& car_list) {
        this->cars = car_list;
        emit dataChanged(createIndex(0, 0), createIndex(rowCount(), 1));
    };
};

#endif //LAB10_11_WASHLISTGUI_H
