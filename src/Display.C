#include "..\inc\includes.h"

#ifdef SINGLE_PHASE_MULTI_TARIFF
#include "..\inc\RN8209.h"
extern volatile RN8209_RMS rn8209a_rms;
extern volatile RN8209_CALIB rn8209a_calib;
extern ENERGY vse1t_de;
#endif

//extern int8u ucBuf[5];

unsigned long Get12MonAddr(unsigned long Addr, unsigned char DLorMD);

extern unsigned char meter_state[];
unsigned char display_mod = 0;

//int32u ulVal = 0;


#if 0
//0xFF represents no display OBIS low bytes before high bytes
const OBISTbl myOBIS[374] = {
	//time date 2 (85)
	0x0000, {0xFF,0x01,0x09,0x00}, 0x0001, {0xFF,0x02,0x09,0x00},

	//active forward reverse tariff 10
	0x1000, {0xFF,0x00,0x08,0x01}, 0x1001, {0xFF,0x01,0x08,0x01}, 0x1002, {0xFF,0x02,0x08,0x01}, 0x1003, {0xFF,0x03,0x08,0x01}, 0x1004, {0xFF,0x04,0x08,0x01},
	0x1010, {0xFF,0x00,0x08,0x02}, 0x1011, {0xFF,0x01,0x08,0x02}, 0x1012, {0xFF,0x02,0x08,0x02}, 0x1013, {0xFF,0x03,0x08,0x02}, 0x1014, {0xFF,0x04,0x08,0x02},

	//active forward reverse tariff 10
	0x1020, {0xFF,0x00,0x08,0x03}, 0x1021, {0xFF,0x01,0x08,0x03}, 0x1022, {0xFF,0x02,0x08,0x03}, 0x1023, {0xFF,0x03,0x08,0x03}, 0x1024, {0xFF,0x04,0x08,0x03},
	0x1030, {0xFF,0x00,0x08,0x04}, 0x1031, {0xFF,0x01,0x08,0x04}, 0x1032, {0xFF,0x02,0x08,0x04}, 0x1033, {0xFF,0x03,0x08,0x04}, 0x1034, {0xFF,0x04,0x08,0x04},
	//apparent forward reverse tariff 10
	0x1080, {0xFF,0x00,0x08,0x09}, 0x1081, {0xFF,0x01,0x08,0x09}, 0x1082, {0xFF,0x02,0x08,0x09}, 0x1083, {0xFF,0x03,0x08,0x09}, 0x1084, {0xFF,0x04,0x08,0x09},
	0x1090, {0xFF,0x00,0x08,0x10}, 0x1091, {0xFF,0x01,0x08,0x10}, 0x1092, {0xFF,0x02,0x08,0x10}, 0x1093, {0xFF,0x03,0x08,0x10}, 0x1094, {0xFF,0x04,0x08,0x10},
	//active forward reverse split-phase 6
	0x1400, {0xFF,0x00,0x08,0x21}, 0x1401, {0xFF,0x00,0x08,0x41}, 0x1402, {0xFF,0x00,0x08,0x61},
	0x1410, {0xFF,0x00,0x08,0x22}, 0x1411, {0xFF,0x00,0x08,0x42}, 0x1412, {0xFF,0x00,0x08,0x62},
	//reactive forward reverse split-phase 6
	0x1420, {0xFF,0x00,0x08,0x23}, 0x1421, {0xFF,0x00,0x08,0x43}, 0x1422, {0xFF,0x00,0x08,0x63},
	0x1430, {0xFF,0x00,0x08,0x24}, 0x1431, {0xFF,0x00,0x08,0x44}, 0x1432, {0xFF,0x00,0x08,0x64},
	//apparent forward reverse split-phase 6
	0x1440, {0xFF,0x00,0x08,0x29}, 0x1441, {0xFF,0x00,0x08,0x49}, 0x1442, {0xFF,0x00,0x08,0x69},
	0x1450, {0xFF,0x00,0x08,0x30}, 0x1451, {0xFF,0x00,0x08,0x50}, 0x1452, {0xFF,0x00,0x08,0x70},
	//reactive 1 2 3 4 quadrant total split-phase 16
	0x1140, {0xFF,0x00,0x08,0x05}, 0x1145, {0xFF,0x00,0x08,0x25}, 0x1146, {0xFF,0x00,0x08,0x45}, 0x1147, {0xFF,0x00,0x08,0x65},
	0x1160, {0xFF,0x00,0x08,0x06}, 0x1165, {0xFF,0x00,0x08,0x26}, 0x1166, {0xFF,0x00,0x08,0x46}, 0x1167, {0xFF,0x00,0x08,0x66},
	0x1170, {0xFF,0x00,0x08,0x07}, 0x1175, {0xFF,0x00,0x08,0x27}, 0x1176, {0xFF,0x00,0x08,0x47}, 0x1177, {0xFF,0x00,0x08,0x67},
	0x1150, {0xFF,0x00,0x08,0x08}, 0x1155, {0xFF,0x00,0x08,0x28}, 0x1156, {0xFF,0x00,0x08,0x48}, 0x1157, {0xFF,0x00,0x08,0x68},

	//last month actice forward reverse tariff 10
	0xC000, {0x01,0x00,0x08,0x01}, 0xC001, {0x01,0x01,0x08,0x01}, 0xC002, {0x01,0x02,0x08,0x01}, 0xC003, {0x01,0x03,0x08,0x01}, 0xC004, {0x01,0x04,0x08,0x01},
	0xC010, {0x01,0x00,0x08,0x02}, 0xC011, {0x01,0x01,0x08,0x02}, 0xC012, {0x01,0x02,0x08,0x02}, 0xC013, {0x01,0x03,0x08,0x02}, 0xC014, {0x01,0x04,0x08,0x02},
	//reactive forward reverse tariff 10
	0xC020, {0x01,0x00,0x08,0x03}, 0xC021, {0x01,0x01,0x08,0x03}, 0xC022, {0x01,0x02,0x08,0x03}, 0xC023, {0x01,0x03,0x08,0x03}, 0xC024, {0x01,0x04,0x08,0x03},
	0xC030, {0x01,0x00,0x08,0x04}, 0xC031, {0x01,0x01,0x08,0x04}, 0xC032, {0x01,0x02,0x08,0x04}, 0xC033, {0x01,0x03,0x08,0x04}, 0xC034, {0x01,0x04,0x08,0x04},
	//apparent forward reverse tariff 10
	0xC080, {0x01,0x00,0x08,0x09}, 0xC081, {0x01,0x01,0x08,0x09}, 0xC082, {0x01,0x02,0x08,0x09}, 0xC083, {0x01,0x03,0x08,0x09}, 0xC084, {0x01,0x04,0x08,0x09},
	0xC090, {0x01,0x00,0x08,0x0A}, 0xC091, {0x01,0x01,0x08,0x0A}, 0xC092, {0x01,0x02,0x08,0x0A}, 0xC093, {0x01,0x03,0x08,0x0A}, 0xC094, {0x01,0x04,0x08,0x0A},
	//active forward reverse split-phase 6
	0xC400, {0xFF,0xFF,0x81,0x21}, 0xC401, {0xFF,0xFF,0x81,0x41}, 0xC402, {0xFF,0xFF,0x81,0x61},
	0xC410, {0xFF,0xFF,0x81,0x22}, 0xC411, {0xFF,0xFF,0x81,0x42}, 0xC412, {0xFF,0xFF,0x81,0x62},
	//reactive forward reverse split-phase 6
	0xC420, {0xFF,0xFF,0x81,0x23}, 0xC421, {0xFF,0xFF,0x81,0x43}, 0xC422, {0xFF,0xFF,0x81,0x63},
	0xC430, {0xFF,0xFF,0x81,0x24}, 0xC431, {0xFF,0xFF,0x81,0x44}, 0xC432, {0xFF,0xFF,0x81,0x64},
	//apparent forward reverse split-phase 6
	0xC440, {0xFF,0xFF,0x81,0x29}, 0xC441, {0xFF,0xFF,0x81,0x49}, 0xC442, {0xFF,0xFF,0x81,0x69},
	0xC450, {0xFF,0xFF,0x81,0x30}, 0xC451, {0xFF,0xFF,0x81,0x50}, 0xC452, {0xFF,0xFF,0x81,0x70},
	//reactive 1 2 3 4  quadrant total split-phase 16
	0xC140, {0x01,0x00,0x08,0x05}, 0xC145, {0xFF,0xFF,0x81,0x25}, 0xC146, {0xFF,0xFF,0x81,0x45}, 0xC147, {0xFF,0xFF,0x81,0x65},
	0xC160, {0x01,0x00,0x08,0x06}, 0xC165, {0xFF,0xFF,0x81,0x26}, 0xC166, {0xFF,0xFF,0x81,0x46}, 0xC167, {0xFF,0xFF,0x81,0x66},
	0xC170, {0x01,0x00,0x08,0x07}, 0xC175, {0xFF,0xFF,0x81,0x27}, 0xC176, {0xFF,0xFF,0x81,0x47}, 0xC177, {0xFF,0xFF,0x81,0x67},
	0xC150, {0x01,0x00,0x08,0x08}, 0xC155, {0xFF,0xFF,0x81,0x28}, 0xC156, {0xFF,0xFF,0x81,0x48}, 0xC157, {0xFF,0xFF,0x81,0x68},

	//last two months active forward reverse tariff 10
	0xD000, {0x02,0x00,0x08,0x01}, 0xD001, {0x02,0x01,0x08,0x01}, 0xD002, {0x02,0x02,0x08,0x01}, 0xD003, {0x02,0x03,0x08,0x01}, 0xD004, {0x02,0x04,0x08,0x01},
	0xD010, {0x02,0x00,0x08,0x02}, 0xD011, {0x02,0x01,0x08,0x02}, 0xD012, {0x02,0x02,0x08,0x02}, 0xD013, {0x02,0x03,0x08,0x02}, 0xD014, {0x02,0x04,0x08,0x02},
	//reactive forward reverse tariff 10
	0xD020, {0x02,0x00,0x08,0x03}, 0xD021, {0x02,0x01,0x08,0x03}, 0xD022, {0x02,0x02,0x08,0x03}, 0xD023, {0x02,0x03,0x08,0x03}, 0xD024, {0x02,0x04,0x08,0x03},
	0xD030, {0x02,0x00,0x08,0x04}, 0xD031, {0x02,0x01,0x08,0x04}, 0xD032, {0x02,0x02,0x08,0x04}, 0xD033, {0x02,0x03,0x08,0x04}, 0xD034, {0x02,0x04,0x08,0x04},
	//apparent forward reverse tariff 10
	0xD080, {0x02,0x00,0x08,0x09}, 0xD081, {0x02,0x01,0x08,0x09}, 0xD082, {0x02,0x02,0x08,0x09}, 0xD083, {0x02,0x03,0x08,0x09}, 0xD084, {0x02,0x04,0x08,0x09},
	0xD090, {0x02,0x00,0x08,0x0A}, 0xD091, {0x02,0x01,0x08,0x0A}, 0xD092, {0x02,0x02,0x08,0x0A}, 0xD093, {0x02,0x03,0x08,0x0A}, 0xD094, {0x02,0x04,0x08,0x0A},
	//actice forward reverse split-phase 6
	0xD400, {0xFF,0xFF,0x82,0x21}, 0xD401, {0xFF,0xFF,0x82,0x41}, 0xD402, {0xFF,0xFF,0x82,0x61},
	0xD410, {0xFF,0xFF,0x82,0x22}, 0xD411, {0xFF,0xFF,0x82,0x42}, 0xD412, {0xFF,0xFF,0x82,0x62},
	//reactive forward reverse split-phase 6
	0xD420, {0xFF,0xFF,0x82,0x23}, 0xD421, {0xFF,0xFF,0x82,0x43}, 0xD422, {0xFF,0xFF,0x82,0x63},
	0xD430, {0xFF,0xFF,0x82,0x24}, 0xD431, {0xFF,0xFF,0x82,0x44}, 0xD432, {0xFF,0xFF,0x82,0x64},
	//ÊÓÔÚÕý·´Ïò ·ÖÏà 6
	0xD440, {0xFF,0xFF,0x82,0x29}, 0xD441, {0xFF,0xFF,0x82,0x49}, 0xD442, {0xFF,0xFF,0x82,0x69},
	0xD450, {0xFF,0xFF,0x82,0x30}, 0xD451, {0xFF,0xFF,0x82,0x50}, 0xD452, {0xFF,0xFF,0x82,0x70},
	//reactive 1 2 3 4 quadrant total split-phase 16
	0xD140, {0x02,0x00,0x08,0x05}, 0xD145, {0xFF,0xFF,0x82,0x25}, 0xD146, {0xFF,0xFF,0x82,0x45}, 0xD147, {0xFF,0xFF,0x82,0x65},
	0xD160, {0x02,0x00,0x08,0x06}, 0xD165, {0xFF,0xFF,0x82,0x26}, 0xD166, {0xFF,0xFF,0x82,0x46}, 0xD167, {0xFF,0xFF,0x82,0x66},
	0xD170, {0x02,0x00,0x08,0x07}, 0xD175, {0xFF,0xFF,0x82,0x27}, 0xD176, {0xFF,0xFF,0x82,0x47}, 0xD177, {0xFF,0xFF,0x82,0x67},
	0xD150, {0x02,0x00,0x08,0x08}, 0xD155, {0xFF,0xFF,0x82,0x28}, 0xD156, {0xFF,0xFF,0x82,0x48}, 0xD157, {0xFF,0xFF,0x82,0x68},

	//current ABC voltage ABC6
	0x0111, {0xFF,0x00,0x07,0x31}, 0x0112, {0xFF,0x00,0x07,0x51}, 0x0113, {0xFF,0x00,0x07,0x71},
	0x0101, {0xFF,0x00,0x07,0x32}, 0x0102, {0xFF,0x00,0x07,0x52}, 0x0103, {0xFF,0x00,0x07,0x72},
	//active power ABC reactive power ABC apparent power ABC--------------------not know OBIS code--------------- 9
	//ÓÐ¹¦¹¦ÂÊABC ÎÞ¹¦¹¦ÂÊABC ÊÓÔÚ¹¦ÂÊABC--------------------²»ÖªOBISÂë--------------- 9
	0x0201, {0xFF,0x00,0x07,0x21}, 0x0202, {0xFF,0x00,0x07,0x41}, 0x0203, {0xFF,0x00,0x07,0x61},
	0x0211, {0xFF,0x00,0x07,0x23}, 0x0212, {0xFF,0x00,0x07,0x43}, 0x0213, {0xFF,0x00,0x07,0x63},
	0x0221, {0xFF,0x00,0x07,0x29}, 0x0222, {0xFF,0x00,0x07,0x49}, 0x0223, {0xFF,0x00,0x07,0x69},
	//power parameter ABC 3
	0x0301, {0xFF,0x00,0x07,0x33}, 0x0302, {0xFF,0x00,0x07,0x53}, 0x0303, {0xFF,0x00,0x07,0x73},
	//frequency 1
	0x0320, {0xFF,0x00,0x07,0x14},
	//kw kvar pf av 3
	0x0200, {0xFF,0x00,0x07,0x01}, 0x0210, {0xFF,0x00,0x07,0x03}, 0x0300, {0xFF,0x00,0x07,0x13},
	0x0220, {0xFF,0x00,0x07,0x09},   //kVA

	/*
	 //current cycle demand apparent forward reverse active forward reverse reactive forward reverse reactive four quadrants 10
	 //µ±Ç°ÖÜÆÚÐèÁ¿ ÊÓÔÚÕý·´Ïò ÓÐ¹¦Õý·´Ïò ÎÞ¹¦Õý·´Ïò ÎÞ¹¦ËÄÏóÏÞ 10
	 0x0310,{0xFF,0x00,0x06,0x01},	0x0311,{0xFF,0x00,0x06,0x02},
	 0x0312,{0xFF,0x00,0x06,0x03},	0x0313,{0xFF,0x00,0x06,0x04},
	 0x0314,{0xFF,0x00,0x06,0x09},	0x0315,{0xFF,0x00,0x06,0x10},

	 0x0316,{0xFF,0x00,0x06,0x05},	0x0317,{0xFF,0x00,0x06,0x06},
	 0x0318,{0xFF,0x00,0x06,0x07},	0x0319,{0xFF,0x00,0x06,0x08},
	 */

	//current maximum demand active forward reverse apparent forward reverse reactive forward reverse reactive four quadrants 10
	//µ±Ç°×î´óÐèÁ¿ ÓÐ¹¦Õý·´Ïò ÊÓÔÚÕý·´Ïò ÎÞ¹¦Õý·´Ïò ÎÞ¹¦ËÄÏóÏÞ 10
	//active
	0x3000, {0xFF,0x00,0x06,0x01},
	0x3001, {0xFF,0x01,0x06,0x01},
	0x3002, {0xFF,0x02,0x06,0x01},
	0x3003, {0xFF,0x03,0x06,0x01},
	0x3004, {0xFF,0x04,0x06,0x01},

	0x3010, {0xFF,0x00,0x06,0x02},
	0x3011, {0xFF,0x01,0x06,0x02},
	0x3012, {0xFF,0x02,0x06,0x02},
	0x3013, {0xFF,0x03,0x06,0x02},
	0x3014, {0xFF,0x04,0x06,0x02},
	//apparent
	0x3020, {0xFF,0x00,0x06,0x09},
	0x3021, {0xFF,0x01,0x06,0x09},
	0x3022, {0xFF,0x02,0x06,0x09},
	0x3023, {0xFF,0x03,0x06,0x09},
	0x3024, {0xFF,0x04,0x06,0x09},

	0x3030, {0xFF,0x00,0x06,0x10},
	0x3031, {0xFF,0x01,0x06,0x10},
	0x3032, {0xFF,0x02,0x06,0x10},
	0x3033, {0xFF,0x03,0x06,0x10},
	0x3034, {0xFF,0x04,0x06,0x10},
	//reactive
	0x3040, {0xFF,0x00,0x06,0x03},
	0x3041, {0xFF,0x01,0x06,0x03},
	0x3042, {0xFF,0x02,0x06,0x03},
	0x3043, {0xFF,0x03,0x06,0x03},
	0x3044, {0xFF,0x04,0x06,0x03},

	0x3050, {0xFF,0x00,0x06,0x04},
	0x3051, {0xFF,0x01,0x06,0x04},
	0x3052, {0xFF,0x02,0x06,0x04},
	0x3053, {0xFF,0x03,0x06,0x04},
	0x3054, {0xFF,0x04,0x06,0x04},
	//reactive one four two three
	0x0820, {0xFF,0x00,0x06,0x05},
	0x0821, {0xFF,0x01,0x06,0x05},
	0x0822, {0xFF,0x02,0x06,0x05},
	0x0823, {0xFF,0x03,0x06,0x05},
	0x0824, {0xFF,0x04,0x06,0x05},

	0x0830, {0xFF,0x00,0x06,0x08},
	0x0831, {0xFF,0x01,0x06,0x08},
	0x0832, {0xFF,0x02,0x06,0x08},
	0x0833, {0xFF,0x03,0x06,0x08},
	0x0834, {0xFF,0x04,0x06,0x08},

	0x0840, {0xFF,0x00,0x06,0x06},
	0x0841, {0xFF,0x01,0x06,0x06},
	0x0842, {0xFF,0x02,0x06,0x06},
	0x0843, {0xFF,0x03,0x06,0x06},
	0x0844, {0xFF,0x04,0x06,0x06},

	0x0850, {0xFF,0x00,0x06,0x07},
	0x0851, {0xFF,0x01,0x06,0x07},
	0x0852, {0xFF,0x02,0x06,0x07},
	0x0853, {0xFF,0x03,0x06,0x07},
	0x0854, {0xFF,0x04,0x06,0x07},
	//last month maximum demand active forward reverse apparent forward reverse reactive forward reverse reactive four quadrants 10 last month
	//active
	0xA000, {0x01,0x00,0x06,0x01},
	0xA001, {0x01,0x01,0x06,0x01},
	0xA002, {0x01,0x02,0x06,0x01},
	0xA003, {0x01,0x03,0x06,0x01},
	0xA004, {0x01,0x04,0x06,0x01},

	0xA010, {0x01,0x00,0x06,0x02},
	0xA011, {0x01,0x01,0x06,0x02},
	0xA012, {0x01,0x02,0x06,0x02},
	0xA013, {0x01,0x03,0x06,0x02},
	0xA014, {0x01,0x04,0x06,0x02},
	//apparent
	0xA020, {0x01,0x00,0x06,0x09},
	0xA021, {0x01,0x01,0x06,0x09},
	0xA022, {0x01,0x02,0x06,0x09},
	0xA023, {0x01,0x03,0x06,0x09},
	0xA024, {0x01,0x04,0x06,0x09},

	0xA030, {0x01,0x00,0x06,0x0A},
	0xA031, {0x01,0x01,0x06,0x0A},
	0xA032, {0x01,0x02,0x06,0x0A},
	0xA033, {0x01,0x03,0x06,0x0A},
	0xA034, {0x01,0x04,0x06,0x0A},
	//reactive
	0xA040, {0x01,0x00,0x06,0x03},
	0xA041, {0x01,0x01,0x06,0x03},
	0xA042, {0x01,0x02,0x06,0x03},
	0xA043, {0x01,0x03,0x06,0x03},
	0xA044, {0x01,0x04,0x06,0x03},

	0xA050, {0x01,0x00,0x06,0x04},
	0xA051, {0x01,0x01,0x06,0x04},
	0xA052, {0x01,0x02,0x06,0x04},
	0xA053, {0x01,0x03,0x06,0x04},
	0xA054, {0x01,0x04,0x06,0x04},
	//reactive one four two three
	0x7820, {0x01,0x00,0x06,0x05},
	0x7821, {0x01,0x01,0x06,0x05},
	0x7822, {0x01,0x02,0x06,0x05},
	0x7823, {0x01,0x03,0x06,0x05},
	0x7824, {0x01,0x04,0x06,0x05},

	0x7830, {0x01,0x00,0x06,0x08},
	0x7831, {0x01,0x01,0x06,0x08},
	0x7832, {0x01,0x02,0x06,0x08},
	0x7833, {0x01,0x03,0x06,0x08},
	0x7834, {0x01,0x04,0x06,0x08},

	0x7840, {0x01,0x00,0x06,0x06},
	0x7841, {0x01,0x01,0x06,0x06},
	0x7842, {0x01,0x02,0x06,0x06},
	0x7843, {0x01,0x03,0x06,0x06},
	0x7844, {0x01,0x04,0x06,0x06},

	0x7850, {0x01,0x00,0x06,0x07},
	0x7851, {0x01,0x01,0x06,0x07},
	0x7852, {0x01,0x02,0x06,0x07},
	0x7853, {0x01,0x03,0x06,0x07},
	0x7854, {0x01,0x04,0x06,0x07},

	//last two months maximum demand active forward reverse apparent forward reverse forward reverse reactive four quadrants 10 last two months
	//ÉÏÉÏÔÂ×î´óÐèÁ¿ ÓÐ¹¦Õý·´Ïò ÊÓÔÚÕý·´Ïò ÎÞ¹¦Õý·´Ïò ÎÞ¹¦ËÄÏóÏÞ 10 ÉÏÉÏÔÂ
	//active
	// ÓÐ¹¦
	0xA100, {0x02,0x00,0x06,0x01},
	0xA101, {0x02,0x01,0x06,0x01},
	0xA102, {0x02,0x02,0x06,0x01},
	0xA103, {0x02,0x03,0x06,0x01},
	0xA104, {0x02,0x04,0x06,0x01},

	0xA110, {0x02,0x00,0x06,0x02},
	0xA111, {0x02,0x01,0x06,0x02},
	0xA112, {0x02,0x02,0x06,0x02},
	0xA113, {0x02,0x03,0x06,0x02},
	0xA114, {0x02,0x04,0x06,0x02},
	//apparent
	// ÊÓÔÚ
	0xA120, {0x02,0x00,0x06,0x09},
	0xA121, {0x02,0x01,0x06,0x09},
	0xA122, {0x02,0x02,0x06,0x09},
	0xA123, {0x02,0x03,0x06,0x09},
	0xA124, {0x02,0x04,0x06,0x09},

	0xA130, {0x02,0x00,0x06,0x0A},
	0xA131, {0x02,0x01,0x06,0x0A},
	0xA132, {0x02,0x02,0x06,0x0A},
	0xA133, {0x02,0x03,0x06,0x0A},
	0xA134, {0x02,0x04,0x06,0x0A},
	//reactive
	// ÎÞ¹¦
	0xA140, {0x02,0x00,0x06,0x03},
	0xA141, {0x02,0x01,0x06,0x03},
	0xA142, {0x02,0x02,0x06,0x03},
	0xA143, {0x02,0x03,0x06,0x03},
	0xA144, {0x02,0x04,0x06,0x03},

	0xA150, {0x02,0x00,0x06,0x04},
	0xA151, {0x02,0x01,0x06,0x04},
	0xA152, {0x02,0x02,0x06,0x04},
	0xA153, {0x02,0x03,0x06,0x04},
	0xA154, {0x02,0x04,0x06,0x04},
	//reactive one four two three
	// ÎÞ¹¦Ò»ËÄ¶þÈý
	0x7920, {0x02,0x00,0x06,0x05},
	0x7921, {0x02,0x01,0x06,0x05},
	0x7922, {0x02,0x02,0x06,0x05},
	0x7923, {0x02,0x03,0x06,0x05},
	0x7924, {0x02,0x04,0x06,0x05},

	0x7930, {0x02,0x00,0x06,0x08},
	0x7931, {0x02,0x01,0x06,0x08},
	0x7932, {0x02,0x02,0x06,0x08},
	0x7933, {0x02,0x03,0x06,0x08},
	0x7934, {0x02,0x04,0x06,0x08},

	0x7940, {0x02,0x00,0x06,0x06},
	0x7941, {0x02,0x01,0x06,0x06},
	0x7942, {0x02,0x02,0x06,0x06},
	0x7943, {0x02,0x03,0x06,0x06},
	0x7944, {0x02,0x04,0x06,0x06},

	0x7950, {0x02,0x00,0x06,0x07},
	0x7951, {0x02,0x01,0x06,0x07},
	0x7952, {0x02,0x02,0x06,0x07},
	0x7953, {0x02,0x03,0x06,0x07},
	0x7954, {0x02,0x04,0x06,0x07},

	//meter number low 8 places high 2 places
	//±íºÅ µÍ8Î» ¸ß2Î»
	0x8020, {0xFF,0xFF,0x20,0x80},
	0x8021, {0xFF,0xFF,0x21,0x80},
	//meter number low 8 places high 4 places
	//±íºÅ µÍ8Î» ¸ß4Î»
	0x8022, {0xFF,0xFF,0x22,0x80},
	0x8023, {0xFF,0xFF,0x23,0x80},

	//3
	0x8888, {0xFF,0xFF,0x88,0x88},
	0x8024, {0xFF,0x02,0x00,0x00},
	0x8025, {0xFF,0x00,0x02,0x00}
};
#endif

