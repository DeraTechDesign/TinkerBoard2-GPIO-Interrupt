#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sqlite3.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define THRESHOLD 255
static volatile int globalCounter [30] ;
static volatile int globalDebounceFlag [30] ;
int pins[14] = {1,4,5,6,11,26,28,29,2,3,21,22,23,24};
int pinsReverse[30] = {0,0,8,9,1,2,3,0,0,0,0,4,0,0,0,0,0,0,0,0,0,10,11,12,13,0,5,0,6,7};



void debounce(int pin,int count,int threshold);
/*
 * myInterrupt:
 *********************************************************************************
 */
void myInterrupt0 (void) { if(globalDebounceFlag[pins[0]] ==0){globalDebounceFlag[pins[0]] = 1; debounce(pins[0],10,THRESHOLD);} }
void myInterrupt1 (void) { if(globalDebounceFlag[pins[1]] ==0){globalDebounceFlag[pins[1]] = 1; debounce(pins[1],10,THRESHOLD);} }
void myInterrupt2 (void) { if(globalDebounceFlag[pins[2]] ==0){globalDebounceFlag[pins[2]] = 1; debounce(pins[2],10,THRESHOLD);} }
void myInterrupt3 (void) { if(globalDebounceFlag[pins[3]] ==0){globalDebounceFlag[pins[3]] = 1; debounce(pins[3],10,THRESHOLD);} }
void myInterrupt4 (void) { if(globalDebounceFlag[pins[4]] ==0){globalDebounceFlag[pins[4]] = 1; debounce(pins[4],10,THRESHOLD);} }
void myInterrupt5 (void) { if(globalDebounceFlag[pins[5]] ==0){globalDebounceFlag[pins[5]] = 1; debounce(pins[5],10,THRESHOLD);} }
void myInterrupt6 (void) { if(globalDebounceFlag[pins[6]] ==0){globalDebounceFlag[pins[6]] = 1; debounce(pins[6],10,THRESHOLD);} }
void myInterrupt7 (void) { if(globalDebounceFlag[pins[7]] ==0){globalDebounceFlag[pins[7]] = 1; debounce(pins[7],10,THRESHOLD);} }
void myInterrupt8 (void) { if(globalDebounceFlag[pins[8]] ==0){globalDebounceFlag[pins[8]] = 1; debounce(pins[8],10,THRESHOLD);} }
void myInterrupt9 (void) { if(globalDebounceFlag[pins[9]] ==0){globalDebounceFlag[pins[9]] = 1; debounce(pins[9],10,THRESHOLD);} }
void myInterrupt10(void) { if(globalDebounceFlag[pins[10]] ==0){globalDebounceFlag[pins[10]] = 1; debounce(pins[10],10,THRESHOLD);} }
void myInterrupt11(void) { if(globalDebounceFlag[pins[11]] ==0){globalDebounceFlag[pins[11]] = 1; debounce(pins[11],10,THRESHOLD);} }
void myInterrupt12(void) { if(globalDebounceFlag[pins[12]] ==0){globalDebounceFlag[pins[12]] = 1; debounce(pins[12],10,THRESHOLD);} }
void myInterrupt13(void) { if(globalDebounceFlag[pins[13]] ==0){globalDebounceFlag[pins[13]] = 1; debounce(pins[13],10,THRESHOLD);} }
// void myInterrupt14(void) { if(globalDebounceFlag[pins[14] ==0){globalDebounceFlag[pins[14] = 1; debounce(14,10,THRESHOLD);} }
// void myInterrupt15(void) { if(globalDebounceFlag[pins[15] ==0){globalDebounceFlag[pins[15] = 1; debounce(15,10,THRESHOLD);} }
// void myInterrupt16(void) { if(globalDebounceFlag[pins[16] ==0){globalDebounceFlag[pins[16] = 1; debounce(16,10,THRESHOLD);} }
// void myInterrupt17(void) { if(globalDebounceFlag[pins[17] ==0){globalDebounceFlag[pins[17] = 1; debounce(17,10,THRESHOLD);} }
// void myInterrupt18(void) { if(globalDebounceFlag[pins[18] ==0){globalDebounceFlag[pins[18] = 1; debounce(18,10,THRESHOLD);} }
// void myInterrupt19(void) { if(globalDebounceFlag[pins[19] ==0){globalDebounceFlag[pins[19] = 1; debounce(19,10,THRESHOLD);} }
// void myInterrupt20(void) { if(globalDebounceFlag[pins[20] ==0){globalDebounceFlag[pins[20] = 1; debounce(20,10,THRESHOLD);} }
// void myInterrupt21(void) { if(globalDebounceFlag[pins[21] ==0){globalDebounceFlag[pins[21] = 1; debounce(21,10,THRESHOLD);} }
// void myInterrupt22(void) { if(globalDebounceFlag[pins[22] ==0){globalDebounceFlag[pins[22] = 1; debounce(22,10,THRESHOLD);} }
// void myInterrupt23(void) { if(globalDebounceFlag[pins[23] ==0){globalDebounceFlag[pins[23] = 1; debounce(23,10,THRESHOLD);} }
// void myInterrupt24(void) { if(globalDebounceFlag[pins[24] ==0){globalDebounceFlag[pins[24] = 1; debounce(24,10,THRESHOLD);} }
// void myInterrupt25(void) { if(globalDebounceFlag[pins[25] ==0){globalDebounceFlag[pins[25] = 1; debounce(25,10,THRESHOLD);} }
// void myInterrupt26(void) { if(globalDebounceFlag[pins[26] ==0){globalDebounceFlag[pins[26] = 1; debounce(26,10,THRESHOLD);} }
// void myInterrupt27(void) { if(globalDebounceFlag[pins[27] ==0){globalDebounceFlag[pins[27] = 1; debounce(27,10,THRESHOLD);} }
// void myInterrupt28(void) { if(globalDebounceFlag[pins[28] ==0){globalDebounceFlag[pins[28] = 1; debounce(28,10,THRESHOLD);} }
// void myInterrupt29(void) { if(globalDebounceFlag[pins[29] ==0){globalDebounceFlag[pins[29] = 1; debounce(29,10,THRESHOLD);} }
typedef int (*f)(void);
f myInterrupts[14] = {&myInterrupt0,&myInterrupt1,&myInterrupt2,&myInterrupt3,&myInterrupt4,&myInterrupt5,&myInterrupt6,&myInterrupt7,&myInterrupt8,&myInterrupt9,&myInterrupt10,&myInterrupt11,&myInterrupt12,&myInterrupt13};
//recursive function to debounce GPIO interrupts, called by myInterrupt
void debounce(int pin,int count,int threshold){
    if(globalDebounceFlag[pin] == 1){
    
        if (count >0 && count <threshold){
            delay(0.5);
            if(digitalRead(pin) ==1){
                debounce(pin,count+1,threshold);
            }else{
                debounce(pin,count-1,threshold);
            }
        }else if (count == threshold){
            globalDebounceFlag[pin] = 0;
            globalCounter[pin]++;
        }else if (count == 0){
            delay(2);
            globalDebounceFlag[pin] = 0;
        }
    }else{
        printf("debounce error\n");
    }
}

