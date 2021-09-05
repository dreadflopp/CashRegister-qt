//
// Created by dreadflopp on 2020-11-15.
//

#ifndef CASHREGISTER_HISTORYTAB_H
#define CASHREGISTER_HISTORYTAB_H


#include <QWidget>
#include "HistoryView.h"

class HistoryTab: public QWidget {

    Q_OBJECT
private:
    HistoryView *historyView;
public:
    explicit HistoryTab(QWidget *parent = nullptr);
    HistoryView* getHistoryView() { return historyView; }
};


#endif //CASHREGISTER_HISTORYTAB_H
