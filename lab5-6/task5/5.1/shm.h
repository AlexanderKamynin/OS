#define DEF_KEY_FILE "key.txt"
#include <sys/sem.h>


typedef struct {
    long type;
    char buf[100];
} Message;


/* semop():
    short    sem_num    Номер семафора в диапозоне от 0 до (кол-во семафоров - 1)
    short    sem_op     Операция семафора
    short    sem_flg    Флаги операций
*/
static struct sembuf readEnable[1] = {0,-1,0};
static struct sembuf writeEnable[1] = {1,-1,0};
static struct sembuf setReadEnable[1] = {0,1,0};
static struct sembuf setWriteEnable[1] = {1,1,0};

