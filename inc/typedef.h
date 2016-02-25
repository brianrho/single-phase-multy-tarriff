
/*
//name: common.h
//function: definition of whole situation parameter, mainly involve to compling environment definition
//author:
//version:
//time:

���ƣ�common.h
���ܣ�ȫ�ֲ����Ķ��壬��Ҫ���漰���뻷���Ķ���
���ߣ�
�汾��
ʱ�� ��
*/

#ifndef 	_TYPEDEF_H_
#define		_TYPEDEF_H_
			
			
/********************************/
typedef	unsigned 	char	int8u ;
typedef	signed 		char	int8s  ;

typedef unsigned 	int		int16u ;
typedef signed 		int		int16s  ;

typedef unsigned	long 	int32u	;
typedef signed 		long 	int32s	;

typedef  double			int64u;


//typedef bit			boolean;
/********************************/

#ifndef	TRUE	
#define	TRUE	1
#define	FALSE	0
#endif

#define	SUCCESS	1
#define	FLASE	0

#define		ON		1
#define		OFF		0

#define		BIG_ENDIAN		0		 
#define		LITTLE_ENDIAN	1

#define		CPU_BIT8		0
#define		CPU_BIT16		1
#define		CPU_BIT32		2

//complier storage order definition
/*�������洢˳����*/
#define		ENDIAN			BIG_ENDIAN
#define		CPU_BIT			CPU_BIT8	




#endif

