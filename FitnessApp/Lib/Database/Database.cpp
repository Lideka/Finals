#include "Database.h"

Database::Database(std::string DatabaseName)
{
   qDebug() << "Initializing database...";

   QSqlDatabase db;
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName(DatabaseName.c_str());

   if(!db.open())
      qDebug() << "!Database could not be opened!";
   else
      qDebug() << "Database read successfuly!";
}

QList<QVariantList> Database::ExecuteSelectQuerry(std::string Table, std::string Tabs)
{
   //Check the provided info
   if(Table.empty() || Tabs.empty())
   {
#ifdef QT_DEBUG
      qDebug() << "! ExecuteSelectQuerry empty variable passed.";
#endif

      return {};
   }

   int TabCount = 1; //If string not empty, atleast one word is present
   QList<QVariantList> retval;

   for(size_t i = 0; i < Tabs.size(); i++)
      if(Tabs.at(i) == ' ')
         TabCount++;

   //Formulate the querry and execute it
   std::string QuerryString = "SELECT " + Tabs + " FROM " + Table;

   QSqlQuery query;
   if(!query.exec(QuerryString.c_str())) //Exit, if an error occurs
   {
#ifdef QT_DEBUG
      qDebug() << "! ExecuteSelectQuerry querry execution failed";
#endif

      return {};
   }

   //Collect the data received
   while (query.next()) { //Go to the second line
      QVariantList temp;

      for(int i = 0; i < TabCount; i++)
         temp.push_back(query.value(i));

      retval.push_back(temp);
   }

#ifdef QT_DEBUG
   qDebug() << "! ExecuteSelectQuerry returns " << retval.size() << " lines and " << TabCount << " tabs.";
#endif

   return retval;
}

bool Database::ExecuteInsertQuerry(std::string Table, std::string Tabs, std::string Values)
{
   //Check the provided info
   if(Table.empty() || Tabs.empty() || Values.empty())
   {
#ifdef QT_DEBUG
      qDebug() << "! ExecuteInsertQuerry empty variable passed.";
#endif

      return {};
   }

   std::string QuerryString = "INSERT INTO " + Table + " (" + Tabs + ") VALUES (" + Values + ")";
   QSqlQuery query;
   if(!query.exec(QuerryString.c_str()))
   {
#ifdef QT_DEBUG
      qDebug() << "! ExecuteSelectQuerry querry: " << QuerryString.c_str() << " execution failed";
#endif

      return false;
   }

   return true;
}
