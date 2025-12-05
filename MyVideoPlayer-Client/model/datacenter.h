#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>

namespace model
{

    class DataCenter : public QObject
    {
        Q_OBJECT
    public:
        static DataCenter *getInstance(); // 获取 DataCenter 对象实例
    private:
        explicit DataCenter(QObject *parent = nullptr);

    private:
        static DataCenter *instance;
    };

} // end model

#endif // DATACENTER_H
