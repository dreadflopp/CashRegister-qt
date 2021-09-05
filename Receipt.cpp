#include <QJsonArray>
#include "Receipt.h"

bool Receipt::removeItem(const std::size_t &id)
{
    auto it = m_items.find(id);
    if (it == m_items.end())
        return false;
    m_items.erase(id);
    return true;
}

double Receipt::getSum() const
{
    double sum = 0.0;
    for (const auto& e: m_items) {
        sum += (e.second.getPrice() - e.second.getPrice() * e.second.getDiscount());
    }

    return sum;
}

void Receipt::clear()
{
    m_id = 0;
    m_time = 0;
    m_items.clear();
}

void Receipt::read(const QJsonObject &json) {

    m_time = json["time"].toInt();

    m_items.clear();
    QJsonArray items = json["items"].toArray();

    for (size_t i = 0; i < items.size(); i++) {
        QJsonObject itemObject = items[i].toObject();
        Item item;
        item.read(itemObject);
        m_items.insert(std::make_pair(i, item));
    }
}

void Receipt::write(QJsonObject &json) const {

    json["time"] = QString::number(m_time);

    QJsonArray items;
    for (const auto& pair: m_items) {
        QJsonObject itemObject;
        pair.second.write(itemObject);
        items.append(itemObject);
    }
    json["items"] = items;
}

bool operator==(const Receipt &r1, const Receipt &r2) {
    return (r1.m_time == r2.m_time &&
            r1.m_items == r2.m_items);
}

bool operator!=(const Receipt &r1, const Receipt &r2) {
    return !(r1 == r2);
}

std::size_t Receipt::addItem(const Item &item) {
    m_time = std::time(nullptr);
    std::size_t id = getId();

    bool result = m_items.insert(std::make_pair(id, item)).second;

    if (result)
        return id;
    else
        throw CRException_badKey(id);
}

Item Receipt::getItem(const size_t &id) const {

    auto it = m_items.find(id);
    if (it == m_items.end())
        throw CRException_badKey(id);
    return m_items.at(id);
}




