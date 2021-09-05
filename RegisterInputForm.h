#ifndef CASHREGISTER_REGISTERINPUTFORM_H
#define CASHREGISTER_REGISTERINPUTFORM_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "Item.h"

class RegisterInputForm: public QWidget {

    Q_OBJECT

public:
    explicit RegisterInputForm(QWidget *parent = nullptr);

private:
    QLineEdit *sellerLineEdit;
    QDoubleSpinBox *priceSpinBox;
    QSpinBox *discountSpinBox;

    QCheckBox *useDiscountCheckBox;

    QPushButton *addPushButton;

signals:
    void sendItemSignal(Item item);

private slots:
    void validator();
    void addButtonHandler();

};


#endif //CASHREGISTER_REGISTERINPUTFORM_H
