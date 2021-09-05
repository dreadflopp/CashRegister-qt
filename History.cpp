#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include "History.h"

Receipt History::getReceipt(size_t id) {
    auto it = m_receipts.find(id);
    if (it == m_receipts.end())
        throw CRException_elementNotFound(id);

    return m_receipts.find(id)->second;
}

size_t History::addReceipt(const Receipt &receipt) {
    size_t id = getId();
    m_receipts.insert(std::make_pair(id, receipt));
    return id;
}

void History::deleteReceipt(std::size_t id) {
    auto it = m_receipts.find(id);
    if (it == m_receipts.end())
        throw CRException_elementNotFound(id);

    m_receipts.erase(it);
}

void History::read(const QJsonObject &json) {

    QJsonArray receipts = json["receipts"].toArray();

    m_receipts.clear();
    for (std::size_t i = 0; i < receipts.size(); i++) {
        QJsonObject receiptObject = receipts[i].toObject();
        Receipt newReceipt;
        newReceipt.read(receiptObject);
        m_receipts.insert(std::make_pair(i, newReceipt));
    }
}

void History::write(QJsonObject &json) const {

    QJsonArray receipts;
    for (const auto& pair: m_receipts) {
        QJsonObject receiptObject;
        pair.second.write(receiptObject);
        receipts.append(receiptObject);
    }
    json["receipts"] = receipts;
}

const std::map<std::size_t, Receipt> &History::getMReceipts() const {
    return m_receipts;
}

void History::clear() {
    m_receipts.clear();
    m_id = 0;
}
