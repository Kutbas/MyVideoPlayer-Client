#include "datacenter.h"

namespace model
{
    DataCenter DataCenter::*instance = nullptr;

    DataCenter *DataCenter::getInstance()
    {
        if (nullptr == instance)
            instance = new DataCenter();

        return instance;
    }

    DataCenter::DataCenter(QObject *parent)
        : QObject{parent}
    {
    }

} // end model
