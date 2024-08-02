// FTP Client ActiveX Control
// (C) Copyright 1995 - 1997 by Distinct Corporation
// All rights reserved

// actions
#define ACTION_NONE                0
#define ACTION_ABORT               1
#define ACTION_CONNECT             2
#define ACTION_DISCONNECT          3
#define ACTION_FW_CONNECT          4
#define ACTION_CANCEL              5

#define FILE_ACTION_NONE           0
#define FILE_ACTION_ABORT          1
#define FILE_ACTION_DELETE         2
#define FILE_ACTION_GET            3
#define FILE_ACTION_PUT            4
#define FILE_ACTION_RENAME         5
#define FILE_ACTION_APPEND         6
#define FILE_ACTION_REMOTE         7
#define FILE_ACTION_REMOTE_APPEND  8
#define FILE_ACTION_PUT_UNIQUE     9

#define DIR_ACTION_NONE            0
#define DIR_ACTION_ABORT           1
#define DIR_ACTION_CHANGE          2
#define DIR_ACTION_CREATE          3
#define DIR_ACTION_DELETE          4
#define DIR_ACTION_LIST            5
#define DIR_ACTION_PARENT          6
#define DIR_ACTION_RENAME          7

// modes
#define TRANSFER_TYPE_ASCII        0
#define TRANSFER_TYPE_BINARY       1

#define TRANSFER_MODE_FILE         0
#define TRANSFER_MODE_EVENT        1

#define LIST_TYPE_SHORT            0
#define LIST_TYPE_LONG             1

// proxy type enum constants
#define PROXY_TYPE_NONE         0
#define PROXY_TYPE_HTTP         1

// transmission mode enum constants
#define TRANSMISSION_MODE_STREAM 0
#define TRANSMISSION_MODE_BLOCK  1

// result
#define FTP_OK                     0
#define FTP_ERROR                  1
#define FTP_CONN_CLOSED            3
#define FTP_NO_ENTRY              -1
#define FTP_BAD_FILE_TYPE         -2
#define FTP_NOT_CONNECTED         -3
#define FTP_BAD_ARGUMENT          -4
#define FTP_BAD_COMMAND           -5
#define FTP_FILE_ERROR            -6
#define FTP_DATA_CONN_ERR         -7
#define FTP_ACCEPT_ERR            -8
#define FTP_REPLY_TIMEOUT         -10
#define FTP_ACCEPT_TIMEOUT        -11
#define FTP_SEND_TIMEOUT          -12
#define FTP_CANCELLED             -13
#define FTP_BUSY                  -14
#define FTP_DATA_TIMEOUT          -15
#define FTP_PASSIVE_FAILED        -16
#define FTP_CONNECT_ERR           -17
#define FTP_FIREWALL_ERR          -18

// error codes
#define ERR_CANNOT_CHANGE_XFER_TYPE     1
#define ERR_CANNOT_CHANGE_XFER_MODE     2
#define ERR_CANNOT_CHANGE_LIST_TYPE     3
#define ERR_CANNOT_CHANGE_PORT          4
#define ERR_PORT_UNDEFINED              5
#define ERR_HOST_UNDEFINED              6
#define ERR_IN_TRANSFER                 7
#define ERR_CANNOT_CONNECT              8
#define ERR_NEED_ACCOUNT                9
#define ERR_CANNOT_LOG_IN               10
#define ERR_NOT_CONNECTED               11
#define ERR_IN_ACTION                   12
#define ERR_NO_DIR_TARGET               13
#define ERR_NO_NEW_DIR_NAME             14
#define ERR_NO_FILE_TARGET              15
#define ERR_NO_NEW_FILE_NAME            16
#define ERR_NO_REMOTE_FILE              17
#define ERR_NO_LOCAL_FILE               18
#define ERR_CANNOT_OPEN_LOCAL_FILE      19
#define ERR_UNABLE_TO_LOAD              20
#define ERR_FW_SERVER_NOT_DEFINED       21
#define ERR_CANNOT_CHANGE_PROXY_TYPE         22
#define ERR_CANNOT_CHANGE_TRANSMISSION_MODE  23
#define ERR_NO_LOCAL_DIR                     24
#define ERR_CANNOT_CREATE_MARKER_FILE        25
#define ERR_CANNOT_CHANGE_HOST_TYPE          26
#define ERR_CANNOT_CHANGE_BLOCK_SIZE         27
#define ERR_CANNOT_CHANGE_MARKER_FREQUENCY   28
#define ERR_CANNOT_CHANGE_RETRY_COUNT        29
#define ERR_NO_LIST_LINE                     30

// server types 
#define SERVER_AUTODETECT   0
#define SERVER_UNIX         1
#define SERVER_ULTRIX       2
#define SERVER_VMS_UCX      3
#define SERVER_DISTINCT     4
#define SERVER_FTP_DOS      5
#define SERVER_DOS          6
#define SERVER_IBM_VM       7
#define SERVER_IBM_AIX      8
#define SERVER_VMS_MULTINET 9
#define SERVER_VMS_FUSION   10
#define SERVER_VMS_WGONG    11
#define SERVER_VMS_UCX_2    12
#define SERVER_IBM_MVS_2    13
#define SERVER_IBM_MVS_3    14
#define SERVER_IBM_OS2      15
#define SERVER_VMS_PROCESS  16
#define SERVER_IBM_AS_400   17
#define SERVER_IBM_MVS_4    18
#define SERVER_IBM_AS_400_3 19
#define SERVER_WINDOWS_NT   20
