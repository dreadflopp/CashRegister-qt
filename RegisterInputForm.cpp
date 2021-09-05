#include <QFormLayout>
#include "RegisterInputForm.h"

RegisterInputForm::RegisterInputForm(QWidget *parent) {

    auto *layout = new QVBoxLayout();
    setLayout(layout);

    auto *formWidget = new QWidget();
    auto *formLayout = new QFormLayout();
    formWidget->setLayout(formLayout);

    sellerLineEdit = new QLineEdit();
    priceSpinBox = new QDoubleSpinBox();
    priceSpinBox->setValue(0.0);
    priceSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    priceSpinBox->setAlignment(Qt::AlignRight);
    discountSpinBox = new QSpinBox();
    discountSpinBox->setValue(50);
    discountSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    discountSpinBox->setAlignment(Qt::AlignRight);

    useDiscountCheckBox = new QCheckBox("Use discount");
    addPushButton = new QPushButton("Add");
    addPushButton->setEnabled(false);

    formLayout->addRow("Seller", sellerLineEdit);
    formLayout->addRow("Price", priceSpinBox);
    formLayout->addRow("Discount", discountSpinBox);
    formLayout->addRow(useDiscountCheckBox);

    layout->addWidget(formWidget);
    layout->addWidget(addPushButton, 0, Qt::AlignRight);

    connect(sellerLineEdit, &QLineEdit::textChanged, this, &RegisterInputForm::validator);
    connect(addPushButton, &QPushButton::released, this, &RegisterInputForm::addButtonHandler);
}

void RegisterInputForm::validator() {

    // remove red error frame around line edit
    sellerLineEdit->setStyleSheet("");

    // enable/disable add button
    QString seller = sellerLineEdit->text();
    if (seller.isEmpty())
        addPushButton->setDisabled(true);
    else
        addPushButton->setDisabled(false);
}

void RegisterInputForm::addButtonHandler() {

    // Get data
    QString seller = sellerLineEdit->text();
    double price = priceSpinBox->value();
    double discount = 0.0;
    if (useDiscountCheckBox->isChecked())
        discount = discountSpinBox->value();

    // validate data
    if (seller.isEmpty()) {

        sellerLineEdit->setStyleSheet("QLineEdit { border-style: solid; border-width: 2px; border-color: red; }");

        // focus on first field
        sellerLineEdit->setFocus();
    } else {
        Item item(seller.toStdString(), price, discount / 100);
        emit sendItemSignal(item);

        sellerLineEdit->setStyleSheet("");
        sellerLineEdit->setText("");
        priceSpinBox->setValue(0.0);
    }
}
