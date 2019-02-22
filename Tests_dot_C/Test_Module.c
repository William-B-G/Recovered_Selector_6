// Test_Module.c

#include "global.h"
#include "Tests.h"

#define MAX_DEBUG 10
#define TURN_OFF_AT_END_OF_TEST -1
#define LEAVE_ON_AT_END_OF_TEST -2

int16 (*Generic_Service_Request_1)( int16*, int16, int16); // function pointer
int16 (*Generic_Service_Request_2)( int16*, int16, int16); // function pointer

int16 Delay_Count = 3; 
int16 Retest_Option_Parm = 0; // Required for Retest Option
int16 RetestResponse = 1; // Required for Retest Option
int16 (*Generic_Service_Request)( int16[], int16, int16); // function pointer
    // taking a ptr, an array, and two numerics
void  *Param_1A_ptr = NULL;
int16 *Param_1B_ptr = NULL;
int16 Param_1A_int = 0;
int16 Param_1B_int = 0;

void  *Param_2A_ptr = NULL;
int16 *Param_2B_ptr = NULL;
int16 Param_2A_int = 0;
int16 Param_2B_int = 0;
    
extern const uint32 Expected_Pattern[]; 
extern int16 CAN_Comm_Tst_Wrapper( int16* array_1, int16 param_A, int16 param_B);   
extern int16 Baud_Tst_Wrapper( int16* array_1, int16 param_A, int16 param_B);

const int16 Jumpers[5] = 
{
   0, 1, 4, 5, 0 
};

// Debug facility
const void *Test_Osignal_array[MAX_TEST_MODULE_SIGNAL_INDEX]= {
    o_CTo0,
    o_CTo1,
    o_CTo2,
    o_CTo3,
    o_CTo4,
    o_CTo5,
    o_CTo6,
    o_CTo7,
    o_CTo8,
    o_CTo9,
    o_CTo10,
    o_CTo11
};

const void *Test_isignal_array[MAX_TEST_MODULE_SIGNAL_INDEX]= {
    i_CTi0,
    i_CTi1,
    i_CTi2,
    i_CTi3,
    i_CTi4,
    i_CTi5,
    i_CTi6,
    i_CTi7,
    i_CTi8,
    i_CTi9,
    i_CTi10,
    i_CTi11,   
};

// wbg 2018-6-27
const void *SEB_debug_out_array[10] = {
    O_dbg01, 
    O_dbg02,
    O_dbg03,
    O_dbg04,
    O_dbg05,
    O_dbg06,
    O_dbg07,
    O_dbg08,
    O_dbg09,
    O_dbg10,             	
};

const char *Test_names[] = 
{
    "REOPEN LED check    ", // 0
    "CN18V check         ", // 1
    "CN19V check         ",
    "CCA-0002N IO Boards ",
    "DCL check           ",
    "RO check            ",
    "DOL check           ", // 6
    "TBD TEST            ",
    "TBD TEST            ",   
    "TBD TEST            ",
    "TBD TEST            ",
    "TBD TEST            ",
    "TBD TEST            ",
    "TBD TEST            ",
    "TBD TEST            ",         
};

const char *Failure_msgs[] = 
{
    "                    ",
    "Initial FAIL        ", // 1
    "Insure JP1 is OUT   ", // 
    "Insure JP1 installed", // 3
    "CCA-0002N           ",
    
    "Check SEB1 wiring 4 ", // 5 // Inspection SW { 5, 6, 7, 0 }
    "CN18V and check CN18",
    "on OPL-0106N        ",
    
    "CN19V and check CN19", // Enable { 8, 9, 10, 0 }
    "Insure brd has power",
    "Chk, MD 1 - 4       ", // 10
    
    "IC5,LED5,R12,CN12   ", //  DCL   
    "IC6,LED6,R13,CN12   ", //  RE-OPEN
    "IC7,LED7,R12,CN14   ", //  DOL
    
    "SW2, or if no +5VDC:", // 14 
    
    "IC14,L1,D4,C26,C27, ", //  
    "C29,TVS2            ",  
    "if no +5VDC, chk:   ", // 17
    						 
    "SW3, or if no +5VDC:", // 
    "insure SW1 in MANUAL", // 19
    "SW4, or if no +5VDC:", // 20 
    "finl FAILURE        ", // 21
    "Check Fire Buzzer   ", // 22
    "Check Bell wiring   ", // 23
    "Check Fire Light    ", // 24
    "wiring              ", // 25
    "Insure JP4 is OUT   ", // 26
    "Insure JP4 installed", // 27
    "Insure JP5 is OUT   ", // 28
    "Insure JP5 installed", // 29 
    "Chk MCU LED blinking", // 30       
};

const char *Operator_LCD_msgs[] = 
{
    "                    ",
    "Do U see red LED's, ", // 1
    "Mode(NO) Enter (YES)",
    "ENTER to Continue   ", // 3
    "MODE to Abort       ",
    "REOPEN DEVICE &     ", // 5
    "REOPEN, on?         ",
    "Verify red LED's,   ",
    "REOPEN, are both OFF",
    "Agn,verify red LED's",
    "R red LED's on for  ", // 10
    "4 IO boards         ",
    
    "CCA-0002N?          ",
    "Place SW1 in AUTO.  ", 
    "Place SW1 in MANUAL.",
    "Hold SW2 in CLOSE & ", // 15  "Hold SW2 in CLOSE & "
    "press ENTER         ",  
    "Hold SW2 in OPEN &  ", // 17 "Hold SW2 in OPEN &  "
    "Enter(YES) Mode(NO) ", // 18
    "Release after test. ", 
    "hold SW3 in NUDGE & ", // 20  "hold SW3 in NUDGE & "
    "Hold SW4 in HEAVY & ",  // 21 "Hold SW4 in HEAVY & "
    "Remove jumper J1 and",    
    "LCSE curtain and    ",  // 23 
    "leave J1 out 4 all  ",  // 24 
    "other tests.        ",  // 25 
    "ENTER to continue   ",  // 26  
    "Insert jumper J1.   ",  // 27
    "After tst, remv J1. ",  // 28 
    "Start wth all SW OFF",  // 29
    "Rear Door           ",   // 30
    "Front Door          ",  // 31 
    "Change BAUD on OPL  ",  // 32  
    "GFI No Trip Test    ",  // 33
    "GFI Reset Trip Test ",  // 34
    "Do you hear bell?   ",  // 35  
    "Do you hear buzzer? ",  // 36
    
    "Pre tst msg, Line 1 ",  // 37
    "Pre tst msg, Line 2 ",  // 38
    "Pre tst msg, Line 3 ",  // 39 
    "Pre tst msg, Line 4 ",  // 40  
    "Waiting msg, Line 1 ",  // 41
    "Waiting msg, Line 2 ",  // 42
    "Waiting msg, Line 3 ",  // 43  
    "Waiting msg, Line 4 ",  // 44 
    
    "Jumpers 1 & 4 OUT   ",  // 45
    "Jumper 5 in         ",  // 46
    "Jumpers 1 & 5 OUT   ",  // 47 
    "Jumpers 4 & 5 in    ",  // 48  
    "Jumper 1 OUT        ",  // 49
    "Jumper 4 in         ",  // 50
    "Waiting msg, Line 3 ",  // 51  
    "Waiting msg, Line 4 ",  // 52  
    "Remove jumper J1.   ",  // 53 
    "Hold SW2 in CLOSE.  ", //  54  "Hold SW2 in CLOSE & " 
    "Hld SW & press ENTER",  // 55
    "Hold SW2 in OPEN.   ",  // 56 "Hold SW2 in OPEN &  "
    "hold SW3 in NUDGE.  ",  // 57  "hold SW3 in NUDGE & "
    "Hld SWs & pres ENTER",  // 58
    "Hold SW4 in HEAVY.  ",  // 59 "Hold SW4 in HEAVY & "
};

