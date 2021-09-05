#include "HistoryTab.h"

HistoryTab::HistoryTab(QWidget *parent) {
    setLayout(new QVBoxLayout());
    historyView = new HistoryView();
    layout()->addWidget(historyView);
}
