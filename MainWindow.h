#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "HistoryController.h"
#include <QMainWindow>
#include <QTabWidget>
#include "ReceiptController.h"
#include "RegisterTab.h"
#include "HistoryTab.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void runTests();

public slots:
    void saveReceipt();
    void moveReceiptSlot(size_t id);

private:
    ReceiptController *receiptController;
    HistoryController *historyController;

    QWidget *centralWidget;
    QTabWidget *tabWidget;
    RegisterTab *registerTab;
    HistoryTab *historyTab;

    const double DEFAULT_DISCOUNT = 50;
    const double DEFAULT_PRICE = 0;
    const bool DEFAULT_DISCOUNT_CHECKBOX_CHECKED = false;
    const bool DISCOUNT_CHECKBOX_REMEMBER_STATE = true;
};
#endif // MAINWINDOW_H
