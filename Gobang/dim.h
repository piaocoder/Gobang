static char *wds[]=/*H是己方棋B是对方棋0是空，数字越小越重要*/
{/*0,1,2 */			"0HHHHH0",	"0HHHHHB",	"BHHHHHB",\
														//赢
/* 3,4,5 */			"0BBBBB0",	"0BBBBBH",	"HBBBBBH",\
														//输

/* 6,7,8,9,10 */    "0HHHH0",	"0HHHHB",	"0HH0HH0",	"0HH0HHB","BHH0HHB",\
/* 11,12,13,14 */   "0H0HHH0",	"BH0HHH0",	"0H0HHHB",	"BH0HHHB",\
														//自己
/* 15,16,17,18,19 */"0BBBB0",	"0BBBBH",	"0BB0BB0",	"0BB0BBH","HBB0BBH",\
/* 20,21,22,23 */   "0B0BBB0",	"HB0BBB0",	"0B0BBBH",	"HB0BBBH",\
														//对手
														//唯一必走棋
/*24,25,26,27*/
					"0H0HH0",	"0HHH0",\
					"0B0BB0",	"0BBB0",\
					
/* 28,29 */
					"0H0H0",	"00HH0",\
/* 30,31,32*/"00HHHB","0HH0HB",	"0H0HHB",\
/*33,34,35*/"0HHH0B",	"0HH0HB","0H0HHB",\
/*36*/		"00H0",\
/*37,38*/"0B0B0", "00BB0",\
/*39,40,41,42,43,44*/   "00BBBH","0BB0BH","0B0BBH", "0BBB0H","0BB0BH","0B0BBH",\
/*45,46,47,48,49*/
"00HHB", "0HH0B", "00B0", "00BBH","0BB0H",\
/*50,51,52,53*/"00HB", "0H0B",  "00BH","0B0H",\
/* 54,55,56,57 */   "B0HHHB", "BH0HHB", "B0HHB", "BH0HB", \
/* 58,59,60,61*/ "H0BBBH", "HB0BBH", "H0BBH", "HB0BH"/*++此处添加更多的棋局++*/
};
