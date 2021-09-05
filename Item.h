#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <utility>
#include <QJsonObject>

class Item {

public:
    // constructor
    Item(): m_price(0.0), m_discount(0.0) {}
    Item(std::string seller, double price, double discount): m_seller(std::move(seller)), m_price(price), m_discount(discount) {}

    // operator overload
    friend bool operator== (const Item &i1, const Item &i2);
    friend bool operator!= (const Item &i1, const Item &i2);


    // Getters and setters
    [[nodiscard]] std::string getSeller() const { return m_seller; }
    void setSeller(const std::string &value) { m_seller = value; }
    [[nodiscard]] double getPrice() const { return m_price; }
    void setPrice(const double &value) { m_price = value; }
    [[nodiscard]] double getDiscount() const { return m_discount; }
    void setDiscount(const double &value) { m_discount = value; }

    // json reader and writer
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    std::string m_seller;
    double m_price;
    double m_discount;
};

#endif // ITEM_H
