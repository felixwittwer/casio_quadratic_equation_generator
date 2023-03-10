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
#include <stdio.h>

void printInt(int x, int y, int f){
    unsigned char buffer[9];
    sprintf(buffer, "%d", f);
    PrintXY(x,y, buffer, 0);
}

void printminiFloat(int x, int y, int f){
    unsigned char buffer[9];
    sprintf(buffer, "%d", f);
    PrintMini(x,y, buffer, MINI_OVER);
}

void orientateSeed(seed){
	PrintXY(100,32, "           ", 0);
	if(seed >= 100){
		printInt(102,32,seed);
	}else if(seed >= 10){
		printInt(105,32,seed);
	}else if(seed < 10 && seed >=0 ){		
		printInt(108,32,seed);
	}else if(seed <= -100){		
		printInt(96,32,seed);
	}else if(seed <= -10){		
		printInt(99,32,seed);
	}else if(seed < 0){		
		printInt(102,32,seed);
	}
}

void renderhelp(int helppage){
	PrintMini(89,2,(unsigned char*)"Page",MINI_OVER);
	printminiFloat(110, 2, helppage);
	if(helppage == 1){
		PrintMini(4,16,(unsigned char*)"Press F2 for generating a    ",MINI_OVER);
		PrintMini(4,24,(unsigned char*)"new quadratic equation       ",MINI_OVER);
		PrintMini(4,36,(unsigned char*)"Press F3 for showing the     ",MINI_OVER);
		PrintMini(4,44,(unsigned char*)"solutions of the equation    ",MINI_OVER);
		PrintMini(95,57,(unsigned char*)"->",MINI_OVER);
		PrintMini(74,57,(unsigned char*)"  ",MINI_OVER);
	}else if(helppage == 2){
		PrintMini(4,16,(unsigned char*)"Use UP and DOWN for          ",MINI_OVER);
		PrintMini(4,24,(unsigned char*)"changing the seed +1 or -1   ",MINI_OVER);
		PrintMini(4,36,(unsigned char*)"Use LEFT and RIGHT for       ",MINI_OVER);
		PrintMini(4,44,(unsigned char*)"changing the seed +10 or -10 ",MINI_OVER);
		PrintMini(74,57,(unsigned char*)"<-",MINI_OVER);
		PrintMini(95,57,(unsigned char*)"   ",MINI_OVER);
	}
}

void renderSettings(int currsetingselected, int statussetone, int statussettwo){
	if(statussetone == 0){
		locate(2,3);
		Print("\xE6\xA5");
	}else if(statussetone ==1){
		locate(2,3);
	 	Print("\xE6\xA6");
	}
	
	if(statussettwo == 0){
		locate(2,5);
		Print("\xE6\xA5");
	}else if(statussettwo ==1){
		locate(2,5);
	 	Print("\xE6\xA6");
	}
}

int savedata(int statussetone, int statussettwo, int seed, int file, FONTCHARACTER*PathName){
	   char save_data[30];

	   Bfile_DeleteFile(PathName);
	   Bfile_CreateFile(PathName, 30);
	   file = Bfile_OpenFile(PathName, _OPENMODE_WRITE);

	   sprintf(save_data, "%d%d%d", statussetone, statussettwo, seed);
	   Bfile_WriteFile(file, &save_data, 30);	

	   Bfile_CloseFile(file);
}

void readdata(int statussetone, int statussettwo, int seed, int file, FONTCHARACTER*PathName){
	   unsigned  char read_data[30];
	   char buffer[30];

	   file = Bfile_OpenFile(PathName, _OPENMODE_READ);
	   Bfile_ReadFile(file, &read_data, 30, 0);

//	   sprintf(buffer, "%d", read_data);
//	   PrintMini(35, 57, buffer, MINI_OVER);

//	   [READ STATUS SET one/two]

//	   int statussetone = [READ STATUS];
//	   int statussettwo = [READ STATUS];

//	   if(statussetone==1){
//		seed = [READSEED];
//	   }

	   Bfile_CloseFile(file);
}

