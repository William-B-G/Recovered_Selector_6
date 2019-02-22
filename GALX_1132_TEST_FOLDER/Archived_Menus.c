// Archived_Menus.c


/*
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 }, 
    { " RS-485             ", The_RS_485_test,        0 },  //   The_RS_485_test(x);// Hl_Tx_to_Grp_Rx
    { " RS-485             ", Hl_Tx_to_Grp_Rx,        0 },  //   The_RS_485_test(x);// Hl_Tx_to_Grp_Rx
    { " Faults             ", DisplayMsgBrd_A,        0 },
    { " ver_rev CPLD1      ", Read_FPGA_ver_rev,      0 }, 
    { " Faults             ", DisplayMsgBrd_A,        0 },
    { " ver_rev CPLD2      ", Read_FPGA_ver_rev,      1 },
    { " Faults             ", DisplayMsgBrd_A,        0 },
    { " ver_rev NTS        ", Read_FPGA_ver_rev,      2 },     
    { " RESET MCU NOW      ", WDT_Test,               0 },
    { " Check ISR timing   ", ISR_test,               0 },
    { " Hall Com - one shot", Hal_com_Tx_test,        0 },
    { " Show the Grp Rx Buf", GrpRxPacket,            0 },       // GrpRxPacket            
    { " Show the Hal Rx Buf", ShowMe_sx_recbuf,       0 },
    { " Show tempBuff      ", ShowMe_tempBuff,        0 },
    { " Clear Faults       ", ClearFaults,            0 },
    { " Display RS-485 BAUD", Display_RS485_Baud,     0 },
    { " Clear Faults       ", ClearFaults,            0 },
    { " Query menu variabls", QueryMenuVariables,     0 },
    { " Fill the 2 Rx Buffs", Call_temp_SW,           0 }, 
    { " Toggle RS485 Ctrl  ", Toggle_RS_485_Ctrl,     0 },   
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
    { " RESET MCU NOW      ", WDT_Test,               0 },    
    { " Machine Room CAN   ", TEST_MRCAN,             0 },
    { " Selector CAN       ", TEST_SLCAN,             0 },    
    { " RS-485             ", The_RS_485_test,        0 },
    { " Toggle RS485 Ctrl  ", Toggle_RS_485_Ctrl,     0 },    
    { " Show the Hal Rx Buf", ShowMeRxBuf,            0 },
    { " MESSAGE BOARD A    ", DisplayMsgBrd_A,        0 },
    { " MESSAGE BOARD B    ", DisplayMsgBrd_B,        0 },
    { " SOFTWARE VERSION   ", Display_SW_Version,     0 },
    { " Car Top CAN        ", TEST_CTCAN,             0 },
    { " Group CAN          ", TEST_GRCAN,             0 },
    { " Clear Faults       ", ClearFaults,            0 },
    { " Query menu variabls", QueryMenuVariables,     0 },
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
    { " Hall Com - one shot", Hal_com_Tx_test,        0 },
    { " Hall Com - ContinUs", Hal_com_Tx_test_Continuous, 0 },
    { " MRAM               ", Test_MRAM,              0 },
    { " RS-232             ", The_RS_232_test,        0 },
    { " WATCH DOG          ", WDT_Test,              30 },
    { " SD CARD            ", TEST_SD,                0 },
    { " WIFI               ", DoNothing,              0 },
    { " REAL TIME CLOCK    ", TEST_RTC,               0 },
    { " PUSH BUTTONS       ", PushButtons_Test,       0 },
    { " 4-LINE DISPLAY     ", Display_Test,           0 },
    { " ADJUST LCD DISPLAY ", DoNothing,              0 },
    { " GAL1132 IO BOARD   ", DoNothing,              0 },           
    { " Enable CAN ctrl    ", CAN_Ctrl_EN_bit,        1 },//Enable_CAN_Ctrl
    { " Disable CAN ctrl   ", CAN_Ctrl_EN_bit,        0 },//Enable_CAN_Ctrl
    { " Query all com ctrl ", DoNothing,              0 },
    { " Query all com ctrl ", Query_Ctrl_bits,        0 },
    { " Item 05 on C       ", DoNothing,              0 },
    { " ver_rev CPLD1      ", Read_FPGA_ver_rev,      0 },     
    { " ver_rev CPLD2      ", Read_FPGA_ver_rev,      1 },
    { " Faults             ", DisplayMsgBrd_A,        0 },
    { " ver_rev NTS        ", Read_FPGA_ver_rev,      2 },    
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
    { " Software Utilities ", Display_SW_Version,     0 },    
    { " Display RS-xxx BAUD", Display_RS485_Baud,     0 },               
    { " Faults             ", DisplayMsgBrd_A,        0 },
    { " ver_rev CPLD2      ", Read_FPGA_ver_rev,      1 },   
    { " Faults             ", DisplayMsgBrd_A,        0 }, 
    { " WIFI enable        ", WiFi_Test,              0 },
    { " WIFI disable       ", WiFi_Test,             25 },   
    { " RESET MCU NOW      ", WDT_Test,               0 },    
    { " Toggle ISR timing  ", ISR_test,               0 },    
    { " RS-485             ", The_RS_485_test,        0 },
    { " Hall Com - one shot", Hal_com_Tx_test,        0 },
    { " Show the Grp Rx Buf", GrpRxPacket,            0 },     
    { " Once frm Grp Com   ", The_RS_485_test,        3 }, 
    { " Send one character ", Special_test_for_Johnny,0 },        
    { " MESSAGE BOARD B    ", DisplayMsgBrd_B,        0 }, 
    { " Re-init GrCom 1    ", ReinitGrCom1,           0 },       
    { " Test 1132 MCU Board", DoNothing,              0 },
    { " Test 1121 IO Board ", DoNothing,              0 },
    { " Selector CAN       ", TEST_SLCAN,             0 },
    { " FPGA CPLD1         ", Read_FPGA_ver_rev,      0 },
    { " FPGA CPLD1         ", Read_FPGA_ver_rev,      1 },
    { " NTS                ", Read_FPGA_ver_rev,      2 }, 
    { " MESSAGE BOARD B    ", DisplayMsgBrd_B,        0 },   
    { " Development        ", Start_MyMenuList,       0 },
    { " Select Baud for COM", Start_SubMenu_B,        0 },
    { " Select Baud for 485", Start_SubMenu_B,        0 },
    { " Sub Menu B         ", Start_SubMenu_B,         0},  
    { " Sub Menu C         ", Start_SubMenu_C,         0},
    { " Utilities          ", Start_SubMenu_C,        0 },          
    { " Diagnostics        ", Start_Tstr_Diagnostics, 0 },
    { " DIAGNOSTICS        ", Start_Tstr_Diagnostics, 0 },
    { " Individual Tests   ", Start_Individual_Tests, 0 },
    

struct a_menu Main_MenuList[] = { /// = 0
    { "       GALaxy       ", DoNothing,              0 },  // WhichMenu = 0
    { " Test & Stop On Err ", FunctionalTest,       0x01},  //  StopOnFail = TRUE(1 Fail then Stop) 	//ADDing "0x100" is for GALX1121 FUNCTIONAL TEST MENU 'B'
    { " Test - Do Not Stop ", FunctionalTest,       0x03},  //  StopOnFail = FALSE(3 Fail dont care, keep going next test)
    { " Test @ Failed Funct", FunctionalTest,       0x02},  //  Only test functions that have failed, and StopOnFail = FALSE
    { " Individual Tests   ", Start_Individual_Tests, 0 },
    { " Faults             ", DisplayMsgBrd_A,        0 },    
    { " Clear Faults       ", ClearFaults,            0 }, 
    { " SOFTWARE VERSION   ", Display_SW_Version,     0 },
    { " Diagnostics        ", Start_a_Menu,           5 },  // menu 5         .
    { " Utilities          ", Start_a_Menu,           3 },	// menu 3
//    { " Main I/O BD TEST   ", Start_a_Menu,          10 },   	
	{ " MESSAGE BOARD A    ", DisplayMsgBrd_A,        0 },
    { " MESSAGE BOARD B    ", DisplayMsgBrd_B,        0 },
    { " MESSAGE BOARD C    ", DisplayMsgBrd_C,        0 },  
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },    
};

struct a_menu IndividualTests_Menu_List[] = { /// WhichMenu  = 1
    { " Individual Tests   ", DoNothing,              0 },
    { " Push Buttons       ", PushButtons_Test,       0 },
    { " 4-Line Display     ", Display_Test,           0 },
    { " RS-232             ", The_RS_232_test,        0 },  
    { " WIFI TEST          ", WiFi_Test,              0 },
//-    { " WIFI Exit Comand MD", WiFi_Test,             25 },
    { " Group CAN          ", TEST_GRCAN,             16},
    { " Selector CAN       ", TEST_SLCAN,             16},
    { " Car Top CAN        ", TEST_CTCAN,             16},
    { " Machine Room CAN R ", TEST_MRCAN,             16},        
    { " RS-485             ", The_RS_485_test,        0 },
    { " SD Card            ", TEST_SD,                0 },          
    { " Real Time Clock    ", TEST_RTC,               0 },
    { " MRAM Chip 1        ", Test_MRAM,              1 },
    { " MRAM Chip 2        ", Test_MRAM,              2 },    
    { " FPGA1 SPI          ", Read_FPGA_ver_rev,      0 },
    { " FPGA2 SPI          ", Read_FPGA_ver_rev,      1 },
    { " NTS SPI            ", Read_FPGA_ver_rev,      2 },    
    { " Watch Dog Timer tst", WDT_Test,               0 }, 
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },   
//- { " SAMPLE IO TEST     ", SAMPLE_IO_TEST,         0 },   
};


struct a_menu SubMenu_B_List[] = { /// WhichMenu  = 2
    { "      Sub Menu B    ", DoNothing,              0 },     
    { " Display RS-485 BAUD", Display_RS485_Baud,     0 },
    { " RSxxx Baud = 2.4k  ", Set_RS485_Baud,      2832 },
    { " RSxxx Baud = 4.8k  ", Set_RS485_Baud,      1416 },
    { " RSxxx Baud = 9.6k  ", Set_RS485_Baud,       708 },
    { " RSxxx Baud = 19.2k ", Set_RS485_Baud,       354 },
    { " RSxxx Baud = 38.4k ", Set_RS485_Baud,       177 },
    { " RSxxx Baud = 57.6k ", Set_RS485_Baud,       118 },
    { " RSxxx Baud = 115.2k", Set_RS485_Baud,        59 },
    { " Faults             ", DisplayMsgBrd_A,        0 }, 
    { " Clear Faults       ", ClearFaults,            0 },
    { " Query menu variabls", QueryMenuVariables,     0 },  
    { " Utilities          ", Start_a_Menu,           3 },  // menu 3  
};

struct a_menu SubMenu_C_List[] = { ///  WhichMenu = 3
    { "      Utilities     ", DoNothing,              0 },  //same as SubMenu_C  
    { " View RTC           ", ViewRTC      ,          0 },    
    { " MESSAGE BOARD A    ", DisplayMsgBrd_A,        0 },
    { " MESSAGE BOARD B    ", DisplayMsgBrd_B,        0 },
//-    { " Disable RS485 com  ", EnableDisableRS485_com_Ctrl, 0 },
//-    { " Enable  RS485 com  ", EnableDisableRS485_com_Ctrl, 1 },
//-    { " Toggle RS485 Ctrl  ", Toggle_RS_485_Ctrl,     0 },
//-    { " Enable CAN ctrl    ", CAN_Ctrl_EN_bit,        1 },//Enable_CAN_Ctrl
//-    { " Disable CAN ctrl   ", CAN_Ctrl_EN_bit,        0 },//Disable_CAN_Ctrl
//-    { " Query all com ctrl ", Query_Ctrl_bits,        0 },
//-    { " Enable all com ctrl", All_Ctrl_EN_bit,        1 },
//-    { " Disable all com ctl", All_Ctrl_EN_bit,        0 },
//-    { " Item 05 on C       ", DoNothing,              0 },
//-    { " Faults             ", DisplayMsgBrd_A,        0 },
//-    { " Clear Faults       ", ClearFaults,            0 },
    { " Query menu variabls", QueryMenuVariables,     0 },
    { " Development        ", Start_a_Menu,           7 }, // menu 7
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
};

struct a_menu groupCom_Menu_List[] = { ///  WhichMenu = 4	
    { " Group Com Study    ", DoNothing,              0 },
    { " Set/Review Baud    ", Start_a_Menu,           2 },	// menu 2
    { " HalCom '[' one shot", Hal_com_Tx_test,       25 },
    { " Show the Grp Rx Buf", GrpRxPacket,            0 },
    { " HalCom 'A' one shot", Hal_com_Tx_test,       22 },
    { " HalCom 'B' one shot", Hal_com_Tx_test,       23 },
    { " Sliding 'A' one sht", Hal_com_Tx_test,       22 },
    { " Clear Msg Board    ", ClearFaults,            0 }, 
    { " MESSAGE BOARD A    ", DisplayMsgBrd_A,        0 },   
    { " Main Menu          ", Start_a_Menu,           0 },	// menu 0
    { " Development        ", Start_a_Menu,           7 },	// menu 7 
    { " WATCH DOG          ", WDT_Test,               0 },         
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
};

struct a_menu Diagnostic_Menu_List[] = {  ///  WhichMenu = 5
    { "      Diagnostics   ", DoNothing,              0 },
//-    { " Watch Dog Timer tst", WDT_Test,               0 },
    { " Hall Com - one shot", Hal_com_Tx_test,        0 },
    { " Show the Grp Rx Buf", GrpRxPacket,            0 },    
//    { " RS-485 GrRx &HlTx  ", GrpRxPacket,            0 },
//-    { " MESSAGE BOARD A    ", DisplayMsgBrd_A,        0 },
//-    { " MESSAGE BOARD B    ", DisplayMsgBrd_B,        0 },
    { " Show the Hal Rx Buf", ShowMe_sx_recbuf,       0 },
    { " Show tempBuff      ", ShowMe_tempBuff,        0 },
//-    { " Faults             ", DisplayMsgBrd_A,        0 },
//-    { " Group CAN          ", Group_CAN_Diagnostics,  0 },
//-    { " Car Top CAN        ", CT_CAN_Diagnostics,     0 },
//-    { " Machine Room CAN   ", MR_CAN_Diagnostics,     0 },
    { " Main Menu          ", Start_a_Menu,           0 },	// menu 0
    { " FPGA Diagnostics   ", Start_a_Menu,           6 },	// menu 6
//-    { " Toggle ISR timing  ", ISR_test,               0 },
    { " Development        ", Start_a_Menu,           7 },	// menu 7
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
};

// Start_FPGA_Diag_Menu_List
struct a_menu FPGA_Diag_Menu_List[] = {  ///  WhichMenu = 6
    { " FPGA Diagnostics   ", DoNothing,              0 },
    { " FPGA1 SPI unpack   ", Read_FPGA_ver_rev,      0 },
    { " View FPGA1 unpk inf", DisplayMsgBrd_A,        0 },
    { " FPGA2 SPI unpack   ", Read_FPGA_ver_rev,      1 }, 
    { " View FPGA2 unpk inf", DisplayMsgBrd_A,        0 },
    { " Set individual out ", Start_a_Menu,           9 },	// menu 9
//-    { " All I/O on         ", Set_All_outputs,        1 },
//-    { " All I/O off        ", Set_All_outputs,        0 },   
//-    { " Enable_iospi_Ctrl  ", Set_iospi_Ctrl_flag,    1 },
//-    { " Disable_iospi_Ctrl ", Set_iospi_Ctrl_flag,    0 },
//-    { " Change FPGA Addr's ", Start_a_Menu,           8 }, 	// menu 8
//-    { " Clear Msg Board    ", ClearFaults,            0 },   
    { " Main Menu          ", Start_a_Menu,           0 },	// menu 0     
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
};

// sx_recbuf[SE1COM][sx_rbf[SE1COM]]
// ShowMeRxBuf
struct a_menu MyMenuList[] = {  ///  WhichMenu = 7   // abcptr = MyMenuList;
    { "     Development    ", DoNothing,              0 },
    { " display consB file ", Display_consB_file,     0 },  // Display_consB_file  
    { " MESSAGE BOARD A    ", DisplayMsgBrd_A,        0 },       
//-    { " Machine Room CAN   ", TEST_MRCAN,             0 },
//-    { " Selector CAN       ", TEST_SLCAN,             0 },    
//-    { " RS-485             ", The_RS_485_test,        0 },        
    { " Show the Hal Rx Buf", ShowMeRxBuf,            0 },    
    { " MESSAGE BOARD B    ", DisplayMsgBrd_B,        0 },      
//-    { " Car Top CAN        ", TEST_CTCAN,             0 },
//-    { " Group CAN          ", TEST_GRCAN,             0 },
    { " Clear Faults       ", ClearFaults,            0 },
    { " Query menu variabls", QueryMenuVariables,     0 },
//-    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
    { " Hall Com - one shot", Hal_com_Tx_test,        0 },
    { " Show the Grp Rx Buf", GrpRxPacket,            0 },
    { " Hall Com - ContinUs", Hal_com_Tx_test_Continuous, 0 },
//-    { " MRAM               ", Test_MRAM,              1 },
//-    { " RS-232             ", The_RS_232_test,        0 },
//-    { " WIFI               ", DoNothing,              0 },
//-    { " REAL TIME CLOCK    ", TEST_RTC,               0 },
//-    { " PUSH BUTTONS       ", PushButtons_Test,       0 },
//-    { " 4-LINE DISPLAY     ", Display_Test,           0 },
//-    { " ADJUST LCD DISPLAY ", DoNothing,              0 },
//-    { " GAL1132 IO BOARD   ", DoNothing,              0 },
    { " GENERIC TEST       ", Generic_Test,           0 },
//-    { " MSG BD A SWITCHES  ", DoNothing,              0 },
//-    { " MSG BD B SWITCHES  ", DoNothing,              0 },
    { " 1106 I/O BD        ", Start_a_Menu,          10 },	// menu 10
    { " FORCE TESTS TO FAIL", SetClearForceToFail,    1 },
    { " Clear the FORCE flg", SetClearForceToFail,    0 },
//-    { " Sub Menu B         ", Start_a_Menu,           2 },	// menu 2
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },
};

struct a_menu FPGA_SetAddrs[] = {  ///  WhichMenu = 8
    { " FPGA Set Addresses ", DoNothing,              0 }, 
    { " CPLD1 Default      ", Set_CPLD1_Addr,         0 },
    { " CPLD1 0x9356       ", Set_CPLD1_Addr,         1 },
    { " CPLD1 0x9357       ", Set_CPLD1_Addr,         2 },
    { " CPLD1 0x9358       ", Set_CPLD1_Addr,         3 },
    { " CPLD1 0x9359       ", Set_CPLD1_Addr,         4 },
    { " CPLD1 0x935A       ", Set_CPLD1_Addr,         5 },
    { " Show FPGA Addr's   ", DisplayMsgBrd_A,        0 },
    { " CPLD2 Default      ", Set_CPLD2_Addr,         0 },
    { " CPLD2 0x612B       ", Set_CPLD2_Addr,         1 },
    { " CPLD2 0x612C       ", Set_CPLD2_Addr,         2 },
    { " CPLD2 0x612D       ", Set_CPLD2_Addr,         3 },
    { " CPLD2 0x612E       ", Set_CPLD2_Addr,         4 },
    { " CPLD2 0x612F       ", Set_CPLD2_Addr,         5 },
    { " Main Menu          ", Start_a_Menu,           0 },	// menu 0
    { " RESET MCU          ", WDT_Test,               0 },    
    { " Run Power-Up Mode  ", JumpToPowerUp,          0 },      
};

struct a_menu Set_main_IO[] = {  ///  WhichMenu = 9
    { " Set main I/O       ", DoNothing,                0 },
    { " SUF on             ", Set_specific_output, 0xf000 },
    { " SUF off            ", Set_specific_output,      0 },
    { " SU on              ", Set_specific_output, 0x0f001}, 
    { " SU off             ", Set_specific_output, 0x0001 },
    { " SDF on             ", Set_specific_output, 0xf002 },
    { " SDF off            ", Set_specific_output,      2 },
    { " SD on              ", Set_specific_output, 0xf003 }, 
    { " SD off             ", Set_specific_output,      3 },   
    { " STE on             ", Set_specific_output, 0xf004 },
    { " STE off            ", Set_specific_output,      4 },
    { " MC1 on             ", Set_specific_output, 0xf005 }, 
    { " MC1 off            ", Set_specific_output,      5 },
    { " MC on              ", Set_specific_output, 0xf006 },
    { " MC off             ", Set_specific_output,      6 },
    { " RUN on             ", Set_specific_output, 0xf007 },
    { " RUN off            ", Set_specific_output,      7 },    
// ZYM 12-5-2017
	{ " UT on              ", Set_specific_output, 0xf008 },
    { " UT off             ", Set_specific_output,      8 },
    { " UN on              ", Set_specific_output, 0xf009 },
    { " UN off             ", Set_specific_output,      9 },
    { " DT on              ", Set_specific_output, 0xf00A },
    { " DT off             ", Set_specific_output,      10},
    { " DN on              ", Set_specific_output, 0xf00B },
    { " DN off             ", Set_specific_output,      11},
        
    { " Main Menu          ", Start_a_Menu,             0 },	// menu 0       
    { " RESET MCU          ", WDT_Test,                 0 },    
    { " Run Power-Up Mode  ", JumpToPowerUp,            0 },
};
// CheckPB
// Set_out1_off
struct a_menu Set_1106AN[] = {  ///  WhichMenu = 10
    { "     1106 I/O BD    ", DoNothing,                0 },
//-    { " Control 1106AD bd 3", Output_on_1106,           3 },
//-    { " Control 1106AD bd 4", Output_on_1106,           4 },
//-    { " All outputs OFF   3", All_On_Off,          0x0003 },
//-    { " All outputs ON bd 3", All_On_Off,          0x1003 },  
//-    { " All outputs OFF   4", All_On_Off,          0x0004 },
//-    { " All outputs ON bd 4", All_On_Off,          0x1004 },
//-    { " Run Power-Up Mode  ", JumpToPowerUp,            0 },      
//-    { " Read 1106 I/O BD 3 ", Read_1106,                3 },
//-    { " Read 1106 I/O BD 4 ", Read_1106,                4 },
    { " MESSAGE BOARD A    ", DisplayMsgBrd_A,          0 },
    { " Clear Faults       ", ClearFaults,              0 },
//-   { " Output out1 on     ", CheckPB,                  0 },
//-   { " Output out1 OFF    ", Set_out1_off,             0 },
//-    { " Run Power-Up Mode  ", JumpToPowerUp,            0 },
    { " All I/O on         ", Set_All_outputs,          1 },
    { " All I/O off        ", Set_All_outputs,          0 },
    { " Set individual out ", Start_a_Menu,             9 },	// menu 9
//-    { " Enable_iospi_Ctrl  ", Set_iospi_Ctrl_flag,      1 },
//-    { " Disable_iospi_Ctrl ", Set_iospi_Ctrl_flag,      0 },      
    { " Main Menu          ", Start_a_Menu,             0 }, 	// menu 0      
    { " Run Power-Up Mode  ", JumpToPowerUp,            0 },
};
    

/*


struct a_menu Test_B_Module_Menu[] = {
    /// = 3
    {" 1134 Module B     3", Really_DoNothing, 0}, //
    {" Perform mock IO tst", Perform_all_IO_Tests, 0x8000}, // this is for SW debug, not a real test
    {" Perform & dsply tst", Perform_all_IO_Tests, 0xC000},
    {" Show Msg Board B   ", DisplayMsgBrd_B, 0}, // ClearAllSEB
    {" Clear all out SEBs ", ClearAllSEB_from_a_Menu, 0},
    {" Perform IO test    ", Perform_all_IO_Tests,      0}, // this is a real test
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Set All Dbgxx      ", Set_or_Clear_All_CTxx, 1},
    {" Clear All Dbgxx    ", Set_or_Clear_All_CTxx, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},
    {" Disply rdoutp(*ptr)", Read_and_Display_rdoutp, 0},
    {" Disply rdinp (*ptr)", Read_and_Display_Rd_Inputs, 0}, 

    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};
*/