const struct Generic_test_params
{
    int16  Initial_output_Item[4]; // Before starting test, 
           // set these items to the
    int16  Initial_output_State[4]; // states indicated 
           // in the Initial_output_State[] and then wait 
             // so that they have time to take effect.
    uint32 expected_final_result;
    int16  LCD_msgs[4]; // initial msgs to display
    int16  LCD_msgs_while_waiting_for_event[4]; // second set of 4-line msg
    int16  LCD_hint_msgs_while_waiting_for_event[4];
    int16  MsgDelayCount; // MsgDelayCount - so as not to display the message if we can detect the event without 
        // operator assist.
    int16  Gen_outputs_to_make[5];  // last item [4] // THESE ARE SET IN INITIAL CONDITIONS
    	// AND POSSIBLY TURNED OFF AT END (if Gen_outputs_to_make[4] == -1)
    	// Set in "case Set_Initial_IO:" 
    // { -1 = turn off items 0, 1, 2, 3 at end of test; -2 = leave them on.}
    uint32 expected_initial_result; // after Gen_outputs_to_make 
           // and after a wait time. 
    int16  Specific_outputs_to_make[5]; 
      // last item [4] { -1 = turn off items 0, 1, 2, 3 at 
      // end of test; -2 = leave them on.}. (in "case Wait_on_event:")
    char   Wait_4_operator_input; // (0 or 1 only): 'Enter' btn, 'Mode' 
           // button to abort. 0 == NO need to wait; 1 == wait.
    char   Wait_4_specific_input; 
    // (0, 1, or 2): Read IO, (if 1: in addition to 'Enter' btn) 
    // to cause logic to proceed. If 2 read all inputs to see
    // if final conditions are already met so we do not have to
    // wait on operator input to continue. If 0, just procedd, do
    // not wait for anything.
    char   Request_confirmation_by_oprtr; // (0 or 1): ask the 
    // operator if he/she (hesh) confirms expected result,
    int16  Input_2_wait_on;  // which input to wait on 
    int16  Which_IO;  // for SW debug only
    int16  Prelim_Failure_msg[4];
    int16  Final_Failure_msg[4];
    int16  DelayMultiplier_1;  // usefull for adding more delay time after setting outputs.
    int16  DelayMultiplier_2;  // usefull for adding more delay time after setting outputs    
    void   *Service_1;  // function pointer (Future capability)
              // takes 4 params (only 3 now being used. First of the four is now NULL):
    void      *A_Ptr_1;     // function pointer - for now NULL.
    int16     *Array_for_1; // Ptr to an array for service_1
    int16     int_Param_1A; // int16 param A for service_1 
    int16     int_Param_1B; // int16 param B for service_1
    void   *Service_2;  // function pointer (Future capability)
              // takes 4 params (only 3 now being used. First of the four is now NULL):    
    void      *A_Ptr_2;  // function pointer - for now NULL.
    int16     *Array_for_2; // Ptr to an array for service_2
    int16     int_Param_2A; // int16 param A for service_2 
    int16     int_Param_2B; // int16 param B for service_2  
    uint32  Assert_ptrn_4_initial; // for testing if the initial condition eval is working correctly.
    uint32  Assert_ptrn_4_final; // for testing if the final condition eval is working correctly.
       
}GenericTests[MAX_GENERIC_TEST] = 
{  // 0   Check that 2 red LED's are on (REOPEN DEVICE & REOPEN)
   { {O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1},  // Before starting test, set these items to the
   {0, 0, 1, -1},                      // states indicated in the Initial_output_State[]
   0x16,         // expected_final_result
   {1, 5, 6, 2},       // LCD_msgs[4]   
   {1, 5, 6, 2},       // LCD_msgs_while_waiting_for_event[4]
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   { -1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]
   0x16,           // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]          
   0, 0, 1, -1, -1,  // Wait_4_operator_input, Wait_4_specific_input, 
       // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 2, 9,  30,  0 },    // Prelim_Failure_msg[4] 
   { 2, 9,  30,  0 },    // Final_Failure_msg[4]
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,  // for testing if the final condition eval is working correctly.
   },
   // Check that 2 red LED's are on (REOPEN DEVICE & REOPEN)
       
   // 1   Verify CN18
   { {O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1},  // Before starting test, set these items to the
   {1, 0, 1, -1},                      // states indicated in the Initial_output_State[]   
   0x15,    // expected_final_result 0x412004
   {7, 5, 8, 2},    // LCD_msgs[4]  
   {7, 5, 8, 2},// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.  
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]
   0x15,     // expected_initial_result
   {O_CN18V_enum, -1, -1, -1, TURN_OFF_AT_END_OF_TEST}, // Specific_outputs_to_make[5]           
   0, 0, 1, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 2, 5,  6,  7 },    // Prelim_Failure_msg[4] 
   { 2, 5,  6,  7 },    // Final_Failure_msg[4] 
   2, // multiplier 1, usefull for adding more delay time after setting outputs.
   2, // multiplier 2, usefull for adding more delay time after setting outputs.   
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // Verify CN18
       
   // 2   Verify CN19
   { {O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1},  // Before starting test, set these items to the
   {0, 1, 1, -1},                      // states indicated in the Initial_output_State[]   
   0x15,    // expected_final_result 0x412004
   {9, 5, 8, 2},    // LCD_msgs[4]  
   {9, 5, 8, 2},// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.   
   {O_CN19V_enum, -1, -1, -1, TURN_OFF_AT_END_OF_TEST}, // Gen_outputs_to_make[5]
   0x15,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   0, 0, 1, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 2, 5,  8,  7 },    // Prelim_Failure_msg[4] 
   { 2, 5,  8,  7 },    // Final_Failure_msg[4] 
   2, // multiplier 1, usefull for adding more delay time after setting outputs.
   2, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // Verify CN19
   
   // 3    Set Close, Open, Nudge, Heavy & verify I/O boards have red LED on  
   { { O_PWR_enum, O_OPEN_enum, O_NUDGE_enum, O_HEAVY_enum },  // Before starting test, set these items to the
   {1, 1, 1, 1},                      // states indicated in the Initial_output_State[]   
   0x016,    // expected_final_result 0x412004 or 0xFFFFFFFF to ignore
   {10, 11, 12, 2},    // LCD_msgs[4]  
   {10, 11, 12, 2},// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {O_CLOSE_enum, O_OPEN_enum, O_NUDGE_enum, O_HEAVY_enum, TURN_OFF_AT_END_OF_TEST }, // Gen_outputs_to_make[5]
   0x016,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   0, 0, 1, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 9, 10, 0, 0 },    // Prelim_Failure_msg[4] 
   { 9, 10, 0, 0 },    // Final_Failure_msg[4] 
   2, // multiplier 1, usefull for adding more delay time after setting outputs.
   2, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // Set Close, Open, Nudge, Heavy & verify I/O boards have red LED on 
   
   // 4  DCL on  
   { {O_DCL_enum, O_PWR_enum, O_CN18V_enum, O_CN19V_enum},  // Before starting test, set these items to the
   {1, 1, 0, 0},                      // states indicated in the Initial_output_State[]   
   0x11A,    // expected_final_result 0x412004
   { 0, 0, 0, 0 },    // LCD_msgs[4]  
   { 0, 0, 0, 0 },// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {O_DCL_enum, -1, -1, -1, TURN_OFF_AT_END_OF_TEST}, // Gen_outputs_to_make[5]
   0x11A,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   0, 0, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 11, 0, 0, 0 },    // Prelim_Failure_msg[4] 
   { 11, 0, 0, 0 },    // Final_Failure_msg[4] 
   2, // multiplier 1, usefull for adding more delay time after setting outputs.
   2, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0x11B,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // DCL on
      
/////////////////////////////////      
      
   // 5   RO on  
   { {O_RO_enum, O_PWR_enum, O_CN18V_enum, O_CN19V_enum },  // Before starting test, set these items to the
   {1, 1, 0, 0},                      // states indicated in the Initial_output_State[] 
       // GFI relay on, L15_T OFF  
   0x16,    // expected_final_result 0x412004
   { 0, 0, 0, 0 },    // LCD_msgs[4]  
   { 0, 0, 0, 0 }, // LCD_msgs_while_waiting_for_event[4]
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist. 
   {O_RO_enum, -1, -1, -1, TURN_OFF_AT_END_OF_TEST}, // Gen_outputs_to_make[5]; 
   0x16,     // expected_initial_result // see L15 input
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   0, 0, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 12, 0, 0, 0 },    // Prelim_Failure_msg[4] 
   { 12, 0, 0, 0 },    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   }, 
   // RO on 
   
///////////////////////////////////   
   // 6   DOL on 
   { {O_DOL_enum,  O_PWR_enum, O_CN18V_enum, O_CN19V_enum },  // Before starting test, set these items to the
   {1, 1, 0, 0},   // states indicated in the Initial_output_State[] 
       // GFI relay off, L15_T OFF   
   0x0206,    // expected_final_result 0x412004
   { 0, 0, 0, 0 },    // LCD_msgs[4]  
   { 0, 0, 0, 0 },// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {O_DOL_enum, -1, -1, -1, TURN_OFF_AT_END_OF_TEST}, // Gen_outputs_to_make[5]; 
   0x0206,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   0, 0, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 13, 0, 0, 0 },    // Prelim_Failure_msg[4] 
   { 13, 0, 0, 0 },    // Final_Failure_msg[4] 
   2, // multiplier 1, usefull for adding more delay time after setting outputs.
   2, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0x0207,   // for testing if the final condition eval is working correctly.
   }, 
   // DOL on   
   
