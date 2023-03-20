#ifndef LAB10_11_QTUI_H
#define LAB10_11_QTUI_H

#include <QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui { class QtUI; }
QT_END_NAMESPACE

class QtUI : public QWidget {
Q_OBJECT

public:
    explicit QtUI(QWidget *parent = nullptr);

    ~QtUI() override;

private:
    Ui::QtUI *ui;
};


#endif //LAB10_11_QTUI_H
