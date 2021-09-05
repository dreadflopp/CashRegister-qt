#include "ReceiptView.h"

ReceiptView::ReceiptView(Complexity complexity, QWidget *parent): QWidget(parent) {

    Q_UNUSED(parent)

    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // Buttons row
    buttonsRow = new QWidget();
    auto *buttonsRowLayout = new QHBoxLayout(buttonsRow);
    layout->addWidget(buttonsRow, 0, Qt::AlignTop);

    // ScrollArea
    scrollArea = new QScrollArea();

    content = new QWidget();
    auto *contentLayout = new QVBoxLayout(content);
    contentLayout->setAlignment(Qt::AlignTop);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(content);
    layout->addWidget(scrollArea);

    // body
    body = new QWidget();
    body->setLayout(new QVBoxLayout());
    contentLayout->addWidget(body, 0, Qt::AlignTop);

    // foot
    footer = new QWidget();
    auto *footerLayout = new QGridLayout(footer);
    footerLayout->setAlignment(Qt::AlignTop);
    contentLayout->addWidget(footer, 0, Qt::AlignTop);

    // Add content
    saveButton = new QPushButton("Save");
    deleteAllButton = new QPushButton("Delete All");
    editButton = new QPushButton("Edit");
    doneButton = new QPushButton("Done");
    buttonsRowLayout->addWidget(saveButton, 0, Qt::AlignLeft);
    buttonsRowLayout->addStretch();
    buttonsRowLayout->addWidget(deleteAllButton, 0, Qt::AlignRight);
    buttonsRowLayout->addWidget(editButton, 0, Qt::AlignRight);
    buttonsRowLayout->addWidget(doneButton, 0, Qt::AlignRight);
    sumDesc = new QLabel("Sum: ");
    footerLayout->addWidget(sumDesc, 0, 0);
    sumValue = new QLabel();
    footerLayout->addWidget(sumValue, 0, 1);
    sumValue->setAlignment(Qt::AlignRight);
    timeDesc = new QLabel("Time: ");
    footerLayout->addWidget(timeDesc, 1, 0);
    timeValue = new QLabel();
    footerLayout->addWidget(timeValue, 1, 1);
    timeValue->setAlignment(Qt::AlignRight);

    // Signals and slots
    connect(scrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, this, &ReceiptView::autoScrollReceipt);
    connect(saveButton, &QPushButton::released, this, &ReceiptView::saveButtonHandler);
    connect(editButton, &QPushButton::released, this, &ReceiptView::editButtonHandler);
    connect(doneButton, &QPushButton::released, this, &ReceiptView::doneButtonHandler);
    connect(deleteAllButton, &QPushButton::released, this, &ReceiptView::deleteAllButtonHandler);

    setComplexity(complexity);
    setState(State::EMPTY);
    setMode(Mode::DEFAULT);
}

void ReceiptView::addItem(size_t id, const QString& seller, double price, double discountRate) {
    auto *container = new QWidget();
    auto *containerLayout = new QGridLayout(container);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    container->setObjectName(QString::number(id));

    auto *itemWidget = new QWidget();
    auto *itemLayout = new QGridLayout();
    itemLayout->setContentsMargins(0, 0, 0, 0);
    itemLayout->setSpacing(0);
    itemWidget->setLayout(itemLayout);

    auto *l1 = new QLabel("Seller: " + seller);
    auto *l2 = new QLabel(QString::number(price, 'f', 2));
    l2->setAlignment(Qt::AlignRight);
    itemLayout->addWidget(l1, 0, 0);
    itemLayout->addWidget(l2, 0, 1);

    if (discountRate != 0){
        auto *l3 = new QLabel("     * Discount " + QString::number(discountRate * 100, 'f', 0) + "%");
        auto *l4 = new QLabel(QString::number(price * discountRate - price, 'f', 2));
        l4->setAlignment(Qt::AlignRight);
        itemLayout->addWidget(l3, 1, 0);
        itemLayout->addWidget(l4, 1, 1);
    }

    auto *del = new QToolButton();
    del->setToolButtonStyle(Qt::ToolButtonTextOnly);
    del->setText("X");
    del->setVisible(false);
    del->setObjectName(QString::number(id));
    connect(del, &QToolButton::released, this, &ReceiptView::deleteButtonHandler);

    containerLayout->addWidget(itemWidget, 0, 0);
    containerLayout->addWidget(del, 0, 1);
    body->layout()->addWidget(container);

    setState(State::NOT_EMPTY);
}

void ReceiptView::setTime(const time_t &t)
{
    tm *time = localtime(&t);

    std::stringstream ss;
    ss << std::put_time(time, "%H:%M:%S %Y-%m-%d");

    timeValue->setText(QString::fromStdString(ss.str()));
}

bool ReceiptView::deleteItem(size_t itemId)
{
    auto *container = body->findChild<QWidget*>(QString::number(itemId), Qt::FindDirectChildrenOnly);

    if (container == nullptr)
        return false;

    delete container;

    return true;
}

void ReceiptView::reset()
{
    while (auto* w = body->findChild<QWidget*>() )
        delete w;

    setState(State::EMPTY);
    setMode(Mode::DEFAULT);
}

void ReceiptView::setState(State state) {

    switch(state) {
        case State::EMPTY:
            saveButton->setEnabled(false);
            editButton->setEnabled(false);
            sumDesc->setVisible(false);
            timeDesc->setVisible(false);
            sumValue->setVisible(false);
            timeValue->setVisible(false);
            break;
        case State::NOT_EMPTY:
            saveButton->setEnabled(true);
            editButton->setEnabled(true);
            sumDesc->setVisible(true);
            timeDesc->setVisible(true);
            sumValue->setVisible(true);
            timeValue->setVisible(true);
            break;
    }
}

void ReceiptView::setMode(ReceiptView::Mode mode) {

    QList<QToolButton*> delButtons = body->findChildren<QToolButton*>();

    switch(mode) {
        case Mode::DEFAULT:
            editButton->setVisible(true);
            doneButton->setVisible(false);
            deleteAllButton->setVisible(false);
            for (QToolButton *delButton: delButtons)
                delButton->setVisible(false);
            break;
        case Mode::EDIT:
            editButton->setVisible(false);
            deleteAllButton->setVisible(true);
            doneButton->setVisible(true);
            for (QToolButton *delButton: delButtons)
                delButton->setVisible(true);
            break;
    }
}

void ReceiptView::setComplexity(ReceiptView::Complexity complexity) {

    switch(complexity) {
        case Complexity::SIMPLE:
            buttonsRow->setVisible(false);
            break;
        case Complexity::FULL:
            buttonsRow->setVisible(true);
            break;
    }
}

void ReceiptView::showErrorDialog(const char* message) {
    QMessageBox::warning(this, tr("Cash Register"),
                                   tr(message),
                                   QMessageBox::Ok);
}