///////////////////////////////////   
   // 7   SW2 - CLOSE
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 1, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0x0116,    // expected_final_result 0x412004
   {14, 54, 0, 0},    // LCD_msgs[4]  - {14, 15, 16, 0}, 
   {14, 54, 55, 0 },// LCD_msgs_while_waiting_for_event[4]  - {14, 15, 16, 0 },
   {-1, -1, 55, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   10, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]; L15_T ON
   0x016,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   1, 2, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 0, 14, 15, 16 },    // Prelim_Failure_msg[4] 
   { 0, 14, 15, 16 },    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   }, 
   // SW2 - CLOSE    
      
///////////////////////////////////   
   // 8   SW2 - OPEN
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 1, -1 },   // states indicated in the Initial_output_State[]  
       //   
   0x0216,    // expected_final_result 0x412004
   { 14, 56, 0, 0 },    // LCD_msgs[4]  - { 14, 17, 16, 0 }, 
   { 14, 56, 55, 0 },// LCD_msgs_while_waiting_for_event[4] - { 14, 17, 16, 0 },
   {-1, -1, 55, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   10, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]; 
   0x016,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   1, 2, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 0, 14, 15, 16 },    // Prelim_Failure_msg[4] 
   { 0, 14, 15, 16 },    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // SW2 - OPEN    
         
///////////////////////////////////   
   // 9   SW3 - NUDGE
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 1, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0x0196,    // expected_final_result 0x412004
   { 14, 15, 57, 0 },    // LCD_msgs[4] - { 14, 15, 20, 16 }, 
   { 14, 15, 57, 58 },// LCD_msgs_while_waiting_for_event[4] - { 14, 15, 20, 16 },
   {-1, -1, -1, 58},       // LCD_hint_msgs_while_waiting_for_event[4]
   10, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist. 
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]; L15_T ON
   0x016,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   1, 2, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 19, 18, 15, 16 },    // Prelim_Failure_msg[4] 
   { 19, 18, 15, 16 },    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // SW3 - NUDGE  
 
///////////////////////////////////   
   // 10   SW4 - HEAVY
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 1, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0x056,    // expected_final_result 0x412004
   { 14, 59, 0, 0 },    // LCD_msgs[4]  - { 14, 21, 16, 0 }, 
   { 14, 59, 55, 0 },// LCD_msgs_while_waiting_for_event[4]  - { 14, 21, 16, 0 },
   {-1, -1, 55, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   10, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]; L15_T ON
   0x016,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   1, 2, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 0, 20, 15, 16 },    // Prelim_Failure_msg[4] 
   { 0, 20, 15, 16 },    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // SW4 - HEAVY   
   
///////////////////////////////////   
   // 11   Insert jumper J1
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 1, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0x15,    // expected_final_result 0x412004
   { 27, 26, 0, 28 },    // LCD_msgs[4]  
   { 0, 0, 0, 28 },// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]; L15_T ON
   0xffffffff,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   1, 0, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   {3, 0, 0, 0},    // Prelim_Failure_msg[4] 
   {3, 0, 0, 0},    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   }, 
   // Insert jumper J1   
   
///////////////////////////////////   
   // 12   Test of msgs
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 1, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0xffffffff,    // expected_final_result 0x412004
   { 37, 38, 39, 40 },    // LCD_msgs[4]  
   { 41, 42, 43, 44 },// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]; L15_T ON
   0xffffffff,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   1, 0, 1, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   {0, 0, 0, 0},    // Prelim_Failure_msg[4] 
   {23, 0, 0, 0},    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // Remove jumper J1   
   
///////////////////////////////////   
   // 13   Remove jumper J4 (BAUD RATE = 57.6 and Front door)
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 0, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0xffffffff,    // expected_final_result 0x412004
   { 32, 45, 46, 3 },    // LCD_msgs[4]  
   { 32, 45, 46, 3 },// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5];
   0xffffffff,     // expected_initial_result
   {O_PWR_enum, -1, -1, -1, LEAVE_ON_AT_END_OF_TEST}, // Specific_outputs_to_make[5]           
   1, 0, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   {26, 29, 0, 0},    // Prelim_Failure_msg[4] 
   {26, 29, 0, 0},    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   10, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   Baud_Tst_Wrapper, NULL, NULL, 0x3001, 0 ,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },    
   // Remove jumper J4 (BAUD RATE = 57.6 and Front door)  // param A was 0x3001  
   
///////////////////////////////////   
   // 14   Remove jumper J5 (REAR door) and use default BAUD (115.2)
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 0, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0xffffffff,    // expected_final_result 0x412004
   { 30, 47, 50, 3 },    // LCD_msgs[4]  
   { 30, 47, 50, 3 },// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5];
   0xffffffff,     // expected_initial_result
   {O_PWR_enum, -1, -1, -1, LEAVE_ON_AT_END_OF_TEST}, // Specific_outputs_to_make[5]           
   1, 0, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   { 28, 29, 0, 0 },    // Prelim_Failure_msg[4] 
   { 28, 29, 0, 0 },    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   10, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   CAN_Comm_Tst_Wrapper, NULL, NULL, 0x6001, 0 ,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.   
   },  
   // Remove jumper J5 (REAR door)          
        
///////////////////////////////////   
   // 15   Remove jumper J1
   { { O_CN18V_enum, O_CN19V_enum, O_PWR_enum, -1 },  // Before starting test, set these items to the
   { 0, 0, 1, -1 },   // states indicated in the Initial_output_State[] 
       //   
   0x16,    // expected_final_result 0x412004
   { 53, 26, 0, 0 },    // LCD_msgs[4]  
   { 0, 0, 0, 0 },// LCD_msgs_while_waiting_for_event[4] 
   {-1, -1, -1, -1},       // LCD_hint_msgs_while_waiting_for_event[4]
   0, // MsgDelayCount - so as not to display the hint message if we can detect the event without 
        // operator assist.
   {-1, -1, -1, -1, -1}, // Gen_outputs_to_make[5]; L15_T ON
   0xffffffff,     // expected_initial_result
   {-1, -1, -1, -1, -1}, // Specific_outputs_to_make[5]           
   1, 0, 0, -1, -1, // Wait_4_operator_input, Wait_4_specific_input,
        // Request_confirmation_by_oprtr, // which input to wait on, Which_IO;  // for SW debug only
   {3, 0, 0, 0},    // Prelim_Failure_msg[4] 
   {3, 0, 0, 0},    // Final_Failure_msg[4] 
   1, // multiplier 1, usefull for adding more delay time after setting outputs.
   1, // multiplier 2, usefull for adding more delay time after setting outputs.
   NULL, NULL, NULL, 0, 0,    // function ptr_1 and three parameters for the function
   NULL, NULL, NULL, 0, 0,   // function ptr_2 and three parameters for the function
   0xffffffff,   // for testing if the initial condition eval is working correctly.
   0xffffffff,   // for testing if the final condition eval is working correctly.
   },
   // Insert jumper J1         
        
};

// GenericTests[MAX_GENERIC_TEST].expected_final_result ;
// GenericTests[MAX_GENERIC_TEST].Wait_4_operator_input;
// GenericTests[MAX_GENERIC_TEST].Wait_4_specific_input;
// GenericTests[Test].Request_confirmation_by_oprtr;
// GenericTests[MAX_GENERIC_TEST].Gen_outputs_to_make[5];
// GenericTests[MAX_GENERIC_TEST].Specific_outputs_to_make[5];

enum
{
	initialize,
	check_initial_IO,
	Wait_on_event,
	require_confirmation,
	run_test,
	View_Log,
	test_pass,
	test_done,
	test_failure,
	Retest_option,
	Set_Initial_IO,
};

enum
{
    dbg01_enum,
    dbg02_enum,
    dbg03_enum,
    dbg04_enum,
    dbg05_enum,
    dbg06_enum,
    dbg07_enum,
    dbg08_enum,
    dbg09_enum,
    dbg10_enum,
};

///////////////////////////////////////////////////

int16 Set_or_Clear_All_CTxx(int16 Set_1_Clear_0)
{
	int16 idx = 0;
	
	for(idx = 0; idx < 12; idx++)
	{
		if(Set_1_Clear_0) setoutp( (void *)Test_Osignal_array[idx] ); // Debug facility
		  else clroutp( (void *)Test_Osignal_array[idx] );
	}
	return FINISHED_WITH_SERVICE;
}

///////////////////////////////////////////////////

int16 Set_or_Clear_All_dbgxx(int16 Set_1_Clear_0)
{
	int16 idx = 0;
	
	for(idx = 0; idx < MAX_DEBUG; idx++)
	{
		if(Set_1_Clear_0) setoutp( (void *)SEB_debug_out_array[idx] );
		  else clroutp( (void *)SEB_debug_out_array[idx] );
	}
	return FINISHED_WITH_SERVICE;
}

