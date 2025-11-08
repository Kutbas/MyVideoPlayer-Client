#ifndef ROLETABLE_H
#define ROLETABLE_H

#include <QWidget>

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

private:
    Ui::RoleTable *ui;
    // key：是否选中 value：样式
    QMap<QString, QString> styleSheet;
};

#endif // ROLETABLE_H