void displaydebugcode(int x, int y, int statussetone, int statussettwo, int file, FONTCHARACTER*PathName){
	   unsigned  char read_data[30];

	   Bdisp_SetPoint_DDVRAM(x-2,y-2,1);
	   Bdisp_SetPoint_DDVRAM(x+4,y-2,1);
	   Bdisp_SetPoint_DDVRAM(x+4,y+4,1);
	   Bdisp_SetPoint_DDVRAM(x-2,y+4,1);

	   if(Bfile_ReadFile(file, &read_data, 30, 0)>=0){
			Bdisp_SetPoint_DDVRAM(x,y,1);
	   }else{
			Bdisp_SetPoint_DDVRAM(x,y,0);
	   }

	   if(Bfile_OpenFile(PathName, _OPENMODE_WRITE)>=0){
			Bdisp_SetPoint_DDVRAM(x+1,y,1);
	   }else{
			Bdisp_SetPoint_DDVRAM(x+1,y,0);
	   }

	   if(Bfile_ReadFile(file, &read_data, 30, 0)>=0){
			Bdisp_SetPoint_DDVRAM(x+2,y,1);
	   }else{
			Bdisp_SetPoint_DDVRAM(x+2,y,0);
	   }

	   if(statussetone==1){
			Bdisp_SetPoint_DDVRAM(x,y+2,1);
	   }else{
			Bdisp_SetPoint_DDVRAM(x,y+2,0);
	   }

	   if(statussettwo==1){
			Bdisp_SetPoint_DDVRAM(x+1,y+2,1);
	   }else{
			Bdisp_SetPoint_DDVRAM(x+1,y+2,0);
	   }
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
    FONTCHARACTER PathName[] = {'\\', '\\', 'f', 'l', 's', '0', '\\', 'Q', 'U', 'A', 'D', 'G', 'E', 'N', '.', 'd', 'a', 't', 0};
    int selecting = 1;
    int running = 1;
    int numberselected = 1;

	int helppage = 1;

    int currsetingselected = 1;
    int statussetone = 0;
    int statussettwo = 0;

    int seed = 1;
    int nullone = 0;
    int nulltwo = 0;
    int p = 0;
    int q = 0;
    char buffer[12];

    int file;

    Bdisp_AllClr_DDVRAM();

//   readdata(statussetone, statussettwo, seed, file, PathName);

    while(1){
	//Startscreen
	   PrintMini(7,2,(unsigned char*)">>>> Quad Gen <<<<",MINI_OVER);
	   PrintMini(14,17,(unsigned char*)"1 Generator",MINI_OVER);
	   PrintMini(14,25,(unsigned char*)"2 HELP",MINI_OVER);
	   PrintMini(14,33,(unsigned char*)"3 SETTINGS",MINI_OVER);
	   PrintMini(14,41,(unsigned char*)"4 Version",MINI_OVER);
	   PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
	   PrintMini(115,57,(unsigned char*)"EXE",MINI_OVER);	   
	   readdata(statussetone, statussettwo, seed, file, PathName);
	   if(statussettwo==1){
			displaydebugcode(90, 30, statussetone, statussettwo, file, PathName);
	   }

	   Bdisp_PutDisp_DD();
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
			numberselected = 1;
			locate(2,3);
	    		Print("\xE6\x9B");
			locate(2,4);
	    		Print("\xE6\x83");
			locate(2,5);
	    		Print("\xE6\x83");
			locate(2,6);
	    		Print("\xE6\x83");
		}
	
		if(key == KEY_CHAR_2){
			numberselected = 2;
			locate(2,3);
	    		Print("\xE6\x83");
			locate(2,4);
	    		Print("\xE6\x9B");
			locate(2,5);
	    		Print("\xE6\x83");
			locate(2,6);
	    		Print("\xE6\x83");
		}
	
		if(key == KEY_CHAR_3){
			numberselected = 3;
			locate(2,3);
	    		Print("\xE6\x83");
			locate(2,4);
	    		Print("\xE6\x83");
			locate(2,5);
	    		Print("\xE6\x9B");
			locate(2,6);
	    		Print("\xE6\x83");
		}

		if(key == KEY_CHAR_4){
			numberselected = 4;
			locate(2,3);
	    		Print("\xE6\x83");
			locate(2,4);
	    		Print("\xE6\x83");
			locate(2,5);
	    		Print("\xE6\x83");
			locate(2,6);
	    		Print("\xE6\x9B");
		}
	
		if(key == KEY_CTRL_F1){
			return 1;
		}
		
		if(key == KEY_CTRL_EXIT){
			return 1;
		}
	// for DEBUG: printInt(50,25,numberselected);
	
	   };
	
	
	    Bdisp_AllClr_DDVRAM();
		
	    if(numberselected==1){
	 	PrintMini(15,2,(unsigned char*)">>>> Generator V1 <<<<",MINI_OVER);
		PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
		PrintMini(24,57,(unsigned char*)"Gen",MINI_OVER);
		PrintMini(43,57,(unsigned char*)"Show",MINI_OVER);
		PrintMini(89,57,(unsigned char*)"SAVE",MINI_OVER);
		
		locate(19,4);
	    	Print("\xE6\x9C");
		locate(19,6);
	    	Print("\xE6\x9D");	
		orientateSeed(seed);
		Bdisp_PutDisp_DD();
		Sleep(1000);
		while(1){
			GetKey(&key);

			if(statussettwo==1){
				displaydebugcode(90, 30, statussetone, statussettwo, file, PathName);
	  		}

			if(key ==  KEY_CTRL_F1){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_F5){
				savedata(statussetone, statussettwo, seed, file, PathName);
			}
			
			if(key ==  KEY_CTRL_EXIT){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_UP){
				seed = seed + 1;
			}

			if(key ==  KEY_CTRL_DOWN){
				seed = seed - 1;
			}

			if(key ==  KEY_CTRL_LEFT){
				seed = seed - 10;
			}

			if(key ==  KEY_CTRL_RIGHT){
				seed = seed + 10;
			}

			if(statussetone == 1){
				savedata(statussetone, statussettwo, seed, file, PathName);
			}

			orientateSeed(seed);

			if(key ==  KEY_CTRL_F2){
				srand(seed);
				nullone=rand()%(10+10+1)-10;
				nulltwo=rand()%(10+10+1)-10;
//rand()%(max-min+1)+ min
				p = (nullone + nulltwo)*(-1);
				q = (nullone * nulltwo);
				
//for DEBUG:	printInt(50,15,nullone);
//for DEBUG:	printInt(50,25,nulltwo);

				PrintXY(1,40, (unsigned char*)"                                                                          ", 0);
				if(p >= 0 && q >= 0){
					sprintf(buffer, "+%dx+%d = 0   ", p, q);
				}else if (q >= 0){
					sprintf(buffer, "%dx+%d = 0   ", p, q);
				}else if(p >= 0){
					sprintf(buffer, "+%dx%d = 0   ", p, q);
				}else{
					sprintf(buffer, "%dx%d = 0   ", p, q);
				}
				
    				PrintXY(18,16, buffer, 0);	
				
				locate(2,3);
				Print((unsigned char*)"x");
				locate(3,3);
				Print("\xE5\xC2");
				
				seed = seed +1;
				if(statussetone == 1){
					savedata(statussetone, statussettwo, seed, file, PathName);
				}
			}

			if(key ==  KEY_CTRL_F3){
				printInt(6,40,nullone);
				printInt(50,40,nulltwo);

				if(nullone==nulltwo){
					PrintXY(50,40, (unsigned char*)"                                      ", 0);
				}
			}

			locate(19,4);
	    		Print("\xE6\x9C");
			locate(19,6);
	    		Print("\xE6\x9D");		

		}
	    }

	    if(numberselected==2){
	 	PrintMini(15,2,(unsigned char*)">>>> HELP <<<<",MINI_OVER);
		PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
		PrintMini(24,57,(unsigned char*)"Gen",MINI_OVER);
		PrintMini(43,57,(unsigned char*)"Show",MINI_OVER);
		PrintMini(115,57,(unsigned char*)"EXE",MINI_OVER);
		renderhelp(helppage);
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

			if(key ==  KEY_CTRL_EXIT){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(helppage == 1 && key == KEY_CTRL_F5 || helppage == 1 && key == KEY_CTRL_RIGHT){
				helppage = 2;
			}else if(helppage == 2 && KEY_CTRL_F4 || helppage == 2 && key == KEY_CTRL_LEFT){
				helppage = 1;
			}

			renderhelp(helppage);

		}
	    }
	
	    if(numberselected==3){
	 	PrintMini(23,2,(unsigned char*)">>>> SETTINGS <<<<",MINI_OVER);
		PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
		PrintMini(115,57,(unsigned char*)"EXE",MINI_OVER);

		renderSettings(currsetingselected, statussetone, statussettwo);

		PrintMini(17,14,(unsigned char*)"Autosaving",MINI_OVER);
		PrintMini(17,20,(unsigned char*)"seed and settings",MINI_OVER);

		PrintMini(17,31,(unsigned char*)"SHOW DEBUG code on the",MINI_OVER);
		PrintMini(17,37,(unsigned char*)"bottom right.",MINI_OVER);
		
		PrintMini(33,57,(unsigned char*)"Setting  1",MINI_OVER);

		Bdisp_PutDisp_DD();
		Sleep(1000);
		while(1){
			GetKey(&key);
			if(key == KEY_CTRL_DOWN && currsetingselected == 1){
				currsetingselected = 2;
			}

			if(key == KEY_CTRL_UP && currsetingselected == 2){
				currsetingselected = 1;
			}

			if(key == KEY_CHAR_1){
				currsetingselected = 1;
			}

			if(key == KEY_CHAR_2){
				currsetingselected = 2;
			}

			if(currsetingselected == 1){
				locate(1,3);
	   		 	Print("\xE6\x91");
				locate(1,5);
			    	Print("\xE6\xE0");
			}else if(currsetingselected==2){
				locate(1,5);
			    	Print("\xE6\x91");
				locate(1,3);
			    	Print("\xE6\xE0");
			}

			renderSettings(currsetingselected, statussetone, statussettwo);			

			PrintMini(33,57,(unsigned char*)"Setting",MINI_OVER);
			printminiFloat(67,57,currsetingselected);
//			printminiFloat(73,57,statussetone);			
//			printminiFloat(79,57,statussettwo);	


			if(key ==  KEY_CTRL_EXE){
				if(currsetingselected == 1 && statussetone == 0){
					statussetone = 1;
				}else if(currsetingselected == 1 && statussetone == 1){
					statussetone = 0;
				}
				if(currsetingselected == 2 && statussettwo == 0){
					statussettwo = 1;
				}else if(currsetingselected == 2 && statussettwo == 1){
					statussettwo = 0;
				}
				renderSettings(currsetingselected, statussetone, statussettwo);	
				savedata(statussetone, statussettwo, seed, file, PathName);
			}

			if(key ==  KEY_CTRL_F6){
				if(currsetingselected == 1 && statussetone == 0){
					statussetone = 1;
				}else if(currsetingselected == 1 && statussetone == 1){
					statussetone = 0;
				}
				if(currsetingselected == 2 && statussettwo == 0){
					statussettwo = 1;
				}else if(currsetingselected == 2 && statussettwo == 1){
					statussettwo = 0;
				}
				renderSettings(currsetingselected, statussetone, statussettwo);
				savedata(statussetone, statussettwo, seed, file, PathName);	
			}

			if(key ==  KEY_CTRL_F1){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}

			if(key ==  KEY_CTRL_EXIT){
				selecting = 1;
				Bdisp_AllClr_DDVRAM();
				break;
			}
		}
	    }

	    if(numberselected==4){
	 	PrintMini(29,2,(unsigned char*)">>>> Version <<<<",MINI_OVER);
		PrintMini(2,57,(unsigned char*)"Exit",MINI_OVER);
		PrintMini(115,57,(unsigned char*)"EXE",MINI_OVER);
		PrintMini(4,16,(unsigned char*)"(c) 2022 Felix Wittwer",MINI_OVER);
		PrintMini(4,24,(unsigned char*)"Version 1.4.4",MINI_OVER);
		PrintMini(4,32,(unsigned char*)"Professional Edition",MINI_OVER);
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

			if(key ==  KEY_CTRL_EXIT){
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
