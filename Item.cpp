#include <QJsonDocument>
#include "Item.h"

void Item::read(const QJsonObject &json) {
    m_seller = json["seller"].toString().toStdString();
    m_price = json["price"].toDouble();
    m_discount = json["discount"].toDouble();
}

void Item::write(QJsonObject &json) const {
    json["seller"] = QString::fromStdString(m_seller);
    json["price"] = m_price;
    json["discount"] = m_discount;

    // test
    QJsonDocument doc(json);
    qDebug() << "ITEM:";
    qDebug() << doc.toJson(QJsonDocument::Compact);
}

bool operator==(const Item &i1, const Item &i2) {
    return (i1.m_seller == i2.m_seller &&
            i1.m_price == i2.m_price &&
            i1.m_discount == i2.m_discount);
}

bool operator!=(const Item &i1, const Item &i2) {
    return !(i1 == i2);
}
