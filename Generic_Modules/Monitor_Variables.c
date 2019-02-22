// Monitor_Variables.c


#include "global.h"
#include "Tests.h"
//#include "GALX_1132_TEST.h"
#include <string.h>

#define MAX_VARIABLE_BLOCKS 5

void Dsply_This_Var(int16 WhchLine, int16 TheFormat);
// void Dsply_This_Var(int16 WhchLine, char *Start_txt, char *TheSeprtr, int16 *ThisVar, int16 TheFormat);
void Dsply_item_in_Group(int16 grp_num, int16 Line_num);

extern int16 PWM_Period_Indicated;
extern int16 Vout_Indicated;
extern int16 Fault_Data_Indicated;
extern int16 Brk_Current_Indicated;
extern int16 Jumper_Setting_Indicated;
extern int16 PWM_Period_plus_Indicated;
extern int16 AC_Line_2_Line_Indicated;
extern int16 AC_Line_Phase_Indicated;
extern int16 Brake_Relay_Bypass;
extern int16 Msg_9_recvd;
extern 	int16 msg_9_sel;
extern int16 msg_9_Return_Command_Byte;
extern int16 trigger_high; // used as a debug source for 1143 MPU. This byte used to display LED's via GALX4-0047.

extern int16 Dynamic_26_D0;
extern int16 Dynamic_26_D1;
extern int16 Dynamic_26_D2;
extern int16 Dynamic_26_D3;
extern int16 Dynamic_26_D4;
extern int16 Dynamic_26_D5;
extern int16 Dynamic_26_D6;
extern int16 Dynamic_26_D7;

extern int16 Dynamic_27_D0;
extern int16 Dynamic_27_D1;
extern int16 Dynamic_27_D2;
extern int16 Dynamic_27_D3;
extern int16 Dynamic_27_D4;
extern int16 Dynamic_27_D5;
extern int16 Dynamic_27_D6;
extern int16 Dynamic_27_D7;

extern uint32 Start_of_APS_tape;
extern int16 APS_delta;  // from start of tape
extern int16 APS_Seq;
extern int16 APS_27_0; // Byte 0, addr 27
extern int16 APS_27_1; // Byte 1, addr 27
extern int16 APS_27_2; // Byte 2, addr 27
extern int16 New_APS_Delta;
extern int16 New_APS_Delta_mm;
extern int16 APS_LR_Alignment ;
extern int16 APS_FarNear_Alignment ;

int16 test_var_1 = 0x111;
int16 test_var_2 = 0x222;
int16 test_var_3 = 0x333;
int16 test_var_4 = 0x444;

int16 Dyn_var_1 = 0x555;
int16 Dyn_var_2 = 0xfff0;
int16 Dyn_var_3 = 0x777;
int16 Dyn_var_4 = 0xff00;

int16 APS_mhb  = 0;
int16 APS_mlb  = 0;
int16 APS_lb = 0;

int16 msg_14_tally = 0;	
int16 msg_16_tally = 0;

int16 Set_The_Select_Data(int16 Selector_Data);
 
//char spinner[6] = "|/-|/";
char spinner[9] = { '|', '/', '-', '\92', '|', '/', '-', '\x5C', '\0' }; 


const char *StartLine_tag[] = 
{
    " ", // one space
    "",  // no spaces
    "Var1b", // 2
    "Var2b",
    "Var3b",
    "Var4b",    
    "Var/x",
    "Dyn_1",
    "Dyn_2",
    "Dyn_3",
    "Dyn_4", // 10
    "Brk ",
    "BUS ",
    "Prd  ",
    "Prd+ ",  // 14
    "Selct",
    "Brk Vout",
    "L 2 L",  // 17
    "Phase",
    "Brk_Rly_Byps",
    "PWM_prd",  // 20
    "Jmpr",
    "Cmnd Byte",
    "trg High", // 23
    "APS",
    "seq num",
    "LowWrd",  // 26
    "MidWrd",
    "HiWrd",  // 28
    "Align",
    "msg 14",
    "msg 16",
};