///////////////////////////////////////////////////

int16 Read_and_Display_rdoutp(int16 dummy)
{
	static int16 First_Pass = 0;
	uint8 Val = 0;
	uint8 idx = 0;
	int16 Rtrnval = 0;
		
	if(First_Pass == 0)
	{
	    Clear_Msg_Board_C();
		for(idx = 0; idx < 12; idx++)
		{
			Val = rdoutp( (void *)Test_Osignal_array[idx] ); // Debug facility
			sprintf(src, "rdoutp[%d]= %d ", idx, Val );
			Log_an_event_C(src);
		}
        First_Pass = 1;	
	}
	Rtrnval = Display_Message_Board_C(0);
	if(Rtrnval == FINISHED_WITH_SERVICE)
	{
	    First_Pass = 0;	
	}
	return Rtrnval;	
}

///////////////////////////////////////////////////

// SEB_0047N_inputs_array
int16 Read_and_Display_Rd_Inputs(int16 dummy)
{
	static int16 First_Pass = 0;
	uint8 Val = 0;
	uint8 idx = 0;
	int16 Rtrnval = 0;
		
	if(First_Pass == 0)
	{
	    Clear_Msg_Board_C();
		for(idx = 0; idx < 4; idx++)
		{
			Val = rdinp( (void *)SEB_0047N_inputs_array[idx] );
			sprintf(src, "rdinp[%d]= %d ", idx, Val );
			Log_an_event_C(src);
		}
        First_Pass = 1;	
	}
	Rtrnval = Display_Message_Board_C(0);
	if(Rtrnval == FINISHED_WITH_SERVICE)
	{
	    First_Pass = 0;	
	}
	return Rtrnval;	
}

///////////////////////////////////////////////////


int16 Read_and_Display_All_Inputs(int16 dummy)
{
	static int16 First_Pass = 0;
	uint8 Val = 0;
	uint8 idx = 0;
	int16 Rtrnval = 0;
		
	if(First_Pass == 0)
	{
	    Clear_Msg_Board_C();
        Read_All_inputs(1);
        First_Pass = 1;	
	}
	Rtrnval = Display_Message_Board_C(0);
	if(Rtrnval == FINISHED_WITH_SERVICE)
	{
	    First_Pass = 0;	
	}
	return Rtrnval;			
}

void Clear_Button_Pressed_Array(void)
{
    int16 j = 0;
    
    for(j = 0; j < 4; j++)
    {
        Button_Pressed[j] = 0;   
    }
}

///////////////////////////////////////////////////

int16 Insert_Remove_Jumper(int16 Jumper_plus_state)
{
    static int16 Kase = 0;
    static int16 Rtrnval = CONTINUE_SERVICE; 
    int16 jumper = Jumper_plus_state & 0xF00;
    int16 jumper_state = Jumper_plus_state & 0x01;
    int16 i = 0;   
    
    switch(Kase)
    {
        case 0:
            clr_lcd_dply();
            Clear_Msg_Board(); // A
            Clear_Button_Pressed_Array();
            i = jumper >> 8;
            sprintf(src, "Jumper=%d;jmpr=%d",Jumpers[i],i  );
            Log_an_event(src);
            if(jumper_state)sprintf(src,"Install jumper %d", Jumpers[i]);
              else sprintf(src,"Remove jumper %d", Jumpers[i]);
            New_write_display(src, 1, 0);
            New_write_display("then press ENTER.   ",2,0); // row, col
//          New_write_display("                    ",0,0); // row, col  
            Kase = 1;
            Rtrnval = CONTINUE_SERVICE;
            break;
            
        case 1:
                if(Check_for_Mode_Button() ) {
                    Kase = 2;
                    Button_Pressed[3] = 1;
                }
                
                if(Check_for_Enter_Button() ) {
                    Kase = 2;
                    Button_Pressed[2] = 1;
                } 
            break;
            
        case 2:
            Rtrnval = FINISHED_WITH_SERVICE;
            Kase = 0;
            break;
            
        default:
            break;           
    }
 
	return Rtrnval;    
}


///////////////////////////////////////////////////

int16 Toggle_O_CTxx(int16 channel)
{ // toggle_O_CTxx_state

    if (channel < 0 || channel > 11)
        return FINISHED_WITH_SERVICE; // error
          
    if ( rdoutp((void *)Test_Osignal_array[channel]) == 0 ) // Debug facility
        setoutp( (void *)Test_Osignal_array[channel] ); //  LED from 'Dbg0' - 'Dbg11'
    else
        clroutp( (void *)Test_Osignal_array[channel] );
    
    return FINISHED_WITH_SERVICE;
}

///////////////////////////////////////////////////

int16 Perform_Switch_tests(int16 Options)
{ // Options: bit 15 = 1, indicates SW debug and not a real test
    static int16 First_Pass = 0;
    static int16 Tst_index = 0;
           int16 ReturnVal = 0;
    
    if(First_Pass == 0)
    {
        Clear_All_Boards(3); // clear the message boards
        First_Pass = 1;
        Tst_index = 0;
    }
    ReturnVal = Generic_Tester(Tst_index + Options); // performs the test
    if( ReturnVal == FINISHED_WITH_SERVICE )
    {
    	if( ++Tst_index >= MAX_GENERIC_TEST )
    	{  // Done
    	    First_Pass = 0;
    	    ClearAllSEB();    		
    	}
    	else ReturnVal = CONTINUE_SERVICE;         
    }
    else if( ReturnVal == MODE_BUTTON )
    { // operator initiated abort
    	    First_Pass = 0;
    	    ClearAllSEB();        
    }
    return ReturnVal;  
}

////////////////////////////////

uint32 Testing_via_substitution(int16 Read_All_inputs_Control_byte_param)
{
    uint16 sw3_state = 0;
    uint16 allow_subs = Read_All_inputs_Control_byte_param & ALLOW_SUB_4_READ_ALL;
    uint16 sub_which_pattern = (Read_All_inputs_Control_byte_param & SUB_FINAL_4_READ_ALL) >> 1;
    uint32 assert_pattern = 0;
    
    sw3_state = rdinp(GALX4_0047_in_array[2]);
    
    if(sub_which_pattern) assert_pattern = GenericTests[GenericTest_index].Assert_ptrn_4_final;
      else assert_pattern = GenericTests[GenericTest_index].Assert_ptrn_4_initial; 
      
    if( !(sw3_state && allow_subs) )
    { // do not allow substitutions
        assert_pattern = 0xffffffff; // value of 0xffffffff == DO NOT SUBSTITUTE   
    }
    
    return assert_pattern; // value of 0xffffffff = DO NOT SUBSTITUTE 
}
// 
///////////////////////////////////////////////////

/*******************************************************************************

  Function:
   int16 Generic_Tester(int16 Test_with_Options)

  Summary:
    Performs one test as defined by data in array of structure, 
    GenericTests[MAX_GENERIC_TEST]. This 'one' test consists of a preliminary test
    and a final test.
     
  Author:
    William Grauer
    
  Description:
    Many of the tests for the UUT take a similar form: display an opnening message:
    set some preliminary stimuli (SEB outputs); insure that the expected response
    is seen; ask the operator to say Yes or No to continue; on continue, to 
    send some more outputs and examine the response; for some tests, to ask the
    operator if he/she (hesh) saw the expected result; and to see if the final
    result is what was expected. This function performs these operations by using
    a table to define and control the above operations.
    
    If the preliminary or final test Fails, the failure msgs will be sent to
    Msg Board A, and at the end of the test, this msg board will be displayed. If 
    a fail, the msg board can be exited with the 'Enter' button to try a 'Retest' 
    or the Mode button to exit test and return to Menu Mgr or Function
    Test Mgr.

  Precondition:
    None.

  Parameters:
    The index into the array GenericTests[MAX_GENERIC_TEST] and certain Options.
      Index into array: Bits 7 thru 0 - the tests (up to 256 different tests).
      Bits 10 thru 8 - Unused.
      Options: Bits 15 and 14.  Bit 15, if set, will display Msg Board A after test
        and will always show a PASS test result.  Bit 14, if set, will not wait for a
        specific SEB input.
        Bit 12, if set, will cause the IO's that were turned on, to then be turned
        off at end of test, even if structure data did not call for it.
        Bit 11, if set, will cause the test to display the startup msg, and after
            user response will just return PASS without displaying pass/fail msg.
            used for telling user to remove jumbers. (Bit 11 not currently used
            and the code is commented out)
                      
  Hardware Requirements:
    Run on the GALx-1132AN MCU board with 4-line, 20 segment display.

  Returns:
    integer to be used by the Menu Manager to continue or terminate further calls
    to the Generic_Tester() function. The return enum, 'CONTINUE_SERVICE' is 
    the most common return until the test is completed, upon which the enum
    'FINISHED_WITH_SERVICE' is returned.

  Remarks:
  	On the GALX4-0047 IO board, the switch SW1 can be used to force the 
  	'Check' option (Bit 15). 
  	This will always show a PASS and will display expected values
    and actual values for IO reads.  Switch SW2 can be use to force a failure for 'Final' test.
    SW2 has precedence over SW1.
    FUTURE:
    {
        Depending on contents of of 'Read_All_inputs_Control_byte':
        SW3 will force the 'Read_All_inputs()' to substitute test stimuli for the actual
        read. The test stimuli; "Assert_initial_read" and "Assert_final_read" will be used
        as long as the values are not 0xffffffff. If they are 0xffffffff then the 
        'Read_All_inputs()' will not make the substitution even if SW3 is set.
    }
    ++++ For references to SW1 - SW3, search for 'rdinp(GALX4_0047_in_array[z]' where
            z = 0, 1, 2 for SW1, SW2, SW3.
            if (rdinp(GALX4_0047_in_array[0]) == 0) // switch 1
            if (rdinp(GALX4_0047_in_array[1]) == 0) // switch 2
            if (rdinp(GALX4_0047_in_array[2]) == 0) // switch 3

 */
