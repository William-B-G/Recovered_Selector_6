// Monitor_Variables.c


#include "global.h"
#include "Tests.h"
#include <string.h>

#define MAX_VARIABLE_BLOCKS 3

void Dsply_This_Var(int16 WhchLine, char *Start_txt, char *TheSeprtr, int16 *ThisVar, int16 TheFormat);
void Dsply_item_in_Group(int16 grp_num, int16 Line_num);

extern int16 PWM_Period_Indicated;
extern int16 Vout_Indicated;
extern int16 Fault_Data_Indicated;
extern int16 Brk_Current_Indicated;
extern int16 Jumper_Setting_Indicated;
extern int16 PWM_Period_plus_Indicated;
extern int16 AC_Line_2_Line_Indicated;
extern int16 AC_Line_Phase_Indicated;

int16 test_var_1 = 0x111;
int16 test_var_2 = 0x222;
int16 test_var_3 = 0x333;
int16 test_var_4 = 0x444;

const char *StartLine_tag[] = 
{
    " ", // one space
    "",  // no spaces
    "Var1b",
    "Var2b",
    "Var3b",
    "Var4b",    
    "Var/x",    
};

const char *Seperator_tag[] = 
{
    " ", // one space
    "",  // no spaces
    "=",
    "= ",
    ":",
    ": ", 
    "-",
    "- ",
    " -",
    " - ",       
};

const char *EndLine_tag[] = 
{
    "",
    " V", 
    " I",  
    " A",
    " mA",
    " mV",       
};

const struct Monitor_Variables_params
{
    int16  Start_Lable[4]; // Lable at start of display,  
           // prior to the variable.
    int16  Lable_to_Var_seperator[4];           
    int16  *Variable_Ptrs[4]; // Array of pointers to the 
           // variables to be displayed.
    int16  Format_to_display_var[4]; // The format to use to display the
    	// variable on one line in msgboard B. 0 = %x, 1 =%d, 2 = %f, 3 = %s
    int16  End_Lable[4]; // Lable at end of display,  
           // after the variable. 	
    int16  Start_idx; // Start of the 4-consecutive locations in msgboard B.   
       
}Monitor_Varbls[MAX_VARIABLE_BLOCKS] =
{
	{
	 // Item 0
		{ 2, 3, 4, 5}, // Lables at start of display,
		{ 3, 3, 3, 3}, // Lables to var seperator,		
		{  // pointers to variables for display
		  &test_var_1, 
		  &test_var_2, 
		  &test_var_3, 
		  &test_var_4
		},
		{ 0, 0, 1, 1}, // formats to use when displaying
		{ 0, 0, 1, 4}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},
//	///////////////////////
	{
	 // Item 1
		{ 0, 0, 0, 0}, // Lables at start of display,
		{ 0, 0, 0, 0}, // Lables to var seperator,		
		{  // pointers to variables for display
		  NULL, 
		  NULL, 
		  NULL, 
		  NULL
		},
		{ 0, 0, 0, 0}, // formats to use when displaying
		{ 0, 0, 0, 0}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},	
//	///////////////////////
	{
	 // Item 2
		{ 0, 0, 0, 0}, // Lables at start of display,
		{ 0, 0, 0, 0}, // Lables to var seperator,		
		{ NULL, NULL, NULL, NULL}, // pointers to the variables to display
		{ 0, 0, 0, 0}, // formats to use when displaying
		{ 0, 0, 0, 0}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},	
//	///////////////////////	
} ;

