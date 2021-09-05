#include "ReceiptController.h"

ReceiptController::ReceiptController(ReceiptView *v)
{
    m_view = v;

    connect(m_view, &ReceiptView::deleteItemSignal, this, &ReceiptController::deleteItem);
    connect(m_view, &ReceiptView::saveReceiptSignal, this, &ReceiptController::saveReceipt);
    connect(m_view, &ReceiptView::deleteAllSignal, this, &ReceiptController::reset);
}

void ReceiptController::addItem(const Item &item)
{
    try {
        // add to m_model
        size_t id = m_model.addItem(item);

        // add to m_view
        m_view->addItem(id, QString::fromStdString(item.getSeller()), item.getPrice(), item.getDiscount());


        // update receipt
        updateViewTime(m_model.getTime());
        updateViewSum(m_model.getSum());
    } catch (CRException_badKey &e) {
        m_view->showErrorDialog(e.what());
    }
}

bool ReceiptController::deleteItem(size_t id)
{
    // delete from m_model
    bool modelResult = m_model.removeItem(id);

    if (!modelResult) {
        m_view->showErrorDialog("The delete operation failed.\nRebuilding receipt.");
        Receipt backup = m_model;
        setReceipt(backup);

        return false;
    }

    // delete from view
    bool viewResult = m_view->deleteItem(id);

    if (!viewResult) {
        m_view->showErrorDialog("The delete operation but updating the receipt failed.\nRebuilding receipt.");
        Receipt backup = m_model;
        setReceipt(backup);
    }
    return true;
}

void ReceiptController::setReceipt(const Receipt &receipt)
{
    m_view->reset();
    m_model.clear();

    auto items = receipt.getItems();
    auto time = receipt.getTime();

    try {
        for (const auto &pair: items) {

            Item item = pair.second;

            // add to m_model
            size_t id = m_model.addItem(item);

            // add to m_view
            m_view->addItem(id, QString::fromStdString(item.getSeller()), item.getPrice(), item.getDiscount());
        }

        m_model.setTime(time);
        m_view->setTime(time);
        m_view->setSum(m_model.getSum());
    } catch (CRException_badKey &e) {
        m_view->showErrorDialog(e.what());

        m_model.clear();
        m_view->reset();
    }
}

void ReceiptController::reset()
{
    // reset m_model
    m_model.clear();

    // reset m_view
    m_view->reset();

}