/******************************************************************************/

int16 Generic_Tester(int16 Test_with_Options_Param) //// "A"
{ //  .  
    int16 i,j,k = 0;
    static int16 test_Kase = initialize;
    static int16 ReturnVal = CONTINUE_SERVICE; // Required for Retest Option
    static int16 ReturnVal_Service = CONTINUE_SERVICE;
    static int16 NewMsgsDisplayed = 0;
    static int16 HintMsgsDisplayed = 0;
    static int16 debug_count = 0;
    static int16 kase_loop = 0; // for delaying a msg while waiting for an event.
           int16 OK_2_continue_Q = 0; // -1 = MODE button; 0 continue to wait; 1 found event.
           int16 Test = Test_with_Options_Param & 0x0ff; // discard bits above bit 7.
           int16 SW_Options = Test_with_Options_Param & 0xC000; // set options to bits 15 and 14
           int16 Test_with_Options = Test_with_Options_Param;
    
    if(Test > MAX_TEST_DEFINED) return FINISHED_WITH_SERVICE;

    SIU.GPDO[Z0_LED].R = !SIU.GPDO[Z0_LED].R;  // toggle LED;
    GenericTest_index = Test; //  a global so that 'Testing_via_substitution()' can
        // read the generic test data.
    if( rdinp(GALX4_0047_in_array[0]) ) // switch SW1
    {
        Test_with_Options |= 0x8000; 
        SW_Options |= 0x8000; // use switch 0 (on GAL 0047)
        // to force the 'Check' option. This will always show a PASS and will display expected values
        // and actual values for IO reads.   
    }
   
    switch (test_Kase)
    {
        case initialize:
            Standard_Init(CLEAR_ALL_MSG_BOARDS, DELAY_3);
           
            ReturnVal = CONTINUE_SERVICE;						
			Set_or_Clear_All_CTxx(0); // turn off all test LEDs on 0047 or SEB used as a debug tool
			Set_or_Clear_All_dbgxx(0); // turn off all 'dbgxx' leds on SEB 6, (addr= 6)
			Set_Clear_all_4_0047(0); // turn off the GALX4-0047N IO7 thru IO12
			setoutp( (void *)Test_Osignal_array[0] ); // Set first debug LED ON, on the GALX4-0047
//			setoutp( (void *)SEB_debug_out_array[dbg01_enum] ); // Set first debug LED ON, on SEB 6, (addr= 6)

            Setup_Initial_SEB_States(Test); //// "B"  // Before starting test, 
				 // set these items to the
				 // states indicated. Then wait.            
            NewMsgsDisplayed = 0;
            HintMsgsDisplayed = 0;
            debug_count = 0;
            // ************* FIRST GROUP OF MESSAGES (4 LINES).  ****************
            Display_LCD_msgs(Test); //// "C" //  start up display from Operator_LCD_msgs[]
            
//			Some tests are more elaborate then just looking at the inputs of the SEB's.  Thus these two
//			service request functions can be called; request_1 for checking initial conditions, and
//			request_2 for checking final conditions.            
            Generic_Service_Request_1 = GenericTests[Test].Service_1; // set up function pointer.
            	Param_1A_int = GenericTests[Test].int_Param_1A; // currently, only two of four parameters used.
            	Param_1B_int = GenericTests[Test].int_Param_1B;
            Generic_Service_Request_2 = GenericTests[Test].Service_2; // set up function pointer.
            	Param_2A_int = GenericTests[Test].int_Param_2A; // currently, only two of four parameters used.
            	Param_2B_int = GenericTests[Test].int_Param_2B;            
            kase_loop = 0; // for delaying a msg while waiting for an event.
            test_Kase = Set_Initial_IO;
            break;
            
        case Set_Initial_IO: // after a short time delay.
            if(timers[t_Generic_Delay] < Delay_Count) break; // for a time delay
            timers[t_Generic_Delay] = 0;
            Set_Initial_Conditions(Test); //// "D" // set general output (up to 4) 
                // from GenericTests[Test].Gen_outputs_to_make[idx]. Then wait
            test_Kase = check_initial_IO;                    
            break;
       
        case check_initial_IO:
            if(timers[t_Generic_Delay] < GenericTests[Test].DelayMultiplier_1 * Delay_Count) break;  
            // DO NOT RESET "timers[t_Generic_Delay]" because we may enter this case many times if
            // Generic_Service_Request_1 is not NULL.
//            Assert_test_read = Assert_initial_read;

            // will allow assert testing if SW3 switch is on from the GALX4-0047N IO board.
            Read_All_inputs_Control_byte = ALLOW_SUB_4_READ_ALL | SUB_INITIAL_4_READ_ALL;
            Read_All_inputs(0); // All_inputs
            sprintf(src,"inital:0x%X",All_inputs);
//            Log_an_event_C(src);           
// CHECK INITIAL
			if(Generic_Service_Request_1 == NULL) // A facility to add custom test routine
			{
                timers[t_Generic_Delay] = 0; // This is where to reset timer.
	            if( Check_Initial_Conditions(Test_with_Options) ) //// "E"
	            { // 1 = pass. Expected are contained in GenericTests[Test].expected_initial_result
	//                Display_LCD_msgs(Test);
	//                setoutp( (void *)SEB_debug_out_array[dbg02_enum] ); // debug LED
	//              Discard any old "ENTER" buttons
	                Check_for_Enter_Button(); // Release Enter key.
	                test_Kase = Wait_on_event;  
	            }
	            else
	            { 
	                Send_Failure_msgs_to_msg_brd_A(0, Test_with_Options); // preliminary error msgs
	                test_Kase = test_failure;	
	            }
				
			}
			else 
			{
				ReturnVal_Service = Generic_Service_Request_1(Param_1A_ptr, Param_1A_int, Param_1B_int);
				if( (ReturnVal_Service & 0x00ff) == CONTINUE_SERVICE) break;
				  else if( (ReturnVal_Service & 0x8000) ) test_Kase = Wait_on_event; else test_Kase = test_failure; 
				  timers[t_Generic_Delay] = 0; // And this is also where to reset timer.
			}
            
            break;
                       
        case Wait_on_event: //// "F" 3)
        //  or maybe just time delay depending on flags in struct GenericTests[Test]
            if(timers[t_Generic_Delay] < (1 * Delay_Count)  ) break;
            timers[t_Generic_Delay] = 0;
            setoutp( (void *)SEB_debug_out_array[dbg01_enum] ); // debug LED
// Show additional info - the hint  
            kase_loop++;
            if( (HintMsgsDisplayed == 0) && (kase_loop > GenericTests[Test].MsgDelayCount) )
            {
            	Display_hint_msgs(Test); // dislpay lines //// "H"            	    
            	HintMsgsDisplayed = 1;
            }          
            OK_2_continue_Q = check_4_event(Test_with_Options);
// ************* THIS IS WHERE A WAIT ON OPERATOR (FOR INSERTING JUMPERS FOR EXAMPLE) WOULD BE DONE.  ****************            
/*            
            if(Test_with_Options &0x800) // Bit 11 - NOT USED CURRENTLY.
            { // This test is only sending the user a msg.
                test_Kase = initialize;
                return FINISHED_WITH_SERVICE;
                // break;
            }
*/            
            if( OK_2_continue_Q == 1 ) // event found = 1
            {
//                Log_an_event_C("into Wait on event  ");
                timers[t_Generic_Delay] = 0;
// ************* THIS IS WHERE PWR COULD BE TURNED BACK ON AFTER INSERTING JUMPERS  ****************                 
                Set_Specific_outputs(Test); //// "G"               
//                setoutp( (void *)SEB_debug_out_array[dbg07_enum] );
                test_Kase = require_confirmation; 
            }
            else if(OK_2_continue_Q == -1)  
            { // abort via MODE btn
                Turn_Off_IOs(Test + ABORT); 
                RetestResponse = 0;
//                ReturnVal =  MODE_BUTTON; // operator aborted testing
                test_Kase = test_done;  
            }
            break;
                        
        case require_confirmation: // or maybe not, depending 
            // on GenericTests[Test].Request_confirmation_by_oprtr
            //// "H" 4)
            if(timers[t_Generic_Delay] < Delay_Count) break; 
            timers[t_Generic_Delay] = 0; 
//            setoutp( (void *)SEB_debug_out_array[dbg01_enum] );

            if( GenericTests[Test].Request_confirmation_by_oprtr )
            { // display new msgs perhaps
//                setoutp( (void *)SEB_debug_out_array[dbg04_enum] ); 
            	// display msgs unless already displayed.
               	if( NewMsgsDisplayed == 0 ) 
            	{
            	    Log_an_event_C("awaiting confirmaton");
            	    Display_new_msgs(Test); // dislpay lines //// "H"
            	    // indicated by "...while_waiting_for_event" 
            	}
            	NewMsgsDisplayed = 1;
            	// wait for operator cofirmation.
            	OK_2_continue_Q = Wait_on_operator();  ///////////  WAIT FOR OPERATOR BEFORE GOING ON
	            if( OK_2_continue_Q == 1 ) // Enter btn
	            {	                	  
//	                setoutp( (void *)Test_Osignal_array[3] ); // Debug facility	                            
	                test_Kase = test_pass; 
	            }
	            else if(OK_2_continue_Q == -1) // Mode btn  
	            { // abort via MODE btn
//	                setoutp( (void *)SEB_debug_out_array[dbg05_enum] );
	                Send_Failure_msgs_to_msg_brd_A(1, Test_with_Options); // final error msgs
	                test_Kase = test_failure;  
	            }  
	            
	            break;          		
            }
            else 
            { //  instead of asking operator to say that the test passed or failed, have the mcu
              //  run an automated test to determine pass/fail.
//                setoutp( (void *)SEB_debug_out_array[dbg06_enum] );
                test_Kase = run_test;   
            }
            break;
            
///  ********************  RUN TEST *****************                                               
        case run_test:
            if(timers[t_Generic_Delay] < ( GenericTests[Test].DelayMultiplier_2 * Delay_Count ) ) break;
            // DO NOT RESET "timers[t_Generic_Delay]" because we may enter this case many times if
            // Generic_Service_Request_1 is not NULL.
                          
//            setoutp( (void *)SEB_debug_out_array[dbg07_enum] );          
// CHECK FINAL //// "I"
            // will allow assert testing if SW3 switch is on from the GALX4-0047N IO board.
            Read_All_inputs_Control_byte = ALLOW_SUB_4_READ_ALL | SUB_FINAL_4_READ_ALL; 
            Read_All_inputs(0); // All_inputs

			if(Generic_Service_Request_2 == NULL)
			{
			    timers[t_Generic_Delay] = 0; // This is where to reset timer.
			    sprintf(src,"final:0x%X",All_inputs);
                Log_an_event_C(src);
               
	            if( Check_final_condition(Test_with_Options) ) //  1= pass; 0 = fail
	            {
	//                setoutp( (void *)SEB_debug_out_array[dbg08_enum] );
	//                Turn_Off_IOs(Test); //  only turn off those that the struct will indicate
	                setoutp( (void *)Test_Osignal_array[4] ); // Debug facility
	                test_Kase =  test_pass;  
	            }
	            else
	            { // test fail
	                Send_Failure_msgs_to_msg_brd_A(1, Test_with_Options); // final error msgs
	                test_Kase =  test_failure;	
	            }				
			}
			else 
			{
// setoutp(GALX4_0047_OUT_array[0]); // TO help debug a problem. LD06 (IO7) IS IN "IO_Test.c", 'Evaluate_The_results'			
				ReturnVal_Service = Generic_Service_Request_2(Param_2A_ptr, Param_2A_int, Param_2B_int);
				debug_count++;
				if( (ReturnVal_Service & 0x00ff) == CONTINUE_SERVICE)
				{
					sprintf(src,"ind_CNTU cnt=%d", debug_count);
					Add_msg_to_array_B(src,1);
					sprintf(src,"rtv=%d:RTS=%X",ReturnVal, ReturnVal_Service);
					Add_msg_to_array_B(src,2);
					break; // must break out otherwise timers[t_Generic_Delay] will get
					// prematurly reset.	
				}
				sprintf(src,"RVS= 0x%X", ReturnVal_Service);
				Log_an_event_C(src);
				if( (ReturnVal_Service & 0x8000) )
				{ // PASS indicated
				    setoutp(GALX4_0047_OUT_array[2]); // O_LDO8 ( label on GALX4_0047 says IO9, and this is [2] ).
				    sprintf(src,"ind_pass cnt=%d", debug_count);
					Add_msg_to_array_B(src,3);
					sprintf(src,"rtv=%d:RTS=%X",ReturnVal, ReturnVal_Service);
					Add_msg_to_array_B(src,4);
				    test_Kase = test_pass;    
				} 
				else
				{ // FAIL indicated
				    setoutp(GALX4_0047_OUT_array[3]); // O_LDO9 ( label on GALX4_0047 says IO10, and this is [3] ).
				    sprintf(src,"ind_fail cnt=%d", debug_count);
					Add_msg_to_array_B(src,5);
					sprintf(src,"rtv=%d:RTS=%X",ReturnVal, ReturnVal_Service);
					Add_msg_to_array_B(src,6);				    
				    test_Kase = test_failure;   
				} 
				timers[t_Generic_Delay] = 0; // And this is also where to reset timer.
				sprintf(src,"RtV= 0x%X", ReturnVal);
				Log_an_event_C(src);
			}			
            
            break;
                        
        case test_pass: 
            CurrentTestPassFail = 1;  
            if(SW_Options)
            {
                setoutp( (void *)Test_Osignal_array[5] ); // Debug facility
                test_Kase = View_Log;	
            }
            else
            {
                New_write_display("                    ",0,0); // row, col
                New_write_display("     Good !         ",1,0); // row, col
                New_write_display("   Test PASSED.     ",2,0); // row, col
                New_write_display("                    ",3,0); // row, col                
                test_Kase = test_done;   
            }
            break;

	    case View_Log: // GET here if SW_Options. This will result in needing one more MODE button to get out
	    				// of test with SW_Options, and will not get a 'Good ! Test PASSED' msg.
	        ReturnVal = DisplayMsgBrd_A(0);
	        if(ReturnVal == FINISHED_WITH_SERVICE)
	        {	            
	            ReturnVal = CONTINUE_SERVICE;
	            setoutp( (void *)Test_Osignal_array[6] ); // Debug facility
	            test_Kase = test_done;	
	        }
	        break;
            
        case test_done: //// "J"
            Turn_Off_IOs(Test); //  only turn off those that the struct will indicate
//            Set_Clear_all_4_0047(0); // turn off the GALX4-0047N IO7 thru IO12
            test_Kase = initialize;
            // Required for Retest Option
            if(RetestResponse == 0)ReturnVal = FINISHED_WITH_SERVICE; // Idle_time  
            else ReturnVal = DONE_BUT_CONTINUE_DISPLAY;              
            break;
                                    
        case test_failure:
            clr_lcd_dply();
//          New_write_display("                    ",0,0); // row, col
            New_write_display(" Test failed        ",1,0); // row, col
            New_write_display( (char *)Test_names[Test], 2, 0 );
            Turn_Off_IOs(Test); //  only turn off those that the struct will indicate
            setoutp( (void *)Test_Osignal_array[7] ); // Debug facility
            test_Kase = Retest_option;
//            ReturnVal = Display_Message_Board(0);
//            if(ReturnVal == FINISHED_WITH_SERVICE) test_Kase = Retest_option;
//            else if(ReturnVal == CLOSE_MSG_BOARD) test_Kase = test_done;  //  CLOSE_MSG_BOARD = 4
            break;
// RetestParam            
        case Retest_option: // Required for Retest Option
            setoutp( (void *)Test_Osignal_array[8] ); // Debug facility
            RetestResponse = Handle_Retest_Request(Retest_Option_Parm);
            Retest_Option_Parm = 1;
            if(RetestResponse == 0) test_Kase = test_done;  // do not retest
            else if(RetestResponse == 1) test_Kase = initialize; // test again
                else ReturnVal = CONTINUE_SERVICE;    
            break;           
               
        default:
            break;                
    } // end of "switch (test_Kase)"
    
    return ReturnVal;
}


