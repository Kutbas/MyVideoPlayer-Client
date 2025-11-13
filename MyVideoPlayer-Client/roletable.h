#ifndef ROLETABLE_H
#define ROLETABLE_H

#include <QWidget>
#include "paginator.h"

namespace Ui
{
    class RoleTable;
}

class RoleTable : public QWidget
{
    Q_OBJECT

public:
    explicit RoleTable(QWidget *parent = nullptr);
    ~RoleTable();

private:
    void initStyle();
    void updateRoleTable();

private slots:
    void onResetBtnClicked();
    void onQueryBtnClicked();
    void onInsertBtnClicked();

private:
    Ui::RoleTable *ui;
    // key：是否选中 value：样式
    QMap<QString, QString> styleSheet;
    Paginator *paginator;
};

#endif // ROLETABLE_H
