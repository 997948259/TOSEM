#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>

/**
* @params Database ile olan bağlantıyı kurmak için global bir değişken tanımlanır.
*/
sqlite3 *db = NULL;

/**
* @params Database adını bir kere set ederek kullanmamıza yardımcı olan değişkendir.
*/
char* db_name = NULL;


/**
* @brief Veri tabanı adını set etmek için kullanılır
*        Not: Bütün işlemler tamamlanıp programı sonlandırmak gerektiğinde free edilmesi için gerekli fonksiyon çağırılmalıdır.
*
* @return Hata numarasıdır.
*
*/
int set_db_name(char* v_db_name)
{
    db_name = malloc(sizeof(v_db_name));
    if (db_name == NULL)
    {
        fprintf(stdout, "set_db_name - malloc failed.");
        return -1;
    }
    memcpy(db_name,v_db_name,sizeof(v_db_name));
    return 0;
}

/**
* @brief Veri tabanı adını öğrenmek için kullanılır.
*
* @return Char pointer olarak dönüş yapar. 
*
*/
char *get_db_name()
{
    return db_name;
}

/**
* @brief Global olarak tanımlanan ve heap bellekten yer alıp kullanılan yerleri free etmek için kullanılır.
*
* @return Hata numarasıdır.
*
*/
int variable_free()
{
    free(db_name);
    return 0;
}

/**
* @brief Veri tabani baglantisi yapar. Baglantiyi sonlandirmaz.
*
* @return Hata numarasıdır.
*
*/
int db_connection()
{
    int connection_result = sqlite3_open(db_name, &db);

    if( connection_result != SQLITE_OK)
    {
        fprintf(stdout,"Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    else
    {
        fprintf(stdout,"Opened database successfully\n");
        return 0;
    }
}

/**
* @brief String olan verilen sorguları çalıştırır. Sadece INSERT,UPDATE ve DELETE sorguları için kullanılabilir.
*       NOT: Select sorgusu için kullanılmaz.
*
* @return Hata numarasinidir.
*
*/
int sqlite3_query_execute(char* sql_query)
{
    int result;
    char *error_message = NULL;

    fprintf(stdout, "%s\n", sql_query);

    db_connection(db_name);
    result = sqlite3_exec(db, sql_query, 0, 0, &error_message);
    sqlite3_close(db);

    for(;;)
    {
            switch(result)
            {
                case SQLITE_BUSY:
                    fprintf(stdout,"busy, wait 0.1 seconds\n");
                    usleep(100000);
                    // Again Query
                    db_connection(db_name);
                    result = sqlite3_exec(db, sql_query, 0, 0, &error_message);
                    sqlite3_close(db);
                    break;

                case SQLITE_ERROR:
                {
                    fprintf(stdout,"SQL ERROR: %s \n", error_message);
                    sqlite3_free(sql_query);
                    sqlite3_free(error_message);
                    return -1;
                }

                case SQLITE_OK:
                {
                    sqlite3_free(sql_query);
                    return 0;
                }

                case SQLITE_FULL: // 13   /* Insertion failed because database is full */
                    break;
            }
    }
    return 0;
}

/**
* @brief SQL DELETE Query için özel olarak tanımlanmış bir fonksiyondur. Gerekli olan "Query String"i yazmaktan kurtarır.
*
* @return Hata numarasıdır.
*
*/
int sqlite3_query_execute_delete_table(char* table_name, int id)
{
    int result;
    char *error_message = NULL;

    char *sql_query = sqlite3_mprintf("DELETE FROM %q WHERE id=%d", table_name, id);

    fprintf(stdout, "%s\n", sql_query);

    db_connection(db_name);
    result = sqlite3_exec(db, sql_query, 0, 0, &error_message);
    sqlite3_close(db);

    for(;;)
    {
            switch(result)
            {
                case SQLITE_BUSY:
                    fprintf(stdout,"busy, wait 0.1 seconds\n");
                    usleep(100000);
                    // Again Query
                    db_connection(db_name);
                    result = sqlite3_exec(db, sql_query, 0, 0, &error_message);
                    sqlite3_close(db);
                    break;

                case SQLITE_ERROR:
                {
                    fprintf(stdout,"SQL ERROR : %s\n", error_message);
                    sqlite3_free(sql_query);
                    sqlite3_free(error_message);
                    return -1;
                }

                case SQLITE_OK:
                {
                    sqlite3_free(sql_query);
                    return 0;
                }

                case SQLITE_FULL: // 13   /* Insertion failed because database is full */
                    break;        
            }
    }
    return 0;
}