/*****************************************************/
/***                   Clear All                ******/
/*****************************************************/
void ClearAllSEB(void)
{
	int i;
//	int j = sizeof(SEB_outputs_array) / sizeof(SEB_outputs_array[0]);
//	int j =  (sizeof(SEB_outputs_array) / sizeof(SEB_outputs_array[0]));
	for (i = 0; i < 9; i++)
	{		
		clroutp( (void *)SEB_outputs_array[i]); // SEB_inputs_array
	}
}

/*****************************************************/
/***                   Clear All    COP         ******/
/*****************************************************/
void ClearAll_COP(void)
{
	int i;
	for (i = 0; i <= MAX_COP_out_index; i++)
	{		
		clroutp( (void *)SEB_1134_COP_out_array[i]);
	}
}


/*****************************************************/
/***                   Clear All from Menu      ******/
/*****************************************************/
int16 ClearAllSEB_from_a_Menu(int16 dummy)
{
    ClearAllSEB();
    return FINISHED_WITH_SERVICE;
}


/*****************************************************/
/***              Set up the inital conditions  ******/
/*****************************************************/
int16 Set_Initial_Conditions(int16 Test)
{
    int16 idx = 0;
    
    for(idx = 0; idx < 4; idx++)
    {
    	if( GenericTests[Test].Gen_outputs_to_make[idx] >= 0)
    	{
    		setoutp((void *)SEB_outputs_array[ GenericTests[Test].Gen_outputs_to_make[idx] ]);
    		if(GenericTests[Test].Gen_outputs_to_make[idx] < 6)
    		{ // These are not going to SEB and thus can not see if on by looking at LED on SEB.
    		  // Therefore, send these sets to the GALX4-0047N so that for SW debug, the LEDs can be seen
    		  // O_LDO6_enum
    		    setoutp((void *)SEB_outputs_array[ GenericTests[Test].Gen_outputs_to_make[idx] + O_LDO6_enum ]);	
    		}
    	}
    	    
    }
    return 0; 
}

