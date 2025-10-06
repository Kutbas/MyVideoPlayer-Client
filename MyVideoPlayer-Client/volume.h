#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>

namespace Ui {
class Volume;
}

class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();

private:
    bool eventFilter(QObject* watched,QEvent* event);
    void calcVolume();

private:
    Ui::Volume *ui;
};

#endif // VOLUME_H
