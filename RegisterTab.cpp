#include "RegisterTab.h"

RegisterTab::RegisterTab(QWidget *parent) {

    auto layout = new QHBoxLayout();
    setLayout(layout);

    auto *left = new QWidget();
    auto *leftLayout = new QVBoxLayout();
    leftLayout->setAlignment(Qt::AlignCenter);
    left->setLayout(leftLayout);

    auto *right = new QWidget();
    auto *rightLayout = new QVBoxLayout();
    right->setLayout(rightLayout);

    inputForm = new RegisterInputForm();
    receiptView = new ReceiptView(ReceiptView::Complexity::FULL);

    layout->addStretch(1);
    layout->addWidget(left);
    layout->addWidget(right, 2);
    layout->addStretch(1);

    leftLayout->addWidget(inputForm);
    rightLayout->addWidget(new QLabel("Receipt"), 0, Qt::AlignCenter);
    rightLayout->addWidget(receiptView);

    connect(inputForm, &RegisterInputForm::sendItemSignal, this, &RegisterTab::sendItemSignal);
}

ReceiptView *RegisterTab::getReceiptView() {
    return receiptView;
}
