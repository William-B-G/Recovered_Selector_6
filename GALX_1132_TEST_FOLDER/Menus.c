// Menus.c

#include "global.h"
#include "Tests.h"

// FOR A COMPLETE LIST OF THE MENUS SEE ARCHIVED_MENUS.C
// OR XMENU.C IN //GALX_1132_TEST_FOLDER
// IN VERSION 'J' OF THE 1134 CTB TEST FIXTURE. (2018-5-24)

/*struct a_menu { // each menu consists of the text to
    // display, a function pointer, and the param
    // value to send to the function. The function
    // is executed when the user clicks the 'enter' button.
    char MenuItem[21]; // text to display.
    void *Service;  // function pointer
    int16 param;    // the parameter to send to the function.
};
*/

// Display_RS485_Baud

// sx_recbuf[SE1COM][sx_rbf[SE1COM]]
// ShowMeRxBuf
// Debug_IO_Eval
struct a_menu Main_Generic_Test_Menu[] = {
    /// = 0
//    {" Main Menu           0", DoNothing, 0}, //
//    {" Display test_vars    ", Generic_2_montr_a_grp_of_4_Vars, 0},
    {" Selctr 6 Tst Fixt 0", Really_DoNothing, 0}, //
	{" Functional Test    ", Run_3_tsts_together, 0}, 
    {" MANUAL TEST MODE  3", Start_a_Menu, 3},
    {" DIAGNOSTICS       1", Start_a_Menu, 1},   
    {" Dsply APS data    1", Dynamic_montr_a_grp_of_4_Vars,   1 }, 
    {" APS mhb,mlb,lb    3", Dynamic_montr_a_grp_of_4_Vars,   3 }, 
    {" SPI CAN msgs      4", Dynamic_montr_a_grp_of_4_Vars,   4 }, 
    {" Run Power-Up Mode  ", JumpToPowerUp, 0}, 
    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
//    {" Generic Var Dsply 0", Generic_2_montr_a_grp_of_4_Vars, 0 },
//    {" Generic Var Dsply 2", Generic_2_montr_a_grp_of_4_Vars, 2 },

/*    
    {" CAN COMM TST, FRONT", Dsply_Msg_29_Return, 1}, // Dsply_Msg_29_Return
    {" CAN COMM TST, REAR ", Dsply_Msg_29_Return, 0x4001},
    {" Rear door, quiet   ", Dsply_Msg_29_Return, 0x6001},
    
    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7}, 
*/       
//    {" CAN BAUD RATE 115.2", ctCAN_BAUD, 0},
//    {" CAN BAUD RATE 57.6 ", ctCAN_BAUD, 1},
//    {" FRONT/REAR DR TST  ", DoNothing, 0},
    {" SW VERSION         ", Display_SW_Version, 0},
//    {" Send Message     28", Start_a_Menu, 2},
//    {" Wrapper tst       6", Start_a_Menu, 6},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
/*    
    {" Perfrm single IO mk", Start_a_Menu, 12}, // this is for SW debug, not a real test
    {" Perform mock IO tst", Perform_all_IO_Tests, 0x8000}, // this is for SW debug, not a real test
    {" Show Msg Board B   ", DisplayMsgBrd_B, 0},
    {" Perform IO test    ", Perform_all_IO_Tests,      0}, // this is a real test
    {" Tgl LDO7 LED       ", Toggle_4_0047, 1}, // index runs from 0 - 5 for LDO6 - LDO11
    {" Tgl LDO8 LED       ", Toggle_4_0047, 2}, // index runs from 0 - 5 for LDO6 - LDO11
    {" Tgl Dbg8 LED       ", Toggle_O_CTxx, 8},
    {" Set All Dbgxx      ", Set_or_Clear_All_CTxx, 1},
    {" Clear All Dbgxx    ", Set_or_Clear_All_CTxx, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" Disply rdoutp(*ptr)", Read_and_Display_rdoutp, 0},
    {" Disply rdinp (*ptr)", Read_and_Display_Rd_Inputs, 0}, 
//  {" Disply All inputs  ", Read_and_Display_All_Inputs, 1},
//  {" Tgl SWi2 switch in ", Toggle_4_0047_input, 2}, // index runs from 0 - 5 for SWi0 - SWi5
    {" Toggle GALX4-0047N ", toggle_4_0047N, 0}, // Toggle_4_0047_input
    {" Debug IFL_COPo     ", Debug_IO_Eval, O_IFL_COPo0_enum},
    {" Debug IFB_COPo     ", Debug_IO_Eval, O_IFB_COPo1_enum},
    {" Debug CUL_COPo     ", Debug_IO_Eval, O_CUL_COPo2_enum},
    {" Debug L15RLo       ", Debug_IO_Eval, O_L15RL_enum},
    {" Show Msg Board B   ", DisplayMsgBrd_B, 0},
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Software Version   ", Display_SW_Version, 0},
    {" Test Module        ", DoNothing, 0},
    {" Faults in B        ", DisplayMsgBrd_B, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" RESET MCU          ", WDT_Test, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
*/    
};