/*******************************************************
 //displaying meter
 *******************************************************/
const unsigned char NumSeg[] = {
		s1_a | s1_b | s1_c | s1_d | s1_e | s1_f,		    //0:
		s1_b | s1_c,								//1:
		s1_a | s1_b | s1_d | s1_e | s1_g,				//2:
		s1_a | s1_b | s1_d | s1_c | s1_g,				//3:
		s1_b | s1_c | s1_f | s1_g,					//4:
		s1_a | s1_c | s1_d | s1_f | s1_g,				//5:
		s1_a | s1_c | s1_d | s1_e | s1_f | s1_g,			//6:
		s1_a | s1_b | s1_c,							//7:
		s1_a | s1_b | s1_d | s1_e | s1_f | s1_g | s1_c,	    //8:
		s1_a | s1_b | s1_c | s1_d | s1_f | s1_g,		    //9:
		s1_a | s1_b | s1_e | s1_f | s1_g | s1_c,		    //a:
		s1_d | s1_e | s1_f | s1_g | s1_c,				//b:
		s1_a | s1_d | s1_e | s1_f,					//c:
		s1_b | s1_d | s1_e | s1_g | s1_c,				//d:
		s1_a | s1_d | s1_e | s1_f | s1_g,		    	//e:
		s1_a | s1_e | s1_f | s1_g,					//f:
		s1_a | s1_b | s1_c | s1_d | s1_f | s1_g,  		//g:
		s1_b | s1_c | s1_f | s1_e | s1_g,       		//H:
		s1_c,		                            //i;
		s1_b | s1_c | s1_d | s1_e,            		//j:
		0, 		                            	//k:
		s1_d | s1_e | s1_f,            		        //L:
		0,                      		        //M:
		s1_g | s1_c | s1_e,		                    //N:
		s1_c | s1_d | s1_e | s1_g,            		//O:
		s1_a | s1_b | s1_e | s1_g | s1_f,            	//P:
		0,                              		//Q:
		s1_e | s1_g,              				//r:
		s1_a | s1_c | s1_d | s1_f | s1_g,				//S:
		s1_f | s1_e | s1_d | s1_g,           			//t:
		s1_b | s1_c | s1_d | s1_e | s1_f,            	//U:
		s1_c | s1_d | s1_e,			          	//v:
		s1_b | s1_c | s1_d | s1_e | s1_f,            	//w:
		s1_b | s1_c | s1_e | s1_f | s1_g,            	//x:
		s1_b | s1_c | s1_d | s1_e | s1_f,            	//y:
		s1_b | s1_c | s1_d | s1_e | s1_f,            	//z:
		s1_g,					            	//-:
		//0,										//space black
		0,										//

		};
//*****************************************************************
//displaying meter
//*****************************************************************
const unsigned char NumSeg2[] = {
s2_a | s2_b | s2_c | s2_d | s2_e | s2_f,		    //0:
		s2_b | s2_c,								//1:
		s2_a | s2_b | s2_d | s2_e | s2_g,				//2:
		s2_a | s2_b | s2_d | s2_c | s2_g,				//3:
		s2_b | s2_c | s2_f | s2_g,					//4:
		s2_a | s2_c | s2_d | s2_f | s2_g,				//5:
		s2_a | s2_c | s2_d | s2_e | s2_f | s2_g,			//6:
		s2_a | s2_b | s2_c,							//7:
		s2_a | s2_b | s2_d | s2_e | s2_f | s2_g | s2_c,	    //8:
		s2_a | s2_b | s2_c | s2_d | s2_f | s2_g,		    //9:
		s2_a | s2_b | s2_e | s2_f | s2_g | s2_c,		    //a:
		s2_d | s2_e | s2_f | s2_g | s2_c,				//b:
		s2_a | s2_d | s2_e | s2_f,					//c:
		s2_b | s2_d | s2_e | s2_g | s2_c,				//d:
		s2_a | s2_d | s2_e | s2_f | s2_g,		    	//e:
		s2_a | s2_e | s2_f | s2_g,					//f:
		s2_a | s2_b | s2_c | s2_d | s2_f | s2_g,  		//g:
		s2_b | s2_c | s2_f | s2_e | s2_g,       		//H:
		s2_c,		                            //i;
		s2_b | s2_c | s2_d | s2_e,            		//j:
		0, 		                            	//k:
		s2_d | s2_e | s2_f,            		        //L:
		0,                      		        //M:
		s2_g | s2_c | s2_e,		                    //N:
		s2_c | s2_d | s2_e | s2_g,            		//O:
		s2_a | s2_b | s2_e | s2_g | s2_f,            	//P:
		0,                              		//Q:
		s2_e | s2_g,              				//r:
		s2_a | s2_c | s2_d | s2_f | s2_g,				//S:
		s2_f | s2_e | s2_d | s2_g,           			//t:
		s2_b | s2_c | s2_d | s2_e | s2_f,            	//U:
		s2_c | s2_d | s2_e,			          	//v:
		s2_b | s2_c | s2_d | s2_e | s2_f,            	//w:
		s2_b | s2_c | s2_e | s2_f | s2_g,            	//x:
		s2_b | s2_c | s2_d | s2_e | s2_f,            	//y:
		s2_b | s2_c | s2_d | s2_e | s2_f,            	//z:
		s2_g,					            	//-:
		//0,										//space black
		0,										//¿Õ¸ñºÚ
		};
