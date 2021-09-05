#include "MainWindow.h"
#include "Database.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {

    // central widget
    centralWidget = new QWidget();
    auto *centralLayout = new QHBoxLayout(centralWidget);
    this->setCentralWidget(centralWidget);

    // tabbed widget
    tabWidget = new QTabWidget();
    registerTab = new RegisterTab();
    historyTab = new HistoryTab();
    tabWidget->addTab(registerTab, "Register");
    tabWidget->addTab(historyTab, "History");
    centralLayout->addWidget(tabWidget);

    // initiate controllers
    receiptController = new ReceiptController(registerTab->getReceiptView());
    historyController = new HistoryController(historyTab->getHistoryView());

    // connect ui objects to functions
    connect(registerTab, &RegisterTab::sendItemSignal, receiptController, &ReceiptController::addItem);
    connect(receiptController, &ReceiptController::saveReceiptSignal, this, &MainWindow::saveReceipt);
    connect(historyController, &HistoryController::moveReceiptSignal, this, &MainWindow::moveReceiptSlot);
}

MainWindow::~MainWindow() {
    delete receiptController;
    delete historyController;
}

void MainWindow::saveReceipt() {
    Receipt receipt = receiptController->getReceipt();
    historyController->addReceipt(receipt);
    receiptController->reset();
}

void MainWindow::moveReceiptSlot(size_t id) {

    if (receiptController->isReceiptEmpty()) {

        int ret = QMessageBox::question(this, tr("Cash Register"),
                                       tr("The receipt will be moved to the register.\n"
                                          "Are you sure?"),
                                       QMessageBox::Ok
                                       | QMessageBox::Cancel,
                                       QMessageBox::Cancel);

        if (ret == QMessageBox::Ok) {
            receiptController->setReceipt(historyController->getReceipt(id));
            historyController->deleteReceipt(id);
            tabWidget->setCurrentWidget(registerTab);
        }
    }

    else {
        QMessageBox::information(this, tr("Cash Register"),
                                       tr("The receipt could not be moved.\n"
                                          "Empty the register and try again."),
                                       QMessageBox::Ok);
    }
}

void MainWindow::runTests() {
    // testing
    for (int j = 0; j < 50; j++) {
        for(int i = 0; i < 30; i++) {
            receiptController->addItem(Item("test" + std::to_string(i), (i + 1) * 100, static_cast<double>(i) / 100));
        }
                saveReceipt();
    }
    historyController->saveHistory();

}

