#ifndef ROLETABLEITEM_H
#define ROLETABLEITEM_H

#include <QWidget>

namespace Ui
{
    class RoleTableItem;
}

class RoleTableItem : public QWidget
{
    Q_OBJECT

public:
    explicit RoleTableItem(QWidget *parent = nullptr, int seqNumber = 0);
    ~RoleTableItem();

private:
    void updateUI(int seqNumber);

private slots:
    void onEditBtnClicked();

private:
    Ui::RoleTableItem *ui;
};

#endif // ROLETABLEITEM_H