/*****************************************************/
/***        Set the specific I/O for this test  ******/
/*****************************************************/
int16 Set_Specific_outputs(int16 Test)
{
    int16 idx = 0;
    
    for(idx = 0; idx < 4; idx++)
    {
    	if( GenericTests[Test].Specific_outputs_to_make[idx] >= 0)
    	{ 
    	    setoutp((void *)SEB_outputs_array[ GenericTests[Test].Specific_outputs_to_make[idx] ]);
            sprintf(src,"Tst=%d,idx=%d,Output=%d", Test, idx, GenericTests[Test].Specific_outputs_to_make[idx] );
            Add_msg_to_array_B(src, 17 + idx);      	    
    		if(GenericTests[Test].Specific_outputs_to_make[idx] < 6)
    		{ // These are not going to SEB and thus can not see if on by looking at LED on SEB.
    		  // Therefore, send these sets to the GALX4-0047N so that for SW debug, the LEDs can be seen
    		  // O_LDO6_enum
    		    setoutp((void *)SEB_outputs_array[ GenericTests[Test].Specific_outputs_to_make[idx] + O_LDO6_enum ]);	
    		}    	    	
    	}    	    
    }
    return 0;    
}

//setoutp((void *)SEB_outputs_array[Diag_IO_index]);
//clroutp((void *)SEB_outputs_array[Diag_IO_index]);

//rdinp((void *)SEB_outputs_array[Diag_IO_index]) 
// GenericTests[MAX_GENERIC_TEST].Gen_outputs_to_make[4];
// GenericTests[MAX_GENERIC_TEST].Specific_outputs_to_make[4];

/*****************************************************/
/***             Put LCD msgs up for operator   ******/
/*****************************************************/
int16 Display_LCD_msgs(int16 Test)
{
    int16 wbg_index = 0;
    
    for (wbg_index = 0; wbg_index < 4; wbg_index++)
    {
        if(GenericTests[Test].LCD_msgs[wbg_index] >= 0)
           	New_write_display( (char *)Operator_LCD_msgs[ GenericTests[Test].LCD_msgs[wbg_index] ] , wbg_index, 0 );
    }

    return 0;     
}

/*****************************************************/
/***        Put Hint  LCD msgs up for operator   ******/
/*****************************************************/
int16 Display_hint_msgs(int16 Test)
{
    int16 wbg_index = 0;
    
    for (wbg_index = 0; wbg_index < 4; wbg_index++)
    {
        if(GenericTests[Test].LCD_hint_msgs_while_waiting_for_event[wbg_index] >= 0)
           	New_write_display( (char *)Operator_LCD_msgs[ GenericTests[Test].LCD_hint_msgs_while_waiting_for_event[wbg_index] ] , wbg_index, 0 );
    }

    return 0;     
}


/*****************************************************/
/***        Put new  LCD msgs up for operator   ******/
/*****************************************************/
int16 Display_new_msgs(int16 Test)
{
    int16 wbg_index = 0;
    
    for (wbg_index = 0; wbg_index < 4; wbg_index++)
    {
        if(GenericTests[Test].LCD_msgs_while_waiting_for_event[wbg_index] >= 0)
           	New_write_display( (char *)Operator_LCD_msgs[ GenericTests[Test].LCD_msgs_while_waiting_for_event[wbg_index] ] , wbg_index, 0 );
    }

    return 0;     
}

/*****************************************************/
/***         Check for Enter button or I/O on   ******/
/***    or final pattern match or mode button   ******/
/*****************************************************/
int16 check_4_event(int16 Test_with_Options)
{
    int16 Test = Test_with_Options & 0x0ff; // use bits 7 thru 0
    int16 SW_Options = Test_with_Options & 0xC000; // set options to bits 15 & 14
    int16  IO_Value_Read = 0;
    uint32 The_Expected_Pattern = GenericTests[Test].expected_final_result;   
   
//    setoutp( (void *)SEB_debug_out_array[dbg03_enum] );
    if( (SW_Options & 0x4000) )
    { // just return as though event happened
//        timers[t_Generic_Delay] = 0;
//        return 1; // simulate that event happened    	
    }
    
    if( GenericTests[Test].Wait_4_operator_input == 0 &&  GenericTests[Test].Wait_4_specific_input == 0)
    { // no need to wait on event, just return
//        timers[t_Generic_Delay] = 0;
//        setoutp( (void *)SEB_debug_out_array[dbg04_enum] );
        return 1;	
    }
    
    if( GenericTests[Test].Wait_4_operator_input == 1) 
    { // wait for Enter or Mode btn   
        Add_msg_to_array_B("waiting for enter   ", 0); 
        
	    if(Check_for_Mode_Button() ) {
			return -1;
	    }          
	    if(Check_for_Enter_Button() ) {
//	        timers[t_Generic_Delay] = 0;
			return 1;
	    }  
	    else if(SW_Options & 0x4000) return 1; // special debug mode
	    	
    }
	if( GenericTests[Test].Wait_4_specific_input == 2)
	{ // see if final conditions are already met.
        Read_All_inputs(0);        
        if(All_inputs == The_Expected_Pattern ) return 1;
	}    
    if(GenericTests[Test].Wait_4_specific_input == 1)
    { // rdinp  //  Read_SEB_invert
    	IO_Value_Read = rdinp((void *)SEB_outputs_array[ GenericTests[Test].Input_2_wait_on ]);
//    	setoutp( (void *)SEB_debug_out_array[dbg05_enum] );
    	if(IO_Value_Read)
    	{
//    	    timers[t_Generic_Delay] = 0;
//            setoutp( (void *)SEB_debug_out_array[dbg06_enum] );
    	    return 1;
    	}	
    }
    
    if(Check_for_Mode_Button() ) {
		return -1; // operator aborted testing.
    }
        
    return 0; // still waiting for event.        
}

/////////////////////////////////////////////

/*****************************************************/
/***         Check for Enter or Mode buttons    ******/
/*****************************************************/
int16 Wait_on_operator(void)
{

    if(Check_for_Enter_Button() ) {
//        setoutp( (void *)SEB_debug_out_array[dbg02_enum] ); // Set debug LED ON, on SEB 6, (addr= 6)
		return 1;
    } 
    
    if(Check_for_Mode_Button() ) {
//        setoutp( (void *)SEB_debug_out_array[dbg03_enum] ); // Set debug LED ON, on SEB 6, (addr= 6)
		return -1; // operator aborted testing.
    }
        
    return 0; // still waiting for event.        
}

