#ifndef RECEIPTCONTROLLER_H
#define RECEIPTCONTROLLER_H

#include "ReceiptView.h"
#include "Item.h"
#include "Receipt.h"
#include <qlabel.h>
#include <QDebug>
#include <QObject>

class ReceiptController: public QObject
{
Q_OBJECT

public:
    explicit ReceiptController(ReceiptView *v);

    void addItem(const Item &item);
    void setReceipt(const Receipt &receipt);
    Receipt getReceipt() { return m_model; }
    bool isReceiptEmpty() { return m_model.empty(); }

signals:
    void saveReceiptSignal();

public slots:
    bool deleteItem(size_t id);
    void reset();

private:
    ReceiptView *m_view;
    Receipt m_model;

    void updateViewSum(const double &sum) { m_view->setSum(sum); }
    void updateViewTime(const time_t &time) { m_view->setTime(time); }
    void saveReceipt() { emit saveReceiptSignal(); }
};

#endif // RECEIPTCONTROLLER_H
