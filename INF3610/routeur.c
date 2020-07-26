#include "routeur.h"
#include "bsp_init.h"
#include "platform.h"
#include <stdlib.h>
#include <stdbool.h>
#include <xil_printf.h>
#include <xgpio.h>

///////////////////////////////////////////////////////////////////////////////////////
//								uC-OS global variables
///////////////////////////////////////////////////////////////////////////////////////
#define TASK_STK_SIZE 8192
PRINT_PARAM print_param[3];

/*DÉCLARATION DES EVENTS*/
/* ************************************************
 *                  Mailbox
 **************************************************/

OS_EVENT *mbox[3];

/* ************************************************
 *                  Queues
 **************************************************/

OS_EVENT *inputQ;
OS_EVENT *lowQ;
OS_EVENT *mediumQ;
OS_EVENT *highQ;

/* ************************************************
 *                  Semaphores
 **************************************************/

/* À compléter */
OS_EVENT *semStop;
OS_EVENT *semReset;
OS_EVENT *semStat;

/* ************************************************
 *                  Mutexes
 **************************************************/
/* À compléter */
OS_EVENT *mutexRejet;
OS_EVENT *mutexPrint;
OS_EVENT *mutexMem;

/*DECLARATION DES COMPTEURS*/
int nbPacketCrees = 0; // Nb de packets total créés
int nbPacketTraites = 0;	// Nb de paquets envoyés sur une interface
int nbPacketSourceRejete = 0; // Nb de packets rejetés pour mauvaise source


///////////////////////////////////////////////////////////////////////////////////////
//								Routines d'interruptions
///////////////////////////////////////////////////////////////////////////////////////

void timer_isr(void* not_valid) {
	if (private_timer_irq_triggered()) {
		private_timer_clear_irq();
		OSTimeTick();
	}
}

void fit_timer_1s_isr(void *not_valid) {
	/* À compléter */
	OSSemPost(semStop);
}

void fit_timer_3s_isr(void *not_valid) {
	/* À compléter */
	OSSemPost(semStat);

}

void gpio_isr(void * not_valid) {
	/* À compléter */
	OSSemPost(semReset);
	XGpio_InterruptClear(&gpSwitch, 0b1);

}

///////////////////////////////////////////////////////////////////////////////////////
//								uC/OS-II part
///////////////////////////////////////////////////////////////////////////////////////
int main() {

	initialize_bsp();

	// Initialize uC/OS-II
	OSInit();

	create_application();

	prepare_and_enable_irq();

	xil_printf("*** Starting uC/OS-II scheduler ***\n");

	OSStart();

	cleanup();
	cleanup_platform();

	return 0;
}

void create_application() {
	int error;

	error = create_events();
	if (error != 0)
		xil_printf("Error %d while creating events\n", error);

	error = create_tasks();
	if (error != 0)
		xil_printf("Error %d while creating tasks\n", error);


}

int create_tasks() {
	// Stacks des tâches
	static OS_STK TaskReceiveStk[TASK_STK_SIZE];
	static OS_STK TaskStopStk[TASK_STK_SIZE];
	static OS_STK TaskResetStk[TASK_STK_SIZE];
	static OS_STK TaskStatsStk[TASK_STK_SIZE];
	static OS_STK TaskComputeStk[TASK_STK_SIZE];
	static OS_STK TaskForwardingStk[TASK_STK_SIZE];
	static OS_STK TaskPrint1Stk[TASK_STK_SIZE];
	static OS_STK TaskPrint2Stk[TASK_STK_SIZE];
	static OS_STK TaskPrint3Stk[TASK_STK_SIZE];
	static OS_STK TaskGenPackageStk[TASK_STK_SIZE];

	/* À compléter */
	uint8_t err;

	err = OSTaskCreate(TaskGeneratePacket, (void*) 0, &TaskGenPackageStk[TASK_STK_SIZE], TASK_GENERATE_PRIO);
	err_msg("erreur dans la creation de la tache Generate Package", err);

	err = OSTaskCreate(TaskComputing, (void*) 0, &TaskComputeStk[TASK_STK_SIZE], TASK_COMPUTING_PRIO);
	err_msg("erreur dans la creation de la tache Computing", err);

	err = OSTaskCreate(TaskForwarding, (void*) 0, &TaskForwardingStk[TASK_STK_SIZE], TASK_FORWARDING_PRIO);
	err_msg("erreur dans la creation de la tache Computing", err);

	print_param[0].Mbox = mbox[0];
	print_param[0].interfaceID = 1;
	err = OSTaskCreate(TaskPrint, &print_param[0], &TaskPrint1Stk[TASK_STK_SIZE], TASK_PRINT1_PRIO);
	err_msg("erreur dans la creation de la tache print1", err);

	print_param[1].Mbox = mbox[1];
	print_param[1].interfaceID = 2;
	err = OSTaskCreate(TaskPrint, &print_param[1], &TaskPrint2Stk[TASK_STK_SIZE], TASK_PRINT2_PRIO);
	err_msg("erreur dans la creation de la tache print2", err);

	print_param[2].Mbox = mbox[2];
	print_param[2].interfaceID = 3;
	err = OSTaskCreate(TaskPrint, &print_param[2], &TaskPrint3Stk[TASK_STK_SIZE], TASK_PRINT3_PRIO);
	err_msg("erreur dans la creation de la tache print3", err);

	err = OSTaskCreate(TaskStop, (void*) 0, &TaskStopStk[TASK_STK_SIZE], TASK_STOP_PRIO);
	err_msg("erreur dans la creation de la tache Stop", err);

	err = OSTaskCreate(TaskReset, (void*) 0, &TaskResetStk[TASK_STK_SIZE], TASK_RESET_PRIO);
	err_msg("erreur dans la creation de la tache Stop", err);

	err = OSTaskCreate(TaskStats, (void*) 0, &TaskStatsStk[TASK_STK_SIZE], TASK_STATS_PRIO);
	err_msg("erreur dans la creation de la tache Stats", err);

	return 0;
}

