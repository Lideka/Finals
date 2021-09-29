#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#include <QtSql>
#include <QtDebug>

class Database
{
public:
    Database(std::string DatabaseName);

    QList<QVariantList> ExecuteSelectQuerry(std::string Table, std::string Tabs);

    //Not sure if bool is needed
    bool ExecuteInsertQuerry(std::string Table, std::string Tabs, std::string Values);
};

#endif // DATABASE_H