/*
struct a_menu Test_C_Module_Menu[] = {
    /// = 4
    {" 1134 Module C     4", Really_DoNothing, 0}, //
    {" Perform mock IO tst", Perform_all_IO_Tests, 0x8000}, // this is for SW debug, not a real test
    {" Perform & dsply tst", Perform_all_IO_Tests, 0xC000},
    {" Show Msg Board B   ", DisplayMsgBrd_B, 0}, // ClearAllSEB
    {" Clear all out SEBs ", ClearAllSEB_from_a_Menu, 0},
    {" Set C24V ON, SEB 4 ", Set_or_clear_24V_on_SEB4, 1},
    {" Clear C24V , SEB 4 ", Set_or_clear_24V_on_SEB4, 0},
    
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},

    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Test_CAN_Msgs_Menu[] = {
    /// = 5
    {" 1134 Test CAN msg 5", Really_DoNothing, 0}, //
    {" Set L15_T ON, SEB 3", L15_T_on_off, 1},
    {"   Clr L15_T, SEB  3", L15_T_on_off, 0},     
    {" Show Msg Board B   ", DisplayMsgBrd_B, 0}, // ClearAllSEB
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    
    {" Clear all out SEBs ", ClearAllSEB_from_a_Menu, 0},
// CT_CAN_Enable_bit
    {" Turn on 120 vac    ", C120_VAC_on_off, 1},
    {"   Turn OFF 120 vac ", C120_VAC_on_off, 0}, 
    
    {" Set C24V ON, SEB 4 ", Set_or_clear_24V_on_SEB4, 1},
    {"   Clear C24V, SEB 4", Set_or_clear_24V_on_SEB4, 0}, 
    
    {" Set L15RL ON, SEB 3", GFI_Relay_on_off, 1},
    {"   Clr L15RL, SEB  3", GFI_Relay_on_off, 0},   
    
    {" Set L15_T ON, SEB 3", L15_T_on_off, 1},
    {"   Clr L15_T, SEB  3", L15_T_on_off, 0},   
         
    {" Set oCSS ON, SEB 1 ", Set_or_clear_oCSS_on_SEB1, 1},
    {"   Clear oCSS, SEB 1", Set_or_clear_oCSS_on_SEB1, 0},
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
// Read_and_Display_All_Inputs(0);    
    {" Read CSS from 1134 ", Read_1134_CAN_input, 0},     
    {" Read CTS from 1134 ", Read_1134_CAN_input, 1},
    {" Read DET from 1134 ", Read_1134_CAN_input, 2},
        
    {" Set IFL, insp FL   ", Set_CAN_msgs, 0},
    {"   Clr IFL, insp FL ", Clear_CAN_msgs, 0},
    
    {" Set IFB, insp F buz", Set_CAN_msgs, 1},
    {"   Clear insp F buz ", Clear_CAN_msgs, 1},    
    
    {" Set CUL, insp UP   ", Set_CAN_msgs, 2},
    {"   Clr CUL, insp UP ", Clear_CAN_msgs, 2},
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
    
    {" Set CDL, insp DWN  ", Set_CAN_msgs, 3},
    {"   Clr CDL, insp DWN", Clear_CAN_msgs, 3},    
    
    {" Set FAN,           ", Set_CAN_msgs, 4},
    {"   Clear FAN        ", Clear_CAN_msgs, 4},
    
    {" Set LIG, Cabin Ligt", Set_CAN_msgs, 5},
    {"   Clear LIG, Light ", Clear_CAN_msgs, 5},   
    
    {" Set Selector COMM  ", Set_CAN_msgs, 6},
    {"   Clr Selector COMM", Clear_CAN_msgs, 6},    
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
        
    {" Set NTS COMM       ", Set_CAN_msgs, 7},
    {"   Clear NTS COMM   ", Clear_CAN_msgs, 7},    
        
    {" Set Fire Srv Stp SW", Set_CAN_msgs, 8},
    {"   Clear Fire Stp SW", Clear_CAN_msgs, 8},    
    
    {" Set FSTP           ", Set_CAN_msgs, 9},
    {"   Clear FSTP       ", Clear_CAN_msgs, 9},        
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
                 
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},

    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Main_Menu[] = {
    /// = 6
    {" Main Menu         6", Really_DoNothing,   0 }, //
    {" Function Test      ", FunctionalTest,     0 }, 
    {" Diagnostic         ", Start_a_Menu,       8 },
    {" Debug              ", Start_a_Menu,       9 }, // ClearAllSEB
    {" SW Version         ", Display_SW_Version, 0 },
    {" Test Module        ", Start_a_Menu,      10 },
    {" Fault Menu         ", Start_a_Menu,      11 },
    {" - - - - - - - - -  ", Really_DoNothing,   0 },
    
    {" Run Power-Up Mode  ", JumpToPowerUp,      0 },
    {" GALX-1134 CTB     0", Start_a_Menu,       0 },    
    {" Message Board A    ", DisplayMsgBrd_A,    0 },
    {" Message Board   B  ", DisplayMsgBrd_B,    0 },
    {" Message Board   C  ", DisplayMsgBrd_C,    0 },
    {" Clear Msg Board A  ", Clear_All_Boards,   1 },
    {" Clear Msg Board B  ", Clear_All_Boards,   2 },
    {" Clear Msg Board C  ", Clear_All_Boards,   4 },
    {" Clear All Faults   ", Clear_All_Boards,   7 },    
    {" RESET MCU          ", WDT_Test,           0 },
    {" Navigator Menu   14", Start_a_Menu, 14},
    {" ON / OFF          5", Start_a_Menu, 5},
    {" GALX-1134 CTB     0", Start_a_Menu,       0 },
    {" Run Power-Up Mode  ", JumpToPowerUp,      0 },
};

struct a_menu Function_Test_Menu[] = {
    /// = 7
    {" Function Test     7", Really_DoNothing, 0}, //
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Diagnostic_Test_Menu[] = {
    /// = 8
    {" Diagnostic Test   8", Really_DoNothing, 0}, //
    {" CSS_SEB_OUT       0", Diagnostic_Control, 0},
    {" C120_SEB_OUT      1", Diagnostic_Control, 1},
    {" L15_SEB_OUT       2", Diagnostic_Control, 2},
    {" FSS_SEB_OUT       3", Diagnostic_Control, 3},
    {" CST_SEB_OUT       4", Diagnostic_Control, 4},
    {" ICC_SEB_OUT       5", Diagnostic_Control, 5},
    {" ICA_SEB_OUT       6", Diagnostic_Control, 6},
    {" ICI_SEB_OUT       7", Diagnostic_Control, 7},
    {" ACC_SEB_OUT       8", Diagnostic_Control, 8},
    {" BELL_SEB_OUT      9", Diagnostic_Control, 9},
    {" C24_SEB_OUT      10", Diagnostic_Control,10},
    {" IFL_TOC_OUT      11", Diagnostic_Control,11},
    {" IFB_TOC_OUT      12", Diagnostic_Control,12},
    {" CUL_TOC_OUT      13", Diagnostic_Control,13},
    {" CDL_TOC_OUT      14", Diagnostic_Control,14},
    {" FANR_TOC_OUT     15", Diagnostic_Control,15},
    {" LIGR_TOC_OUT     16", Diagnostic_Control,16},
    {" CTS_SEB_IN     xxxx", Really_DoNothing, 0},
    {" INS_SEB_IN     xxxx", Really_DoNothing, 0},
    {" IEN_SEB_IN     xxxx", Really_DoNothing, 0},
    {" IU_SEB_IN      xxxx", Really_DoNothing, 0},
    {" ID_SEB_IN      xxxx", Really_DoNothing, 0},    
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Debug_Menu[] = {
    /// = 9
    {" Debug             9", Really_DoNothing, 0}, //    
    {" Clear all out SEBs ", ClearAllSEB_from_a_Menu, 0},
    {" Turn on 120 vac    ", C120_VAC_on_off, 1},
    {"   Turn OFF 120 vac ", C120_VAC_on_off, 0},     
    {" Set C24V ON, SEB 4 ", Set_or_clear_24V_on_SEB4, 1},
    {"   Clear C24V SEB 4 ", Set_or_clear_24V_on_SEB4, 0},
    {" Set oCSS ON, SEB 1 ", Set_or_clear_oCSS_on_SEB1, 1},
    {"   Clear oCSS, SEB 1", Set_or_clear_oCSS_on_SEB1, 0},
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
               
    {" Set IFL, insp FL   ", Set_CAN_msgs, 0},
    {"   Clear IFL,insp FL", Clear_CAN_msgs, 0},    
    {" Set IFB, insp F buz", Set_CAN_msgs, 1},
    {"   Clear insp F buz ", Clear_CAN_msgs, 1},        
    {" Set CUL, insp UP   ", Set_CAN_msgs, 2},
    {"   Clear CUL,insp UP", Clear_CAN_msgs, 2},    
    {" Set CDL, insp DWN  ", Set_CAN_msgs, 3},
    {"   Clr CDL,insp DWN ", Clear_CAN_msgs, 3}, 
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
                
    {" Set FAN,           ", Set_CAN_msgs, 4},
    {"   Clear FAN        ", Clear_CAN_msgs, 4},    
    {" Set LIG, Cabin Ligt", Set_CAN_msgs, 5},
    {"   Clear LIG, Light ", Clear_CAN_msgs, 5},       
    {" Set Selector COMM  ", Set_CAN_msgs, 6},
    {"   Clear Select COMM", Clear_CAN_msgs, 6}, 
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
                
    {" Set NTS COMM       ", Set_CAN_msgs, 7},
    {"   Clear NTS COMM   ", Clear_CAN_msgs, 7},            
    {" Set Fire Srv Stp SW", Set_CAN_msgs, 8},
    {"   Clear Fire Stp SW", Clear_CAN_msgs, 8},        
    {" Set FSTP           ", Set_CAN_msgs, 9},
    {"   Clear FSTP       ", Clear_CAN_msgs, 9}, 
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
         
    {" Read CSS from 1134 ", Read_1134_CAN_input, 0},     
    {" Read CTS from 1134 ", Read_1134_CAN_input, 1},
    {" Read DET from 1134 ", Read_1134_CAN_input, 2},               
    
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
         
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Test_Module_10_Menu[] = {
    /// = 10
    {" Test Module      10", Really_DoNothing,         0 }, //
    {" Check 24 V         ", Check_24V,                0 },
    {" Check Car Light    ", Check_Car_Light,          0 },
    {" Check loud Buzzer  ", Check_Car_Buzzer_or_Bell, 0 },
    {" Check Bell         ", Check_Car_Buzzer_or_Bell, 1 },
    {" Check Fire Light   ", Check_Car_Buzzer_or_Bell, 2 },
    {" CHECK LOUD BUZZER!!", Generic_Tester, 7 },
    {" CHECK BELL !!      ", Generic_Tester, 8 },
    {" CHECK FIRE LIGHT !!", Generic_Tester, 9 },
    {" Check Run/Stop SW  ", Generic_Tester,       0 },
    {" Check Inspection SW", Generic_Tester,       1 },
    {" Check Enable SW    ", Generic_Tester,       2 },
    {" Check Enbl + UP SW ", Generic_Tester,       3 },
    {" Check Enbl + DWN SW", Generic_Tester,       4 },  
    {" Check GFI Reset ON ", Generic_Tester,       5 }, // should not trip
    {" Check GFI Reset OFF", Generic_Tester,       6 }, // will trip
    {" Perform IO test    ", Perform_all_IO_Tests,     0 },
    
    {" Message Board A    ", DisplayMsgBrd_A,          0 },
    {" Message Board   B  ", DisplayMsgBrd_B,          0 },
    {" Message Board   C  ", DisplayMsgBrd_C,          0 },
    {" Clear Msg Board A  ", Clear_All_Boards,         1 },
    {" Clear Msg Board B  ", Clear_All_Boards,         2 },
    {" Clear Msg Board C  ", Clear_All_Boards,         4 },
    {" Clear All Faults   ", Clear_All_Boards,         7 },    
    {" RESET MCU          ", WDT_Test,                 0 },
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 },
};


struct a_menu Fault_Menu[] = {
    /// = 11
    {" Fault Menu       11", Really_DoNothing, 0}, //
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

// {" Perform mock IO tst", Perform_all_IO_Tests, 0x8000},
struct a_menu Single_IO_Menu[] = {
    /// = 12
    {" Single IO test   12", Really_DoNothing, 0}, //
    {" O_IFL_COPo0_enum 0 ", Perform_all_IO_Tests, 0xA000}, // 0x400,600
    {" O_IFB_COPo1_enum 1 ", Perform_all_IO_Tests, 0xA001}, // 0x400,600
    
    {" O_CUL_COPo2_enum 2 ", Perform_all_IO_Tests, 0xA002}, // 0x400,600
    {" O_CDL_COPo3_enum 3 ", Perform_all_IO_Tests, 0xA003}, // 0x400,600
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    
    {" O_FAN_COPo4_enum 4 ", Perform_all_IO_Tests, 0xE004}, // 0x400,400
    {" O_LIG_COPo5_enum 5 ", Perform_all_IO_Tests, 0xE005}, // 0x400,200
    
    {" O_CSS_enum 6       ", Perform_all_IO_Tests, 0xE006}, // 0x400,600
    {" O_FSS_enum 10      ", Perform_all_IO_Tests, 0xE007}, // 0x400,600
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    
    {" O_CST_enum 11      ", Perform_all_IO_Tests, 0xE008}, // 0x408,600
    {" O_ICC_enum 12      ", Perform_all_IO_Tests, 0xE009}, // 0x400,600
    
    {" O_ICA_enum 13      ", Perform_all_IO_Tests, 0xE00A}, // 0x420,600
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" O_ICI_enum 14      ", Perform_all_IO_Tests, 0xE00B}, // 0x440,600
    {" O_ACC_enum 15      ", Perform_all_IO_Tests, 0xE00C}, // 0x480,600
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" IO Menu            ", Start_a_Menu,  13},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu IO_Menu[] = {
    /// = 13
    {" IO Menu       13   ", Really_DoNothing, 0}, //
    {" Perform IO test    ", Perform_all_IO_Tests,     0 },
    {" Single IO          ", Start_a_Menu,  12},
    {" Perform mock IO tst", Perform_all_IO_Tests, 0x8000}, // this is for SW debug, not a real test
    {" IO tst- w/msgs     ", Perform_all_IO_Tests, 0xC000}, // this is for SW debug, not a real test
    
    {" Message Board   A  ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" MAIN Menu         0", Start_a_Menu,  6 },
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Navigator_Menu[] = {
    /// = 14
    {" Navigator Menu   14", Really_DoNothing, 0}, //
    {" Check GFI          ", Generic_Tester,       5 },
    {" ON - OFF      5    ", Start_a_Menu, 5},
    {" Diagnostics   1    ", Start_a_Menu, 1},
    {" IO            13   ", Start_a_Menu, 13},
    {" IO - Single   12   ", Start_a_Menu, 12},
    {" Main          6    ", Start_a_Menu, 6},
    {" Generic w/Optns 15 ", Start_a_Menu, 15},
    {" GFI & IO      16   ", Start_a_Menu, 16},
    {" Sngl IO NO OPT   17", Start_a_Menu, 17},
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7}, 
   
    {" RESET MCU          ", WDT_Test, 0},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Generic_Options_Menu[] = {
    /// = 15
    {" Generic w/Options15", Really_DoNothing,         0 }, //
    
    {" Turn on 120 + 24   ", C120_Plus_24_on_off, 1}, 
        
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 },
    
    {" Check GFI          ", Generic_Tester,        5 },
    {" Check GFI w/ optns ", Generic_Tester,       0x8000 + 5 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 },
        
    {" Check Run/Stop SW  ", Generic_Tester,        0 },
    {" Check R/S w Optns  ", Generic_Tester,       0x8000 + 0 },
    
    {" Check Inspection SW", Generic_Tester,       1 },
    {" Check Insp w optns ", Generic_Tester,       0x8000 + 1 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 },
        
    {" Check Enable SW    ", Generic_Tester,       2 },
    {" Check Enbl w Optns ", Generic_Tester,       0x8000 + 2 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 }, 
     
    {" Check Enbl + UP SW ", Generic_Tester,       3 },
    {" Check Enbl+Up w opt", Generic_Tester,       0x8000 + 3 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 }, 
    
    {" Check Enbl + UP DWN", Generic_Tester,       4 },
    {" Check Enbl+Dwn opts", Generic_Tester,       0x8000 + 4 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 }, 
    
    {" Turn on 120 + 24   ", C120_Plus_24_on_off, 1},
    {" Turn OFF 120 + 24  ", C120_Plus_24_on_off, 0},          

    {" Message Board A    ", DisplayMsgBrd_A,          0 },
    {" Message Board   B  ", DisplayMsgBrd_B,          0 },
    {" Message Board   C  ", DisplayMsgBrd_C,          0 },
    {" Clear All Faults   ", Clear_All_Boards,         7 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 },
        
    {" Turn on 120 vac    ", C120_VAC_on_off, 1},
    {"   Turn OFF 120 vac ", C120_VAC_on_off, 0}, 
    
    {" Set C24V ON, SEB 4 ", Set_or_clear_24V_on_SEB4, 1},
    {"   Clear C24V, SEB 4", Set_or_clear_24V_on_SEB4, 0},                     
    
    {" Message Board A    ", DisplayMsgBrd_A,          0 },
    {" Message Board   B  ", DisplayMsgBrd_B,          0 },
    {" Message Board   C  ", DisplayMsgBrd_C,          0 },
    {" Clear Msg Board A  ", Clear_All_Boards,         1 },
    {" Clear Msg Board B  ", Clear_All_Boards,         2 },
    {" Clear Msg Board C  ", Clear_All_Boards,         4 },
    {" Clear All Faults   ", Clear_All_Boards,         7 },    
    {" RESET MCU          ", WDT_Test,                 0 },
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp,            0 },
};

struct a_menu GFI_a_IO_Menu[] = {
    /// = 16
    {" GFI and IO menu  16", Really_DoNothing, 0}, //
    {" Check GFI No Trip  ", Generic_Tester,       5 },
    {" Chk GFI Reset Trips", Generic_Tester,       6 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0}, 
    {" Navigator Menu   14", Start_a_Menu, 14},   
    {" Clear all out SEBs ", ClearAllSEB_from_a_Menu, 0},
    {" Perform IO test    ", Perform_all_IO_Tests,     0 },
    {" Perfm IO tst Optns ", Perform_all_IO_Tests,     0xC000 },
    {" Single IO          ", Start_a_Menu,  17},    
    {" Check BELL         ", Check_Car_Buzzer_or_Bell, 1 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    
    {" Turn on L15 Relay  ", L15RL_on_off, 1},
    {"   L15 Relay OFF    ", L15RL_on_off, 0},
    {" Turn on 120 vac    ", C120_VAC_on_off, 1},
    {"   Turn OFF 120 vac ", C120_VAC_on_off, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
         
    {" Set C24V ON, SEB 4 ", Set_or_clear_24V_on_SEB4, 1},
    {"   Clear C24V SEB 4 ", Set_or_clear_24V_on_SEB4, 0}, 
    {" Set L15_T ON, SEB 2", L15_T_on_off, 1},
    {"   Clear L15_T SEB 2", L15_T_on_off, 0},
    {" Set three ON,      ", Set_Clear_C120V_24_L15_T, 1},
    {"   Clear three      ", Set_Clear_C120V_24_L15_T, 0},     
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
       
    // L15_T_on_off   Set_Clear_C120V_24_L15_T
    {" Clear all out SEBs ", ClearAllSEB_from_a_Menu, 0},
    {" Turn on 120 + 24   ", C120_Plus_24_on_off, 1},
    {" Turn OFF 120 + 24  ", C120_Plus_24_on_off, 0},
    {" Show me SEB inputs ", Read_and_Display_All_Inputs, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},    
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    {" Main          6    ", Start_a_Menu, 6},
    {" Generic w/Optns 15 ", Start_a_Menu, 15},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
};

struct a_menu Single_IO_Menu_B[] = {
    /// = 17  NO OPTIONS - REAL THING
    {" Sngl IO NO OPT   17", Really_DoNothing, 0}, //
    {" RESET MCU          ", WDT_Test, 0},
    {" O_IFL_COPo0_enum 0 ", Perform_all_IO_Tests, 0x400 + 0}, // 0x400,600
    {" O_IFB_COPo1_enum 1 ", Perform_all_IO_Tests, 0x400 + 1}, // 0x400,600
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    
    {" O_CUL_COPo2_enum 2 ", Perform_all_IO_Tests, 0x400 + 2}, // 0x400,600
    {" O_CDL_COPo3_enum 3 ", Perform_all_IO_Tests, 0x400 + 3}, // 0x400,600
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    
    {" O_FAN_COPo4_enum 4 ", Perform_all_IO_Tests, 0x400 + 4}, // 0x400,400
    {" O_LIG_COPo5_enum 5 ", Perform_all_IO_Tests, 0x400 + 5}, // 0x400,200
    
    {" O_CSS_enum 6       ", Perform_all_IO_Tests, 0x400 + 6}, // 0x400,600
    {" O_FSS_enum 10      ", Perform_all_IO_Tests, 0x400 + 7}, // 0x400,600
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    
    {" O_CST_enum 11      ", Perform_all_IO_Tests, 0x400 + 8}, // 0x408,600
    {" O_ICC_enum 12      ", Perform_all_IO_Tests, 0x400 + 9}, // 0x400,600
    
    {" O_ICA_enum 13      ", Perform_all_IO_Tests, 0x400 + 0xA}, // 0x420,600
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" O_ICI_enum 14      ", Perform_all_IO_Tests, 0x400 + 0xB}, // 0x440,600
    {" O_ACC_enum 15      ", Perform_all_IO_Tests, 0x400 + 0xC}, // 0x480,600
    {" Run Power-Up Mode  ", JumpToPowerUp, 0},
    
    {" Message Board A    ", DisplayMsgBrd_A, 0},
    {" Message Board   B  ", DisplayMsgBrd_B, 0},
    {" Message Board   C  ", DisplayMsgBrd_C, 0},
    {" Clear Msg Board A  ", Clear_All_Boards, 1},
    {" Clear Msg Board B  ", Clear_All_Boards, 2},
    {" Clear Msg Board C  ", Clear_All_Boards, 4},
    {" Clear All Faults   ", Clear_All_Boards, 7},    
    {" RESET MCU          ", WDT_Test, 0},
    {" IO Menu            ", Start_a_Menu,  13},
    {" GFI and IO menu  16", Start_a_Menu,  16},
    {" Main Menu          ", Start_a_Menu,   6},
    {" GALX-1134 CTB     0", Start_a_Menu,  0 },
    {" Run Power-Up Mode  ", JumpToPowerUp,  0},
};
*/
          
