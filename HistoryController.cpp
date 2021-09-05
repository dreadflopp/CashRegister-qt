#include <QFile>
#include <QJsonDocument>
#include "HistoryController.h"

HistoryController::HistoryController(HistoryView *v) {
    view = v;

    connect(view, &HistoryView::receiptSelectedSignal, this, &HistoryController::showReceipt);
    connect(view, &HistoryView::deleteReceiptSignal, this, &HistoryController::deleteReceipt);
    connect(view, &HistoryView::moveReceiptSignal, this, &HistoryController::moveReceiptSlot);
}

void HistoryController::addReceipt(const Receipt &receipt) {
    size_t id = model.addReceipt(receipt);
    view->addReceipt(id, receipt);
}

void HistoryController::showReceipt(size_t id) {
    Receipt receipt = model.getReceipt(id);
    view->showReceipt(receipt);
}

void HistoryController::deleteReceipt(size_t id) {
    model.deleteReceipt(id);
    view->deleteReceipt(id);
    if (model.isEmpty()) {
        view->enableHistoryButtons(false);
    }
}

bool HistoryController::saveHistory() const {

    QFile saveFile("save.json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject receiptsObject;
    model.write(receiptsObject);

    // test
    QJsonDocument doc(receiptsObject);
    qDebug() << doc.toJson(QJsonDocument::Compact);

    QJsonDocument saveDoc(receiptsObject);
    saveFile.write(saveDoc.toJson());

    return true;
}

bool HistoryController::loadHistory() {

    QFile loadFile("save.json");

    if (!loadFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    History history;
    history.read(loadDoc.object());
    auto receipts = history.getMReceipts();

    model.clear();
    view->reset();

    for (const auto& receiptPair: receipts) {
        addReceipt(receiptPair.second);
    }

    return true;
}
