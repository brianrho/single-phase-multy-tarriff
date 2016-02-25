/*****************************************************************
	Asm.s43 (ASM)
*****************************************************************/
// BCD Calculation Subroutine
extern void _BCD1INC( char *Dest );
extern void _BCD2INC( char *Dest );
extern void _BCD3INC( char *Dest );
extern void _BCD4INC( char *Dest );
extern void _BCD5INC( char *Dest );
extern void _BCD1DEC( char *Dest);
extern void _BCD4ADD( char *Dest, char *Src);
extern void _BCD5ADD( char *Dest, char *Src);
extern void _BCD3ADD( char *Dest, char *Src);
extern void _BCD1ADD( char *Dest, char *Src);
extern void	_BCD2DEC( char *Dest );

void HexToBcd(int8u * buf, int32u value);

void Long_BCD4aA(char *Ptr, unsigned long Data);
unsigned long BCD4_LongA(char *Ptr2BCD4);
//*****************************************************************
// General.c
//*****************************************************************
char  AtoB( char Asc );
char Byte_BCD( char Data );
char BCD_Byte( char Data );
void Long_BCD4(char *Ptr, unsigned long Data);
unsigned long BCD4_Long(char * Ptr2BCD4);
void Long_BCD3(char *Ptr,unsigned long Data);

void Asc_BCD( char *BCD, char *Asc, int Lenth );
void BCD_Asc( char *Asc, char *BCD ,int Lenth ); 
void Word_BCD2( char *Ptr, unsigned int Data );
unsigned int BCD2_Word(unsigned char *Ptr);

void BCD_AscA( char *Asc, char *BCD ,int Lenth );
void Asc_BCDA( char *BCD, char *Asc, int Lenth );

