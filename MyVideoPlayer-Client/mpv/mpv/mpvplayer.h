#ifndef MPVPLAYER_H
#define MPVPLAYER_H

#include <QObject>

class MpvPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MpvPlayer(QObject *parent = nullptr);

signals:
};

#endif // MPVPLAYER_H