const char *Seperator_tag[] = 
{
    " ", // one space
    "",  // no spaces
    "=", // 2
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
    " I", // 2 
    " A",
    " mA",
    " mV",
    " VAC", // 6 
    " mm",
    " LR",  // 8
    " FrNr",      
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
		{ 0, 0, 1, 1}, // formats to use when displaying (0 = %x, 1 =%d, 2 = %f, 3 = %s).
		{ 0, 0, 1, 4}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},
//	///////////////////////
	{
	 // Item 1
		{ 24, 25, 29, 29}, // Lables at start of display,
		{ 0, 0, 0, 0}, // Lables to var seperator,		
		{  // pointers to variables for display 
		  &New_APS_Delta_mm,	 
		  &APS_Seq,
		  &APS_LR_Alignment,		  
		  &APS_FarNear_Alignment,
		},
		{ 1, 0, 0, 0}, // formats to use when displaying (0 = %x, 1 =%d, 2 = %f, 3 = %s).
		{ 7, 0, 8, 9}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},	
//	///////////////////////
	{
	 // Item 2
        { 18, 19, 20, 21}, // Lables at start of display,
        { 0, 0, 0, 0}, // Lables to var seperator,      
        { 
            &APS_27_0, 
            &APS_27_1, 
            &APS_27_2, 
            NULL
		}, // pointers to the variables to display
		{ 0, 0, 0, 0}, // formats to use when displaying (0 = %x, 1 =%d, 2 = %f, 3 = %s).
		{ 0, 0, 0, 0}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},	
//	///////////////////////	

	{
	 // Item 3
        { 26, 27, 28, 24}, // Lables at start of display,
        { 0, 0, 0, 0}, // Lables to var seperator,      
        { 
            &APS_mhb, 
            &APS_mlb, 
            &APS_lb, 
            &New_APS_Delta,
		}, // pointers to the variables to display
		{ 0, 0, 0, 0}, // formats to use when displaying (0 = %x, 1 =%d, 2 = %f, 3 = %s).
		{ 0, 0, 0, 0}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},	
//	///////////////////////	

	{
	 // Item 4
        { 30, 31, 0, 0}, // Lables at start of display,
        { 2, 2, 0, 0}, // Lables to var seperator,      
        { 
            &msg_14_tally, 
            &msg_16_tally, 
            NULL, 
            NULL,
		}, // pointers to the variables to display
		{ 1, 1, 0, 0}, // formats to use when displaying (0 = %x, 1 =%d, 2 = %f, 3 = %s).
		{ 0, 0, 0, 0}, // Lables at the end of the display line
		0,   // starting index in msgboard B. All four variables displayed
			// in consecutive bins starting at this index.
	},	
//	///////////////////////	
} ;

	char  *Start_tag; // = StartLine_tag[ Monitor_Varbls[which_grp_of_vars].Start_Lable[0] ];
	char  *Seprtr; //    = Seperator_tag[ Monitor_Varbls[which_grp_of_vars].Lable_to_Var_seperator[0] ];
	int16 *TheVar; 
	int16 Format  ; 
	int16 grp_num = 0;
	int16 Line_num = 0;
	char str1[22];
	char *str1_ptr;
	char str2[22];
	char str3[22];
	char *str2_ptr;
	char *str3_ptr;
	int16 Dynamic_var_mode = 0; // no dynamic mode; static only
	int16 Previous_var_value[4] = { -1, -1, -1, -1 };
	
	enum
	{
	    Initialize,
	    Run_Test,
	};

