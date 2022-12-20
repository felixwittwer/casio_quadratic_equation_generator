/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include "MonochromeLib.h"
#include <stdio.h>

void printFloat(int x, int y, float f){
    unsigned char buffer[9];
    sprintf(buffer, "%f", f);
    PrintXY(x,y, buffer, 0);
//    PrintMini(x,y, buffer, MINI_OVER);
}

void printminiFloat(int x, int y, float f){
    unsigned char buffer[9];
    sprintf(buffer, "%f", f);
//    PrintXY(x,y, buffer, 0);
    PrintMini(x,y, buffer, MINI_OVER);
}

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
    int selecting = 1;
    int running = 1;
    float numerselected = 0;
    float pi = 3.121593;
    int nullone = 0;
    int nulltwo = 0;
    int p = 0;
    int q = 0;

	    ML_CLEAR_VRAM;
	    ML_CLEAR_SCREEN;

    while(1){
	//Startscreen
	   PrintMini(7,2,(unsigned char*)">>>> Quad Gen <<<<",MINI_OVER);
	   PrintMini(14,17,(unsigned char*)"1 Generator",MINI_OVER);
	   PrintMini(14,25,(unsigned char*)"2 HELP",MINI_OVER);
	   PrintMini(14,33,(unsigned char*)"3 Version",MINI_OVER);
	   PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
	   PrintMini(115,57,(unsigned char*)"EXE",MINI_OVER);
	   
	   ML_DISPLAY_VRAM;
	
	
	   while(selecting==1){
	
		GetKey(&key);
	
		if(key ==  KEY_CTRL_EXE){
			selecting = 0;
			PrintMini(50,17,(unsigned char*)"Break",MINI_OVER);
			break;
		}
	
		if(key ==  KEY_CTRL_F6 ){
			selecting = 0;
			PrintMini(50,17,(unsigned char*)"Break",MINI_OVER);
			break;
		}
		
		if(key == KEY_CHAR_1){
			numerselected = 1;
			locate(2,3);
	    		Print("\xE6\x9B");
			locate(2,4);
	    		Print("\xE6\x83");
			locate(2,5);
	    		Print("\xE6\x83");
		}
	
		if(key == KEY_CHAR_2){
			numerselected = 2;
			locate(2,3);
	    		Print("\xE6\x83");
			locate(2,4);
	    		Print("\xE6\x9B");
			locate(2,5);
	    		Print("\xE6\x83");
		}
	
		if(key == KEY_CHAR_3){
			numerselected = 3;
			locate(2,3);
	    		Print("\xE6\x83");
			locate(2,4);
	    		Print("\xE6\x83");
			locate(2,5);
	    		Print("\xE6\x9B");
		}
	
		if(key == KEY_CTRL_F1){
			return 1;
		}
	// for DEBUG: printFloat(50,25,numerselected);
	
	   };
	
	
	    Bdisp_AllClr_DDVRAM();
		
	    if(numerselected==1){
	 	PrintMini(15,2,(unsigned char*)">>>> Generator V1 <<<<",MINI_OVER);
		PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
		PrintMini(24,57,(unsigned char*)"Gen",MINI_OVER);
		PrintMini(43,57,(unsigned char*)"Show",MINI_OVER);
		Bdisp_PutDisp_DD();
		Sleep(1000);
		while(1){
			GetKey(&key);
			if(key ==  KEY_CTRL_F1){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_F2){
				nullone=rand()%(10+10+1)-10;
				nulltwo=rand()%(10+10+1)-10;
//rand()%(max-min+1)+ min
				p = (nullone + nulltwo)*(-1);
				q = (nullone * nulltwo);
				
//for DEBUG:	printFloat(50,15,nullone);
//for DEBUG:	printFloat(50,25,nulltwo);

				PrintXY(1,40, (unsigned char*)"                                                                          ", 0);

				if(p >= 0){
					locate(4,3);
					Print((unsigned char*)"+");
					printFloat(24,16,p);	
				}
				else{
					printFloat(18,16,p);
				}

				if(p < 10 && p > -10){
					PrintXY(30,16, (unsigned char*)"x   ", 0);
					if(q >= 0){
						PrintXY(37,16, (unsigned char*)"+", 0);
						printFloat(43,16,q);	
						
						if(q < 10 && q > -10){
							PrintXY(49,16, (unsigned char*)" = 0               ", 0);
						}
						else{
							PrintXY(55,16, (unsigned char*)" = 0              ", 0);
						}

					}
					else{
						printFloat(37,16,q);

						if(q < 10 && q > -10){
							printFloat(37,16,q);
							PrintXY(49,16, (unsigned char*)" = 0               ", 0);
//	DEBUG for Version 1.2 fix							
//							locate(4,4);
//							Print((unsigned char*)"Error");
						}
						else{
							PrintXY(55,16, (unsigned char*)" = 0              ", 0);
						}
					}
				}
				else{
				PrintXY(36,16, (unsigned char*)"x  ", 0);
					if(q >= 0){
						PrintXY(43,16, (unsigned char*)"+", 0);
						printFloat(49,16,q);
						
						if(q < 10 && q > -10){
							PrintXY(55,16, (unsigned char*)" = 0               ", 0);
						}
						else{
							PrintXY(61,16, (unsigned char*)" = 0              ", 0);
						}	
					}
					else{
						printFloat(43,16,q);

						if(q < 10 && q > -10){
							printFloat(37,16,q);
							PrintXY(49,16, (unsigned char*)" = 0               ", 0);
						}
						else{
							PrintXY(55,16, (unsigned char*)" = 0              ", 0);
						}
					}
				}
				
				locate(2,3);
				Print((unsigned char*)"x");
				locate(3,3);
				Print("\xE5\xC2");
			}

			if(key ==  KEY_CTRL_F3){
				printFloat(6,40,nullone);
				PrintXY(43,40, (unsigned char*)"                      ", 0);
				printFloat(50,40,nulltwo);
				PrintXY(87,40, (unsigned char*)"                                      ", 0);
			}
		}
	    }
	
	    if(numerselected==2){
	 	PrintMini(33,2,(unsigned char*)">>>> HELP <<<<",MINI_OVER);
		PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
		PrintMini(24,57,(unsigned char*)"Gen",MINI_OVER);
		PrintMini(43,57,(unsigned char*)"Show",MINI_OVER);

		PrintMini(4,16,(unsigned char*)"Press F2 for generating a ",MINI_OVER);
		PrintMini(4,24,(unsigned char*)"new quadratic equation",MINI_OVER);
		PrintMini(4,36,(unsigned char*)"Press F3 for showing the",MINI_OVER);
		PrintMini(4,44,(unsigned char*)"solutions of the equation",MINI_OVER);

		PrintMini(115,57,(unsigned char*)"EXE",MINI_OVER);
		Bdisp_PutDisp_DD();
		Sleep(1000);
		while(1){
			GetKey(&key);
			if(key ==  KEY_CTRL_EXE){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_F6){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_F1){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}
		}
	    }
	
	    if(numerselected==3){
	 	PrintMini(29,2,(unsigned char*)">>>> Version <<<<",MINI_OVER);
		PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
		PrintMini(115,57,(unsigned char*)"EXE",MINI_OVER);
		PrintMini(4,16,(unsigned char*)"(c) 2022 Felix Wittwer",MINI_OVER);
		PrintMini(4,24,(unsigned char*)"Version 1.3",MINI_OVER);
		Bdisp_PutDisp_DD();
		Sleep(1000);
		while(1){
			GetKey(&key);
			if(key ==  KEY_CTRL_EXE){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_F6){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_F1){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}
		}
	    }
    }


    while(1){
        GetKey(&key);
    }

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

