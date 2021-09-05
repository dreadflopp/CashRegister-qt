#include "HistoryView.h"

HistoryView::HistoryView(QWidget *parent) : QWidget(parent) {

    layout = new QHBoxLayout();
    setLayout(layout);

    // containers
    auto *left = new QWidget();
    auto *leftLayout = new QVBoxLayout(left);
    auto *right = new QWidget();
    auto *rightLayout = new QVBoxLayout(right);

    // listWidget
    listWidget = new QWidget();
    listLayout = new QVBoxLayout(listWidget);
    listLayout->setAlignment(Qt::AlignTop);

    // ScrollArea
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(listWidget);

    // list title
    listTitle = new QLabel("Select a receipt:");

    // move button
    moveButton = new QPushButton("Move to register");
    moveButton->setEnabled(false);

    // delete button
    deleteButton = new QPushButton("Delete");
    deleteButton->setEnabled(false);

    // Button container
    buttonRow = new QWidget;
    auto *buttonRowLayout = new QHBoxLayout(buttonRow);
    buttonRowLayout->setContentsMargins(0, 0, 0, 0);
    buttonRowLayout->addWidget(moveButton, 1, Qt::AlignLeft);
    buttonRowLayout->addWidget(deleteButton, 1, Qt::AlignRight);

    // receipt title
    receiptTitle = new QLabel("Receipt");

    // receipt
    receiptView = new ReceiptView(ReceiptView::Complexity::SIMPLE);
    receiptController = new ReceiptController(receiptView);

    // add content to containers
    leftLayout->addWidget(listTitle);
    leftLayout->addWidget(buttonRow);
    leftLayout->addWidget(scrollArea);
    rightLayout->addWidget(receiptTitle, 0, Qt::AlignCenter);
    rightLayout->addWidget(receiptView);
    layout->addStretch(0);
    layout->addWidget(left);
    layout->addWidget(right);
    layout->addStretch(0);

    // connect
    connect(deleteButton, &QPushButton::released, this, &HistoryView::deleteButtonHandler);
    connect(moveButton, &QPushButton::released, this, &HistoryView::moveButtonHandler);

}

void HistoryView::addReceipt(size_t id, const Receipt& r) {
    time_t t = r.getTime();
    tm *time = localtime(&t);

    std::stringstream ss;
    ss << std::put_time(time, "%H:%M:%S %Y-%m-%d");

    QString name = QString::fromStdString(ss.str());

    auto *radio = new QRadioButton(name);
    radio->setObjectName(QString::number(id));
    listLayout->insertWidget(0, radio);

    connect(radio, &QRadioButton::toggled, this, &HistoryView::radioButtonHandler);
}

void HistoryView::showReceipt(const Receipt &r) {
    receiptController->setReceipt(r);
}

void HistoryView::enableHistoryButtons(bool b) {
    deleteButton->setEnabled(b);
    moveButton->setEnabled(b);
}

void HistoryView::radioButtonHandler(bool checked)
{
    size_t buttonId = sender()->objectName().toUInt();
    if (checked) {
        enableHistoryButtons(true);
        emit receiptSelectedSignal(buttonId);
    }
}

void HistoryView::deleteButtonHandler() {
    int ret = QMessageBox::warning(this, tr("Cash Register"),
                                    tr("The receipt will be deleted.\n"
                                       "Are you sure?"),
                                    QMessageBox::Ok
                                    | QMessageBox::Cancel,
                                    QMessageBox::Cancel);

    if (ret == QMessageBox::Ok) {
        QRadioButton *selectedButton = getSelectedRadioButton();
        if (selectedButton == nullptr) {
            // @TODO error handling
        } else {
            size_t id = selectedButton->objectName().toUInt();
            receiptController->reset();
            emit deleteReceiptSignal(id);
        }
    }
}

void HistoryView::moveButtonHandler()
{
    QRadioButton *selectedButton = getSelectedRadioButton();

    if (selectedButton == nullptr) {
        // @TODO error handling
    }

    else {
        // move
        emit moveReceiptSignal(selectedButton->objectName().toUInt());
    }
}

QRadioButton *HistoryView::getSelectedRadioButton() {

    QList<QRadioButton*> radioButtons = listWidget->findChildren<QRadioButton*>();

    for (auto button: radioButtons)
        if (button->isChecked()) {
            return button;
        }
    return nullptr;
}

void HistoryView::deleteReceipt(size_t id) {
    QList<QRadioButton*> radioButtons = listWidget->findChildren<QRadioButton*>();
    QRadioButton *buttonToDelete = nullptr;

    for (auto button: radioButtons)
        if (button->objectName().toUInt() == id) {
            buttonToDelete = button;
            break;
        }

    if (buttonToDelete != nullptr) {
        delete buttonToDelete;
        enableHistoryButtons(false);
    }
}

void HistoryView::reset() {

    while (auto* w = listWidget->findChild<QWidget*>() )
        delete w;

    enableHistoryButtons(false);
    receiptController->reset();


}