//*****************************************************************
//display buffer
//*****************************************************************
unsigned char gDispBuf[18];
//*****************************************************************
//VT, CT, PT ratio
//*****************************************************************
int32u g_ulPTV, g_ulCTV, g_ulPPT;

//*****************************************************************
//acquire ratio value
//*****************************************************************
void DispGetCTPT(void) {

#if (METER_CTPT_EN == 1)

	int16u uiCT[2], uiPT[2];
	int8u ucBuf[8];
	if ((display_mod & 0x10) == 0x00) {
		g_ulPPT = 1;
		g_ulPTV = 1;
		g_ulCTV = 1;
	} else {
#ifdef NO_FRAM
		E2P_Read((char*) ucBuf, PARA_PTCT, 8);
#else
		FRAM_Read((char*) ucBuf, PARA_PTCT, 8);
#endif

		uiCT[1] = BCD2_Word(ucBuf);
		uiCT[0] = BCD2_Word(&ucBuf[2]);
		uiPT[1] = BCD2_Word(&ucBuf[4]);
		uiPT[0] = BCD2_Word(&ucBuf[6]);
		g_ulPTV = uiPT[0] / uiPT[1];
		g_ulCTV = uiCT[0] / uiCT[1];

		if (g_ulPTV == 0) {
			g_ulPTV = 1;
		}
/////////////////////
		if (g_ulCTV == 0) {
			g_ulCTV = 1;
		}
		g_ulPPT = g_ulPTV * g_ulCTV;
	}

#else
	g_ulPPT=1;
	g_ulPTV=1;
	g_ulCTV=1;
#endif

}
//*****************************************************************
//display clear
//*****************************************************************
void DispClr(void) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
	LCDM17 = LCDM16 = LCDM15 = LCDM14 = LCDM13 = LCDM12 = LCDM11 = LCDM10 = LCDM9 =
			LCDM8 = LCDM7 = LCDM6 = LCDM5 = LCDM4 = LCDM3 = LCDM2 = LCDM1 = 0x00;
#else
	memset(gDispBuf, 0, sizeof(gDispBuf));
#endif
}

//*****************************************************************
//display test
//*****************************************************************
void DispTest(void) {
	memset(gDispBuf, 0, sizeof(gDispBuf));
	gDispBuf[0] = 0xff;
	gDispBuf[2] = 0xff;

	BU9792_Refresh(gDispBuf, 0);
}
//*****************************************************************
//display voltage mark
//*****************************************************************
void DispPhaseV(int8u Phase) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
//	S34_ON;
#else
	switch (Phase) {
	case 0:
		gDispBuf[0] |= 0x08;	//
		break;
	case 1:
		gDispBuf[2] |= 0x04;	//
		break;
	case 2:
		gDispBuf[3] |= 0x80;	//
		break;
	default:
		break;
	}
#endif
}
//*****************************************************************
//display current mark
//*****************************************************************
void DispPhaseI(int8u Phase) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
//	S22_ON;
#else
	switch (Phase) {
	case 0:
		gDispBuf[1] |= 0x08;	//
		break;
	case 1:
		gDispBuf[2] |= 0x08;	//
		break;
	case 2:
		gDispBuf[4] |= 0x80;	//
		break;
	default:
		break;
	}
#endif
}
//*****************************************************************
//display power mark
//*****************************************************************
void DispActiPower(int8u phase) {
	switch (phase) {
	case 0:	//power A
		gDispBuf[5] |= 0x10;	//power
		gDispBuf[13] |= 0x01;
		break;
	case 1:	//power B
		gDispBuf[5] |= 0x10;	//power
		gDispBuf[13] |= 0x02;
		break;
	case 2:	//power C
		gDispBuf[5] |= 0x10;	//power
		gDispBuf[13] |= 0x20;
		break;
	case 3:	//power Total
		gDispBuf[5] |= 0x10;	//power
		gDispBuf[16] |= 0x10;
		break;
	default:
		break;
	}
}
//*****************************************************************
//display active power mark
//*****************************************************************
void DispActivePower(int8u phase) {

	DispActiPower(phase);

	if (gsAttRealVal.DIR_Flag & PDirTbl[phase]) {
		//load
		gDispBuf[16] |= 0x01;
	} else {
		//log Exprot
		gDispBuf[0] |= 0x10;
	}

}
//*****************************************************************
//display reactive power mark
//*****************************************************************
void DispReavPower(int8u phase) {

	DispActiPower(phase);

	if (gsAttRealVal.DIR_Flag & QDirTbl[phase]) {
		//load
		gDispBuf[16] |= 0x01;
	} else {
		//log Exprot
		gDispBuf[0] |= 0x10;
	}

}
//*****************************************************************
//display unit
//*****************************************************************
void DispUnit(int8u ucType) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
	switch (ucType) {
		case 0:
			//kwh s33+s34+s35+s36+s41
			S33_ON;S34_ON;S35_ON;S36_ON;S41_ON;
			break;
		case 1:
			//kw s33+s34+s35+s36
			S33_ON;S34_ON;S35_ON;S36_ON;
			break;
		case 2:
			//kvarh s33+s34+s36+s37+s38+s41
			S33_ON;S34_ON;S36_ON;S37_ON;S38_ON;S41_ON;
			break;
		case 3:
			//kvar s33+s34+s36_s37+s38
			S33_ON;S34_ON;S36_ON;S37_ON;S38_ON;
			break;
		case 4:
			//Mwh S55+s34+s35+s36+s41
			S55_ON;S34_ON;S35_ON;S36_ON;S41_ON;
			break;
		case 5:
			//Mvarh s55+s34+s36+s36+s37+s41
			S55_ON;S34_ON;S36_ON;S37_ON;S38_ON;S41_ON;
			break;
		case 6:
			//Fre + HZ s42
			S42_ON;S27_ON;
			break;
		case 7:
			//V s34
			S34_ON;
			break;
		case 8:
			//KV s33+s34
			S33_ON;S34_ON;
			break;
		case 9:
			//KA s33+s36+s37
			S33_ON;S36_ON;S37_ON;
			break;
		case 10:
			//A s36+s37
			S36_ON;S37_ON;
			break;
		case 11:
			//unit angle s20+s43
			S20_ON;S43_ON;
			break;
		case 12:
			//cos& S19
			S19_ON;
			break;
		default:
			break;
		}
#endif
#ifdef HARDWARE_TWO//with four quadrants reactive
//#ifdef HARDWARE_TWO//
	switch (ucType) {
	case 0:
		//kwh s41+s42+s43+s44+s49
		gDispBuf[10] |= 0x07;
		gDispBuf[11] |= 0x20;
		gDispBuf[17] |= 0x02;
		break;
	case 1:
		//kw s41+s42+s43+s44
		gDispBuf[10] |= 0x06;
		gDispBuf[11] |= 0x20;
		gDispBuf[17] |= 0x02;
		break;
	case 2:
		//kvarh s41+s42+s44+s45+s46+s49
		gDispBuf[10] |= 0x07;
		gDispBuf[11] |= 0x03;
		gDispBuf[17] |= 0x02;
		break;
	case 3:
		//kvar s41+s42+s44+s45+s46
		gDispBuf[10] |= 0x06;
		gDispBuf[11] |= 0x03;
		gDispBuf[17] |= 0x02;
		break;
	case 13:
		//Mwh M+s42+s43+s44+s49
		gDispBuf[10] |= 0x43;
		gDispBuf[11] |= 0x20;
		gDispBuf[17] |= 0x02;
		break;
	case 14:
		//Mvarh M+s42+s44+s45+s46+s49
		gDispBuf[10] |= 0x43;
		gDispBuf[11] |= 0x02;
		gDispBuf[17] |= 0x02;
		break;
	case 4:
		//HZ s50
		gDispBuf[10] |= 0x20;
		break;
	case 5:
		//V s42
		gDispBuf[10] |= 0x02;
		break;
	case 11:
		//KV s41+s42
		gDispBuf[10] |= 0x06;
		break;
	case 12:
		//KA s41+s44+s45
		gDispBuf[10] |= 0x04;
		gDispBuf[17] |= 0x02;
		gDispBuf[11] |= 0x02;
		break;
	case 6:
		//A s44+s45
		gDispBuf[17] |= 0x02;
		gDispBuf[11] |= 0x02;
		break;
	case 7:
		//unit ¡ã+& A s51+s17+s16
		//µ¥Î»¡ã+& A s51+s17+s16
		gDispBuf[10] |= 0x10;
		gDispBuf[14] |= 0x01;
		gDispBuf[13] |= 0x01;
		break;
	case 8:
		//µ¥Î»¡ã+& B s51+s17+s15
		gDispBuf[10] |= 0x10;
		gDispBuf[14] |= 0x01;
		gDispBuf[13] |= 0x02;
		break;
	case 9:
		//unit ¡ã+& C s51+s17+s14
		//µ¥Î»¡ã+& C s51+s17+s14
		gDispBuf[10] |= 0x10;
		gDispBuf[14] |= 0x01;
		gDispBuf[13] |= 0x20;
		break;
	case 10:
		//cos&
		gDispBuf[17] |= 0x10;
		break;
	default:
		break;
	}
#else
	switch(ucType)
	{
		case 0:
		//kwh
		gDispBuf[10]|=0x40+0x20+0x10+0x02;
		gDispBuf[11]|=0x08;
		break;
		case 1:
		//kw
		gDispBuf[10]|=0x40+0x20+0x10+0x02;
		break;
		case 2:
		//kvarh
		gDispBuf[10]|=0x40+0x20+0x02+0x04;
		gDispBuf[11]|=0x40;
		gDispBuf[11]|=0x08;
		break;
		case 3:
		//kvar
		gDispBuf[10]|=0x40+0x20+0x02+0x04;
		gDispBuf[11]|=0x40;
		break;
		case 13:
		//Mwh
		gDispBuf[10]|=0x20+0x10+0x02;
		gDispBuf[11]|=0x04+0x08;
		break;
		case 14:
		//Mvarh
		gDispBuf[10]|=0x20+0x02+0x04;
		gDispBuf[11]|=0x04+0x40+0x08;
		break;
		case 4:
		//HZ
		gDispBuf[11]|=0x10;
		break;
		case 5:
		//V
		gDispBuf[10]|=0x20;
		break;
		case 11:
		//V
		gDispBuf[10]|=0x40;
		gDispBuf[10]|=0x20;
		break;
		case 12:
		//A
		gDispBuf[10]|=0x40;
		gDispBuf[10]|=0x06;
		break;
		case 6:
		//A
		gDispBuf[10]|=0x06;
		break;
		case 7:
		//unit ¡ã+& A
		//µ¥Î»¡ã+& A
		gDispBuf[10]|=0x01;
		gDispBuf[14]|=0x01;
		gDispBuf[13]|=0x01;
		break;
		case 8:
		//unit ¡ã+& B
		//µ¥Î»¡ã+& B
		gDispBuf[10]|=0x01;
		gDispBuf[14]|=0x01;
		gDispBuf[13]|=0x02;
		break;
		case 9:
		//unit ¡ã+& C
		//µ¥Î»¡ã+& C
		gDispBuf[10]|=0x01;
		gDispBuf[14]|=0x01;
		gDispBuf[13]|=0x20;
		break;
		case 10:
		//cos&
		gDispBuf[17]|=0x10;
		break;
		default:break;
	}
#endif

}

//*****************************************************************
//display data
//*****************************************************************
void DispNum(int8u Num, int8u No) {
	int8u ucTmp, ucCh, Byte;//, gDispBuf[5];

	ucTmp = NumSeg2[Num];
	gDispBuf[0] = (ucTmp & 0x0f) << 4;
	gDispBuf[1] = (ucTmp & 0xf0) >> 4;
	gDispBuf[2] = NumSeg2[Num];

	ucTmp = NumSeg[Num];
	gDispBuf[3] = (ucTmp & 0xf0);
	gDispBuf[4] = (ucTmp & 0x0f);

#ifdef SINGLE_PHASE_MULTI_TARIFF
	switch (No) {
	case 1:
		LCDM1 &= 0x1F;
		LCDM1 |= gDispBuf[0];
		LCDM2 &= 0xF0;
		LCDM2 |= gDispBuf[1];
		break;
	case 2:
		LCDM2 &= 0x1F;
		LCDM2 |= gDispBuf[0];
		LCDM3 &= 0xF0;
		LCDM3 |= gDispBuf[1];
		break;
	case 3:
		LCDM3 &= 0x1F;
		LCDM3 |= gDispBuf[0];
		LCDM4 &= 0xF0;
		LCDM4 |= gDispBuf[1];
		break;
	case 4:
		LCDM4 &= 0x1F;
		LCDM4 |= gDispBuf[0];
		LCDM5 &= 0xF0;
		LCDM5 |= gDispBuf[1];
		break;
	case 6:
		LCDM8 &= 0x1F;
		LCDM8 |= gDispBuf[0];
		LCDM9 &= 0xF0;
		LCDM9 |= gDispBuf[1];
		break;
	case 5:
		LCDM6 &= 0x01;
		LCDM6 |= gDispBuf[2];
		break;
	case 7:
		LCDM10 &= 0x01;
		LCDM10 |= gDispBuf[2];
		break;
	case 8:
		LCDM11 &= 0x01;
		LCDM11 |= gDispBuf[2];
		break;
	case 11:
		LCDM7 &= 0x01;
		LCDM7 |= gDispBuf[2];
		break;
	case 9:
		LCDM13 &= 0x0F;
		LCDM13 |= gDispBuf[3];
		LCDM14 &= 0xF8;
		LCDM14 |= gDispBuf[4];
		break;
	case 10:
		LCDM15 &= 0x0F;
		LCDM15 |= gDispBuf[3];
		LCDM16 &= 0xF8;
		LCDM16 |= gDispBuf[4];
		break;
	}

#else
	const int8u NoTbl[] = { 1, 2, 3, 4, 6, 7, 8, 9, 11, 14, 16 };
	if (Num > 37) {
		Num = 0;
	}
	Byte = NoTbl[No - 1];

	switch (No) {
	case 1:
	case 2:
	case 5:
	case 6:
	ucTmp = NumSeg[Num];
	gDispBuf[Byte - 1] |= (ucTmp & 0x0f);
	gDispBuf[Byte] |= (ucTmp & 0xf0);
	break;

	case 3:
	case 4:
	case 7:
	case 8:
		ucTmp = NumSeg[Num];
		ucCh = (ucTmp & 0x0f) << 4;
		ucTmp >>= 4;
		ucTmp += ucCh;
		gDispBuf[Byte] |= ucTmp;
		break;
	case 9:
	case 10:
		ucTmp = NumSeg2[Num];
		gDispBuf[Byte] |= ucTmp;
		break;
	case 11:
		ucTmp = NumSeg2[Num];
		gDispBuf[Byte - 1] |= (ucTmp & 0xf0) >> 4;
		gDispBuf[Byte] |= (ucTmp & 0x0f) << 4;
		break;
	default:
		break;

	}
#endif
}

//*****************************************************************
//display decimal dots
// DotSta = 1-> display on but off
//*****************************************************************
void DispDot(int8u DotSta, int8u DotNo) {
	const struct DotNo {
		int8u ucByte;
		int8u ucBit;
	} DotTbl[] = { 	2, 0x02,	//1
					2, 0x01,	//2
					5, 0x40,	//3
					5, 0x20,	//4
					6, 0x08,	//5
					7, 0x01,	//6
					7, 0x04,	//7
					7, 0x02,	//8
					9, 0x80		//9
				};

	int8u Byte, Bit;

	if (DotNo == 0) {
		return;
	}
	Byte = DotTbl[DotNo - 1].ucByte;
	Bit = DotTbl[DotNo - 1].ucBit;
	if (DotSta == 1) {
		gDispBuf[Byte] |= Bit;
	} else {
		gDispBuf[Byte] &= Bit;
	}
}