int16 Generic_2_montr_a_grp_of_4_Vars(int16 which_grp_of_vars)  // proto in test.h
{ // Display up to four variables. Takes a Snap-shot; not a dynamic monitor. 

	char  *Start_tag; // = StartLine_tag[ Monitor_Varbls[which_grp_of_vars].Start_Lable[0] ];
	char  *Seprtr; //    = Seperator_tag[ Monitor_Varbls[which_grp_of_vars].Lable_to_Var_seperator[0] ];
	int16 *TheVar; 
	int16 Format     = Monitor_Varbls[which_grp_of_vars].Format_to_display_var[0]  ;
	int16 grp_num = 0;
	int16 Line_num = 0;
	char str1[22];
	char *str1_ptr;
	char str2[22];
	char str3[22];
	char *str2_ptr;
	char *str3_ptr;


	clr_lcd_dply() ;
    if(which_grp_of_vars >= MAX_VARIABLE_BLOCKS )
    {
    	New_write_display("out of range", 0, 0);  // row 0
    	return DONE_BUT_CONTINUE_DISPLAY;	
    }		
	
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[0] != NULL )
	{
	
		TheVar = Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[0] ;
		str1_ptr = strcpy(str1, StartLine_tag[ Monitor_Varbls[which_grp_of_vars].Start_Lable[0] ] );
		str2_ptr = strcpy(str2, Seperator_tag[ Monitor_Varbls[which_grp_of_vars].Lable_to_Var_seperator[0] ] );
		str3_ptr = strcpy(str3, EndLine_tag[ Monitor_Varbls[which_grp_of_vars].End_Lable[0] ] );
		Format   = Monitor_Varbls[which_grp_of_vars].Format_to_display_var[0] ;
		
		grp_num = 0;
		Line_num = 0;
//		Dsply_item_in_Group(grp_num,Line_num);
//		Dsply_This_Var(0, str1_ptr, str2_ptr, str3_ptr, TheVar, Format);
	    sprintf(src, "tstV1=0x%X", *TheVar);
	    New_write_display(src, 0, 0); // row 0		
	}
	else New_write_display(" = null", 0, 0);  // row 0
		
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[1] != NULL )
	{
		TheVar = Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[1] ;
		str1_ptr = strcpy(str1, StartLine_tag[ Monitor_Varbls[which_grp_of_vars].Start_Lable[1] ] );
		str2_ptr = strcpy(str2, Seperator_tag[ Monitor_Varbls[which_grp_of_vars].Lable_to_Var_seperator[1] ] );
		str3_ptr = strcpy(str3, EndLine_tag[ Monitor_Varbls[which_grp_of_vars].End_Lable[1] ] );
		Format   = Monitor_Varbls[which_grp_of_vars].Format_to_display_var[1] ;
//		Dsply_This_Var(1, str1_ptr, str2_ptr, str3_ptr, TheVar, Format);
	    sprintf(src, "tstV2=0x%X", *TheVar);
	    New_write_display(src, 1, 0); // row 1		
	} 
	else New_write_display(" = null", 1, 0);  // row 1
		
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[2] != NULL )
	{
		TheVar = Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[2] ;
		str1_ptr = strcpy(str1, StartLine_tag[ Monitor_Varbls[which_grp_of_vars].Start_Lable[2] ] );
		str2_ptr = strcpy(str2, Seperator_tag[ Monitor_Varbls[which_grp_of_vars].Lable_to_Var_seperator[2] ] );
		str3_ptr = strcpy(str3, EndLine_tag[ Monitor_Varbls[which_grp_of_vars].End_Lable[2] ] );
		Format   = Monitor_Varbls[which_grp_of_vars].Format_to_display_var[2] ;
//		Dsply_This_Var(2, str1_ptr, str2_ptr, str3_ptr, TheVar, Format);
		Dsply_This_Var(2, str1_ptr, str2_ptr, TheVar, Format);		
	}
	else New_write_display(" = null", 2, 0);  // row 2
		
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[3] != NULL )
	{
		TheVar = Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[3] ;
		str1_ptr = strcpy(str1, StartLine_tag[ Monitor_Varbls[which_grp_of_vars].Start_Lable[3] ] );
		str2_ptr = strcpy(str2, Seperator_tag[ Monitor_Varbls[which_grp_of_vars].Lable_to_Var_seperator[3] ] );
		str3_ptr = strcpy(str3, EndLine_tag[ Monitor_Varbls[which_grp_of_vars].End_Lable[3] ] );
		Format   = Monitor_Varbls[which_grp_of_vars].Format_to_display_var[3] ;
		Dsply_This_Var(3, str1_ptr, str2_ptr, TheVar, Format);		
	}
	else New_write_display(" = null", 3, 0);  // row 3		
			
