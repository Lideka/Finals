#include "Database.h"

Database::Database(std::string DatabaseFilePath)
{
   qDebug() << "Initializing database...";

   m_Database = QSqlDatabase::addDatabase("QSQLITE");
   m_Database.setDatabaseName(DatabaseFilePath.c_str());

   if(m_Database.open())
   {
      qDebug() << "Database found successfuly!";
      m_Database.close();
   }
   else
      qDebug() << "!Database wasn't found!";
}

void Database::Open()
{
   assert(m_Database.open());
}

void Database::Close()
{
   m_Database.close();
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

   std::string QuerryString = "SELECT " + Tabs + " FROM " + Table; //Formulate the querry and execute it

   QSqlQuery query(m_Database);
   if(!query.exec(QuerryString.c_str())) //Exit, if an error occurs
   {
      qDebug() << "! ExecuteSelectQuerry querry execution failed: " << query.lastError();

      return {};
   }

   //Collect the data received
   while (query.next()) //Go to the second line
   {
      QVariantList temp;

      for(int i = 0; i < TabCount; i++)
         temp.push_back(query.value(i));

      retval.push_back(temp);
   }

   return retval;
}

bool Database::ExecuteInsertQuerry(std::string Table, std::string Tabs, std::string Values)
{
   //Check the provided info
   if(Table.empty() || Tabs.empty() || Values.empty())
   {
      qDebug() << "! ExecuteInsertQuerry empty variable passed.";

      return {};
   }

   std::string QuerryString = "INSERT INTO " + Table + " (" + Tabs + ") VALUES (" + Values + ")";
   QSqlQuery query;
   if(!query.exec(QuerryString.c_str()))
   {
      qDebug() << "! ExecuteSelectQuerry querry: " << QuerryString.c_str() << " execution failed";

      return false;
   }

   return true;
}