// //Listen for http Post requests from nodeJS server on port 5000. If a reset request is received, reset the counter for the specified pin and respond to request with ok. request body should be in the form of {"pin":pinNumber,"reset":1}.
// void *httpListener(void *arg){
//     int server_fd, new_socket, valread;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);
//     char buffer[1024] = {0};
//     char *hello = "ok";
//     // Creating socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//     {
//         perror("socket failed");
//         exit(EXIT_FAILURE);
//     }
//     // Forcefully attaching socket to the port 5000
//     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                                                   &opt, sizeof(opt)))
//     {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons( 5000 );
//     // Forcefully attaching socket to the port 5000
//     if (bind(server_fd, (struct sockaddr *)&address,
//                                  sizeof(address))<0)
//     {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }
//     if (listen(server_fd, 3) < 0)
//     {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }
//     if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
//                        (socklen_t*)&addrlen))<0)
//     {
//         perror("accept");
//         exit(EXIT_FAILURE);
//     }
//     printf("http listener started\n");
//     valread = read( new_socket , buffer, 1024);
//     printf("%s %d",buffer,valread);
//     if(valread >0){
//         char *pin = strstr(buffer,"pin");
//         char *reset = strstr(buffer,"reset");
//         if(pin != NULL && reset != NULL){
//             int pinNumber = atoi(pin+5);
//             int resetValue = atoi(reset+7);
//             if(resetValue == 1){
//                 globalCounter[pinNumber] = 0;
//                 printf("reset pin %d",pinNumber);
//             }else printf("reset value %d",resetValue);
//             send(new_socket , hello , strlen(hello) , 0 );
//         }
//         //kill the server
//         httpListener(void *arg);
//         break;
//     }
// }