//*****************************************************************
//display one number and last four numbers
//*****************************************************************
void DispTimes(int16u ucTime) {
	//int8u i;

	//maximum four places
	DispNum(ucTime % 10, 8);
	ucTime /= 10;
	DispNum(ucTime % 10, 7);
	ucTime /= 10;
	DispNum(ucTime % 10, 6);
	ucTime /= 10;
	DispNum(ucTime % 10, 5);
}
//*****************************************************************
//auquire error type
//*****************************************************************
int8u GetErrPtr(void) {
	const int8u ucBitMask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

	int8u i;
	int16u iFlag;

	iFlag = EventFlag.States;

	meter_state[1] = iFlag;

	DisK.ErrNum = 0;
	for (i = 0; i < 7; i++) {
		if (iFlag & ucBitMask[i]) {
			DisK.ErrNum++;
			break;
		}
	}
	if (DisK.ErrNum == 0) {
		if (DisK.DisMode != DISP_MODE_KEY) {
			DisK.DisMode = DISP_MODE_AUTO;
		}
		DisK.ErrPtr = 0;
		return FALSE;
	}

	for (i = 0; i < 7; i++) {
		if (DisK.ErrPtr > 7) {
			DisK.ErrPtr = 0;
		}
		if (iFlag & ucBitMask[DisK.ErrPtr]) {
			break;
		}
		DisK.ErrPtr++;
	}

	i = 0;
	//DisK.ErrPtr=i;

	return TRUE;

}
//*****************************************************************
//display error
//*****************************************************************
void DispErr(int8u ucNum) {
#ifdef BNTHANG
	DispClr();
#endif
	DisK.DisMode = DISP_MODE_ERR;

	DispNum('E' - 0x41 + 10, 3);
	DispNum('R' - 0x41 + 10, 4);
	DispNum('R' - 0x41 + 10, 5);
	DispNum('Z' - 0x41 + 11, 6);
	DispNum(0, 7);
	DispNum(ucNum, 8);

}
//*****************************************************************
//display phase order
//*****************************************************************
void Disp_VPHASE() {
	//if(meter_state[1]&0x08)//split-phase
	if (meter_state[1] & 0x08) //
			{
		DispNum('Z' - 0x41 + 11, 1);
		DispNum('Z' - 0x41 + 11, 2);
		DispNum('Z' - 0x41 + 11, 3);
		DispNum('Z' - 0x41 + 11, 4);
		DispNum('Z' - 0x41 + 11, 5);
		DispNum('Z' - 0x41 + 11, 6);
		DispNum('Z' - 0x41 + 11, 7);
		DispNum('Z' - 0x41 + 11, 8);
	} else {
		//if(meter_state[1]&0x04)//wrong phase order
		if (meter_state[1] & 0x04) //
				{
			DispNum('A' - 0x41 + 10, 2);
			DispNum('Z' - 0x41 + 11, 3);
			DispNum('C' - 0x41 + 10, 4);
			DispNum('Z' - 0x41 + 11, 5);
			DispNum('B' - 0x41 + 10, 6);
		}
		//else//correct phase order
		else //
		{
			DispNum('A' - 0x41 + 10, 2);
			DispNum('Z' - 0x41 + 11, 3);
			DispNum('B' - 0x41 + 10, 4);
			DispNum('Z' - 0x41 + 11, 5);
			DispNum('C' - 0x41 + 10, 6);
		}
	}
}
//*****************************************************************
//display time
//*****************************************************************
void DispTime(int8u *ucClk) {

#ifdef SINGLE_PHASE_MULTI_TARIFF
	DispClr();
  	DispNum(ucClk[0] >> 4, 3);
	DispNum(ucClk[0] & 0x0f, 4);
	DispNum(ucClk[1] >> 4, 5);
	DispNum(ucClk[1] & 0x0f, 6);
	DispNum(ucClk[2] >> 4, 7);
	DispNum(ucClk[2] & 0x0f, 8);
	S46_ON;
	S47_ON;
	S50_ON;
	S51_ON;
	S11_ON;
#else
	DispNum(ucClk[0] >> 4, 3);
	DispNum(ucClk[0] & 0x0f, 4);
	DispNum(ucClk[1] >> 4, 5);
	DispNum(ucClk[1] & 0x0f, 6);
	DispNum(ucClk[2] >> 4, 7);
	DispNum(ucClk[2] & 0x0f, 8);
	DispDot(1, 7);
	DispDot(1, 8);
	DispDot(1, 3);
	DispDot(1, 4);
	//time
	gDispBuf[12] |= 0x01;
	//R
//	gDispBuf[12]|=0x80;
//	DispNum(8, 9);	
#endif
}
//*****************************************************************
//display date
//*****************************************************************
void DispData(int8u *ucClk) {
#ifdef BNTHANG
	DispClr();
#endif
	DispNum(ucClk[0] >> 4, 1);
	DispNum(ucClk[0] & 0x0f, 2);
	DispNum(ucClk[1] >> 4, 3);
	DispNum(ucClk[1] & 0x0f, 4);
	DispNum(2, 5);
	DispNum(0, 6);
	DispNum(ucClk[2] >> 4, 7);
	DispNum(ucClk[2] & 0x0f, 8);
#ifdef SINGLE_PHASE_MULTI_TARIFF
	S44_ON;
	S45_ON;
	S46_ON;
	S47_ON;
	S12_ON;
#else
	DispDot(1, 1);
	DispDot(1, 2);
	DispDot(1, 3);
	DispDot(1, 4);
	//data
	gDispBuf[13] |= 0x10;
#endif
}

//*****************************************************************
//display BCD code, pBcd display pointer, uclen lengnth, ucDot decimal places, dir-flag direction mark
//*****************************************************************
void DispBCD(int8u *pBcd, int8u ucLen, int8u ucDot, int8u LR, int8u dir_flag) {
	int8u i, f, k;
	int8u ucBuf[10];
	int8u *Ptr;
	const int8u ucDotTlb[] = { 0, 9, 7, 5, 3 };

	memset(ucBuf, 0, sizeof(ucBuf));

	if (LR == 0) {
		Ptr = pBcd + ucLen - 1;
		for (i = 0; i < ucLen; i++) {
			ucBuf[2 * i] = *Ptr >> 4;
			ucBuf[2 * i + 1] = *Ptr & 0x0f;
			Ptr--;
		}
	} else {
		for (i = 0; i < ucLen; i++) {
			ucBuf[2 * i] = *pBcd >> 4;
			ucBuf[2 * i + 1] = *pBcd & 0x0f;
			pBcd++;
		}
	}

	f = 0;
	ucLen <<= 1;	//*2
	k = ucLen;
	for (i = 0; i < ucLen; i++) {

		if ((ucBuf[i] == 0) || (ucBuf[i] > 9)) {
			continue;
		} else {
			if (f == 0) {
				k = i;
			}
			f = 1;
		}
	}
	k = ucLen - k;
	//if(k<ucDot+1)//whole number is 0
	if (k < ucDot + 1)	//
			{
		k = ucDot + 1;
	}
	ucLen -= 1;
	for (i = 0; i < k; i++) {
		DispNum(ucBuf[ucLen - i], 8 - i);
	}
	//display flag / Liao Bin
	if (dir_flag == 1) {
		DispNum(36, 8 - k);
	}
	DispDot(1, ucDotTlb[ucDot]);
}

//*****************************************************************
//real time power display forward reverse active, reactive, apparent
//type 0: forward active 1: reverse active
//       2:forward reactive 3:reverse reactive
//       4:forward apparent 5:reverse apparent
//*****************************************************************
void DispEnergy(int8u ucFee, int8u Type) {
	int8u ucBuf[5];
	int8u ucDot = 0;
	int8u ucMh = 0; //0Ê±Ç§WÊ±   1Ê±£¬MWh
	int32u ulTmp;
	long long udTmp;

	DispClr();
#ifdef SINGLE_PHASE_MULTI_TARIFF
	if (Type == 0) {
		Long_BCD4aA(ucBuf, rn8209a_rms.Active_energy);
	}
	else if (Type == 1) {// lag
		Long_BCD4aA(ucBuf, rn8209a_rms.Q_Lag);
		S53_ON;
	}
	else if (Type == 2) {// lead
		Long_BCD4aA(ucBuf, rn8209a_rms.Q_Lead);
		S54_ON;
	}

#else
	//if(Type%2)//reverse
	if (Type%2) //
		//gDispBuf[16]|=0x01;//display Inprot
		gDispBuf[16] |= 0x01;       //
	else
		//gDispBuf[0]|=0x10;//display Exprot
		gDispBuf[0] |= 0x10;       //

	FRAM_Read((char*) ucBuf, (EC_Pp0 + 5 * ucFee + 27 * Type), 5);
#endif
	//acquire CT,PT value
	DispGetCTPT();

	//default two decimals
		//default two decimals
	ulTmp = BCD4_Long((char*) ucBuf);
	udTmp = (unsigned long long) ulTmp
			+ ((unsigned long long) BCD_Byte(ucBuf[4]))
					* (unsigned long long) 100000000;
//	udTmp *= g_ulPPT;
	ucDot = DOT[0] & 0x03;

//#ifdef  HARDWARE_ONE
	ucMh = DOT[1] & 0x01;
	if (ucMh) {
		udTmp /= 1000;
	}
//#endif

	if (ucDot >= 2) {
		ucDot = 2;
		S51_ON;
	}
	if (ucDot == 0) {
		udTmp /= 100;
	} else if (ucDot == 1) {
		udTmp /= 10;
		S52_ON;
	}
	while (udTmp > 99999999) {

		if (ucDot > 0) {
			ucDot--;
			udTmp /= 10;
		}
		if (ucDot == 0) {
			break;
		}
	}

	DispBCD(ucBuf, 5, ucDot, 0, 0);
	//if(Type<2)//active unit
	if (Type < 2)  //
			{
		if (ucMh)
			DispUnit(4);// Mwh
		else
			DispUnit(0);// kwh
	}
	//else//reactive, apparent unit
	else  //
	{
		if (ucMh)
			DispUnit(5);// Mvarh
		else
			DispUnit(2);// Kvarh
	}
	//total
	if (ucFee == 0) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S14_ON;// Total
#else
		gDispBuf[16] |= 0x10;
#endif
	}
	//split-tariff
	else {	//Rate
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S15_ON;//Rate
#else
		gDispBuf[17] |= 0x20;
#endif
		DispNum(ucFee, 11);
	}
}
/*****************************************************************
 //function description: four quadrants reactive display
 //parameter description:
 //ucFee: tariff
 //quad: quadrant
 **(**************************************************************/
void DispRqEnergy(int8u ucFee, int8u quad) {
	int8u ucBuf[5];
	int8u ucDot = 0;
	int8u ucMh = 0; //0Ê±Ç§WÊ±   1Ê±£¬MWh
	int32u ulTmp;
	long long udTmp;
	int16u add;
	//acquire CT, PT value
	DispGetCTPT();

	//calculate address
	// if(ucFee==0)//total power quantity
	if (ucFee == 0)  //
			{
		add = EC_Rq1 + 22 * (quad - 1);
		gDispBuf[16] |= 0x10;
	}
	//else//each tariff power quantity
	else  //
	{
		add = EC_Rq1F1 + 5 * (ucFee - 1) + 22 * (quad - 1);
		gDispBuf[17] |= 0x20;
		DispNum(ucFee, 11);
	}
	//four quadrants mark display
	gDispBuf[17] |= 0x04;  //Q1
	switch (quad) {
	case 1:  //Q2
		gDispBuf[11] |= 0x04;
		break;
	case 2:  //Q3
		gDispBuf[11] |= 0x40;
		break;
	case 3:  //Q4
		gDispBuf[11] |= 0x80;
		break;
	case 4:  //Q5
		gDispBuf[11] |= 0x08;
		break;
	default:
		break;
	}
	FRAM_Read((char*) ucBuf, add, 5);

	//default two decimals
	ulTmp = BCD4_Long((char*) ucBuf);
	udTmp = (unsigned long long) ulTmp
			+ ((unsigned long long) BCD_Byte(ucBuf[4]))
					* (unsigned long long) 100000000;
	udTmp *= g_ulPPT;

	ucDot = DOT[0] & 0x03;

#ifdef  HARDWARE_ONE
	ucMh = DOT[1] & 0x01;
	if (ucMh) {
		udTmp /= 1000;
	}
#endif

	if (ucDot > 2) {
		ucDot = 2;
	}
	if (ucDot == 0) {
		udTmp /= 100;
	} else if (ucDot == 1) {
		udTmp /= 10;
	}
	while (udTmp > 99999999) {

		if (ucDot > 0) {
			ucDot--;
			udTmp /= 10;
		}
		if (ucDot == 0) {
			break;
		}
	}

	Long_BCD4((char*) ucBuf, (unsigned long) (udTmp % 100000000));
	ucBuf[4] = (unsigned char) ((udTmp / 100000000) % 100);
	ucBuf[4] = Byte_BCD(ucBuf[4]);

	DispBCD(ucBuf, 5, ucDot, 0, 0);
	if (ucMh)
		DispUnit(14);
	else
		DispUnit(2);
}
/*****************************************************************
 //function description: user-defined register display
 //parameter description:
 //Type: register number
 ****************************************************************/
void DispUserde(int8u Type) {
	int8u ucBuf[6];
	int8u ucDot = 0;
	int8u ucMh = 0;  //0Ê±Ç§WÊ±   1Ê±£¬MWh
	int32u ulTmp;
	long long udTmp;
	//acquire CT, PT value
	DispGetCTPT();
	//default two decimals
	ulTmp = BCD4_Long((char*) UserdeBCD[Type]);
	udTmp = (unsigned long long) ulTmp
			+ ((unsigned long long) BCD2_Word(&UserdeBCD[Type][4]))
					* (unsigned long long) 100000000;
	udTmp *= g_ulPPT;

	ucDot = DOT[0] & 0x03;

#ifdef  HARDWARE_ONE
	ucMh = DOT[1] & 0x01;
	if (ucMh) {
		udTmp /= 1000;
	}
#endif

	if (ucDot > 2) {
		ucDot = 2;
	}
	if (ucDot == 0) {
		udTmp /= 100;
	} else if (ucDot == 1) {
		udTmp /= 10;
	}
	while (udTmp > 99999999) {

		if (ucDot > 0) {
			ucDot--;
			udTmp /= 10;
		}
		if (ucDot == 0) {
			break;
		}
	}

	Long_BCD4((char*) ucBuf, (unsigned long) (udTmp % 100000000));
	Word_BCD2((char*) (&ucBuf[4]),
			(unsigned int) ((udTmp / 100000000) % 10000));

	//DispBCD(ucBuf,6,ucDot,0,0);//display number
	DispBCD(ucBuf, 6, ucDot, 0, 0);  //ÏÔÊ¾Êý×Ö

	ucBuf[0] = 0;
	ucBuf[1] = 0;
	FRAM_Read((char*) ucBuf, USER_DEFINE + Type * 2, 2);
	//if(ucMh)//display unit
	if (ucMh)  //ÏÔÊ¾µ¥Î»
	{
		if (ucBuf[0] > 0)
			DispUnit(13);
		else
			DispUnit(14);
	} else {
		if (ucBuf[0] > 0)
			DispUnit(0);
		else
			DispUnit(2);
	}
	DISP_Userde()
	;
	DispNum(Type + 1, 11);
}
//*****************************************************************
//maximum demand display
//*****************************************************************
void DispMaxDem(int8u ucFee, int8u ucType) {
	int8u ucBuf[20];
	int8u ucDot = 0;
	int32u ulTmp;
	long long udTmp;
#ifdef BNTHANG
	DispClr();
#endif
	ucFee = ucFee;

	//read demand value
	if (ucType == 0) {

#ifdef NO_FRAM

#else
		FRAM_Read((char*) ucBuf, MD_Pp, 3);
#endif
		//acquire CT, PT value
		DispGetCTPT();

		ucBuf[3] = 0;
		ulTmp = BCD4_Long((char*) ucBuf);
		udTmp = (unsigned long long) ulTmp * (unsigned long long) g_ulPPT;

		ucDot = 3;
		while (udTmp > 99999999) {
			udTmp /= 10;
			ucDot--;
			if (ucDot == 0) {
				break;
			}
		}
		Long_BCD4((char*) ucBuf, (unsigned long) (udTmp % 100000000));
		Long_BCD4(((char*) ucBuf) + 4, (unsigned long) (udTmp / 100000000));

		DispBCD(ucBuf, 5, ucDot, 0, 0);

		//KW
		DispUnit(1);
		//
	}
	//read demand sending time
	else if (ucType == 1) {

#ifdef NO_FRAM

#else
		FRAM_Read((char*) ucBuf, MD_Pp + 3, 5);
#endif
		//ÏÔÊ¾time
		ucBuf[10] = ucBuf[1];	//hh
		ucBuf[11] = ucBuf[0];	//MM
		ucBuf[12] = 0;		//ss
		DispTime(&ucBuf[10]);
	} else
	//{	//display data
	{
#ifdef NO_FRAM

#else
		FRAM_Read((char*) ucBuf, MD_Pp + 3, 5);
#endif
		ucBuf[10] = ucBuf[2];	//dd
		ucBuf[11] = ucBuf[3];	//mm
		ucBuf[12] = ucBuf[4];	//yy
		DispData(&ucBuf[10]);
	}
#ifdef SINGLE_PHASE_MULTI_TARIFF
	S5_ON;S6_ON;
#else
	//display MAX Demand
	gDispBuf[15] |= 0x20 + 0x10;
#endif
}
//*****************************************************************
//display ID table number
//*****************************************************************
void DispMeterID(void) {
	int8u i;
	int8u ucBuf[12];

#ifdef BNTHANG
	DispClr();
#endif
//ID	
#ifdef SINGLE_PHASE_MULTI_TARIFF
	MEM_Read((char*) &ucBuf[0], DeviceAddr + 4, 8, Mem_E2PROM);
	S1_ON;
#else
	MEM_Read((char*) &ucBuf[0], DeviceAddr + 4, 8, Mem_FRAM);
	gDispBuf[16] |= 0x08;
#endif
	
//	MEM_Read((char*) &ucBuf[0], DeviceAddr + 4, 8, Mem_FRAM);

	for (i = 0; i < 8; i++) {
		DispNum(ucBuf[i] - '0', i + 1);
	}
	

}

