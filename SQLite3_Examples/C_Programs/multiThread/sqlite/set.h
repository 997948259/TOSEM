#include<windows.h>
#include <stdio.h>
#include "sqlite3.h"

/**  Database define  **/
#define IOPEN_DB_ERROR 1
#define SDB_PATH "./AddressBook.db"
#define STABLE_NAME "users"

#define SC_id  "id"
#define SC_nam "name"
#define SC_sex "sex"
#define SC_add "address"
#define SC_tel "tel"
#define SC_qq  "qq"

/**  Command define  **/
#define ICMD_MIN 1
#define ICMD_ADD 1
#define ICMD_DEL 2
#define ICMD_SCA 3
#define ICMD_FIN 4
#define ICMD_SOR 5
#define ICMD_COUNT 6
#define ICMD_EXIT 7
#define ICMD_MAX 7