/*	
    sprintf(src, "I=%d,AC=%d,TrgH=0x%X",Brk_Current_Indicated, AC_Line_2_Line_Indicated, trigger_high);
    New_write_display(src, 0, 0);  // row 0
    sprintf(src, "Vout=%d, Phase=%d",Vout_Indicated, AC_Line_Phase_Indicated);
    New_write_display(src, 1, 0); // row 1    
    sprintf(src, "Perd=%d, Prd+=%d",PWM_Period_Indicated, PWM_Period_plus_Indicated);
    New_write_display(src, 2, 0); // row 2     
    sprintf(src, "Flt=%d,Jmpr=%d",Fault_Data_Indicated, Jumper_Setting_Indicated);
    New_write_display(src, 3, 0); // row 3
*/     
    return DONE_BUT_CONTINUE_DISPLAY;
}

//void Dsply_This_Var(int16 WhchLine, char *Start_txt, char *TheSeprtr, char *TheUnits, int16 *ThisVar, int16 TheFormat)
void Dsply_This_Var(int16 WhchLine, char *Start_txt, char *TheSeprtr, int16 *ThisVar, int16 TheFormat)
{
/*
char str1[14] = "Hello,";    // The array has enough space for 'Hello,' plus " world!" plus a null terminator 
strcat(str1, " world!");
puts(str1);                 // prints "Hello, world!" to stdout followed by a newline 
*/
	char str1[22] = "";
	char str2[22] = "";
	
	strcpy(str1, Start_txt);
	strcpy(str2, TheSeprtr);
	strcat(str1, str2);
//	strcpy(str2, TheUnits);
	
	if( ThisVar = NULL) return;
		
	switch (TheFormat)
	{
		case 0: // %x
		    strcat(str1, "0x%X");
//		    strcat(str1, str2);
			sprintf(src, str1, *ThisVar);			
			break;
			
		case 1: // %d
		    strcat(str1, "%d");
//		    strcat(str1, str2);
			sprintf(src, str1, *ThisVar);			
			break;
			
		case 2: // %f
		    strcat(str1, "%f");
//		    strcat(str1, str2);
			sprintf(src, str1, *ThisVar);			
			break;
			
		case 3: // %s
		    strcat(str1, "%s");
//		    strcat(str1, str2);
			sprintf(src, str1, *ThisVar);			
			break;						
	}	
		
//	strcat(str1, "0x%X");
//	sprintf(src, str1, *ThisVar);
//	New_write_display(str1, WhchLine, 0);  // row WhchLine
	New_write_display(src, WhchLine, 0);  // row WhchLine
}

void Dsply_item_in_Group(int16 grp_num, int16 Line_num)
{
    int16 *TheVar; 
    int16 Format ;  
    char str1[22];
    char *str1_ptr;
    char str2[22];
    char str3[22];
    char *str2_ptr;
    char *str3_ptr;
    
    TheVar = Monitor_Varbls[grp_num].Variable_Ptrs[Line_num] ;
    str1_ptr = strcpy(str1, StartLine_tag[ Monitor_Varbls[grp_num].Start_Lable[Line_num] ] );
    str2_ptr = strcpy(str2, Seperator_tag[ Monitor_Varbls[grp_num].Lable_to_Var_seperator[Line_num] ] );
    str3_ptr = strcpy(str3, EndLine_tag[ Monitor_Varbls[grp_num].End_Lable[Line_num] ] );
    Format   = Monitor_Varbls[grp_num].Format_to_display_var[Line_num] ; 

    Dsply_This_Var(Line_num, str1_ptr, str2_ptr, TheVar, Format);   
}