#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <sstream>
#include <iomanip>
#include <QDebug>
#include <QMessageBox>
#include <QGroupBox>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include "Receipt.h"
#include "ReceiptController.h"
#include <QScrollArea>
#include <QRadioButton>

class HistoryView : public QWidget
{
Q_OBJECT
public:
    explicit HistoryView(QWidget *parent = nullptr);
    ~HistoryView() override { delete receiptController; }

    void addReceipt(size_t id, const Receipt& r);
    void deleteReceipt(size_t id);
    void reset();
    void showReceipt(const Receipt &r);
    void enableHistoryButtons(bool b);

signals:
    void receiptSelectedSignal(size_t id);
    void deleteReceiptSignal(size_t id);
    void moveReceiptSignal(size_t id);

private:
QHBoxLayout *layout;

    QWidget *buttonRow;
    QPushButton *moveButton;
    QPushButton *deleteButton;
    QLabel *listTitle;

    QScrollArea *scrollArea;
    QWidget *listWidget;
    QVBoxLayout *listLayout;

    QLabel *receiptTitle;
    ReceiptView *receiptView;

    ReceiptController *receiptController;

    QRadioButton* getSelectedRadioButton();
    void radioButtonHandler(bool checked);
    void deleteButtonHandler();
    void moveButtonHandler();
};

#endif // HISTORYVIEW_H
