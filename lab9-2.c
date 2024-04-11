#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* data[10];
	int count;
};

// Compute the hash function
int hash(int x)
{
	return x % 31;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray->data[i]!= NULL)
		{
			printf("Index %d -> ", i);
			struct RecordType *record = pHashArray->data[i];
			printf("%d %c %d\n", record->id, record->name, record->order);
		}
	}
}

// Insert a record into the hash table
void insert(struct HashType *hashTable, struct RecordType *record)
{
	int index = hash(record->id);

	// Implement collision resolution here, such as linear probing or chaining
	// For example, using linear probing:
	while (hashTable->data[index]!= NULL)
	{
		index = (index + 1) % 31;
	}

	hashTable->data[index] = record;
	hashTable->count++;
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	// Initialize hash table
	struct HashType hashTable;
	hashTable.count = 0;
	for (int i = 0; i < 10; i++)
	{
		hashTable.data[i] = NULL;
	}

	// Insert records into hash table
	for (int i = 0; i < recordSz; i++)
	{
		insert(&hashTable, &pRecords[i]);
	}

	// Display records in hash table
	displayRecordsInHash(&hashTable, 10);

	return 0;
}