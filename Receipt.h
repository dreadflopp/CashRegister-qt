#ifndef RECEIPT_H
#define RECEIPT_H

#include "Item.h"
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <map>
#include "CashRegisterException.h"

class Receipt {

public:
    // constructor
    Receipt(): m_id(0), m_time(0) {}

    // operator overload
    friend bool operator== (const Receipt &r1, const Receipt &r2);
    friend bool operator!= (const Receipt &r1, const Receipt &r2);

    // getters and setters
    [[nodiscard]] std::time_t getTime() const { return m_time; }
    void setTime(const std::time_t &t) { m_time = t; }
    [[nodiscard]] std::map<std::size_t,Item> getItems() const { return m_items; }
    void setItems(const std::map<std::size_t,Item> &i) { m_items = i;}

    // other public functions

    /**
     * @brief Adds an item to the receipt. The m_id must be unique.
     * @param id
     * @param item
     * @return True if added, false if not added (not unique m_id)
     */
    //bool addItem(const std::size_t &m_id, const Item &item);
    std::size_t addItem(const Item &item);
    bool removeItem(const std::size_t &id);
    Item getItem(const size_t &id) const;
    [[nodiscard]] std::size_t countItems() const { return m_items.size(); }
    [[nodiscard]] bool empty() const { return m_items.empty(); }
    [[nodiscard]] double getSum() const;
    void clear();

    // read / write json
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    std::time_t m_time;
    std::map<std::size_t,Item> m_items;
    std::size_t m_id;

    std::size_t getId() { return m_id++; }

};

#endif // RECEIPT_H