/*          
          
         { Main_MenuList, (sizeof(Main_MenuList) / sizeof(Main_MenuList[0])) - 1},										//0
         { IndividualTests_Menu_List, (sizeof(IndividualTests_Menu_List) / sizeof(IndividualTests_Menu_List[0])) - 1},	//1
         { SubMenu_B_List, (sizeof(SubMenu_B_List) / sizeof(SubMenu_B_List[0])) - 1},									//2
         { SubMenu_C_List, (sizeof(SubMenu_C_List) / sizeof(SubMenu_C_List[0])) - 1},  									//3
         { groupCom_Menu_List, (sizeof(groupCom_Menu_List) / sizeof(groupCom_Menu_List[0])) - 1},						//4
         { Diagnostic_Menu_List, (sizeof(Diagnostic_Menu_List) / sizeof(Diagnostic_Menu_List[0])) - 1},					//5
         { FPGA_Diag_Menu_List, (sizeof(FPGA_Diag_Menu_List) / sizeof(FPGA_Diag_Menu_List[0])) - 1},					//6
         { MyMenuList, (sizeof(MyMenuList) / sizeof(MyMenuList[0])) - 1},												//7
         { FPGA_SetAddrs, (sizeof(FPGA_SetAddrs) / sizeof(FPGA_SetAddrs[0])) - 1},										//8
         { Set_main_IO, (sizeof(Set_main_IO) / sizeof(Set_main_IO[0])) - 1},											//9
         { Set_1106AN, (sizeof(Set_1106AN) / sizeof(Set_1106AN[0])) - 1},               

*/