//////////////////////////////////////////////

/*****************************************************/
/***         Check for Initial inputs OK        ******/
/*****************************************************/
int16 Check_Initial_Conditions(int16 Test_with_Options)
{
    uint16 Test = Test_with_Options & 0x0ff; // use only bits 7 thru 0
    uint16 SW_Options = Test_with_Options & 0x08000; // set options to bit 15
    uint32 The_Expected_Pattern = GenericTests[Test].expected_initial_result;
    uint16 Which_IO = 0 ; 
     
    Read_All_inputs(0);
//    Which_IO = GenericTests[Test].Which_IO;
    sprintf(src,"AI_init=0x%X", All_inputs); 
    Log_an_event(src);    
    sprintf(src,"Expct=0x%X", The_Expected_Pattern); 
    Log_an_event(src);    
    if(SW_Options)
    { // add All_inputs to msg board for SW debug
        return PASS; // pass    	
    }
    else return Evaluate_The_Results( The_Expected_Pattern, (uint16)Test_with_Options); // the real thing
      // not SW debug
}

////////////////////////////////////////////// 

/*****************************************************/
/***       Check that all expected IOs are met  ******/
/*****************************************************/
int16 Check_final_condition(int16 Test_with_Options)
{
    int16 Test = Test_with_Options & 0x7fff; // discard bit 15
    int16 SW_Options = Test_with_Options & 0x8000; // set options to bit 15
    uint32 The_Expected_Pattern = GenericTests[Test].expected_final_result;
    int16 Which_IO =0; 
      
    Read_All_inputs(0); // do not send results to msg board C
    Which_IO = GenericTests[Test].Which_IO;
 // add All_inputs to msg board for SW debug
    sprintf(src,"AI_final=0x%X", All_inputs); 
    Log_an_event(src);    
    sprintf(src,"EXP_final=0x%X", The_Expected_Pattern); 
    Log_an_event(src); 
    if(SW_Options)
    {
        return PASS; // pass    	
    }
    if( rdinp(GALX4_0047_in_array[1]) ) return FAIL;  // switch SW1 to force a failure
    else return Evaluate_The_Results( The_Expected_Pattern, (uint16)Which_IO); // the real thing
      // not SW debug
}

//////////////////////////////////////////////

// GenericTests[MAX_GENERIC_TEST].Gen_outputs_to_make[5];
// GenericTests[MAX_GENERIC_TEST].Specific_outputs_to_make[5];

/*****************************************************/
/***         Leave system in the initial condts ******/
/*****************************************************/
int16 Turn_Off_IOs(int16 Test_and_options)
{   int16 Abort = Test_and_options & ABORT; // 0x2000
    int16 Test  =  Test_and_options & 0xBFFF; // exclude ABORT 
    int16 idx   = 0; 

    if(Abort) ClearAllSEB();
     else 
     {  // { -1 = turn off items 0, 1, 2, 3 at end of test; -2 = leave them on.}
//        setoutp( (void *)SEB_debug_out_array[dbg02_enum] ); // debug LED
//        sprintf(src,"[4a]=%d", GenericTests[Test].Gen_outputs_to_make[4] );
//                Log_an_event(src);
         if(GenericTests[Test].Gen_outputs_to_make[4] == -1) // if A
         { // turn off
             for(idx = 0; idx < 4; idx++)
             {  // sprintf(src,"idx=%d io=%d ",idx, GenericTests[Test].Gen_outputs_to_make[idx] );
                // Log_an_event(src);
		    	if( GenericTests[Test].Gen_outputs_to_make[idx] >= 0)
		    	{  // setoutp( (void *)SEB_debug_out_array[dbg03_enum] ); // debug LED
		    		clroutp((void *)SEB_outputs_array[ GenericTests[Test].Gen_outputs_to_make[idx] ]);
		    		if(GenericTests[Test].Gen_outputs_to_make[idx] < 6) // Debug facility
		    		{ // These are not going to SEB and thus can not see if on by looking at LED on SEB.
		    		  // Therefore, send these sets to the GALX4-0047N so that for SW debug, the LEDs can be seen
		    		  // O_LDO6_enum
		    		    clroutp((void *)SEB_outputs_array[ GenericTests[Test].Gen_outputs_to_make[idx] + O_LDO6_enum ]);	
		    		}
		    	}             	
             }                      	
         } // end of "if A"
     	sprintf(src,"[4b]=%d", GenericTests[Test].Specific_outputs_to_make[4] );
                Log_an_event(src);
         if(GenericTests[Test].Specific_outputs_to_make[4] == -1) // if B
         { // turn off
             for(idx = 0; idx < 4; idx++)
             {  // sprintf(src,"IDX=%d IO=%d ",idx, GenericTests[Test].Gen_outputs_to_make[idx] );
                // Log_an_event(src);
		    	if( GenericTests[Test].Specific_outputs_to_make[idx] >= 0)
		    	{ // setoutp( (void *)SEB_debug_out_array[dbg04_enum] ); // debug LED
		    		clroutp((void *)SEB_outputs_array[ GenericTests[Test].Specific_outputs_to_make[idx] ]);
		    		if(GenericTests[Test].Specific_outputs_to_make[idx] < 6)
		    		{ // These are not going to SEB and thus can not see if on by looking at LED on SEB.
		    		  // Therefore, send these sets to the GALX4-0047N so that for SW debug, the LEDs can be seen
		    		  // O_LDO6_enum
		    		    clroutp((void *)SEB_outputs_array[ GenericTests[Test].Specific_outputs_to_make[idx] + O_LDO6_enum ]);	
		    		}
		    	}             	
             }                      	
         } // end of "if B"     	     	     	
     } // end of else     
}

int16 Standard_Init(int16 Clear_msg_Boards, int16 Stnd_Time_Delay)
{
            clr_lcd_dply();
//          Clear_Msg_Board();
			Clear_All_Boards(Clear_msg_Boards); // bit 0 for A; bit 1 for B; bit 2 for C
            CurrentTestPassFail =0;  // fail
            Retest_Option_Parm = 0; 
            RetestResponse = 1;
            Delay_Count = 3; 
            timers[t_Generic_Delay] = 0;
            return CONTINUE_SERVICE;
}

//     'Prelim_Failure_msg[]'  and 'Final_Failure_msg[]'
// and 'Prelim_Failure_msgs[]' and 'Final_Failure_msgs[]'

int16 Send_Failure_msgs_to_msg_brd_A(int16 Prelim_or_Final, int16 Test_with_Options)
{ // Log_an_event(src);
	int16 wbg_index = 0;
	int16 which_array = Prelim_or_Final;
    int16 Test = Test_with_Options & 0x3fff; // discard bits 15 and 14
    int16 SW_Options = Test_with_Options & 0xC000; // set options to bits 15 and 14	
		
	switch (which_array)
	{ // SW_Options not yet used.
		case 0: // Preliminary test
		    for (wbg_index = 0; wbg_index < 4; wbg_index++)
		    {
		        if(GenericTests[Test].Prelim_Failure_msg[wbg_index] >= 0)
		        {
		            Log_an_event( (char *)Failure_msgs[ GenericTests[Test].Prelim_Failure_msg[wbg_index] ] );   
		        }		           	
		    }		
		    break;
		   
		case 1: // Final test
		    for (wbg_index = 0; wbg_index < 4; wbg_index++)
		    {
		        if(GenericTests[Test].Final_Failure_msg[wbg_index] >= 0)
		           	Log_an_event( (char *)Failure_msgs[ GenericTests[Test].Final_Failure_msg[wbg_index] ] );
		    }		
		    break;

		default: 
		    break;		    		    		    
	} // end of "switch (which_array)"    

    return 0;
}

//    int16  Initial_output_Item[4]; // Before starting test, set these items to the
//    int16  Initial_output_State[4];

void Setup_Initial_SEB_States(int16 index_to_Generic_Test)
{
    int16 wbg_idx = 0;
    int16 OnOff = 0;
    int16 Item_to_set = 0;
    
    for(wbg_idx = 0; wbg_idx < 4; wbg_idx++)
    {
        Item_to_set = GenericTests[index_to_Generic_Test].Initial_output_Item[wbg_idx];
        OnOff       = GenericTests[index_to_Generic_Test].Initial_output_State[wbg_idx];
        
        if( Item_to_set >= 0) 
        {
            if(OnOff == 1) setoutp((void *)
                SEB_outputs_array[ GenericTests[index_to_Generic_Test].Initial_output_Item[wbg_idx] ]); 
            else clroutp((void *)
                SEB_outputs_array[ GenericTests[index_to_Generic_Test].Initial_output_Item[wbg_idx] ]);
        }
    }
}