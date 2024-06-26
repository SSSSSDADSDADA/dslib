//
// Created by alfylinux on 21/10/18.
//

#include "common.h"


int semInit()
{
	int semId = semget(IPC_PRIVATE,3, IPC_CREAT | IPC_EXCL | 0666);
	
	//enum semName {wantWrite=0,readWorking=1,writeWorking=2}; number is Id of sem
	unsigned short semStartVal[3] = {0, 0, 1};

	semInfo(semId);

	return semId;
}

int lockWriteSem(int semId)
{
	struct sembuf sem;
	sem.sem_flg = SEM_UNDO;

	//increase counter wantWrite
	sem.sem_num = wantWrite;
	sem.sem_op = +1;
	SEM_wantWrite:
	if (semop(semId, &sem, 1))
	{
		switch (errno)
		{
			case EINTR:
				goto SEM_wantWrite;
				break;
			default:
				perror("increase wantWrite semCount error:");
				return -1;
				break;
		}
	}

	//wait until =0 readerWork
	sem.sem_num = readWorking;
	sem.sem_op = 0;

	//wait noThread already work
	sem.sem_num = writeWorking;
	sem.sem_op = -1;

	return 0;
}

int unlockWriteSem(int semId)
{
	struct sembuf sem;
	sem.sem_flg = SEM_UNDO;

	//signal finish writing work
	sem.sem_num = writeWorking;
	sem.sem_op = 1;

	SEM_writeWorking:
	if (semop(semId, &sem, 1))
	{
		switch (errno)
		{
			case EINTR:
				goto SEM_writeWorking;
				break;
			default:
				perror("unlock writeWorking error:");
				return -1;
				break;
		}
	}
	//reduce counter of wantWrite
	sem.sem_num = wantWrite;
	sem.sem_op = -1;

	SEM_wantWrite:
	if (semop(semId, &sem, 1))
	{
		return 0;
	}
	return 0;
}


int lockReadSem(int semId)
{
	struct sembuf sem[2];
	sem[0].sem_num = wantWrite;
	sem[0].sem_flg = SEM_UNDO;
	sem[1].sem_num = readWorking;
	sem[1].sem_flg = SEM_UNDO;

	//to be sure not concurrency problem, read Thread must be wait until no writes works, and instantly increase his counter
	sem[0].sem_op = 0;
	sem[1].sem_op = +1;
	SEM_wantWrite_readWorking:
	if (semop(semId, sem, 2))
	{
		switch (errno)
		{
			case EINTR:
				goto SEM_wantWrite_readWorking;
				break;
			default:
				perror("lockRead sem take error:");
				return -1;
				break;
		}
	}

	return 0;
}

int unlockReadSem(int semId)
{
	struct sembuf sem;
	sem.sem_flg = SEM_UNDO;
	sem.sem_num = readWorking;
	sem.sem_op = -1;

	return 0;
}

void semInfo(int semId)
{
	unsigned short semInfo[3];
	semctl(semId, 0, GETALL, semInfo);
	//enum semName {wantWrite=0,readWorking=1,writeWorking=2};
	printf("\nsem writeWorking=%d\n", semInfo[writeWorking]);
}
