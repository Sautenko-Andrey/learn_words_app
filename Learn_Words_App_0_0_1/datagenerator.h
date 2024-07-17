#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QObject>
#include <QThread>
#include <QSqlQuery>


class DataGenerator : public QObject
{
    Q_OBJECT
public:
    DataGenerator(const QString &request_msg, const QString &path_to_flag,
                  QSqlQuery &query, QObject *parent = nullptr);

    ~DataGenerator();

public slots:

    void dataPrepare();

private:
    QString m_request_msg;
    QString m_path_to_flag;
    QSqlQuery m_query;
};

#endif // DATAGENERATOR_H