int16 Dynamic_montr_a_grp_of_4_Vars(int16 msg8_plus_which_grp_of_vars)  // proto in test.h
{  // Display up to four variables. Displays dynamicaly; if the value changes, it is
    // updated. Update rate 1/2s
    
    int16 i,j,k = 0;
    int16 Request_CT_CAN_Msg_Send;
    int16 which_grp_of_vars;
    int16 Show_Spinner = 0;
    static int16 test_Kase = Initialize;
    static int16 spinner_idx = 0;
    static int16 Special_Char = 0; //Special Characters create by "load_special_char()"
    static int16 Msg_9_Special_Char = 0;
    static int16 Delay_Count = 3; // 3 = 3 * 100ms = 300ms

    static int16 ReturnVal = CONTINUE_SERVICE; // Required for Retest Option
    
    SIU.GPDO[Z0_LED].R = !SIU.GPDO[Z0_LED].R;  // toggle LED;
    which_grp_of_vars = msg8_plus_which_grp_of_vars & 0x3FFF; // mask off 2 msb
    Request_CT_CAN_Msg_Send = msg8_plus_which_grp_of_vars & 0x8000; // use msb to signal to send
    //  msg 8 to 1143 brake board.
    Show_Spinner = msg8_plus_which_grp_of_vars & 0x4000;
    switch (test_Kase)
    {
        case Initialize:
            //  ADD CODE
            clr_lcd_dply();
            ReturnVal = CONTINUE_SERVICE;
            CurrentTestPassFail =0;  // fail
            Retest_Option_Parm = 0; 
            RetestResponse = 1;
            Delay_Count = 3; //  10 = 1s; 3 = 300 ms
            timers[t_Generic_Delay] = 0;
            Previous_var_value[0] = -1;
            Previous_var_value[1] = -1;
            Previous_var_value[2] = -1;
            Previous_var_value[3] = -1;
            Generic_2_montr_a_grp_of_4_Vars(0x1000 + which_grp_of_vars); // the 0x1000 is to only
                // update display if Previous_var1_val_x has changed.
            test_Kase = Run_Test;
            break;
            
        case Run_Test:
            if(timers[t_Generic_Delay] < Delay_Count) break;
            timers[t_Generic_Delay] = 0;            
            //  ADD CODE
            Generic_2_montr_a_grp_of_4_Vars(0x1000 + which_grp_of_vars); // the 0x1000 is to only
                // update display if Previous_var1_val_x has changed.
            if(Request_CT_CAN_Msg_Send) Msg_8_Request = 1; // only for 1143 brake board.
            if(Check_for_Mode_Button() )  {
                test_Kase = Initialize;
                ReturnVal = FINISHED_WITH_SERVICE;
            }   
// Show operator that system is alive by spinning row 0, column 20
            if(Show_Spinner)
            {
//                LCD_Display[0][19] = spinner[spinner_idx++];
//                if(spinner_idx > 7) spinner_idx = 0; 
                // Just to show that this function is being continueally called.
                LCD_Display[0][19] =  (char)Special_Char++; 
                if(Special_Char > 7) Special_Char = 0;  
                
                if(Msg_9_recvd)
                { // To show that a new message 9 is being received from 1143AN
                    Msg_9_recvd = 0; // reset trigger that gets set in ctcan.c
                    LCD_Display[2][19] =  (char)Msg_9_Special_Char++; 
                    if(Msg_9_Special_Char > 7) Msg_9_Special_Char = 0;   
                }
            }
                                               
            break;
               
        default:
            break;                
    }
    return ReturnVal;    
}