// Toggle_O_CTxx

struct a_menu Diagnostic_Generic_Menu[] = {
    /// = 1
    {" Diagnostic menu   1", Really_DoNothing, 0}, //
    {" Message Boards     ", Start_a_Menu, 7},
/*    
    {" Message Boards     ", Start_a_Menu, 7},
    {" Menu Navigator     ", Start_a_Menu, 8},
    {" Test CAN bus       ", ctCAN_BAUD, 0},
    {" Set Power to OPL   ", Set_or_clear_OPL_PWR, 1},
    {" Clear Power to OPL ", Set_or_clear_OPL_PWR, 0},
        
    {" Set CN19V          ", Set_or_clear_CN19V, 1},
    {" Clear CN19V        ", Set_or_clear_CN19V, 0},
    {" Set CN18V          ", Set_or_clear_CN18V, 1},
    {" Clear CN18V        ", Set_or_clear_CN18V, 0},
    
    {" Set CLOSE          ", Set_or_clear_CLOSE, 1},
    {" Clear CLOSE        ", Set_or_clear_CLOSE, 0},
    {" Set OPEN           ", Set_or_clear_OPEN, 1},
    {" Clear OPEN         ", Set_or_clear_OPEN, 0},
    
    {" Set NUDGE          ", Set_or_clear_NUDGE, 1},
    {" Clear NUDGE        ", Set_or_clear_NUDGE, 0},
    {" Set HEAVY          ", Set_or_clear_HEAVY, 1},
    {" Clear HEAVY        ", Set_or_clear_HEAVY, 0},
    
    {" Set DCL            ", Set_or_clear_DCL, 1},
    {" Clear DCL          ", Set_or_clear_DCL, 0},
    {" Set RO             ", Set_or_clear_RO, 1},
    {" Clear RO           ", Set_or_clear_RO, 0},
    {" Set DOL            ", Set_or_clear_DOL, 1},
    {" Clear DOL          ", Set_or_clear_DOL, 0},
    
    {" Tgl LDO6 LED       ", Toggle_4_0047, 0}, // index runs from 0 - 5 for LDO6 - LDO11
    	// Toggle_4_0047[0] refers to IO7 on 0047 board, and Toggle_4_0047[5] is IO12
    {" Tgl LDO7 LED       ", Toggle_4_0047, 1}, // index runs from 0 - 5 for LDO6 - LDO11
    {" Tgl LDO8 LED       ", Toggle_4_0047, 2}, // index runs from 0 - 5 for LDO6 - LDO11
    {" Tgl LDO9 LED       ", Toggle_4_0047, 3}, // index runs from 0 - 5 for LDO6 - LDO11
    {" Tgl LDO10 LED      ", Toggle_4_0047, 4}, // index runs from 0 - 5 for LDO6 - LDO11
    {" Tgl LDO11 LED      ", Toggle_4_0047, 5}, // index runs from 0 - 5 for LDO6 - LDO11 
    {" Read SW0-5 states  ", Read_State_of_0047_input_SWs, 0},
    {" Show Msg Board B   ", DisplayMsgBrd_B, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0}, 
    {" Read SW0           ", Read_State_of_one_0047_input_SWs, 0},
    {" Read SW1           ", Read_State_of_one_0047_input_SWs, 1},
    {" Read SW2           ", Read_State_of_one_0047_input_SWs, 2},
    {" Read SW3           ", Read_State_of_one_0047_input_SWs, 3},
    {" Read SW4           ", Read_State_of_one_0047_input_SWs, 4},
    {" Read SW5           ", Read_State_of_one_0047_input_SWs, 5},
    {" Clear all out SEBs ", ClearAllSEB_from_a_Menu, 0},
    {" OPL-0106N Door Op 0", Start_a_Menu, 0},
    {" Send Message     28", Start_a_Menu, 2}, 
*/    
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},          
    
