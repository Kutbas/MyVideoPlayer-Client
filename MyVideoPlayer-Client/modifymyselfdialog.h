#ifndef MODIFYMYSELFDIALOG_H
#define MODIFYMYSELFDIALOG_H

#include <QWidget>

namespace Ui {
class ModifyMyselfDialog;
}

class ModifyMyselfDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyMyselfDialog(QWidget *parent = nullptr);
    ~ModifyMyselfDialog();

private:
    Ui::ModifyMyselfDialog *ui;
};

#endif // MODIFYMYSELFDIALOG_H
