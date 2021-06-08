/* Ofront+ 1.0 -s3 -48 */
#include "SYSTEM.oh"
#include "Files.oh"

typedef
	struct TapeTAP_TapeFile {
		Files_FileToWrite file;
		BOOLEAN error;
		INTEGER errcode;
		SET checksum;
	} TapeTAP_TapeFile;

export void TapeTAP_TapeFile_Finalize (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ);
export void TapeTAP_TapeFile_ReCreate (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *tapeName, INTEGER tapeName__len);
export void TapeTAP_TapeFile_SaveBasic (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER startLine, INTEGER dataLength, BYTE *data, INTEGER data__len);
static void TapeTAP_TapeFile_SaveBasicHeader (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER startLine, INTEGER dataLength);
static void TapeTAP_TapeFile_SaveByte (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, BYTE byte);
static void TapeTAP_TapeFile_SaveCheckSum (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ);
export void TapeTAP_TapeFile_SaveCode (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER startAddr, INTEGER dataLength, BYTE *data, INTEGER data__len);
static void TapeTAP_TapeFile_SaveCodeHeader (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER dataStartAddr, INTEGER dataLength);
static void TapeTAP_TapeFile_SaveDataBlock (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, INTEGER dataLength, BYTE *data, INTEGER data__len);
static void TapeTAP_TapeFile_SaveName (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len);
static void TapeTAP_TapeFile_SaveWord (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, INTEGER word);
#define __TapeTAP_TapeFile_Finalize(tap, tap__typ) __SEND(tap__typ, TapeTAP_TapeFile_Finalize, 1, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *), (tap, tap__typ))
#define __TapeTAP_TapeFile_ReCreate(tap, tap__typ, tapeName, tapeName__len) __SEND(tap__typ, TapeTAP_TapeFile_ReCreate, 2, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, CHAR*, INTEGER ), (tap, tap__typ, tapeName, tapeName__len))
#define __TapeTAP_TapeFile_SaveBasic(tap, tap__typ, name, name__len, startLine, dataLength, data, data__len) __SEND(tap__typ, TapeTAP_TapeFile_SaveBasic, 3, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, CHAR*, INTEGER , INTEGER, INTEGER, BYTE*, INTEGER ), (tap, tap__typ, name, name__len, startLine, dataLength, data, data__len))
#define __TapeTAP_TapeFile_SaveBasicHeader(tap, tap__typ, name, name__len, startLine, dataLength) __SEND(tap__typ, TapeTAP_TapeFile_SaveBasicHeader, 4, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, CHAR*, INTEGER , INTEGER, INTEGER), (tap, tap__typ, name, name__len, startLine, dataLength))
#define __TapeTAP_TapeFile_SaveByte(tap, tap__typ, byte) __SEND(tap__typ, TapeTAP_TapeFile_SaveByte, 5, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, BYTE), (tap, tap__typ, byte))
#define __TapeTAP_TapeFile_SaveCheckSum(tap, tap__typ) __SEND(tap__typ, TapeTAP_TapeFile_SaveCheckSum, 6, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *), (tap, tap__typ))
#define __TapeTAP_TapeFile_SaveCode(tap, tap__typ, name, name__len, startAddr, dataLength, data, data__len) __SEND(tap__typ, TapeTAP_TapeFile_SaveCode, 7, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, CHAR*, INTEGER , INTEGER, INTEGER, BYTE*, INTEGER ), (tap, tap__typ, name, name__len, startAddr, dataLength, data, data__len))
#define __TapeTAP_TapeFile_SaveCodeHeader(tap, tap__typ, name, name__len, dataStartAddr, dataLength) __SEND(tap__typ, TapeTAP_TapeFile_SaveCodeHeader, 8, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, CHAR*, INTEGER , INTEGER, INTEGER), (tap, tap__typ, name, name__len, dataStartAddr, dataLength))
#define __TapeTAP_TapeFile_SaveDataBlock(tap, tap__typ, dataLength, data, data__len) __SEND(tap__typ, TapeTAP_TapeFile_SaveDataBlock, 9, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, INTEGER, BYTE*, INTEGER ), (tap, tap__typ, dataLength, data, data__len))
#define __TapeTAP_TapeFile_SaveName(tap, tap__typ, name, name__len) __SEND(tap__typ, TapeTAP_TapeFile_SaveName, 10, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, CHAR*, INTEGER ), (tap, tap__typ, name, name__len))
#define __TapeTAP_TapeFile_SaveWord(tap, tap__typ, word) __SEND(tap__typ, TapeTAP_TapeFile_SaveWord, 11, void(*)(TapeTAP_TapeFile*, SYSTEM_ADRINT *, INTEGER), (tap, tap__typ, word))



export SYSTEM_ADRINT *TapeTAP_TapeFile__typ;



/*============================================================================*/

void TapeTAP_TapeFile_ReCreate (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *tapeName, INTEGER tapeName__len)
{
	__Files_File_OpenToWrite((void*)&(*tap).file, Files_FileToWrite__typ, (void*)tapeName, tapeName__len);
	(*tap).error = (*tap).file.error;
}

/*----------------------------------------------------------------------------*/
static void TapeTAP_TapeFile_SaveByte (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, BYTE byte)
{
	if (!(*tap).error) {
		__Files_FileToWrite_WriteByte(&(*tap).file, Files_FileToWrite__typ, byte);
		(*tap).error = (*tap).file.error;
		(*tap).checksum = (*tap).checksum ^ (SET)byte;
	}
}