//*****************************************************************
//parameter page display
//*****************************************************************
void DispPara(int8u type, int8u Page) {
	switch (type) {
	case 1:		//PAGA
		DISP_PARA();
		break;
	case 2:		//
		DISP_POWER();
		break;
	case 3:
		DISP_HMD();
		break;
	case 4:
		DISP_HBI()
		;
		break;
	case 5:
		DISP_PROG();
		break;
	case 6:
		DISP_PCUT();
		break;
	case 7:
		DISP_VTPT()
		;
		break;
#ifdef HARDWARE_TWO
	case 8:
		DISP_Userde()
		;
		break;
#endif
	default:
		break;

	}
	if (Page != 0) {
		DispNum(Page, 8);
	} else {
		DispNum(0x0e, 8);
	}
}

//*****************************************************************
//history power quantity display
//*****************************************************************
void DispHisCE(int8u id, int8u Type) {

	int32u ulAdr;
	int8u ucBuf[10];
	int8u ucOfs, i;
	int16u Info;
	int16u In;
	int8u ucMh = 0;
	int8u ucDot = 0;
	int32u ulTmp;
	long long udTmp;

	memset(ucBuf, 0, sizeof(ucBuf));

#ifdef  HARDWARE_ONE
	ucMh = DOT[1] & 0x01;
#endif

	//forward active
	if (Type < 5) {
		In = 0x0000;
		ucOfs = Type * 5;
		//gDispBuf[0]|=0x10;//display Exprot
		gDispBuf[0] |= 0x10; //ÏÔÊ¾Exprot
		if (Type == 0)
		//{					//total
				{					//×Ü
			gDispBuf[16] |= 0x10;
		} else {	//Rate
			gDispBuf[17] |= 0x20;
			DispNum(Type, 11);
		}
		if (ucMh)
			DispUnit(13);
		else
			DispUnit(0);
	}
	//total load
	else if (Type == 5) {
		In = 0x0020;
		ucOfs = 0;

		gDispBuf[16] |= 0x10;
		//display Lag Exprot
		gDispBuf[0] |= 0x10;
		if (ucMh)
			DispUnit(14);
		else
			DispUnit(2);
	}
	//total lag
	else if (Type == 6) {
		In = 0x0030;
		ucOfs = 0;
		gDispBuf[16] |= 0x10;
		//display load
		gDispBuf[16] |= 0x01;
		if (ucMh)
			DispUnit(14);
		else
			DispUnit(2);
	} else if (Type > 8) {
		//if(Type<0x1d)//reactive four quadrants
		if (Type < 0x1d)    //
				{
			ucOfs = 0;
			//if(Type<0x0e)//first quadrant
			if (Type < 0x0e)    //
					{
				//if(Type==9)//total
				if (Type == 9)    //×Ü
						{
					In = 0x00C0;
					gDispBuf[16] |= 0x10;    //Total
				}
				//else//each tariff
				else    //
				{
					In = 0x0100;
					ucOfs = (Type - 10) * 5;
					gDispBuf[17] |= 0x20;    //Rate
					DispNum((Type - 9), 11);
				}
				//gDispBuf[11]|=0x04;//first quadrant
				gDispBuf[11] |= 0x04;    //

			} else if (Type < 0x13) {
				//if(Type==0x0e)//total
				if (Type == 0x0e)    //
						{
					In = 0x00D0;
					gDispBuf[16] |= 0x10;    //Total
				}
				//else//each tariff
				else    //
				{
					In = 0x0110;
					ucOfs = (Type - 0x0f) * 5;
					gDispBuf[17] |= 0x20;    //Rate
					DispNum((Type - 0x0e), 11);
				}
				//gDispBuf[11]|=0x40;//second quadrant
				gDispBuf[11] |= 0x40;    //
			} else if (Type < 0x18) {
				//if(Type==0x13)//total
				if (Type == 0x13)    //×Ü
						{
					In = 0x00E0;
					gDispBuf[16] |= 0x10;    //Total
				}
				//else//each tariff
				else    //
				{
					In = 0x0120;
					ucOfs = (Type - 0x14) * 5;
					gDispBuf[17] |= 0x20;    //Rate
					DispNum((Type - 0x13), 11);
				}
				//gDispBuf[11]|=0x80;//third quadrant
				gDispBuf[11] |= 0x80;    //
			} else if (Type < 0x1d) {
				//if(Type==0x18)//total
				if (Type == 0x18)    //
						{
					In = 0x00F0;
					gDispBuf[16] |= 0x10;    //Total
				}
				//else//each tariff
				else    //
				{
					In = 0x0130;
					ucOfs = (Type - 0x19) * 5;
					gDispBuf[17] |= 0x20;    //Rate
					DispNum((Type - 0x18), 11);
				}
				//gDispBuf[11]|=0x08;//forth quadrant
				gDispBuf[11] |= 0x08;    //
			}

			if (ucMh)
				DispUnit(14);
			else
				DispUnit(2);

			gDispBuf[17] |= 0x04;    //Q1
			//else if(Type<0x22)//reverse reactive
		} else if (Type < 0x22)		 //
				{
			In = 0x0010;
			ucOfs = (Type - 0x1d) * 5;
			//gDispBuf[16]|=0x01;//display Inprot
			gDispBuf[16] |= 0x01;		 //
			if (Type == 0x1d)
			// {			        //total
					{					//
				gDispBuf[16] |= 0x10;
			} else {	//Rate
				gDispBuf[17] |= 0x20;
				DispNum((Type - 0x1d), 11);
			}
			if (ucMh)
				DispUnit(13);
			else
				DispUnit(0);
			//  }else if(Type<0X2c)//apparent power quantity
		} else if (Type < 0X2c)	//
				{
			ucOfs = 0;
			//if(Type<0x27)//forward
			if (Type < 0x27)	//
					{
				In = 0x0040;
				ucOfs = (Type - 0x22) * 5;
				// gDispBuf[0]|=0x10;//display Exprot
				gDispBuf[0] |= 0x10;	//
				if (Type == 0x22)
				// {				 //total
						{					//×Ü
					gDispBuf[16] |= 0x10;
				} else {	//Rate
					gDispBuf[17] |= 0x20;
					DispNum((Type - 0x22), 11);
				}
			}
			//else//reverse
			else	//·´Ïò
			{
				In = 0x0050;
				ucOfs = (Type - 0x27) * 5;
				//gDispBuf[16]|=0x01;//display Inprot
				gDispBuf[16] |= 0x01;	//
				if (Type == 0x27)
				// {					//total
						{					//
					gDispBuf[16] |= 0x10;
				} else {	//Rate
					gDispBuf[17] |= 0x20;
					DispNum((Type - 0x27), 11);
				}
			}
			if (ucMh)
				DispUnit(14);
			else
				DispUnit(2);
		}
	}

	if (Type == 7) {
		//ssmmhhDDMMyy
		FRAM_Read((char*) ucBuf, BILLYMDHms, 6);
		//display tim
		for (i = 0; i < 3; i++) {
			ucBuf[6 + i] = ucBuf[2 - i];
		}
		DispTime(&ucBuf[6]);
	} else if (Type == 8) {
		FRAM_Read((char*) ucBuf, BILLYMDHms, 6);
		//display tim
		ucBuf[6] = ucBuf[3];
		ucBuf[7] = ucBuf[4];
		ucBuf[8] = ucBuf[5];

		//display data
		DispData(&ucBuf[6]);
	} else {
		if (TRUE == GetBillAdr(id, In, 0, &ulAdr, &Info)) {
			//total active
			MEM_Read((char*) &ucBuf[0], ulAdr + ucOfs, 5, Mem_DFlash);
		} else {
			memset(ucBuf, 0, sizeof(ucBuf));
		}
		//acquire CT, PT value
		DispGetCTPT();

		ulTmp = BCD4_Long((char*) ucBuf);
		udTmp = (unsigned long long) ulTmp
				+ ((unsigned long long) BCD_Byte(ucBuf[4]))
						* ((unsigned long long) 100000000);
		udTmp *= g_ulPPT;
		if (ucMh) {
			udTmp /= 1000;
		}
		ucDot = 2;
		while (udTmp > 99999999) {
			udTmp /= 10;
			ucDot--;
			if (ucDot == 0) {
				break;
			}
		}
		Long_BCD4((char*) ucBuf, (unsigned long) (udTmp % 100000000));
		Long_BCD4(((char*) ucBuf) + 4, (unsigned long) (udTmp / 100000000));
		DispBCD(ucBuf, 5, ucDot, 0, 0);
	}

	DISP_HBI()
	;
	//display MAX Demand
	//gDispBuf[15]|=0x20+0x10;
	//
	//DispNum(id+1, 11);
}

/*****************************************************************
 void DispHisCE(int8u id,int8u Type)
 {

 int32u ulAdr;
 int8u ucBuf[10];
 int8u ucOfs,i;
 int16u Info;
 int16u In;
 int8u  ucMh = 0;
 int8u ucDot=0;
 int32u ulTmp;
 long long   udTmp;

 memset(ucBuf,0,sizeof(ucBuf));

 #ifdef  HARDWARE_ONE
 ucMh  = DOT[1] & 0x01;
 #endif

 //forward active
 //ÕýÏòÓÐ¹¦
 if(Type<5)
 {
 In=0x0000;
 ucOfs=Type*5;
 if(Type==0)
 //{					//total
 {					//×Ü
 gDispBuf[16]|=0x10;
 }
 else
 {	//Rate
 gDispBuf[17]|=0x20;
 DispNum(Type, 11);
 }
 if(ucMh)
 DispUnit(13);
 else
 DispUnit(0);
 }
 //total load
 //×Ü load
 else if(Type==5)
 {
 In=0x0020;
 ucOfs=0;

 gDispBuf[16]|=0x10;
 //display Lag
 //ÏÔÊ¾Lag
 gDispBuf[0]|=0x10;
 if(ucMh)
 DispUnit(14);
 else
 DispUnit(2);

 }
 //total lag
 //×Ü lag
 else if(Type==6)
 {
 In=0x0030;
 ucOfs=0;
 gDispBuf[16]|=0x10;
 //display load
 //ÏÔÊ¾load
 gDispBuf[16]|=0x01;
 if(ucMh)
 DispUnit(14);
 else
 DispUnit(2);
 }


 if(Type<7)
 {
 if(TRUE==GetBillAdr(id, In, 0,&ulAdr,&Info))
 {
 //total active
 //×ÜÓÐ¹¦
 MEM_Read((char*)&ucBuf[0], ulAdr+ucOfs, 5,Mem_DFlash);
 }
 else
 {
 memset(ucBuf,0,sizeof(ucBuf));
 }
 }

 if(Type<7)
 {

 //acquire CT, PT value
 //È¡CT,PT±ÈÖµ
 DispGetCTPT();

 ulTmp=BCD4_Long((char*)ucBuf);
 udTmp=(unsigned long long)ulTmp+((unsigned long long)BCD_Byte(ucBuf[4]))*((unsigned long long)100000000);
 udTmp*=g_ulPPT;
 if(ucMh)
 {
 udTmp /= 1000;
 }
 ucDot=2;
 while(udTmp>99999999)
 {
 udTmp/=10;
 ucDot--;
 if(ucDot==0)
 {
 break;
 }
 }
 Long_BCD4((char*)ucBuf, (unsigned long)(udTmp%100000000));
 Long_BCD4(((char*)ucBuf)+4, (unsigned long)(udTmp/100000000));
 DispBCD(ucBuf,5,ucDot,0,0);


 }
 else if(Type==7)
 {
 //ssmmhhDDMMyy
 FRAM_Read((char*)ucBuf, BILLYMDHms, 6);
 //display tim
 //ÏÔÊ¾tim
 for(i=0;i<3;i++)
 {
 ucBuf[6+i]=ucBuf[2-i];
 }
 DispTime(&ucBuf[6]);
 }
 else if(Type==8)
 {
 FRAM_Read((char*)ucBuf, BILLYMDHms, 6);
 //display tim
 //ÏÔÊ¾tim
 ucBuf[6]=ucBuf[3];
 ucBuf[7]=ucBuf[4];
 ucBuf[8]=ucBuf[5];

 //display data
 //ÏÔÊ¾data
 DispData(&ucBuf[6]);
 }

 DISP_HBI();
 //display MAX Demand
 //ÏÔÊ¾MAX Demand
 //gDispBuf[15]|=0x20+0x10;
 //
 //DispNum(id+1, 11);
 }
 */

//*****************************************************************
//history demand display
//*****************************************************************
void DispHisMD(int8u id, int8u Type) {

	int32u ulAdr;
	int8u ucBuf[10], ucBufBak[10];
	int16u Info;

	int8u ucDot = 0;
	int32u ulTmp;
	long long udTmp;

	memset(ucBuf, 0, sizeof(ucBuf));

	if (TRUE == GetBillAdr(id, 0x0000, 1, &ulAdr, &Info)) {
		//total active
		//×ÜÓÐ¹¦
		MEM_Read((char*) &ucBuf[0], ulAdr, 8, Mem_DFlash);
	} else {
		memset(ucBuf, 0, sizeof(ucBuf));
	}

	if (Type == 0) {

		//acquire CT, PT value
		//
		DispGetCTPT();
		ucBuf[3] = 0;
		ulTmp = BCD4_Long((char*) ucBuf);
		udTmp = (unsigned long long) ulTmp * (unsigned long long) g_ulPPT;

		ucDot = 3;
		while (udTmp > 99999999) {
			udTmp /= 10;
			ucDot--;
			if (ucDot == 0) {
				break;
			}
		}
		Long_BCD4((char*) ucBuf, (unsigned long) (udTmp % 100000000));
		Long_BCD4(((char*) ucBuf) + 4, (unsigned long) (udTmp / 100000000));
		DispBCD(ucBuf, 5, ucDot, 0, 0);

		DispUnit(1);

	} else if (Type == 1) {
		//display tim
		//
		ucBufBak[0] = ucBuf[4];	//hh
		ucBufBak[1] = ucBuf[3];	//MM
		ucBufBak[2] = 0;		//ss
		DispTime(&ucBufBak[0]);
	} else
	// {	//display data
	{	//
		//read frozen date
		//
		DispData(&ucBuf[5]);
	}
	//display MAX Demand
	//
	gDispBuf[15] |= 0x20 + 0x10;
	//
	DispNum(id + 1, 10);
}

