#include "qtui.h"
#include "ui_QtUI.h"


QtUI::QtUI(QWidget *parent) :
        QWidget(parent), ui(new Ui::QtUI) {
    ui->setupUi(this);
}

QtUI::~QtUI() {
    delete ui;
}