/*    
Read_State_of_0047_input_SWs
Read_State_of_one_0047_input_SWs
    {" Read CSS_SEB_OUT   ", Read_the_Output, 0},
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Main Menu        12", Start_a_Menu, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" RESET MCU          ", WDT_Test, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
*/    
};

struct a_menu SndMsg28_Menu[] = {
    /// = 2
    {" Send Message 28   2", Really_DoNothing, 0}, //
    {" Clear GALX4-0047N  ", Set_Clear_all_4_0047, 0},
    {" Msg28 CLEAR OUT    ", Construct_Msg_28, 0},
    {" Msg28 Open Cmnd    ", Construct_Msg_28, DR_DZ_STATUS + DR_OPEN},
    {" Msg28 Close Cmnd   ", Construct_Msg_28, DR_DZ_STATUS + DR_CLOSE},
    {" Msg28 Nudge Close  ", Construct_Msg_28, DR_DZ_STATUS + DR_CLOSE + DR_NUDGE_CLOSE},
    {" Msg28 DZ StaTs Cmnd", Construct_Msg_28, DR_DZ_STATUS}, 
    {" Msg28 Heavy Cmnd   ", Construct_Msg_28, DR_HEAVY + DR_DZ_STATUS + DR_CLOSE + DR_NUDGE_CLOSE},
    {" Msg28 Narrow Cmnd  ", Construct_Msg_28, DR_NARROW},
    {" Dsply msg 28 Cmnd  ", Display_msg28_Cmnd, 0},
    