/*        
        {Test_B_Module_Menu, (sizeof(Test_B_Module_Menu) / sizeof(Test_B_Module_Menu[0])) - 1},
        {Test_C_Module_Menu, (sizeof(Test_C_Module_Menu) / sizeof(Test_C_Module_Menu[0])) - 1},
        {Test_CAN_Msgs_Menu, (sizeof(Test_CAN_Msgs_Menu) / sizeof(Test_CAN_Msgs_Menu[0])) - 1},
        {Main_Menu, (sizeof(Main_Menu) / sizeof(Main_Menu[0])) - 1}, 							    	// 6
        {Function_Test_Menu, (sizeof(Function_Test_Menu) / sizeof(Function_Test_Menu[0])) - 1},  		// 7
        {Diagnostic_Test_Menu, (sizeof(Diagnostic_Test_Menu) / sizeof(Diagnostic_Test_Menu[0])) - 1},   // 8
        {Debug_Menu, (sizeof(Debug_Menu) / sizeof(Debug_Menu[0])) - 1},  								// 9
        {Test_Module_10_Menu, (sizeof(Test_Module_10_Menu) / sizeof(Test_Module_10_Menu[0])) - 1},      // 10
        {Fault_Menu, (sizeof(Fault_Menu) / sizeof(Fault_Menu[0])) - 1},  							    // 11
        {Single_IO_Menu, (sizeof(Single_IO_Menu) / sizeof(Single_IO_Menu[0])) - 1},  				    // 12
        {IO_Menu, (sizeof(IO_Menu) / sizeof(IO_Menu[0])) - 1},  				                        // 13
        {Navigator_Menu, (sizeof(Navigator_Menu) / sizeof(Navigator_Menu[0])) - 1},                     // 14
        {Generic_Options_Menu, (sizeof(Generic_Options_Menu) / sizeof(Generic_Options_Menu[0])) - 1},   // 15
        {GFI_a_IO_Menu, (sizeof(GFI_a_IO_Menu) / sizeof(GFI_a_IO_Menu[0])) - 1},                        // 16
        {Single_IO_Menu_B, (sizeof(Single_IO_Menu_B) / sizeof(Single_IO_Menu_B[0])) - 1},  
*/ 

//ZYM 12-18-2017	     
//-    { " TEST JIG COMM      ", TEST_JIG_COMM,          0 },
//-    { " Machine Room CAN L ", TEST_MLCAN,             16},        
//-    { " NTS CAN            ", TEST_NTSCAN,            0 },
//-	   { " v120AC Power Check ", v120AC_Power_Check,     0 },
//-    { " SW TEST            ", SW_TEST,                0 }, 
//-    { " SEB IO TEST        ", SEB_IO_TEST,            0 }, 
//-    { " FPGA1 IO TEST      ", FPGA1_IO_TEST,          0 }, 
//-    { " FPGA2 IO TEST      ", FPGA2_IO_TEST,          0 }, 


