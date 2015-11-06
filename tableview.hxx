#pragma once

#include <qtableview.h>

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget* p);
};