int16 Generic_2_montr_a_grp_of_4_Vars(int16 which_grp_parms)  // proto in test.h
{ // Display up to four variables. Takes a Snap-shot; not a dynamic monitor. 
    int16 which_grp_of_vars = which_grp_parms & 0x0fff;
    
	if(Dynamic_var_mode == 0)clr_lcd_dply() ; // do not clear if doing dynamic mode.
	Dynamic_var_mode = 0x1000 & which_grp_parms;
    if(which_grp_of_vars >= MAX_VARIABLE_BLOCKS )
    {
    	New_write_display("out of range", 0, 0);  // row 0
    	return DONE_BUT_CONTINUE_DISPLAY;	
    }		
    grp_num = which_grp_of_vars;	
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[0] != NULL )
	{			
		
		Line_num = 0;
		Dsply_item_in_Group(grp_num,Line_num);
//		Dsply_This_Var(0, str1_ptr, str2_ptr, str3_ptr, TheVar, Format);
//	    sprintf(src, "tstV1=0x%X", *TheVar);
//	    New_write_display(src, 0, 0); // row 0		
	}
	else New_write_display(" = null", 0, 0);  // row 0
		
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[1] != NULL )
	{
		Line_num = 1;
		Dsply_item_in_Group(grp_num,Line_num);		
	} 
	else New_write_display(" = null", 1, 0);  // row 1
		
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[2] != NULL )
	{
		Line_num = 2;
		Dsply_item_in_Group(grp_num,Line_num);		
	}
	else New_write_display(" = null", 2, 0);  // row 2
		
	if( Monitor_Varbls[which_grp_of_vars].Variable_Ptrs[3] != NULL )
	{
		Line_num = 3;
		Dsply_item_in_Group(grp_num,Line_num);		
	}
	else New_write_display(" = null", 3, 0);  // row 3		
   
    return DONE_BUT_CONTINUE_DISPLAY;
}

//void Dsply_This_Var(int16 WhchLine, char *Start_txt, char *TheSeprtr, char *TheUnits, int16 *ThisVar, int16 TheFormat)
void Dsply_This_Var(int16 WhchLine, int16 TheFormat)
{
/*
char str1[14] = "Hello,";    // The array has enough space for 'Hello,' plus " world!" plus a null terminator 
strcat(str1, " world!");
puts(str1);                 // prints "Hello, world!" to stdout followed by a newline 
*/
	if( TheVar == NULL) return;
	if( *TheVar == Previous_var_value[WhchLine]) return;
		
	Previous_var_value[WhchLine] = *TheVar;
	switch (TheFormat)
	{
		case 0: // %x
		    strcat(str1, "0x%-4X"); // something like "Var_1 ="0x%X"		
			break;
			
		case 1: // %d
		    strcat(str1, "%-4d");			
			break;
			
		case 2: // %f
		    strcat(str1, "%-4f");			
			break;
			
		case 3: // %s
		    strcat(str1, "%-4s");		
			break;						
	}			

    strcat(str1, str3); // something like "Var_1 ="0x%X mA"
    sprintf(src, str1, (uint16)*TheVar);
	New_write_display(src, WhchLine, 0);  // row WhchLine
}

void Dsply_item_in_Group(int16 grp_num, int16 Line_num)
{    
    TheVar = Monitor_Varbls[grp_num].Variable_Ptrs[Line_num] ;
    strcpy(str1, StartLine_tag[ Monitor_Varbls[grp_num].Start_Lable[Line_num] ] ); // something like "Var_1"
    strcpy(str2, Seperator_tag[ Monitor_Varbls[grp_num].Lable_to_Var_seperator[Line_num] ] ); // something like " ="
    strcat(str1, str2); //  create something like "Var_1 ="
    strcpy(str3, EndLine_tag[ Monitor_Varbls[grp_num].End_Lable[Line_num] ] ); // something like " mA"
    Format   = Monitor_Varbls[grp_num].Format_to_display_var[Line_num] ; // 0 - 3

    Dsply_This_Var(Line_num, Format);   
//    sprintf(src, "v= 0x%X", *TheVar);
//	New_write_display(src, Line_num, 0);  // row WhchLine
}

/*
int16 Set_The_Select_Data(int16 Selector_Data)
{
	if(Selector_Data == -1) debug_select_data = 0; // to allow brake_data_req to cycle thru 0 - 4
	else
	{
		if(Selector_Data > 4) return FINISHED_WITH_SERVICE;
		debug_select_data = 1; //  to freeze the brake_data_req with this value. 
		brake_data_req = Selector_Data;		
	}
	return FINISHED_WITH_SERVICE;
}
*/

