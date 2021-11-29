/*
 Simple usage example:

   Database db("Database.db");

   db.Open();
   QList<QVariantList> result = db.ExecuteSelectQuerry("Exercises", "Id, Name, Description, Calories");
   db.Close();
   for(QVariantList tab : result)
   {
      for(QVariant record : tab)
         qDebug() << record;
   }

   db.Open();
   db.ExecuteInsertQuerry("Exercises", "Name, Description, Calories", "'vards1', 'aprasyms', 200");
   db.Close();
*/


#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#include <QtSql>
#include <QtDebug>

class Database
{
public:
    Database(std::string DatabaseFilePath);

    void Open();
    void Close();

    bool ExecuteCustomQuerry(std::string Querry, QList<QVariantList> *resultArray = nullptr, int TabCount = 0);

    QList<QVariantList> ExecuteSelectQuerry(std::string Table, std::string Tabs, std::string Where = "");
    bool ExecuteInsertQuerry(std::string Table, std::string Tabs, std::string Values);//Not sure if bool is needed

private:
    QSqlDatabase m_Database;
};

extern Database* GlobalDatabase;

#endif // DATABASE_H