//*****************************************************************
//programme times display
//*****************************************************************
int8u DispProg(int8u Type) {

	int8u ucTmp;
	int16u cutmp = 0;

	int8u ucBuf[6], ucBak[6];

	ucTmp = (Type >> 4) & 0x0f;
	Type &= 0x0f;
	EventsReadTimes(EVENT_PROG_TIMES, (unsigned char *) &cutmp);
	if (cutmp > 9999) {
		cutmp = 0;
	}
	//times is one
	//
	if (cutmp == 0) {
		if ((Type == 2) || (Type == 1)) {
			return 0;
		}
	}

	//
	if ((ucTmp + 1) > cutmp) {
		return 0;
	}

	EventsRead(ucBuf, EVENT_PROG_PTR, ucTmp);

	//time
	//
	if (Type == 2) {
		ucBuf[5] = 0;
		DispTime(&ucBuf[3]);
	} else if (Type == 1) {

		ucBak[0] = ucBuf[2];
		ucBak[1] = ucBuf[1];
		ucBak[2] = ucBuf[0];
		DispData(&ucBak[0]);
	} else {
		EventsReadTimes(EVENT_PROG_TIMES, (unsigned char *) &cutmp);
		if (cutmp > 9999) {
			cutmp = 0;
		}

		DispTimes(cutmp);
	}

	//prog
	gDispBuf[0] |= 0x40;

	return 1;
}

//*****************************************************************
//on-power off-power times display
//*****************************************************************
int8u DispCut(int8u Type) {

	int8u ucBuf[6], ucBak[6];
	int16u cutmp = 0;
	if (Type > 2) {
		EventsReadTimes(EVENT_PON_TIMES, (unsigned char *) &cutmp);
	} else {
		//EventsReadTimes(EVENT_POFF_TIMES,(unsigned char *)&cutmp);
		EventsReadTimes(EVENT_PON_TIMES, (unsigned char *) &cutmp);
	}

	if (cutmp == 0) {
		return 0;
	}

	if (Type > 2) {
		EventsRead(ucBuf, EVENT_PON_PTR, 0);
	} else {
		EventsRead(ucBuf, EVENT_POFF_PTR, 0);
	}

	if ((Type == 2) || (Type == 5)) {
		ucBuf[5] = 0;
		DispTime(&ucBuf[3]);
	} else if ((Type == 1) || (Type == 4))

	{
		ucBak[0] = ucBuf[2];
		ucBak[1] = ucBuf[1];
		ucBak[2] = ucBuf[0];
		//ddmmyy
		DispData(&ucBak[0]);
	} else if ((Type == 0) || (Type == 3)) {
		// if(Type == 0)
		// EventsReadTimes(EVENT_POFF_TIMES,&ucBuf[0]);
		// else
		// EventsReadTimes(EVENT_PON_TIMES,&ucBuf[0]);
		DispTimes(cutmp);
	}
	if (Type < 3) {               //P.cut
		gDispBuf[0] |= 0x80;
	} else {               //P.on
#ifdef HARDWARE_TWO
		gDispBuf[17] |= 0x08;
#else
		gDispBuf[11]|=0x02;
#endif
	}
	return 1;
}
//*****************************************************************
//PTCT display
//*****************************************************************
void DispTVCT(int8u Type) {
	int8u ucBuf[8], i;
	int8u ucBufBak[8], ucLen;

	if (Type == 0) {
		FRAM_Read((char*) ucBuf, PARA_PTCT + 4, 4);
		DispUnit(5);
		DispDot(1, 5);
		DispDot(1, 6);
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S18_ON;
#else
		//VT
		gDispBuf[16] |= 0x04;
#endif
	} else {

		FRAM_Read((char*) ucBuf, PARA_PTCT, 4);

		DispDot(1, 5);
		DispDot(1, 6);

		DispUnit(6);
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S16_ON;S17_ON;
#else
		//CT
		gDispBuf[17] |= 0x40;
#endif
	}

	ucBufBak[0] = (ucBuf[3] >> 4) & 0x0f;
	ucBufBak[1] = ucBuf[3] & 0x0f;
	ucBufBak[2] = (ucBuf[2] >> 4) & 0x0f;
	ucBufBak[3] = (ucBuf[2]) & 0x0f;

	if (ucBufBak[0] == 0) {
		i = 2;
	} else {
		i = 1;
	}
	for (; i < 5; i++) {
		DispNum(ucBufBak[i - 1], i + 1);
	}

	ucBufBak[0] = (ucBuf[1] >> 4) & 0x0f;
	ucBufBak[1] = (ucBuf[1]) & 0x0f;
	ucBufBak[2] = (ucBuf[0] >> 4) & 0x0f;
	ucBufBak[3] = (ucBuf[0]) & 0x0f;

	for (i = 0; i < 4; i++) {
		if (ucBufBak[i] != 0) {
			break;
		}
	}
	ucLen = 4 - i;
	if (ucLen == 0) {
		ucLen = 1;
		i = 0;
	}

	for (i = 0; i < ucLen; i++) {
		DispNum(ucBufBak[4 - ucLen + i], i + 6);
	}
}

//*****************************************************************
//real test parameter display
//*****************************************************************
void DisIRMRVal(int8u Phase, int8u Type) {
	int32u ulVal = 0;
	int8u ucBuf[8];

	int8u ucDot = 0;
	int32u ulTmp;
	long long udTmp;

	switch (Type) {
	//case 0://voltage 0.1
	case 0: //
		DispGetCTPT();
		udTmp = rn8209a_rms.V_RMS.val;
		//999.9
		if (udTmp > 9999) {
			udTmp /= 100;
			ulTmp = udTmp;
			Long_BCD4aA((char*) ucBuf, ulTmp);
			DispBCD(ucBuf, 4, 2, 1, 0);

			//switch to 0.00KV
			//
			S52_ON;
			DispUnit(7); // V
		} else {
			ulTmp = udTmp;
			Long_BCD4aA((char*) ucBuf, ulTmp);
			DispUnit(5);
			DispBCD(ucBuf, 4, 1, 1, 0);
		}

		break;
		//case 1://current 0.01
	case 1:
		DispGetCTPT();
		udTmp = rn8209a_rms.I_RMS.val;
		//999.99
		if (udTmp > 99999) {
			udTmp /= 1000;
			ulTmp = udTmp;
			Long_BCD4aA((char*) ucBuf, ulTmp);
			DispBCD(ucBuf, 4, 3, 1, 0);

			//switch to 0.000KA
			//
			DispUnit(9);//Display segment KA
		} else {
			ulTmp = udTmp;
			Long_BCD4aA((char*) ucBuf, ulTmp);
			DispUnit(10);//Display segment A
			DispBCD(ucBuf, 4, 2, 1, 0);
		}
		S51_ON;
		break;
		//case 2://active power
	case 2:		//
//		ulVal = gsAttRealVal.Power_Real[Phase];

		ulVal = rn8209a_rms.P_RMS.val;
		DispUnit(1);
#ifdef  HARDWARE_TWO
		//DispActivePower(Phase);//with direction display
		DispActivePower(Phase);				//
#else
		DispActiPower(Phase);
#endif
		HexToBcd(ucBuf, ulVal);

		//acquire CT, PT value
		//
		DispGetCTPT();

		ulTmp = BCD4_LongA((char*) ucBuf);
		udTmp = (unsigned long long) ulTmp * (unsigned long long) g_ulPPT;

		ucDot = 3;
		while (udTmp > 99999999) {
			udTmp /= 10;
			ucDot--;
			if (ucDot == 0) {
				break;
			}
		}
		Long_BCD4aA((char*) ucBuf, (unsigned long) (udTmp % 100000000));
		DispBCD(ucBuf, 4, ucDot, 1, 0);

//		Long_BCD4aA(((char*) ucBuf) + 4, (unsigned long) (udTmp / 100000000));
//		{
//			unsigned char flag = 0;
//			//if((gsAttRealVal.DIR_Flag&ATT7022_DIR_PA)&&(Phase == 0))//A phase
//			if ((gsAttRealVal.DIR_Flag & ATT7022_DIR_PA) && (Phase == 0))//AÏà
//					{
//				flag = 1;
//			}
//			// else if((gsAttRealVal.DIR_Flag&ATT7022_DIR_PB)&&(Phase == 1))//B phase
//			else if ((gsAttRealVal.DIR_Flag & ATT7022_DIR_PB) && (Phase == 1))//BÏà
//					{
//				flag = 1;
//			}
//			//else if((gsAttRealVal.DIR_Flag&ATT7022_DIR_PC)&&(Phase == 2))//C phase
//			else if ((gsAttRealVal.DIR_Flag & ATT7022_DIR_PC) && (Phase == 2))//CÏà
//					{
//				flag = 1;
//			}
//			// else if((gsAttRealVal.DIR_Flag&ATT7022_DIR_PT)&&(Phase == 3))//combined-phase
//			else if ((gsAttRealVal.DIR_Flag & ATT7022_DIR_PT) && (Phase == 3))//ºÏÏà
//					{
//				flag = 1;
//			}
//
//			DispBCD(ucBuf, 4, ucDot, 1, flag);
//		}
		break;
		//case 3://reactive power
	case 3:			//
//		ulVal = gsAttRealVal.Var_Real[Phase];

		ulVal = rn8209a_rms.Q_RMS.val;
		DispUnit(3);
		DispReavPower(Phase);
		HexToBcd(ucBuf, ulVal);

		//acquire CT, PT value
		//
		DispGetCTPT();

		ulTmp = BCD4_LongA((char*) ucBuf);
		udTmp = (unsigned long long) ulTmp * (unsigned long long) g_ulPPT;

		ucDot = 3;
		while (udTmp > 99999999) {
			udTmp /= 10;
			ucDot--;
			if (ucDot == 0) {
				break;
			}
		}

		Long_BCD4aA((char*) ucBuf, (unsigned long) (udTmp % 100000000));
		Long_BCD4aA(((char*) ucBuf) + 4, (unsigned long) (udTmp / 100000000));
		DispBCD(ucBuf, 4, ucDot, 1, 0);

		break;
#ifdef  HARDWARE_TWO
		//case 4://apparent power
	case 4:			//
		ulVal = gsAttRealVal.APPA_Real[Phase];
		DispUnit(3);
		DispReavPower(Phase);
		//DispNum(5, 11);//display "s"
		DispNum(5, 11);			//
		HexToBcd(ucBuf, ulVal);

		//acquire CT, PT value
		//
		DispGetCTPT();

		ulTmp = BCD4_LongA((char*) ucBuf);
		udTmp = (unsigned long long) ulTmp * (unsigned long long) g_ulPPT;

		ucDot = 3;
		while (udTmp > 99999999) {
			udTmp /= 10;
			ucDot--;
			if (ucDot == 0) {
				break;
			}
		}

		Long_BCD4aA((char*) ucBuf, (unsigned long) (udTmp % 100000000));
		Long_BCD4aA(((char*) ucBuf) + 4, (unsigned long) (udTmp / 100000000));
		DispBCD(ucBuf, 4, ucDot, 1, 0);

		break;
#endif
		//case 5://frequency
	case 5:			//
		HexToBcd(ucBuf, (unsigned long)rn8209a_rms.F_RMS.val);
		DispBCD(ucBuf, 4, 1, 1, 0);
		S52_ON;
		DispUnit(6);
		break;
		//case 6://calibration angle
	case 6:			//
		ulVal = gsAttRealVal.PG[Phase];
		HexToBcd(ucBuf, ulVal);
		DispBCD(ucBuf, 4, 1, 1, 0);

		DispUnit(11);

		//display minus
		//Liao Bin modified Vietnam people said angle has reversed
//		if (ulVal != 0) {
//			if ((gsAttRealVal.DIR_Flag & ADirTbl[Phase])) {
//			} else {
//				DispNum(36, 3);
//			}
//		}
		break;
		//case 7://total power factor
	case 7:                        //
//		ulVal = gsAttRealVal.PF[Phase];

		ulVal = rn8209a_rms.PF_RMS.val;
		HexToBcd(ucBuf, ulVal);
		DispBCD(ucBuf, 4, 3, 1, 0);

//		ulVal = gsAttRealVal.PG[Phase];
//		if (ulVal != 0) {
//			if (gsAttRealVal.DIR_Flag & PDirTbl[Phase]) {
//				if ((gsAttRealVal.DIR_Flag & ADirTbl[Phase])) {
//					DispNum(21, 1);
//				} else {
//					DispNum(12, 1);
//				}
//				DispNum(36, 4);
//			} else {
//				if ((gsAttRealVal.DIR_Flag & ADirTbl[Phase])) {
//					DispNum(12, 1);
//				} else {
//					DispNum(21, 1);
//				}
//			}
//		}
		S19_ON;S49_ON;
//		DispUnit(10);
	default:
		break;
	}
}

//*****************************************************************
//wrong table
//*****************************************************************

const int16u DisErrTbl[] = { 0xfff1, 0xfff2, 0xfff3, 0xfff4, 0xfff5, 0xfff6,
		0xfff7, 0xfff8, 0xfff2, 0xfff9, 0xfffa, 0xfffb, 0xfffc, 0xfffd, };

#if 1
//automatically display default table
const int16u DisAutoTbl[] = { 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005,
		0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e,
		0x000f, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014

};
#else
#define		DISP_AUTO_NUM		14//6+8
const int16u DisAutoTbl[]= {
//0x1000,0x1001,0x1002,	//voltage
	0x1000,0x1001,0x1002,//µçÑ¹
	0x1020,0x1021,0x1022,//µçÁ÷
////0x1070,						//frequency
//0x1070,						//ÆµÂÊ
	//0x1060,0x1061,0x1062,0x1063,	//phase angle
//0x1060,0x1061,0x1062,0x1063,	//Ïà½Å

//0x1030,0x1031,0x1032,0x1033,	//active power
	0x1030,0x1031,0x1032,0x1033,//ÓÐ¹¦¹¦ÂÊ
//0x1040,0x1041,0x1042,0x1043,	//reactive power
	0x1040,0x1041,0x1042,0x1043,//ÎÞ¹¦¹¦ÂÊ

};
#endif

//key display table, not working
int16u const DisKeyTblPara1[] = {
//0x1072,//phase order
		0x1072,//ÏàÐò
//0x1000,0x1001,0x1002,	//voltage
		0x1000, 0x1001, 0x1002,	//
//0x1020,0x1021,0x1022,	//current
		0x1020, 0x1021, 0x1022,	//
//0x1070,							//frequency
		0x1070,							//
//0x1060,0x1061,0x1062,	//phase angle
		0x1060, 0x1061, 0x1062,	//
//0x1071,			//power factor
		0x1071,			//
		0xe000,

};
//not working


#ifdef HARDWARE_TWO

int16u const DisKeyTblPara2[] = {
//0x1030,0x1031,0x1032,0x1033,	//active power
		0x1030, 0x1031, 0x1032, 0x1033,	//
//0x1040,0x1041,0x1042,0x1043,	//reactive power
		0x1040, 0x1041, 0x1042, 0x1043,	//
//0x1050,0x1051,0x1052,0x1053,	//apparent power
		0x1050, 0x1051, 0x1052, 0x1053,	//
		0xe001 };

#else

int16u const DisKeyTblPara2[]= {
//0x1030,0x1031,0x1032,0x1033,	//active power
	0x1030,0x1031,0x1032,0x1033,//ÓÐ¹¦¹¦ÂÊ
//0x1040,0x1041,0x1042,0x1043,    //reactive power
	0x1040,0x1041,0x1042,0x1043,//ÎÞ¹¦¹¦ÂÊ
	0xe001
};

