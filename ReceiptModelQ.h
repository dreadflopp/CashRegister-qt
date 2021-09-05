#ifndef CASHREGISTER_RECEIPTMODELQ_H
#define CASHREGISTER_RECEIPTMODELQ_H

#include <QAbstractListModel>
#include "Receipt.h"

class ReceiptModelQ: public QAbstractListModel {

    Q_OBJECT

public:
    explicit ReceiptModelQ(QObject *parent = nullptr): QAbstractListModel(parent) {}
    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid())
            return QVariant();

        if (index.row() >= receipt.countItems())
            return QVariant();

        if (role == Qt::DisplayRole)
            return receipt.getItem(index.row());
        else
            return QVariant();
    }
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

private:
    Receipt receipt;

};


#endif //CASHREGISTER_RECEIPTMODELQ_H
