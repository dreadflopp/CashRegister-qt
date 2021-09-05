#ifndef RECEIPTVIEW_H
#define RECEIPTVIEW_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>
#include <QToolButton>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <QDebug>
#include <QMessageBox>

class ReceiptView : public QWidget
{
Q_OBJECT

public:
    enum class Complexity {
        SIMPLE,
        FULL
    };

private:
    enum class State {
    EMPTY,
    NOT_EMPTY
};
    enum class Mode {
    DEFAULT,
    EDIT
};

public:
    explicit ReceiptView(Complexity complexity, QWidget *parent = nullptr);

    void addItem(size_t id, const QString& seller, double price, double discountRate = 0);
    bool deleteItem(size_t itemId);
    void setTime(const time_t &t);
    void setSum(double sum) { sumValue->setText(QString::number(sum, 'f', 2)); }
    void reset();
    void showErrorDialog(const char* message);

public slots:
    void autoScrollReceipt() { scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum()); }

signals:
    void deleteItemSignal(size_t id);
    void deleteAllSignal();
    void saveReceiptSignal();

private:

    QVBoxLayout *layout;
    QWidget *buttonsRow;
    QScrollArea *scrollArea;
    QWidget *content;
    QWidget *body;
    QWidget *footer;

    QPushButton *saveButton;
    QPushButton *deleteAllButton;
    QPushButton *editButton;
    QPushButton *doneButton;

    QLabel *sumDesc;
    QLabel *sumValue;
    QLabel *timeDesc;
    QLabel *timeValue;

    // private functions
    void editButtonHandler() { setMode(Mode::EDIT); }
    void doneButtonHandler() { setMode(Mode::DEFAULT); }
    void saveButtonHandler() { emit saveReceiptSignal(); }
    void deleteAllButtonHandler() { emit deleteAllSignal(); }
    void deleteButtonHandler() { emit deleteItemSignal(QObject::sender()->objectName().toUInt()); }
    void setState(State state);
    void setMode(Mode mode);
    void setComplexity(Complexity complexity);
};

#endif // RECEIPTVIEW_H
