#ifndef ROLETABLE_H
#define ROLETABLE_H

#include <QWidget>

namespace Ui {
class RoleTable;
}

class RoleTable : public QWidget
{
    Q_OBJECT

public:
    explicit RoleTable(QWidget *parent = nullptr);
    ~RoleTable();

private:
    Ui::RoleTable *ui;
};

#endif // ROLETABLE_H
