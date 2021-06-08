/* Ofront+ 1.0 -mxa3 -21 */
#include "SYSTEM.oh"
#include "Basic.oh"






/*============================================================================*/


int main (int argc, char **argv)
{
	__INIT(argc, argv);
	__IMPORT(Basic__init);
	__REGMAIN("BasicLoader", 0);
/* BEGIN */
	Basic_DATA2(0, 0);
	Basic_DATAW(63);
	Basic_DATACH5(0xf4, '0', 0x0e, 0x00, 0x00);
	Basic_DATAW(23693);
	Basic_DATA(0);
	Basic_DATACH8(',', 0xc3, 0xa7, ':', 0xe7, 0xc3, 0xa7, ':');
	Basic_DATACH5(0xfd, '0', 0x0e, 0x00, 0x00);
	Basic_DATAW(24099);
	Basic_DATA(0);
	Basic_DATACH2(':', 0xf4);
	Basic_DATACH4('0', 0x0e, 0x00, 0x00);
	Basic_DATAW(23739);
	Basic_DATA(0);
	Basic_DATACH5(',', '0', 0x0e, 0x00, 0x00);
	Basic_DATAW(111);
	Basic_DATA(0);
	Basic_DATACH2(':', 0xef);
	Basic_DATA2(34, 34);
	Basic_DATACH(0xaa);
	Basic_DATACH2(':', 0xef);
	Basic_DATA2(34, 34);
	Basic_DATACH2(0xaf, ':');
	Basic_DATACH3(0xf9, 0xc0, '0');
	Basic_DATACH3(0x0e, 0x00, 0x00);
	Basic_DATAW(24100);
	Basic_DATA(0);
	Basic_DATACH(0x0d);
	__FINI;
}