static void TapeTAP_TapeFile_SaveWord (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, INTEGER word)
{
	__ASSERT(word >= 0 && word <= 65535, 0, (CHAR*)"TapeTAP", -3654);
	if (!(*tap).error) {
		__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, (BYTE)__MASK(word, -256));
		(*tap).error = (*tap).file.error;
		if (!(*tap).error) {
			__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, (BYTE)__ASHR(word, 8, INTEGER));
			(*tap).error = (*tap).file.error;
		}
	}
}

static void TapeTAP_TapeFile_SaveName (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len)
{
	INTEGER i, nameIdx, _for__12;
	nameIdx = 0;
	i = 0;
	_for__12 = 10;
	do {
		if (nameIdx <= name__len && name[__X(nameIdx, name__len, (CHAR*)"TapeTAP", -4398)] != 0x00) {
			__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, (BYTE)name[__X(nameIdx, name__len, (CHAR*)"TapeTAP", -4323)]);
			nameIdx += 1;
		} else {
			__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, 32);
		}
		i += 1;
	} while (--_for__12);
}

static void TapeTAP_TapeFile_SaveCheckSum (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ)
{
	__Files_FileToWrite_WriteByte(&(*tap).file, Files_FileToWrite__typ, (BYTE)(*tap).checksum);
}

static void TapeTAP_TapeFile_SaveBasicHeader (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER startLine, INTEGER dataLength)
{
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, 19);
	(*tap).checksum = 0x0;
	__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, 0);
	__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, 0);
	__TapeTAP_TapeFile_SaveName(&*tap, tap__typ, (void*)name, name__len);
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, dataLength);
	if ((startLine >= 0 && startLine <= 9999) || startLine == 32768) {
		__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, startLine);
	} else {
		(*tap).error = 1;
	}
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, dataLength);
	__TapeTAP_TapeFile_SaveCheckSum(&*tap, tap__typ);
}

static void TapeTAP_TapeFile_SaveCodeHeader (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER dataStartAddr, INTEGER dataLength)
{
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, 19);
	(*tap).checksum = 0x0;
	__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, 0);
	__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, 3);
	__TapeTAP_TapeFile_SaveName(&*tap, tap__typ, (void*)name, name__len);
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, dataLength);
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, dataStartAddr);
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, 32768);
	__TapeTAP_TapeFile_SaveCheckSum(&*tap, tap__typ);
}

static void TapeTAP_TapeFile_SaveDataBlock (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, INTEGER dataLength, BYTE *data, INTEGER data__len)
{
	INTEGER i, _for__10;
	__TapeTAP_TapeFile_SaveWord(&*tap, tap__typ, (1 + dataLength) + 1);
	(*tap).checksum = 0x0;
	__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, -1);
	i = 0;
	_for__10 = dataLength - 1;
	if (i <= _for__10) {
		_for__10 = (__U_INTEGER)(_for__10 - i) + 1;
		do {
			__TapeTAP_TapeFile_SaveByte(&*tap, tap__typ, data[__X(i, data__len, (CHAR*)"TapeTAP", -10686)]);
			i += 1;
		} while (--_for__10);
	}
	__TapeTAP_TapeFile_SaveCheckSum(&*tap, tap__typ);
}

void TapeTAP_TapeFile_SaveBasic (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER startLine, INTEGER dataLength, BYTE *data, INTEGER data__len)
{
	__TapeTAP_TapeFile_SaveBasicHeader(&*tap, tap__typ, (void*)name, name__len, startLine, dataLength);
	__TapeTAP_TapeFile_SaveDataBlock(&*tap, tap__typ, dataLength, (void*)data, data__len * 1);
}

/*----------------------------------------------------------------------------*/
void TapeTAP_TapeFile_SaveCode (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ, CHAR *name, INTEGER name__len, INTEGER startAddr, INTEGER dataLength, BYTE *data, INTEGER data__len)
{
	__TapeTAP_TapeFile_SaveCodeHeader(&*tap, tap__typ, (void*)name, name__len, startAddr, dataLength);
	__TapeTAP_TapeFile_SaveDataBlock(&*tap, tap__typ, dataLength, (void*)data, data__len * 1);
}

/*----------------------------------------------------------------------------*/
void TapeTAP_TapeFile_Finalize (TapeTAP_TapeFile *tap, SYSTEM_ADRINT *tap__typ)
{
	__Files_File_Close((void*)&(*tap).file, Files_FileToWrite__typ);
}

/*----------------------------------------------------------------------------*/
__TDESC(TapeTAP_TapeFile__desc, 13, 0) = {__TDFLDS("TapeFile", 24), {-4}};

export void *TapeTAP__init (void)
{
	__DEFMOD;
	__IMPORT(Files__init);
	__REGMOD("TapeTAP", 0);
	__INITYP(TapeTAP_TapeFile, TapeTAP_TapeFile, 0);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_Finalize, 1);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_ReCreate, 2);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveBasic, 3);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveBasicHeader, 4);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveByte, 5);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveCheckSum, 6);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveCode, 7);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveCodeHeader, 8);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveDataBlock, 9);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveName, 10);
	__INITBP(TapeTAP_TapeFile, TapeTAP_TapeFile_SaveWord, 11);
/* BEGIN */
	__ENDMOD;
}
