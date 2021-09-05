#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H

#include "HistoryView.h"
#include "Receipt.h"
#include "ReceiptController.h"
#include "ReceiptView.h"
#include "History.h"

#include <QObject>

class HistoryController: public QObject
{
Q_OBJECT
public:
    explicit HistoryController(HistoryView *v);

    void addReceipt(const Receipt& receipt);
    Receipt getReceipt(size_t id) { return model.getReceipt(id); }

    bool saveHistory() const;
    bool loadHistory();

signals:
    void moveReceiptSignal(size_t id);

public slots:
    void showReceipt(size_t id);
    void deleteReceipt(size_t id);
    void moveReceiptSlot(size_t id) { emit moveReceiptSignal(id); }

private:
    HistoryView *view;
    //std::map<std::size_t, Receipt> m_model;
    History model;
};

#endif // HISTORYCONTROLLER_H