#endif
//*history demand*/
/*ÀúÊ·ÐèÁ¿*/
const int16u DisKeyTblPara3[] = {
//0x2000,	//maximum demand of last month
		0x2000,//
//0x2001,	//sending time of maximum demand of last month
		0x2001,	//
//0x2002,	//sending date of maximum demand of last month
		0x2002,	//
//0x2010,	//maximum demand of last two months
		0x2010,	//
//0x2011,	//sending time of maximum demand of last two months
		0x2011,	//
//0x2012,	//sending date of maximun demand of last two months
		0x2012,	//
//0x2020,	//maximum demand of last three months
		0x2020,	//
		0x2021,	//
		0x2022,	//
//0x2030,	//maximum demand of last four months
		0x2030,	//
		0x2031,	//
		0x2032,	//
		0xe002, };
//history power quantity
//
#ifdef HARDWARE_TWO
const int16u DisKeyTblPara4[] = {
//0x3007,  //settlement time
		0x3007,//
//0x3008,  //settlement date
		0x3008,  //
//0x3000,  //forward total active
		0x3000,  //
//0x3001,  //forward tariff 1
		0x3001,  //
//0x3002,  //forward tariff 2
		0x3002,  //
//0x3003,  //forward tariff 3
		0x3003,  //
// 0x3004,  //forward tariff
		0x3004,  //
//0x301d,  //reverse total active
		0x301d,  //
//0x301e,  //reverse tariff 1
		0x301e,  //
// 0x301f,  //reverse tariff 2
		0x301f,  //
//0x3020,  //reverse tariff 3
		0x3020,  //
//0x3021,  //reverse tariff 4
		0x3021,  //
//0x3005,  //reactive forward
		0x3005,  //
//0x3006,  //reactive reverse
		0x3006,  //
//0x3009,  //total first quadrant
		0x3009,  //
//0x300a,  //tariff 1
		0x300a,  //
//0x300b,  //tariff 2
		0x300b,  //
//0x300c,  //tariff 3
		0x300c,  //
//0x300d,  //tariff 4
		0x300d,  //
//0x300e,  //total second quadrant
		0x300e,  //
//0x300f,  //tariff 1
		0x300f,  //
//0x3010,  //tariff 2
		0x3010,  //
//0x3011,  //tariff 3
		0x3011,  //
//0x3012,  //tariff 4
		0x3012,  //
//0x3013,  //total third quadrant
		0x3013,  //
//0x3014,  //tariff 1
		0x3014,  //
//0x3015,  //tariff 2
		0x3015,  //
//0x3016,  //tariff 3
		0x3016,  //
//0x3017,  //tariff 4
		0x3017,  //
//0x3018,  //total forth quadrant
		0x3018,  //
//0x3019,  //tariff 1
		0x3019,  //
//0x301a,  //tariff 2
		0x301a,  //
//0x301b,  //tariff 3
		0x301b,  //
//0x301c,  //tariff 4
		0x301c,  //
//0x3022,  //forward total apparent
		0x3022,  //
//0x3023,  //tariff 1
		0x3023,  //
//0x3024,  //tariff 2
		0x3024,  //
//0x3025,  //tariff 3
		0x3025,  //
//0x3026,  //tariff 4
		0x3026,  //
//0x3027,  //reverse total apparent
		0x3027,  //
//0x3028,  //tariff 1
		0x3028,  //
//0x3029,  //tariff 2
		0x3029,  //
//0x302a,  //tariff 3
		0x302a,  //
//0x302b,  //tariff 4
		0x302b,  //·
		0xe003 };
#else
const int16u DisKeyTblPara4[]= {
	// 0x3007,	//settlement time
	0x3007,//½áËãÊ±¼ä
	//0x3008,	//settlement date
	0x3008,//½áËãÈÕÆÚ
	//0x3000,	//total active
	0x3000,//×ÜÓÐ¹¦
	//0x3001,	//tariff 1 active
	0x3001,//·ÑÂÊ1ÓÐ¹¦
	//0x3002,	//tariff 2
	0x3002,//·ÑÂÊ2
	//0x3003,	//tariff 3
	0x3003,//·ÑÂÊ3
	//0x3004,	//tariff 4
	0x3004,//·ÑÂÊ4
	//0x3005,	//reactive forward
	0x3005,//ÎÞ¹¦ÕýÏò
	//0x3006,	//reactive reverse
	0x3006,//ÎÞ¹¦·´Ïò
	0xe003
};
#endif

//programme event
const int16u DisKeyTblPara5[] = {
//0x4000,	//programme event
		0x4000,//
		//0x4001,	//programme event
		0x4001,//
		//0x4002,	//programme event
		0x4002,//

		//0x4011,	//programme event
		0x4011,//
		//0x4012,	//programme event
		0x4012,//

		//0x4021,	//programme event
		0x4021,//
		//0x4022,	//programme event
		0x4022,//

		//0x4031,	//programme event
		0x4031,//
		// 0x4032,	//programme event
		0x4032,//

		0xe004 };
//off-power event display table

const int16u DisKeyTblPara6[] = {
//0x4011,	//off-power event
//0x4011,	//
////0x4012,	//off-power event
//0x4012,	//
////0x4013,	//off-power event
//0x4013,	//
//0xe005

//0x4101,	//off-power event
		0x4101,//
		0x4102,	//
		0x4103,	//
		0x4104, 0x4105, 0x4106, 0xe005

};
//PTCT display table

const int16u DisKeyTblPara7[] = { 0x5000, 0x5001, 0xe006,

};

//user defined register display table

#ifdef HARDWARE_TWO
const int16u DisKeyTblPara8[] = { 0x6000, 0x6001, 0x6002, 0xe007,

};
#endif

//parameter page display table

//#ifdef HARDWARE_TWO//add the eighth page display user defined register
#ifdef HARDWARE_TWO//
const int16u * const pDisPara[] = { DisKeyTblPara1, DisKeyTblPara2,
		DisKeyTblPara3, DisKeyTblPara4, DisKeyTblPara5, DisKeyTblPara6,
		DisKeyTblPara7, DisKeyTblPara8, };
#else
const int16u * const pDisPara[]= {
	DisKeyTblPara1,DisKeyTblPara2,
	DisKeyTblPara3,DisKeyTblPara4,
	DisKeyTblPara5,DisKeyTblPara6,
	DisKeyTblPara7,
};
#endif
//*****************************************************************
//full display
//*****************************************************************
void DispFull(void) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
	LCDM17 = LCDM16 = LCDM15 = LCDM14 = LCDM13 = LCDM12 = LCDM11 = LCDM10 = LCDM9 =
			LCDM8 = LCDM7 = LCDM6 = LCDM5 = LCDM4 = LCDM3 = LCDM2 = LCDM1 = 0xFF;
#else
	memset(gDispBuf, 0xff, 18);
	BU9792_Refresh(gDispBuf, 0);
#endif
}

//*****************************************************************
//turn off display
//*****************************************************************
void Get_ShutDispTm(void) {
	DisK.ShutDnInv = 10;
	DisK.ShutDnCnt = DisK.ShutDnInv;
}

//*****************************************************************
//display statement
//*****************************************************************
void DispState(void) {
	int8u ucTmp;

	if (Flag.Power == F_PwrUp){
		S21_ON;
		if((!Flag.Power_dir)&&(rn8209a_rms.I_RMS.val > 0))
			S22_ON;
	}
	else
		S21_OFF;

	if ((display_mod & 0x10) == 0x00) {

	} else {
		DISP_VTPT();
	}

	if ((Flag.Power & F_PwrUp) == F_PwrUp) {
		//display tariff number
		//
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S10_ON;
#else
		gDispBuf[13] |= 0x80;	//R
#endif
		DispNum(Fee.CurrentFee, 9);
	}

	//display battery
	//
	if ((Flag.Alarm & F_Al_BatLow) && (DisK.FlashSige == 0)) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S28_ON;
		if((Flag.Power_dir)&&(rn8209a_rms.I_RMS.val > 0))
			S22_ON;
#else
		gDispBuf[5] |= 0x80;
#endif
		meter_state[0] |= STA_POW_LOW;
	} else {
		if (Flag.Alarm & F_Al_BatLow) {
			meter_state[0] |= STA_POW_LOW;
		} else {
			meter_state[0] &= ~STA_POW_LOW;
		}
	}

	//reset locked
	//
	E2P_Read((char *) &ucTmp, SysSW, 1);
	if ((ucTmp & 0x02) == 0x00) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S32_ON;
#else
		gDispBuf[10] |= 0x80;
#endif
		meter_state[0] |= STA_SW_LOCK;

	} else
		meter_state[0] &= ~STA_SW_LOCK;

	//demand zero clearing mark
	//
	if (Flag.MDClrFlag == 1) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
//		S6_ON;
#else
		gDispBuf[5] |= 0x08;
#endif
	}

	//demand zero clearing
	//

	if (IEC_Comm.ProgCnt > 0) {
		//display programme
		//
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S31_ON;
#else
		gDispBuf[7] |= 0x08;
#endif
	}
	//display communication
	//
	if (Flag.FlsLP & FlsLP_Com_RBsy) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
		S31_ON;
#else
		gDispBuf[8] |= 0x80;
#endif
	}
	//lock
	//gDispBuf[10]|=0x80;
	//exit
	//gDispBuf[11]|=0x80;

#if	(METER_3H3W==0)
	//anti-phase can only be judged under all three phase has voltage
	if ((gsAttRealVal.Att7022Flag & ATT7022Flag_VPHASE_ERR)
			&& (DisK.FlashSige == 1)
			&& ((gsAttRealVal.Att7022Flag & 0x07) == 0x07)) {
		_NOP();
	}
#else
	if((gsAttRealVal.Att7022Flag&ATT7022Flag_VPHASE_ERR)
			&&(DisK.FlashSige==1)&&((gsAttRealVal.Att7022Flag&0x05)==0x05))
	{
		_NOP();
	}
#endif
	else if (DisK.UIFg == 1) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
		DispPhaseV(0);
#else
		//display voltage flag  %10*230.0	A
		if (gsAttRealVal.Att7022Flag & ATT7022Flag_LOWUA_ERR) {
			DispPhaseV(0);
		}
		//B
		if (gsAttRealVal.Att7022Flag & ATT7022Flag_LOWUB_ERR) {
			DispPhaseV(1);
		}
		//C
		if (gsAttRealVal.Att7022Flag & ATT7022Flag_LOWUC_ERR) {
			DispPhaseV(2);
		}
#endif
	}
	//if((gsAttRealVal.DIR_Flag&ATT7022_DIR_PA)&&(DisK.FlashSige==1))	//A phase current direction
	if ((gsAttRealVal.DIR_Flag & ATT7022_DIR_PA) && (DisK.FlashSige == 1))//
			{
	} else if (DisK.UIFg == 1) {
		//display current flag  >0.4%IB 5*0.004=0.020
		if (gsAttRealVal.IRMS[0] > 2) {
			DispPhaseI(0);
		}
	}
	//if((gsAttRealVal.DIR_Flag&ATT7022_DIR_PB)&&(DisK.FlashSige==1))	//B phase current direction
	if ((gsAttRealVal.DIR_Flag & ATT7022_DIR_PB) && (DisK.FlashSige == 1))//
			{
	} else if (DisK.UIFg == 1) {
		if (gsAttRealVal.IRMS[1] > 2) {
			DispPhaseI(1);
		}
	}
	//if((gsAttRealVal.DIR_Flag&ATT7022_DIR_PC)&&(DisK.FlashSige==1))//C phase current direction
	if ((gsAttRealVal.DIR_Flag & ATT7022_DIR_PC) && (DisK.FlashSige == 1))//
			{

	} else if (DisK.UIFg == 1) {
		if (gsAttRealVal.IRMS[2] > 2) {
			DispPhaseI(2);
		}
	}


	if (DisK.FlashSige == 0) {
		DisK.FlashSige = 1;

	} else {
		DisK.FlashSige = 0;
	}

}

//*****************************************************************
//display main function
//*****************************************************************
void DisplayData(void) {
	static int8u stop_disp_flag = 0;
	int16u uiDisID;
	int8u ucBuf[32];
	int8u ucTmp, i;

	int16u const *ptr;

	if (DisK.ShutDnCnt > 0) {
		DisK.ShutDnCnt--;
	}

	if (DisK.DisInv > 0) {
		DisK.DisInv--;
	}

	if (RunDly.AllDspDly > 0) {
		return;
	}

	if (gsKey.KeyDisp == 0){	//
	//if off-power , no display before rotation		
		if ((DisK.DisInv != 0x00) && (Flag.Power & F_PwrUp) == 0x00) {
			return;
		}
	} else {
		DisK.ShutDnCnt = DisK.ShutDnInv;
	}

	//display time reaches, turn off display when power off
	if ((DisK.ShutDnCnt == 0) && ((Flag.Power & F_PwrUp) == 0x00)) {
		if (stop_disp_flag == 0) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
			DispClr();
#else
			memset(gDispBuf, 0, sizeof(gDispBuf));
			BU9792_Refresh(gDispBuf, 0);
#endif
			stop_disp_flag = 1;
		}
		DisK.DisPtr = DISP_AUTO_NUM;
		return;
	}
	stop_disp_flag = 0;

	//DispClr();//clear display buffer data
	DispClr();  //
	//automatic rotation
	if (DisK.DisMode == DISP_MODE_AUTO) {
		static unsigned char err_flag = 0;
		if ((DisK.DisInv == 0) && (err_flag == 0)) {
			DisK.DisPtr++;

#ifdef SINGLE_PHASE_MULTI_TARIFF
			E2P_Read((char*) &ucTmp, Disp_ScNum, 1);  //-> 0x051E
#else
			//  FRAM_Read((char*)&ucTmp, Disp_ScNum, 1);//read automatic rotation option number
			FRAM_Read((char*) &ucTmp, Disp_ScNum, 1);  //
#endif
			if (ucTmp > DISP_AUTO_NUM) {
				ucTmp = DISP_AUTO_NUM;
			}

			if (DisK.DisPtr >= ucTmp) {
				DisK.DisPtr = 0;
				err_flag = 7;
			}
		}
#ifdef SINGLE_PHASE_MULTI_TARIFF
		E2P_Read((char*) &ucBuf[0], Disp_ScTab + DisK.DisPtr * 2, 2); //->0x04de
#else
		//FRAM_Read((char*)&ucBuf[0], Disp_ScTab+DisK.DisPtr*2, 2);//read automatic rotation meter
		FRAM_Read((char*) &ucBuf[0], Disp_ScTab + DisK.DisPtr * 2, 2); //
#endif

		for (i = 0; i < 2; i++) {
			uiDisID <<= 8;
			uiDisID += ucBuf[i];
		}
		DisK.UIFg = 1;	//
		if (DisK.ErrCnt == 0) {
			//check if there is wrong display or not
			if ((TRUE == GetErrPtr()) && (DisK.DisPtr == 0) && (err_flag > 0)) {
				if ((--err_flag) == 0) {
					DisK.DisInv = 0;
				} else {
					uiDisID = DisErrTbl[DisK.ErrPtr];
				}
				if (DisK.DisInv == 0) {
					DisK.ErrPtr++;
					if (DisK.ErrPtr >= 7) {
						DisK.ErrPtr = 0;
					}
				}
			} else {
				err_flag = 0;
			}
		}
		//update automatic rotation spacing time
		if (DisK.DisInv == 0) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
			E2P_Read((char*) &ucTmp, DspInv, 1);//-> 0x0564
			if (ucTmp <= 15)
				DisK.DisInv = ucTmp;
			else
				DisK.DisInv = 15;
#else
			FRAM_Read((char*) &ucTmp, DspInv, 1);//-> 0x0564
			DisK.DisInv = ucTmp & 0x0f;
#endif
			DisK.DisInv += ((ucTmp >> 4) * 0x0f) * 10;
		}

		// key rotation
	}    //
	else if (DisK.DisMode == DISP_MODE_CLICK) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
		E2P_Read((char*) &ucTmp, Disp_KeyNum, 1);    //->
#else
		//FRAM_Read((char*)&ucTmp, Disp_KeyNum, 1);//read key rotation option number
		FRAM_Read((char*) &ucTmp, Disp_KeyNum, 1);    //-> 0x0561
