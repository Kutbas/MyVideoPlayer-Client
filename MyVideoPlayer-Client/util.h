#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QFileInfo>
#include <QDebug>

// 从文件路径中提取文件名
inline QString getFileName(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.fileName();
}

// 封装日志宏
#define TAG QString("[%1:%2]").arg(getFileName(__FILE__), QString::number(__LINE__))
#define LOG() qDebug().noquote() << TAG

#endif // UTIL_H