// //async function to run httpListener in a separate thread. If httpListener returns, restart it.
// void *httpListenerAsync(void *arg){
//     pthread_t thread;
//     pthread_create(&thread, NULL, httpListener, NULL);
//     pthread_detach(thread);
//     return NULL;
// }



/*Read config.json file and set pin modes accordingly. Example config.json file:
{
"pins": [
{
"pin": 1,
"mode": "INPUT"
},
{
"pin": 2,
"mode": "OUTPUT"
}
]
}
*/
void readConfigFile(){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("config.json", "r");
    if (fp == NULL){
        printf("Error opening config file\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Config file opened successfully\n");
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        if(strstr(line, "pin") != NULL){
            printf("Pin found: %s", line);
            int pin = atoi(strstr(line, ":")+1);
            printf("Pin number: %d\n", pin);
            if(strstr(line, "INPUT") != NULL){
                pinMode(pin, INPUT);
                wiringPiISR (pin, INT_EDGE_RISING, myInterrupts[pinsReverse[pin]]);
                printf("Pin %d set to input\n", pin);
            }
            else if(strstr(line, "OUTPUT") != NULL){
                pinMode(pin, OUTPUT);
                printf("Pin %d set to output\n", pin);
            }
        }
    }
    printf("Config file read successfully\n");
    fclose(fp);
    if (line)
        free(line);
}



/*
 * Create Table with pin number (primary) and counter colums and insert 30 empty rows if the rows do not exist:
 *********************************************************************************
 */
int createTable(sqlite3 *db)
{
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sql = "CREATE TABLE IF NOT EXISTS Counters (pin INTEGER PRIMARY KEY, counter INTEGER);";
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }
    sqlite3_stmt *stmt;
    for (int i = 0; i < 14; i++)
    {
        char *sql;
        sql = "INSERT INTO Counters (pin, counter) VALUES (?, ?);";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            return 1;
        }
        sqlite3_bind_int(stmt, 1, pins[i]);
        sqlite3_bind_int(stmt, 2, 0);
        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }
    sqlite3_finalize(stmt);
    return 0;
}
/*
 *********************************************************************************
 * main
 *********************************************************************************
 */

int main (void)
{
    wiringPiSetup ();

    readConfigFile();
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }   
    createTable(db);

    int gotOne, pin ;
    int myCounter [14] ;

    for (pin = 0 ; pin < 14 ; ++pin) {
        //select counter from table
        char *sql;
        sql = "SELECT counter FROM Counters WHERE pin = ?;";
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            return 1;
        }
        sqlite3_bind_int(res, 1, pins[pin]);
        sqlite3_step(res);
        myCounter[pins[pin]] = sqlite3_column_int(res, 0);
        sqlite3_finalize(res);
      globalCounter [pins[pin]] = myCounter [pins[pin]];
      globalDebounceFlag [pins[pin]] = 0 ;
    }

    // for(pin = 0 ; pin < 14 ; ++pin)
    // {
    //     pinMode (pins[pin], INPUT) ;
    //     //pullUpDnControl (pins[pin], PUD_DOWN) ;
    //     wiringPiISR (pins[pin], INT_EDGE_RISING, myInterrupts[pin]) ;
    // }

    char *sql;
    for (;;)
    {
      gotOne = 0 ;
      printf ("Waiting ... ") ; fflush (stdout) ;
      for (;;)
      {
        for (pin = 0 ; pin < 14 ; ++pin)
        {
    	if (globalCounter [pins[pin]] != myCounter [pins[pin]])
    	{
    	  printf (" Int on pin %d: Counter: %5d\n", pin, globalCounter [pins[pin]]) ;
    	  myCounter [pins[pin]] = globalCounter [pins[pin]] ;
    	  ++gotOne ;
          sql = "UPDATE Counters SET counter = ? WHERE pin = ?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
                return 1;
            }
            sqlite3_bind_int(res, 1, globalCounter [pins[pin]]);
            sqlite3_bind_int(res, 2, pins[pin]);
            sqlite3_step(res);
            sqlite3_reset(res);
    	}
        }
        if (gotOne != 0){
          sqlite3_finalize(res);
          break ;
        }
      }
    }
    sqlite3_close(db);
   
   return 0 ;
}  
   