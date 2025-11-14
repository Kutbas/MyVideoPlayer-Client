#ifndef CHECKTABLE_H
#define CHECKTABLE_H

#include <QWidget>
#include "paginator.h"

namespace Ui
{
    class CheckTable;
}

class CheckTable : public QWidget
{
    Q_OBJECT

public:
    explicit CheckTable(QWidget *parent = nullptr);
    ~CheckTable();

private:
    void updateCheckTable();

private slots:
    void onResetBtnClicked();
    void onQueryBtnClicked();

private:
    Ui::CheckTable *ui;
    Paginator *paginator;
};

#endif // CHECKTABLE_H