    {" Dsply Msg 29 rtrn  ", Dsply_Msg_29_Return, 0},
               
    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" Toggle OPL_0106    ", toggle_OPL_0106, 0},
    {" OPL-0106N Door Op 0", Start_a_Menu, 0},
    {" Diagnostic menu   1", Start_a_Menu, 1},    
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Manual_Test_Menu[] = {
    /// = 3 // Generic_Tester
    {" MANUAL TEST MODE  3", Really_DoNothing, 0}, // 
    {" APS Test           ", Run_APS_tst, 0x30}, // keep track of APS counts and show msgs.
    {" DTS / UTS Test     ", Run_DTS_UTS_tst, 0x30},
    {" SPI CAN Test       ", Run_SPI_CAN_tst, 0x30},
    {" DTS Test           ", Run_DTS_tst, 0},
    {" UTS Test           ", Run_UTS_tst, 0},
/*    
    {" Remove jumper J1   ", Insert_Remove_Jumper, 0x100 + 0}, // jumper_enum + OUT
    {" Insert jumper J1   ", Insert_Remove_Jumper, 0x100 + 1}, // jumper_enum + IN
    {" Message Board   A  ", DisplayMsgBrd_A, 0},
    {" Remove jumper J4   ", Insert_Remove_Jumper, 0x200 + 0}, // jumper_enum + OUT
    {" Insert jumper J4   ", Insert_Remove_Jumper, 0x200 + 1}, // jumper_enum + IN
    
    {" Remove jumper J5   ", Insert_Remove_Jumper, 0x300 + 0}, // jumper_enum + OUT
    {" Insert jumper J5   ", Insert_Remove_Jumper, 0x300 + 1}, // jumper_enum + IN        
    
    {" Chk REOPEN LED's on", Generic_Tester, 0xC000 + 0},
*/    
    
        
//    {" Run Power-Up Mode  ", JumpToPowerUp, 0},   
/*       
    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" OPL-0106N Door Op 0", Start_a_Menu, 0},
    {" Diagnostic menu   1", Start_a_Menu, 1},
    {" Send Message 28   2", Start_a_Menu, 2},
*/    
     
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Switches_Menu[] = {
    /// = 4
    {" Switches Menu     4", Really_DoNothing, 0}, //
//    {" AUTO Switch TEST   ", FunctionalTest, 0x100 }, // functional tests 'B'
//    {" Check Manual Close ", Generic_Tester, 0x8000 + 7},
    {" Verify Manual Close", Generic_Tester, 7},
//    {" Check Manual Open  ", Generic_Tester, 0x8000 + 8},
    {" Verify Manual Open ", Generic_Tester, 8}, 
//    {" Check Manual Nudge ", Generic_Tester, 0x8000 + 9},
    {" Verify Manual Nudge", Generic_Tester, 9},
//    {" Check Manual Heavy ", Generic_Tester, 0x8000 + 10},
    {" Verify Manual Heavy", Generic_Tester, 10}, 
//    {" Function switch Tst", FunctionalTest, 0 },      
/*
    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" Toggle OPL_0106    ", toggle_OPL_0106, 0},
    {" OPL-0106N Door Op 0", Start_a_Menu, 0},
    {" Diagnostic menu   1", Start_a_Menu, 1},
    {" Send Message 28   2", Start_a_Menu, 2},
    {" MANUAL TEST MODE  3", Start_a_Menu, 3}, 
    {" Jumpers Menu      5", Start_a_Menu, 5},       
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
*/    
};

struct a_menu Jumpers_Menu[] = {
    /// = 5
    {" Jumpers Menu      5", Really_DoNothing, 0}, //
//    {" Test pre & post msg", Generic_Tester, 12},
//    {" Check Jumper J1  IN", Generic_Tester, 0x8000 + 11},
    {" Verify Jumper J1 IN", Generic_Tester, 11},
//    {" Check Jumper J1 OUT", Generic_Tester, 0x8000 + 15},
    {" Verify Jmpr J1 OUT ", Generic_Tester, 15},    
//    {" Check Jumper J4    ", Generic_Tester, 0x8000 + 13}, // BAUD RATE
    {" Verify Jumper J4   ", Generic_Tester, 13}, 
//    {" Check Jumper J5    ", Generic_Tester, 0x8000 + 14}, // WHICH DOOR
    {" Verify Jumper J5   ", Generic_Tester, 14},
 
//    {" Function jumper Tst", FunctionalTest, 0 },      
/*
    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" Clear GALX4-0047N  ", Set_Clear_all_4_0047, 0},

    {" OPL-0106N Door Op 0", Start_a_Menu, 0},
    {" Diagnostic menu   1", Start_a_Menu, 1},
    {" Send Message 28   2", Start_a_Menu, 2},
    {" MANUAL TEST MODE  3", Start_a_Menu, 3}, 
    {" Switches Menu     4", Start_a_Menu, 4}, 
    {" Wrappers Menu     6", Start_a_Menu, 6},  
*/        
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Wrappers_Menu[] = {
    /// = 6
    {" Wrappers Menu     6", Really_DoNothing, 0}, //
    {" Check Jumper J1    ", Generic_Tester, 0x8000 + 11},
    {" Verify Jumper J1   ", Generic_Tester, 11},
    {" Check Jumper J4    ", Generic_Tester, 0x8000 + 13}, // BAUD RATE
    {" Verify Jumper J4   ", Generic_Tester, 13}, 
    {" Check Jumper J5    ", Generic_Tester, 0x8000 + 14}, // WHICH DOOR
    {" Verify Jumper J5   ", Generic_Tester, 14},
    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},    
    {" Clear GALX4-0047N  ", Set_Clear_all_4_0047, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" CAN COMM TST, FRONT", Dsply_Msg_29_Return, 1}, // Dsply_Msg_29_Return
    {" CAN COMM TST, REAR ", Dsply_Msg_29_Return, 0x4001},
    {" Rear door, quiet   ", Dsply_Msg_29_Return, 0x6001},     

    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" OPL-0106N Door Op 0", Start_a_Menu, 0},
    {" Diagnostic menu   1", Start_a_Menu, 1},
    {" Send Message 28   2", Start_a_Menu, 2},
    {" MANUAL TEST MODE  3", Start_a_Menu, 3}, 
    {" Switches Menu     4", Start_a_Menu, 4},  
    {" Jumpers Menu      5", Start_a_Menu, 5},     
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu MessageBds_Menu[] = {
    /// = 7
    {" Message Boards    7", Really_DoNothing, 0}, //

    {" Message Board   A  ", DisplayMsgBrd_A, 0}, 
    {" Message Board   B  ", DisplayMsgBrd_B, 0},   
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear All Msg Bds  ", Clear_All_Boards, 7},    
    {" Clear GALX4-0047N  ", Set_Clear_all_4_0047, 0},    
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};
// Navigator_Menu
struct a_menu Navigator_Menu[] = {
    /// = 8
    {" Navigator         8", Really_DoNothing, 0}, //
//    {" OPL-0106N Door Op 0", Start_a_Menu, 0},
//    {" Diagnostic menu   1", Start_a_Menu, 1},
    {" Send Message 28   2", Start_a_Menu, 2},
//    {" MANUAL TEST MODE  3", Start_a_Menu, 3}, 
    {" Switches Menu     4", Start_a_Menu, 4},  
    {" Jumpers Menu      5", Start_a_Menu, 5},
    {" Wrappers Menu     6", Start_a_Menu, 6},
    {" Message Boards    7", Start_a_Menu, 7},
    {" AUTO MODE TEST    9", Start_a_Menu, 9},
   
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu AutoTest_Menu[] = {
    /// = 9
    { " AUTO MODE TEST    9", Really_DoNothing,  0}, //
//    { " Test & Stop On Err ", FunctionalTest, 0x01},  //  StopOnFail = TRUE(1 Fail then Stop)     //ADDing "0x100" is for GALX1121 FUNCTIONAL TEST MENU 'B'
    { " Test - Do Not Stop ", FunctionalTest, 0x03},  //  StopOnFail = FALSE(3 Fail dont care, keep going next test)
    { " Test & Stop On Err ", FunctionalTest, 0x01},  //  StopOnFail = TRUE(1 Fail then Stop)     //ADDing "0x100" is for GALX1121 FUNCTIONAL TEST MENU 'B'    
    { " Test @ Failed only ", FunctionalTest, 0x02},  //  Only test functions that have failed, and StopOnFail = FALSE
    { " AUTO no Jmps, SW   ", FunctionalTest, 0x100 }, // functional tests 'B'   
    { " Run Power-Up Mode  ", JumpToPowerUp, 0},
};


/*
struct Menus_in_System  {
    // This info gets pushed onto the menu stack 
    // with a call to "Start_a_Menu(WhichMenu)".  (WBG)
    // Handles sub-menus up to 23 deep.
    void *MenuPtr;
    int16 LengthOfMenu;
} 
*/

// Manual_Test_Menu
struct Menus_in_System The_Menus_in_System[] = 
{
        {Main_Generic_Test_Menu, (sizeof(Main_Generic_Test_Menu) / sizeof(Main_Generic_Test_Menu[0])) - 1},       
        {Diagnostic_Generic_Menu, (sizeof(Diagnostic_Generic_Menu) / sizeof(Diagnostic_Generic_Menu[0])) - 1}, // 1        
        {SndMsg28_Menu, (sizeof(SndMsg28_Menu) / sizeof(SndMsg28_Menu[0])) - 1}, // 2
        {Manual_Test_Menu, (sizeof(Manual_Test_Menu) / sizeof(Manual_Test_Menu[0])) - 1}, // 3
        {Switches_Menu, (sizeof(Switches_Menu) / sizeof(Switches_Menu[0])) - 1}, // 4
        {Jumpers_Menu, (sizeof(Jumpers_Menu) / sizeof(Jumpers_Menu[0])) - 1}, // 5
        {Wrappers_Menu, (sizeof(Wrappers_Menu) / sizeof(Wrappers_Menu[0])) - 1}, // 6
        {MessageBds_Menu, (sizeof(MessageBds_Menu) / sizeof(MessageBds_Menu[0])) - 1}, // 7
        {Navigator_Menu, (sizeof(Navigator_Menu) / sizeof(Navigator_Menu[0])) - 1}, // 8
        {AutoTest_Menu, (sizeof(AutoTest_Menu) / sizeof(AutoTest_Menu[0])) - 1}, // 9                             
};
        

int16 Start_a_Menu(int16 WhichMenu)
{
    if (PushMenuPtrArray(MenuPtr))
    {
        MenuPtr = The_Menus_in_System[WhichMenu].MenuPtr; //
        TheMenuLength = The_Menus_in_System[WhichMenu].LengthOfMenu;
        //    MenuPtrArrayIndex = 0;
        LCD_Pointer = 1;
        LCD_Upd_Dpy = 1; // force update of display
    }
    return FINISHED_WITH_SERVICE;
}

int16 PushMenuPtrArray(void *MenuPtr) // saves the current menu ifo on a stack
{
    if (MenuPtr == NULL)
        return 1; // indicate success even though not.
                  // This is necessary, since the start menu may not be the
                  // main menu, and thus we should not push a NULL ptr to the stack
                  // prior to starting a child menu from a parent menu.
    if (MenuPtrArrayIndex < MAX_MENU_DEPTH)
    {
        The_menu_stack[MenuPtrArrayIndex].MenuPtrOnStack = MenuPtr;
        The_menu_stack[MenuPtrArrayIndex].LCD_PointerOnStack = LCD_Pointer;
        The_menu_stack[MenuPtrArrayIndex].LengthOfMenuOnStack = TheMenuLength;
        MenuPtrArrayIndex++;
        SW_Vers_disp();
        return SUCCESS; // = 1
    }
    else
        return FAILED; // = 0
}

int16 PopMenuPtrArray(void)
{
    if (MenuPtrArrayIndex > 0)
    {
        --MenuPtrArrayIndex;
        LCD_Pointer = The_menu_stack[MenuPtrArrayIndex].LCD_PointerOnStack;
        MenuPtr = The_menu_stack[MenuPtrArrayIndex].MenuPtrOnStack;
        //        sprintf(src,"index/MenP1: %d: %d",MenuPtrArrayIndex, MenuPtr);
        //        Log_a_fault(src,0);
        TheMenuLength = The_menu_stack[MenuPtrArrayIndex].LengthOfMenuOnStack;
        //        sprintf(src,"menLen: %d", TheMenuLength);
        //        Log_a_fault(src,0);
        //        Log_a_fault("pop OK",0);
        //        if(MenuPtr != MainMenuPtr) Log_a_fault("pointers NG",0);
        //        sprintf(src,"ML: %d", TheMenuLength);
        //        Log_a_fault(src,0);
        //        sprintf(src,"lcdP: %d", LCD_Pointer);
        //        Log_a_fault(src,0);
        //        sprintf(src,"MenP2: %d", MenuPtr);
        //        Log_a_fault(src,0);
        LCD_Upd_Dpy = 1; // force update of display
        SW_Vers_disp();
        return SUCCESS;
    }
    else
    {
        return FAILED;
    }
}

int16 Get_Num_of_Menus(void)
{
    return (sizeof(The_Menus_in_System) / sizeof(The_Menus_in_System[0]));
}
