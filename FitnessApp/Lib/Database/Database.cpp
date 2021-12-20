#include "Database.h"

Database* GlobalDatabase = nullptr;

Database::Database(std::string DatabaseFilePath)
{
   qDebug() << "Initializing database..." << DatabaseFilePath.c_str();

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


bool Database::ExecuteCustomQuerry(std::string Querry, QList<QVariantList> *resultArray, int TabCount)
{
   QSqlQuery query(m_Database);
   if(!query.exec(Querry.c_str())) //Exit, if an error occurs
   {
      qDebug() << "! Database::ExecuteCustomQuerry querry execution failed: " << query.lastError();

      return false;
   }

   //If location to save result were provided, handle results
   if(resultArray != nullptr)
   {
      //Collect the data received
      while (query.next()) //Iterate through each line
      {
         QVariantList temp;

         for(int i = 0; i < TabCount; i++)
            temp.push_back(query.value(i));

         resultArray->push_back(temp);
      }
   }

   return true;
}

QList<QVariantList> Database::ExecuteSelectQuerry(std::string Table, std::string Tabs, std::string Where)
{
   //Check the provided info
   if(Table.empty() || Tabs.empty())
   {
#ifdef QT_DEBUG
      qDebug() << "! Database::ExecuteSelectQuerry empty variable passed.";
#endif

      return {};
   }

   int TabCount = 1; //If string not empty, atleast one word is present
   QList<QVariantList> retval = {};

   for(size_t i = 0; i < Tabs.size(); i++)
      if(Tabs.at(i) == ' ')
         TabCount++;

   std::string QuerryString = "SELECT " + Tabs + " FROM " + Table; //Formulate the querry and execute it

   if(!Where.empty())
   {
      QuerryString += " WHERE " + Where;
   }

   ExecuteCustomQuerry(QuerryString, &retval, TabCount);

   //If ExecuteCustomQuerry() fails, we'll still return an empty list, indicationg an error
   return retval;

}

bool Database::ExecuteInsertQuerry(std::string Table, std::string Tabs, std::string Values)
{
   //Check the provided info
   if(Table.empty() || Tabs.empty() || Values.empty())
   {
      qDebug() << "! Database::ExecuteInsertQuerry empty variable passed.";

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

