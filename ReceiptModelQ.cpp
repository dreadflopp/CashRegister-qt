//
// Created by dreadflopp on 2020-11-30.
//

#include "ReceiptModelQ.h"

int ReceiptModelQ::rowCount(const QModelIndex &parent) const {
    return receipt.countItems();
}
