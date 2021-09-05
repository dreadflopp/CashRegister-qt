
#ifndef CASHREGISTER_HISTORY_H
#define CASHREGISTER_HISTORY_H

#include "Receipt.h"
#include <map>
#include <QJsonArray>
#include "CashRegisterException.h"

class History {

public:

    enum SaveFormat {
        Json, Binary
    };

    History(): m_id(0) {}

    size_t addReceipt(const Receipt& receipt);
    Receipt getReceipt(size_t id);
    bool isEmpty() { return m_receipts.empty(); }
    void deleteReceipt(std::size_t id);
    void clear();
    size_t countReceipts() { return m_receipts.size(); }

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    bool saveGame(SaveFormat saveFormat) const;

private:
    std::size_t m_id;
    std::size_t getId() { return m_id++; }
    std::map<std::size_t, Receipt> m_receipts;
public:
    const std::map<std::size_t, Receipt> &getMReceipts() const;

};


#endif //CASHREGISTER_HISTORY_H
