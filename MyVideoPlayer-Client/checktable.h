#ifndef CHECKTABLE_H
#define CHECKTABLE_H

#include <QWidget>

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
};

#endif // CHECKTABLE_H
