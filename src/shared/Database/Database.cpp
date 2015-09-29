/****************************************************************************
 *
 * General Object Type File
 *
 */

#include "DatabaseEnv.h"

Database* Database::CreateDatabaseInterface()
{
#ifdef DATABASE_SUPPORT_MYSQL
    return new MySQLDatabase();
#endif
}

void Database::CleanupLibs()
{
#ifdef DATABASE_SUPPORT_MYSQL
    mysql_library_end();
#endif
}

QueryResult::QueryResult(uint32 FieldCount, uint32 RowCount, uint32 Type)
{
    mCurrentRow = new Field[FieldCount];
    mRowCount = RowCount;
    mFieldCount = FieldCount;
    mType = Type;
}

QueryResult::~QueryResult()
{
    delete [] mCurrentRow;
    switch(mType)
    {

#ifdef DATABASE_SUPPORT_MYSQL

    case DATABASE_TYPE_MYSQL:
        ((MySQLQueryResult*)this)->Destroy();
        break;

#endif

#ifdef DATABASE_SUPPORT_PGSQL

    case DATABASE_TYPE_PGSQL:
        ((PostgreQueryResult*)this)->Destroy();
        break;

#endif

    default:
        assert(false);
        break;
    }
}
