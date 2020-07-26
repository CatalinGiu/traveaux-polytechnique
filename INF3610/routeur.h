#include <ucos_ii.h>
#include <stdlib.h>
#include <inttypes.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define TASK_STK_SIZE 8192

/* ************************************************
 *                TASK PRIOS
 **************************************************/

#define          TASK_GENERATE_PRIO        11
#define 		 TASK_STOP_PRIO            8
#define 		 TASK_RESET_PRIO           9
#define			 TASK_STATS_PRIO		   16
#define          TASK_COMPUTING_PRIO       15
#define          TASK_FORWARDING_PRIO      17
#define          TASK_PRINT1_PRIO          12
#define          TASK_PRINT2_PRIO          13
#define          TASK_PRINT3_PRIO          14

// Routing info.
#define INT1_LOW      0x00000000
#define INT1_HIGH     0x3FFFFFFF
#define INT2_LOW      0x40000000
#define INT2_HIGH     0x7FFFFFFF
#define INT3_LOW      0x80000000
#define INT3_HIGH     0xBFFFFFFF
#define INT_BC_LOW    0xC0000000
#define INT_BC_HIGH   0xFFFFFFFF

// Reject source info.
#define REJECT_LOW1   0x10000000
#define REJECT_HIGH1  0x17FFFFFF
#define REJECT_LOW2   0x50000000
#define REJECT_HIGH2  0x57FFFFFF
#define REJECT_LOW3   0x60000000
#define REJECT_HIGH3  0x67FFFFFF
#define REJECT_LOW4   0xD0000000
#define REJECT_HIGH4  0xD7FFFFFF

typedef enum {
	PACKET_VIDEO,
	PACKET_AUDIO,
	PACKET_AUTRE,
	NB_PACKET_TYPE
} PACKET_TYPE;

typedef struct {
    unsigned int src;
    unsigned int dst;
    PACKET_TYPE type;
    unsigned int data[13];
} Packet;

typedef struct {
    unsigned int interfaceID;
    OS_EVENT *Mbox;
} PRINT_PARAM;

/* ************************************************
 *              TASK PROTOTYPES
 **************************************************/

void TaskGeneratePacket(void *data); // Function prototypes of tasks
void TaskStats(void *data);
void TaskStop(void *data);
void TaskReset(void *data);
void TaskComputing(void *data);
void TaskForwarding(void *data);
void TaskVerify(void *data);
void TaskPrint(void *data);


void create_application();
int create_tasks();
int create_events();
void err_msg(char* ,uint8_t);
void dispatch(Packet *);