int create_events() {
	uint8_t err;

	// Buffers pour les files
	static void* inputMsg[1024];
	static void* lowMsg[1024];
	static void* mediumMsg[1024];
	static void* highMsg[1024];

	/* À compléter: création des files, mailbox, sémaphores et mutex */

	inputQ = OSQCreate(inputMsg, 1024);
	lowQ = OSQCreate(lowMsg, 1024);
	mediumQ = OSQCreate(mediumMsg, 1024);
	highQ = OSQCreate(highMsg, 1024);

	mbox[0] = OSMboxCreate((void *) 0);
	mbox[1] = OSMboxCreate((void *) 0);
	mbox[2] = OSMboxCreate((void *) 0);

	semStop = OSSemCreate(0);
	semReset = OSSemCreate(0);
	semStat = OSSemCreate(0);

	mutexRejet = OSMutexCreate(5, &err);
	err_msg("erreur mutex reject", err);
	mutexPrint = OSMutexCreate(7, &err);
	err_msg("erreur mutex print", err);
	mutexPrint = OSMutexCreate(4, &err);
	err_msg("erreur mutex print", err);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//								uC/OS-II part
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
//									TASKS
///////////////////////////////////////////////////////////////////////////////////////

/*
 *********************************************************************************************************
 *											  TaskGeneratePacket
 *  - Génère des paquets et les envoie dans la InputQ.
 *  - À des fins de développement de votre application, vous pouvez *temporairement* modifier la variable
 *    "shouldSlowthingsDown" à true pour ne générer que quelques paquets par seconde, et ainsi pouvoir
 *    déboguer le flot de vos paquets de manière plus saine d'esprit. Cependant, la correction sera effectuée
 *    avec cette variable à false.
 *********************************************************************************************************
 */
void TaskGeneratePacket(void *data) {
	srand(42);
	uint8_t err;
	bool isGenPhase = true; 		//Indique si on est dans la phase de generation ou non
	const bool shouldSlowThingsDown = false;		//Variable à modifier
	int packGenQty = (rand() % 250);
	while(true) {
		if (isGenPhase) {

			OSMutexPend(mutexMem, 0, &err);
			Packet *packet = malloc(sizeof(Packet));
			OSMutexPost(mutexMem);

			packet->src = rand() * (UINT32_MAX/RAND_MAX);
			packet->dst = rand() * (UINT32_MAX/RAND_MAX);
			packet->type = rand() % NB_PACKET_TYPE;

			for (int i = 0; i < ARRAY_SIZE(packet->data); ++i)
				packet->data[i] = (unsigned int)rand();
			packet->data[0] = nbPacketCrees;

			nbPacketCrees++;

			if (shouldSlowThingsDown) {
				OSMutexPend(mutexPrint, 0, &err);
				xil_printf("GENERATE : ********Génération du Paquet # %d ******** \n", nbPacketCrees);
				xil_printf("ADD %x \n", packet);
				xil_printf("	** src : %x \n", packet->src);
				xil_printf("	** dst : %x \n", packet->dst);
				xil_printf("	** type : %d \n", packet->type);
				OSMutexPost(mutexPrint);
			}

			err = OSQPost(inputQ,  packet);

			if (err == OS_ERR_Q_FULL) {
				OSMutexPend(mutexPrint, 0, &err);
				xil_printf("GENERATE: Paquet rejeté a l'entrée car la FIFO est pleine !\n");
				OSMutexPost(mutexPrint);

				OSMutexPend(mutexMem, 0, &err);
				free(packet);
				OSMutexPost(mutexMem);

			}

			if (shouldSlowThingsDown) {
				OSTimeDlyHMSM(0,0,0, 200 + rand() % 600);
			} else {
				OSTimeDlyHMSM(0, 0, 0, 2);

				if ((nbPacketCrees % packGenQty) == 0) //On genère jusqu'à 250 paquets par phase de géneration
				{
					isGenPhase = false;
				}
			}
		}
		else
		{
			OSTimeDlyHMSM(0, 0, 0, 500);
			isGenPhase = true;
			packGenQty = (rand() % 250);
			OSMutexPend(mutexPrint, 0, &err);
			xil_printf("GENERATE: Génération de %d paquets durant les %d prochaines millisecondes\n", packGenQty, packGenQty*2);
			OSMutexPost(mutexPrint);
		}
	}
}

/*
 *********************************************************************************************************
 *											  TaskStop
 *  -Stoppe le routeur une fois que 100 paquets ont été rejetés pour mauvais CRC
 *  -Ne doit pas stopper la tâche d'affichage des statistiques.
 *********************************************************************************************************
 */
void TaskStop(void *data) {
	uint8_t err;
	while(true) {
		/* À compléter */
		OSSemPend(semStop, 0, &err);
		OSMutexPend(mutexRejet, 0, &err);
		err_msg("Failed to pend mutex in TaskStop", err);
		if (nbPacketSourceRejete >= 10)
		{
			err = OSTaskSuspend(TASK_GENERATE_PRIO);
			err_msg("Failed to suspend", err);

			err = OSTaskSuspend(TASK_PRINT1_PRIO);
			err_msg("Failed to suspend", err);

			err = OSTaskSuspend(TASK_PRINT2_PRIO);
			err_msg("Failed to suspend", err);

			err = OSTaskSuspend(TASK_PRINT3_PRIO);
			err_msg("Failed to suspend", err);

			err = OSTaskSuspend(TASK_COMPUTING_PRIO);
			err_msg("Failed to suspend", err);

			err = OSTaskSuspend(TASK_FORWARDING_PRIO);
			err_msg("Failed to suspend", err);
		}
		err = OSMutexPost(mutexRejet);
		err_msg("Failed to post mutexRejet in TaskStop", err);

	}
}

/*
 *********************************************************************************************************
 *											  TaskReset
 *  -Remet le compteur de mauvaises sources à 0
 *  -Si le routeur était arrêté, le redémarre
 *********************************************************************************************************
 */
void TaskReset(void *data) {
	uint8_t err;
	while(true) {
		/* À compléter */
		OSSemPend(semReset, 0, &err);
		OSMutexPend(mutexRejet, 0, &err);
		nbPacketSourceRejete = 0;
		OSMutexPost(mutexRejet);

		err_msg("Failed to post mutexRejet in TaskStop", err);

		err = OSTaskResume(TASK_GENERATE_PRIO);
		err_msg("Failed to suspend", err);

		err = OSTaskResume(TASK_PRINT1_PRIO);
		err_msg("Failed to suspend", err);

		err = OSTaskResume(TASK_PRINT2_PRIO);
		err_msg("Failed to suspend", err);

		err = OSTaskResume(TASK_PRINT3_PRIO);
		err_msg("Failed to suspend", err);

		err = OSTaskResume(TASK_COMPUTING_PRIO);
		err_msg("Failed to suspend", err);

		err = OSTaskResume(TASK_FORWARDING_PRIO);
		err_msg("Failed to suspend", err);
	}
}

/*
 *********************************************************************************************************
 *											  TaskComputing
 *  -Vérifie si les paquets sont conformes (CRC,Adresse Source)
 *  -Dispatche les paquets dans des files (HIGH,MEDIUM,LOW)
 *
 *********************************************************************************************************
 */
void TaskComputing(void *pdata) {
	uint8_t err;
	Packet *packet = NULL;
	bool validPacket;
	uint32_t compteur;
	while(true){
		/* À compléter */
		packet = OSQPend(inputQ, 0, &err);
		validPacket = true;
		compteur = 0;
		err_msg("Task Computing flop", err);

		if ((packet->src >= REJECT_LOW1 && packet->src <= REJECT_HIGH1) ||
			(packet->src >= REJECT_LOW2 && packet->src <= REJECT_HIGH2) ||
			(packet->src >= REJECT_LOW3 && packet->src <= REJECT_HIGH3) ||
			(packet->src >= REJECT_LOW4 && packet->src <= REJECT_HIGH4))
		{
			OSMutexPend(mutexMem, 0, &err);
			free(packet);
			OSMutexPost(mutexMem);
			validPacket = false;
			OSMutexPend(mutexRejet, 0, &err);
			++nbPacketSourceRejete;
			OSMutexPost(mutexRejet);
		}

		if (validPacket)
		{
			switch (packet->type)
			{
				case PACKET_VIDEO:
					err = OSQPost(highQ, packet);
					break;
				case PACKET_AUDIO:
					err = OSQPost(mediumQ, packet);
					break;
				case PACKET_AUTRE:
					err = OSQPost(lowQ, packet);
					break;
				default:
					OSMutexPend(mutexMem, 0, &err);
					free(packet); //Discard le paquet car son type n'est pas défini.
					OSMutexPost(mutexMem);
					break;
			}
			if (err != OS_NO_ERR)
			{
				err_msg("Erreur en placant un paquet dans une queue", err);
				OSMutexPend(mutexMem, 0, &err);
				free(packet);
				OSMutexPost(mutexMem);
			}
		}
		nbPacketTraites++;

		while(compteur++ <= 220000){}

	}
}

/*
 *********************************************************************************************************
 *											  TaskForwarding
 *  -traite la priorité des paquets : si un paquet de haute priorité est prêt,
 *   on l'envoie à l'aide de la fonction dispatch, sinon on regarde les paquets de moins haute priorité
 *********************************************************************************************************
 */
void TaskForwarding(void *pdata) {
	uint8_t err;
	Packet *packet = NULL;
	while(true){
		/* À compléter */
		packet = NULL;
		packet = OSQPend(highQ, 1, &err);
		if ( packet != NULL )
			dispatch(packet);
		else
		{
			packet = OSQPend(mediumQ, 1, &err);
			if ( packet != NULL )
				dispatch(packet);
			else
			{
				packet = OSQPend(lowQ, 1, &err);
				if ( packet != NULL )
					dispatch(packet);

			}
		}
	}
}

void dispatch(Packet *p)
{
	uint8_t err;
	if (p->dst < 1073741823)
	{
		err = OSMboxPost(mbox[0], p);
	}
	else if (p->dst >= 1073741823 && p->dst < 2147483647)
	{
		err = OSMboxPost(mbox[1], p);
	}
	else if (p->dst >= 2147483647 && p->dst < 3221225472 )
	{
		err = OSMboxPost(mbox[2], p);
	}
	else //BROADCAST
	{
		OSMutexPend(mutexMem, 0, &err);
		Packet *copie1 = malloc(sizeof(Packet));
		Packet *copie2 = malloc(sizeof(Packet));
		OSMutexPost(mutexMem);
		*copie1 = *p;
		*copie2 = *p;
		err = OSMboxPost(mbox[0], p);
		err = OSMboxPost(mbox[1], copie1);
		err = OSMboxPost(mbox[2], copie2);
	}

}

/*
 *********************************************************************************************************
 *                                              TaskStats
 *  -Est déclenchée lorsque le gpio_isr() libère le sémaphore
 *  -Lorsque déclenchée, imprime les statistiques du routeur à cet instant
 *********************************************************************************************************
 */
void TaskStats(void *pdata) {
	uint8_t err;

	while(true){
		/* À compléter */
		OSSemPend(semStat, 0, &err);

		xil_printf("\n------------------ Affichage des statistiques ------------------\n");
		xil_printf("Nb de packets total créés : %d\n",nbPacketCrees);
		xil_printf("Nb de packets total traités : %d\n", nbPacketTraites);
		xil_printf("Nb de packets rejetés pour mauvaise source : %d\n",nbPacketSourceRejete);

	}
}

/*
 *********************************************************************************************************
 *											  TaskPrint
 *  -Affiche les infos des paquets arrivés à destination et libere la mémoire allouée
 *********************************************************************************************************
 */
void TaskPrint(void *data) {
	uint8_t err;
	Packet *packet = NULL;
	int intID = ((PRINT_PARAM*)data)->interfaceID;
	OS_EVENT* mb = ((PRINT_PARAM*)data)->Mbox;

	while(true)
	{
		/* À compléter */
		packet = OSMboxPend(mb, 0, &err);
		err_msg("erreur lors de la lecture de la mailbox", err);
		OSMutexPend(mutexPrint, 0, &err);
		xil_printf("Interface: %u | Destination : %x | Source : %x | Type : %u | Data : %u\n",
				intID, packet->dst, packet->src, packet->type, packet->data);
		OSMutexPost(mutexPrint);

		OSMutexPend(mutexMem, 0, &err);
		free(packet);
		OSMutexPost(mutexMem);
	}

}


void err_msg(char* entete, uint8_t err)
{
	if(err != OS_ERR_NONE) {
		OSMutexPend(mutexPrint, 0, &err);
		xil_printf(entete);
		xil_printf(": Une erreur est retournée : code %d \n",err);
		OSMutexPost(mutexPrint);
	}
}
