#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>
#include "data.h"

namespace model
{

    class DataCenter : public QObject
    {
        Q_OBJECT
    public:
        ~DataCenter();
        static DataCenter *getInstance(); // 获取 DataCenter 对象实例

        const KindAndTag *getKindAndTagClassPtr();

    private:
        explicit DataCenter(QObject *parent = nullptr);

    private:
        static DataCenter *instance;
        KindAndTag *kindAndTag = nullptr;
    };

} // end model

#endif // DATACENTER_H