#endif
		if (ucTmp > DISP_AUTO_NUM) {
			ucTmp = DISP_AUTO_NUM;
		}

		if (DisK.DisPtr >= ucTmp) {
			DisK.DisPtr = 0;
		}
#ifdef SINGLE_PHASE_MULTI_TARIFF
		E2P_Read((char*) &ucBuf[0], Disp_KeyTab + DisK.DisPtr * 2, 2); //
#else
		//FRAM_Read((char*)&ucBuf[0],Disp_KeyTab+DisK.DisPtr*2, 2);//read key rotation option
		FRAM_Read((char*) &ucBuf[0], Disp_KeyTab + DisK.DisPtr * 2, 2); // -> 0x0521
#endif
		for (i = 0; i < 2; i++) {
			uiDisID <<= 8;
			uiDisID += ucBuf[i];
		}
		//DisK.UIFg=1;	//need to display UI
		DisK.UIFg = 1;	//
	}
	//key enter into menu option display
	else if (DisK.DisMode == DISP_MODE_KEY) {
		uiDisID = DisAutoTbl[DisK.DisPtr];

		if (DisK.SPtr == 0) {
			uiDisID = 0xf000 + DisK.MPtr - 1;
			DisK.UIFg = 0;
		} else {
			DisK.UIFg = 1;
			if (DisK.MPtr < (DISP_PARA_7 + 1) && (DisK.MPtr > 1)) {
				ptr = pDisPara[DisK.MPtr - 2];
				if (DisK.MPtr == 2) {
					DISP_PARA();
				}
			}
			if (DisK.SPtr > 0) {
				uiDisID = ptr[DisK.SPtr - 1];
			}
			if (DisK.MPtr == 2) {
				//only when display U,I, no full display of U,I
				if (DisK.SPtr < 8) {
					DisK.UIFg = 0;
				}
			}
		}

	}

	//under factory pattern main area flicker function

	if (gFactMode == 0xf001) {
		if (DisK.FlashSige == 1) {
			goto DispNull;
		}
	}



	switch (uiDisID) {
	//wrong display
	case 0xfff1:
	case 0xfff2:
	case 0xfff3:
	case 0xfff4:
	case 0xfff5:
	case 0xfff6:
	case 0xfff7:
		uiDisID -= 0xfff0;
		DispErr(uiDisID);//ok
		break;
		// case 0x0000:	//time
	case 0x0000:	//
		ucBuf[0] = Clk.Day[0];
		ucBuf[1] = Clk.Mon[0];
		ucBuf[2] = Clk.Year[0];
		DispData(ucBuf);
		break;
		//case 0x0001:	//date
	case 0x0001:	//
		ucBuf[0] = Clk.Hour[0];
		ucBuf[1] = Clk.Min[0];
		ucBuf[2] = Clk.Sec[0];
		DispTime(ucBuf);
		break;
	case 0x0002:	//ID
		DispMeterID();
		break;
	case 0x0003:	//acti Total
	case 0x0004:	//acti	fee1
	case 0x0005:	//acti	fee2
	case 0x0006:	//acti	fee3
	case 0x0007:	//acti	fee4
		uiDisID -= 0x0003;
		//DispEnergy(uiDisID,0);//forward active power
		DispEnergy(uiDisID, 0);	//
		break;
	case 0x0008:
	case 0x0009:
	case 0x000a:
	case 0x000b:
	case 0x000c:
		uiDisID -= 0x0008;
		DispEnergy(uiDisID,2);//forward reactive power (lag)
		break;
//		DispEnergy(uiDisID, 2);	//
	case 0x000d:
	case 0x000e:
	case 0x000f:
	case 0x0010:
	case 0x0011:
		uiDisID -= 0x000d;
		//DispEnergy(uiDisID,3);//reverse reactive power (Lead)
		DispEnergy(uiDisID, 3);	//
		break;
	case 0x0012:
	case 0x0013:
	case 0x0014:
		uiDisID -= 0x0012;
		//DispMaxDem(0,uiDisID);//maximum demand display
		DispMaxDem(0, uiDisID);	//
		break;
#ifdef HARDWARE_TWO
		// case 0x0015:	//reactive first quadranat total
	case 0x0015:	//
	case 0x0016:	//fee1
	case 0x0017:	//fee2
	case 0x0018:	//fee3
	case 0x0019:	//fee4
		uiDisID -= 0x0015;
		//DispRqEnergy(uiDisID,1);//each quadrant tariff display
		DispRqEnergy(uiDisID, 1);	//
		break;
		//case 0x001a:	//reactive second quadrant total
	case 0x001a:	//
	case 0x001b:	//fee1
	case 0x001c:	//fee2
	case 0x001d:	//fee3
	case 0x001e:	//fee4
		uiDisID -= 0x001a;
		//DispRqEnergy(uiDisID,2);//each quadrant tariff display
		DispRqEnergy(uiDisID, 2);	//
		break;
		//case 0x001f:	//reactive third quadrant total
	case 0x001f:	//
	case 0x0020:	//fee1
	case 0x0021:	//fee2
	case 0x0022:	//fee3
	case 0x0023:	//fee4
		uiDisID -= 0x001f;
		//DispRqEnergy(uiDisID,3);//each quadrant tariff display
		DispRqEnergy(uiDisID, 3);	//
		break;
		// case 0x0024:	//reactive four quadrant total
	case 0x0024:	//
	case 0x0025:	//fee1
	case 0x0026:	//fee2
	case 0x0027:	//fee3
	case 0x0028:	//fee4
		uiDisID -= 0x0024;
		//DispRqEnergy(uiDisID,4);//each quadrant tariff display
		DispRqEnergy(uiDisID, 4);	//
		break;
	case 0x0029:
	case 0x002a:
	case 0x002b:
	case 0x002c:
	case 0x002d:
		uiDisID -= 0x0029;
		//DispEnergy(uiDisID,1);//reverse active power
		DispEnergy(uiDisID, 1);	//
		break;
	case 0x002e:
	case 0x002f:
	case 0x0030:
	case 0x0031:
	case 0x0032:
		uiDisID -= 0x002e;
		//DispEnergy(uiDisID,4);//forward apparent power
		DispEnergy(uiDisID, 4);	//
		break;
	case 0x0033:
	case 0x0034:
	case 0x0035:
	case 0x0036:
	case 0x0037:
		uiDisID -= 0x0033;
		//DispEnergy(uiDisID,5);//reverse apparent power
		DispEnergy(uiDisID, 5);	//
		break;
#endif

		//	case 0xf000:	//key menu exit key
		//	case 0xf000:	//
		//case 0xf001:	//key menu option 1~7
	case 0xf001:	//
		//case 0xf002:	//key menu option 1~7
	case 0xf002:	//
		//case 0xf003:	//key menu option 1~7
	case 0xf003:	//
		//case 0xf004:	//key menu option 1~7
	case 0xf004:	//
		//case 0xf005:	//key menu option 1~7
	case 0xf005:	//
		//case 0xf006:	//key menu option 1~7
	case 0xf006:	//
		//case 0xf007:	//key menu option 1~7
	case 0xf007:	//
#ifdef HARDWARE_TWO
		//case 0xf008:  //new added display user defined register
	case 0xf008:  //
#endif
		uiDisID -= 0xf000;
		//DispPara(uiDisID,uiDisID);//key menu option
		DispPara(uiDisID, uiDisID);  //
		break;
		//case 0xe000:	//key menu option 1~7
	case 0xe000:	//
		//case 0xe001:	//key menu option 1~7
	case 0xe001:	//
		//case 0xe002:	//key menu option 1~7
	case 0xe002:	//
		//case 0xe003:	//key menu option 1~7
	case 0xe003:	//
		//case 0xe004:	//key menu option 1~7
	case 0xe004:	//
		//case 0xe005:	//key menu option 1~7
	case 0xe005:	//
		//case 0xe006:	//key menu option 1~7
	case 0xe006:	//
#ifdef HARDWARE_TWO
		// case 0xe007:  //new added display user defined register
	case 0xe007:  //ÐÂÔöÏÔÊ¾×Ô¶¨Òå¼Ä´æÆ÷
#endif
		uiDisID -= 0xe000;
		uiDisID += 1;
		DispPara(uiDisID, 0);
		break;
		//case 0x1000:	//equivalent voltage A, B, C
	case 0x1000:	//
	case 0x1001:
	case 0x1002:
		uiDisID -= 0x1000;
		//DisIRMRVal(uiDisID,0);    //three phase voltage
		DisIRMRVal(uiDisID, 0);    //
		break;
		//case 0x1020:	//equivalent current A, B, C
	case 0x1020:	//
	case 0x1021:
	case 0x1022:
		uiDisID -= 0x1020;
		// DisIRMRVal(uiDisID,1);//three phase current
		DisIRMRVal(uiDisID, 1);	//
		break;
		// case 0x1030:	//active power
	case 0x1030:	//
	case 0x1031:
	case 0x1032:
	case 0x1033:
		uiDisID -= 0x1030;
		//DisIRMRVal(uiDisID,2);//three phase active
		DisIRMRVal(uiDisID, 2);	//
		break;
		//case 0x1040:	//reactive power
	case 0x1040:	//
	case 0x1041:
	case 0x1042:
	case 0x1043:
		uiDisID -= 0x1040;
		DisIRMRVal(uiDisID, 3);
		break;
		//case 0x1050:	//apparent
	case 0x1050:	//
	case 0x1051:
	case 0x1052:
	case 0x1053:
		uiDisID -= 0x1050;
		DisIRMRVal(uiDisID, 4);
		break;
		//case 0x1060:	//phase angle
	case 0x1060:	//
	case 0x1061:
	case 0x1062:
	case 0x1063:
		uiDisID -= 0x1060;
		DisIRMRVal(uiDisID, 6);
		break;
		//case 0x1070:	//frequency
	case 0x1070:	//
		uiDisID -= 0x1070;
		DisIRMRVal(uiDisID, 5);
		break;
		//case 0x1071:	//power factor
	case 0x1071:	//
		DisIRMRVal(3, 7);
		break;
		// case 0x1072: //phase order display
	case 0x1072: //
		Disp_VPHASE();
		// DisK.UIFg=1;//display current phase
		DisK.UIFg = 1; //
		break;
		//case 0x2000:	//maximum demand of last month
	case 0x2000:	//
		//case 0x2001:	//sending time of maximum demand of last month
	case 0x2001:	//
		// case 0x2002:	//sending date of maximum demand of last month
	case 0x2002:	//
		// case 0x2010:	//maximum demand of last two months
	case 0x2010:	//
		// case 0x2011:	//sending time of maximum demand of last two months
	case 0x2011:	//
		//case 0x2012:	//sending date of maximum demand of last two months
	case 0x2012:	//
		//case 0x2020:	//maximum demand of last three months
	case 0x2020:	//
	case 0x2021:	//
	case 0x2022:	//
		//case 0x2030:	//maximum demand of last four months
	case 0x2030:	//
	case 0x2031:	//
	case 0x2032:	//
		uiDisID -= 0x2000;
		ucTmp = (uiDisID >> 4) & 0x000f;
		DispHisMD(ucTmp, uiDisID & 0x0f);
		break;
		//case 0x3000:	//forward total active
	case 0x3000:	//
		//case 0x3001:	//forward tariff 1
	case 0x3001:	//
		//case 0x3002:	//forward tariff 2
	case 0x3002:	//
		//case 0x3003:	//forward tariff 3
	case 0x3003:	//
		// case 0x3004:	//forward tariff 4
	case 0x3004:	//
		//case 0x3005:	//reactive forward
	case 0x3005:	//
		//case 0x3006:	//reactive reverse
	case 0x3006:	//
		// case 0x3007:	//settlement time
	case 0x3007:	//
		// case 0x3008:	//settelement date
	case 0x3008:	//
#ifdef  HARDWARE_TWO
		//case 0x3009:  //total first quadrant
	case 0x3009:  //
		//case 0x300a:  //tariff 1
	case 0x300a:  //
		//case 0x300b:  //tariff 2
	case 0x300b:  //
		//case 0x300c:  //tariff 3
	case 0x300c:  //
		//case 0x300d:  //tariff 4
	case 0x300d:  //
		// case 0x300e:  //total second quadrant
	case 0x300e:  //
		//case 0x300f:  //tariff 1
	case 0x300f:  //
		// case 0x3010:  //tariff 2
	case 0x3010:  //
		//case 0x3011:  //tariff 3
	case 0x3011:  //
		//case 0x3012:  //tariff 4
	case 0x3012:  //
		//case 0x3013:  //total third quadrant
	case 0x3013:  //
		// case 0x3014:  //tariff 1
	case 0x3014:  //
		//case 0x3015:  //tariff 2
	case 0x3015:  //
		//case 0x3016:  //tariff 3
	case 0x3016:  //
		//case 0x3017:  //tariff 4
	case 0x3017:  //
		// case 0x3018:  //total forth quadrant
	case 0x3018:  //
		//case 0x3019:  //tariff 1
	case 0x3019:  //
		//case 0x301a:  //tariff 2
	case 0x301a:  //
		//case 0x301b:  //tariff 3
	case 0x301b:  //
		//case 0x301c:  //tariff 4
	case 0x301c:  //
		// case 0x301d:	//total reverse active
	case 0x301d:	//
		//case 0x301e:	//reverse tariff 1
	case 0x301e:	//
		// case 0x301f:	//reverse tariff 2
	case 0x301f:	//
		// case 0x3020:	//reverse tariff 3
	case 0x3020:	//
		//case 0x3021:	//reverse tariff 4
	case 0x3021:	//
		//case 0x3022:  //total forward apparent
	case 0x3022:  //
		//case 0x3023:  //tariff 1
	case 0x3023:  //
		//case 0x3024:  //tariff 2
	case 0x3024:  //
		//case 0x3025:  //tariff 3
	case 0x3025:  //
		//case 0x3026:  //tariff 4
	case 0x3026:  //
		//case 0x3027:  //total reverse apparent
	case 0x3027:  //
		//case 0x3028:  //tariff 1
	case 0x3028:  //
		// case 0x3029:  //tariff 2
	case 0x3029:  //
		//case 0x302a:  //tariff 3
	case 0x302a:  //
		//case 0x302b:  //tariff 4
	case 0x302b:  //
#endif
		uiDisID -= 0x3000;
		DispHisCE(0, uiDisID);
		break;
		//case 0x4000:	//programme event
	case 0x4000:	//
		//case 0x4001:	//programme event
	case 0x4001:	//
		//case 0x4002:	//programme event
	case 0x4002:	//

		// case 0x4011:	//programme event
	case 0x4011:	//
		//case 0x4012:	//programme event
	case 0x4012:	//

		// case 0x4021:	//programme event
	case 0x4021:	//
		//case 0x4022:	//programme event
	case 0x4022:	//

		//case 0x4031:	//programme event
	case 0x4031:	//
		//case 0x4032:	//programme event
	case 0x4032:	//
		uiDisID -= 0x4000;
		// if(0==DispProg(uiDisID))//no event record display,exit page
		if (0 == DispProg(uiDisID))	//
				{
			DisK.SPtr = ucPageTbl[4];
			return;
		}
		break;
		//case 0x4101:	//off-power event
	case 0x4101:	//
	case 0x4102:	//
	case 0x4103:	//
	case 0x4104:
	case 0x4105:
	case 0x4106:
		uiDisID -= 0x4101;
		// if(0==DispCut(uiDisID))//no event record display, exit page
		if (0 == DispCut(uiDisID))	//
				{
			DisK.SPtr = ucPageTbl[5];
			return;
		}
		break;
	case 0x5000:	//VT,CT
	case 0x5001:
		uiDisID -= 0x5000;
		DispTVCT(uiDisID);
		break;

#ifdef HARDWARE_TWO
		//case 0x6000://user defined register
	case 0x6000:	//
	case 0x6001:
	case 0x6002:
		uiDisID -= 0x6000;
		DispUserde(uiDisID);
		break;
#endif

	default:
		break;
	}

	DispNull:
	//add mark
	DispState();
#ifdef SINGLE_PHASE_MULTI_TARIFF

#else
	BU9792_Refresh(gDispBuf, 0);
#endif
}

