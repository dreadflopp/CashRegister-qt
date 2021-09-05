#ifndef CASHREGISTER_REGISTERTAB_H
#define CASHREGISTER_REGISTERTAB_H


#include <QWidget>
#include <QVBoxLayout>
#include <utility>
#include "RegisterInputForm.h"
#include "ReceiptView.h"

class RegisterTab: public QWidget {

    Q_OBJECT
public:
    explicit RegisterTab(QWidget *parent = nullptr);
    ReceiptView* getReceiptView();
private:
    RegisterInputForm *inputForm;
    ReceiptView *receiptView;

signals:
    void sendItemSignal(Item item);

public slots:
    void itemReceiver(Item item) { emit sendItemSignal(std::move(item)); }
};


#endif //CASHREGISTER_REGISTERTAB_H
