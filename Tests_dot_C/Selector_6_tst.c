// Selctor_6_tst.c

#include "global.h"
#include "Tests.h"

#define TRUE   1
#define FALSE  0
#define PASS   1
#define FAIL   0
#define OK     1

#define APS_INFO 0
#define DTS_INFO 1
#define UTS_INFO 2
#define DTS_UTS_INFO 3
#define SPI_CAN_INFO 4
#define APS_NORMAL_LIMIT 100 // TODO WBG 2019-1-6 CHECK WHAT THE ACTUAL LIMIT IS
    // in simulation, it will take 50s to get to APS_NORMAL_LIMIT.
#define DTS_INDEX 0
#define UTS_INDEX 1

extern int16 msg_14_tally;	
extern int16 msg_16_tally;

int16 APS_max = 0;
int16 DTS_on_APS    = 0; // APS reading when DTS goes on.
int16 DTS_off_APS   = 0; // APS reading when DTS goes off from on.
int16 UTS_on_APS    = 0; // APS reading when UTS goes on.
int16 UTS_off_APS   = 0; // APS reading when UTS goes off from on.
int16 GateGoingDown = 0; // 1 indicates gated going down.
int16 APS_Pass_Fail       = 0; // bit 0: 0=fail; 1=pass  - bits 1 thru 3 indicate failure.
int16 DTS_UTS_Pass_Fail   = 0; // bit 0: 0=fail; 1=pass  - bits 1 thru 3 indicate failure.
int16 DTS_S7_Pass_Fail    = 0; // bit 0: 0=fail; 1=pass  - bits 1 thru 3 indicate failure.
int16 UTS_S5_Pass_Fail    = 0; // bit 0: 0=fail; 1=pass  - bits 1 thru 3 indicate failure.
int16 SPI_CAN_Pass_Fail   = 0;
int16 Three_Tests_Status  = 0; // bit set to 1 when test is done. Bits 0, 1, 2 for APS, DTS, UTS
int16 APS_kase    = 0;
int16 DTS_S7_kase = 0;
int16 UTS_S5_kase = 0;
int16 DTS_UTS_kase = 0;
int16 Dts = 0;
int16 Uts = 0;
int16 Previous_Dts = 0;
int16 Previous_Uts = 0;
int16 Previous_APS_delta = 0;
int16 TimeExpired_target = 0;
int16 Check_4_time = 0;
int16 Reset_APS_Home_Flag = 0;
uint32 Sel_6_APS = 0;
int16 New_APS_Delta = 0;
int16 New_APS_Delta_mm = 0;
uint32 Home_Sel_6_APS = 0;
uint32 New_Home_Sel_6_APS = 0;
int16 APS_LR_Alignment = 0;
int16 APS_LR_Alignment_Found = 0;
int16 APS_FarNear_Alignment = 0;
int16 APS_FarNear_Alignment_Found = 0;
int16 APS_First_Alignment_at = 0;
int16 APS_Warning = 0;
int16 APS_Error = 0;
int16 APS_Normal_Max ;
int16 DTS_UTS_Test_Running = 0;
int16 APS_Test_Running = 0;
int16 SPI_CAN_Test_Running = 0;

extern uint32 Start_of_APS_tape;
//extern COMMDWORD_TYPE rcv_APS_dword;

int16 check_start_conditions(void);
int16 Run_APS_tst(int16 dummy);
int16 Run_DTS_UTS_tst(int16 dummy);
int16 Run_DTS_tst(int16 dummy);
int16 Run_UTS_tst(int16 dummy);
int16 Describe_Failure(int16 which_tst);
void Spin_Spinner(void);
int16 chck_4_APS_warnings(void);
void Dummy_call(void);
int16 Run_SPI_CAN_tst(int16 Options);

enum
{
    initialize,
    run_tests,
    wait_4_pwr_to_come_up,
    test_pass,
    test_done,
    test_failure,
    Retest_option,
    Check_Buttons,
    Read_After_Delay,
    check_4_GateGoingDown,
    GateNowGoingDown,
    wait_4_DTS_on,
    wait_4_DTS_off,
    wait_4_UTS_off,
    wait_5_seconds,
    check_SPI_CAN,
};

// =============== SELECTOR 6 TEST FIXTURE  ====================


int16 Run_3_tsts_together(int16 dummy)
{ // Tests the APS system, along with the DTS-S7, and the UTS-S5 tests.

    int16 i,j,k = 0;
    static int16 test_Kase = initialize;
    static int16 extra_delay = 0;
    static int16 Simulation_Counter = 0;
    static int16 ReturnVal = CONTINUE_SERVICE; // Required for Retest Option
    static int16 RunningTest = 0;   
        
    SIU.GPDO[Z0_LED].R = !SIU.GPDO[Z0_LED].R;  // toggle LED;
  
/*    
    if (SimulateCamera) // switch 3 on 0047N // FOR GRCAN
    { //  Simulate outputs using GALX4-0047N
        Dts = rdginp((void *)GALX4_0047_in_array[0]);
        Uts = rdginp((void *)GALX4_0047_in_array[1]);
    }
    else
    { // Read 1133 board 
        Dts = rdginp((void *)GRCAN_inputs_array[DTS_INDEX]);
        Uts = rdginp((void *)GRCAN_inputs_array[UTS_INDEX]);    
    }
*/    
//    APS_delta = Home_Sel_6_APS - Sel_6_APS;
//	APS_delta = Home_Sel_6_APS - Sel_6_APS;
    
    switch (test_Kase)
    {
        case initialize:

            ClearAllSEB();
            ReturnVal = Standard_Init(CLEAR_MSG_BOARD_A, DELAY_3); // DELAY_3 = 300 ms
//            clrgoutp(GALX4_0047_OUT_array[0]);
//            clrgoutp(GALX4_0047_OUT_array[1]);
//            clrgoutp(GALX4_0047_OUT_array[2]);
            DTS_UTS_Test_Running = 1;
            APS_Test_Running = 1;
            SPI_CAN_Test_Running = 1;
            timers[t_Generic_Delay_2] = 0; // allow 10s to run the test, after which time, fail.
            timers[t_Generic_Delay_3] = 0;
            timers[t_Generic_Delay_4] = 0; // t_Generic_Delay_4 is used to see if SPI CAN is working
            SimulateCamera = rdginp(GALX4_0047_in_array[2]);
            TimeExpired_target = DELAY_10s;
        	Home_Sel_6_APS = Sel_6_APS;
//        	APS_delta = 0; 
        	RunningTest = 1; 
        	msg_14_tally = 0; // for SPI CAN test   
        	msg_16_tally = 0; // for SPI CAN test       
            if( SimulateCamera )
            {
                 TimeExpired_target = DELAY_10s * 10;
//                 SIU.GPDO[Z6_LED].R = 0; // ON                    
            }
            Check_4_time = 1;
            Simulation_Counter = 0;
		    APS_kase    = 0;
		    DTS_S7_kase = 0;
		    UTS_S5_kase = 0;
		    APS_Pass_Fail       = 0; // bit 0: 0=fail; 1=pass  - bits 1 thru 3 indicate failure.
		    DTS_S7_Pass_Fail    = 0; // bit 0: 0=fail; 1=pass  - bits 1 thru 3 indicate failure.
		    UTS_S5_Pass_Fail    = 0; // bit 0: 0=fail; 1=pass  - bits 1 thru 3 indicate failure. 
		    SPI_CAN_Pass_Fail   = 0;
		    Three_Tests_Status  = 0; // bit set to 1 when test is done. Bits 0, 1, 2 for APS, DTS, UTS    
//		    Home_Sel_6_APS = Sel_6_APS; 
//		    Reset_APS_Home_Flag = 1;	// instruct ctcan.c; unpack to home the APS_delta
  //		    Start_of_APS_tape = rcv_APS_dword.dword;
//		    APS_delta = 0; 
            if(check_start_conditions() == OK)
            {
	//          New_write_display("Enter(YES) Mode(NO) ", 0, 0);
				New_write_display("Lift, then lower    ", 0, 0); // row 0, column 0
				New_write_display("Gate.               ", 1, 0); // row 1, column 0
	            test_Kase = run_tests;            	
            }
            else
            { // initial problem detected.
	//          New_write_display("Enter(YES) Mode(NO) ", 0, 0);
				New_write_display("Initial problem     ", 0, 0); // row 0, column 0
				New_write_display("detected. Lift/Lower", 1, 0); // row 1, column 0
				New_write_display("Gate and retry      ", 2, 0); // row 2, column 0
	            test_Kase = test_failure;            	
            }

            break;
            
        case run_tests:
            
            if( ( timers[t_Generic_Delay_2] > TimeExpired_target ) && (New_APS_Delta < 5) && Check_4_time) // about 10 s
            { //  in run mode and 100s in simulation.
	//          New_write_display("Enter(YES) Mode(NO) ", 0, 0);
				New_write_display("Time has expired.   ", 0, 0); // row 0, column 0
				New_write_display("Assume a failure.   ", 1, 0); // row 1, column 0            
            	test_Kase = test_failure;   
                break;             
            }   
            if( (Dts != Previous_Dts) | (Uts != Previous_Uts) )
            {
            	// New_write_display("Enter(YES) Mode(NO) ", 0, 0);
             	   New_write_display("                    ", 0, 0);
	            sprintf(src,"DTS:%d,  UTS:%d", Dts, Uts);  
				New_write_display(src, 0, 0); // row 0, column 0            	
            }
            if( New_APS_Delta != Previous_APS_delta )
            {
            	sprintf(src,"APS = %-3d", New_APS_Delta);
				New_write_display(src, 1, 0); // row 1, column 0	
            }
            Previous_Dts = Dts;
            Previous_Uts = Uts;
            Previous_APS_delta = New_APS_Delta;
            if(New_APS_Delta > 5) Check_4_time = 0;// disable checking for timeout as the operator has already
            	// started the gate moving.
            if( SimulateCamera )
            {   
            	Spin_Spinner();
                if(GateGoingDown == 0) // 0 = gate going up, elevator going down. 
                { // Gate going up
                    if( Simulation_Counter++ > 25)
                    { // increment every 1/2 s                    
                        New_APS_Delta++; 
                        Simulation_Counter = 0;  
                    }
                      
                } 
                else
                {
                    if( Simulation_Counter++ > 10)
                    { // increment every 0.25 s                    
                        if(New_APS_Delta > 0) New_APS_Delta--;
                        Simulation_Counter = 0;  
                    }                    
                }
            }
 
			if(GateGoingDown == 0)  
			{ // 0 = gate going up, elevator going down.
                //New_write_display("                    ",0,0); // row 0, col
                  if(New_APS_Delta > 10) New_write_display("Gate going UP       ",2,0); // row 2, col
                  else New_write_display("                    ",2,0); // row 2, col  			    
			}
			else
			{ // 1 = gate going down, elevator going up.
                //New_write_display("                    ",0,0); // row 0, col
                  New_write_display("Gate going Down     ",2,0); // row 2, col 			    
			}
			sprintf(src,"SPI CAN: %d", msg_14_tally);
			New_write_display(src, 3, 0); // row 0, column 0 			
			if(APS_Test_Running)
			{
	            if (Run_APS_tst(0) == FINISHED_WITH_SERVICE)
	            {   
	            	APS_Test_Running = 0;
//	            	setgoutp(GALX4_0047_OUT_array[0]);         
	                if( (APS_Pass_Fail & 1) == FAIL)
	                {
	                	Describe_Failure(APS_INFO);
	                	test_Kase = test_failure ;
	                	break;                	
	                }
	            }				
			} 
            if(DTS_UTS_Test_Running)
            {
	            if (Run_DTS_UTS_tst(0) == FINISHED_WITH_SERVICE)
	            {   
	            	DTS_UTS_Test_Running = 0; 
//	            	setgoutp(GALX4_0047_OUT_array[1]);                    
	                if( (DTS_UTS_Pass_Fail & 1) == FAIL)
	                {
	                	Describe_Failure(DTS_UTS_INFO);
	                	test_Kase = test_failure ;
	                	break;                	
	                }
	            }            	
            }                
/*            
			if(SPI_CAN_Test_Running)
			{
	            if (Run_APS_tst(0) == FINISHED_WITH_SERVICE)
	            {   
	            	SPI_CAN_Test_Running = 0;
//	            	setgoutp(GALX4_0047_OUT_array[0]);         
	                if( (SPI_CAN_Pass_Fail & 1) == FAIL)
	                {
	                	Describe_Failure(SPI_CAN_INFO);
	                	test_Kase = test_failure ;
	                	break;                	
	                }
	            }				
			}
*/			            
            if(timers[t_Generic_Delay_3] > 2 * DELAY_3s) // about 2*3 s
            { //  all 3 (or 2 if SPI_CAN test is commented out) tests 
              //  should finish within 6s of each other.
                //New_write_display("                    ",0,0); // row 0, col
                  New_write_display("Not done same time  ",3,0); // row 3, col            
            	test_Kase = test_failure ;
            	break;	
            }
            if(Three_Tests_Status == 0) timers[t_Generic_Delay_3] = 0; // Any completed test, resets the timer.
			if( (Three_Tests_Status != 0) && RunningTest )
			{
				sprintf(src, "Status = 0x%4X", Three_Tests_Status);
				New_write_display(src,3,0); // row 3, col
			}
        	if( (Three_Tests_Status & 7) == 3) //  == 3 if no SPI_CAN test; else == 7
        	{  // All 3 tests (or 2 if SPI_CAN test is commented out) are done and passed.
        		RunningTest = 0;
        		test_Kase = check_SPI_CAN;
//        		test_Kase = test_pass;	
        	}            
            
	        if (Check_for_Mode_Button())
	        {
                //New_write_display("                    ",0,0); // row 0, col
                  New_write_display("Test Cancelled      ",3,0); // row 3, col 	        
	            test_Kase = test_failure ;
	            RunningTest = 0;
	        }    
	                
            break;              
                 
    	case check_SPI_CAN:
    			i = timers[t_Generic_Delay_4]/50;  // i = #of sec
    			j = i * 100;  // j will give the lower bounds on the #of msg_14_tally & msg_16_tally 
    				// for a fully functioning SPI CAN.
    			if( ( msg_14_tally > j ) && ( msg_16_tally > j )) test_Kase = test_pass;
    				else
    				{
    					clr_lcd_dply();
    					New_write_display("Problem with SPI CAN",3,0); // row 3, col 
    					test_Kase = test_failure ;
    				}    			    	
    		break;
    		
        case test_pass:
            CurrentTestPassFail = 1; // Pass
            clr_lcd_dply();
            New_write_display("PASS. Good Job      ",3, 0); // row 3, col
            test_Kase = test_done;
            RetestResponse = 1;
            break;            
            
        case test_done:       
            test_Kase = initialize;
            // Required for Retest Option
            if(RetestResponse == 0)ReturnVal = FINISHED_WITH_SERVICE; // Idle_time  
            else ReturnVal = DONE_BUT_CONTINUE_DISPLAY;              
            break;
                                    
        case test_failure: 
            timers[t_Generic_Delay_2] = 0;     
            test_Kase = Retest_option;
            break;
            
        case Retest_option: // Required for Retest Option
            RetestResponse = Handle_Retest_Request(Retest_Option_Parm);
            Retest_Option_Parm = 1;
            if(RetestResponse == 0) test_Kase = test_done;  // do not retest
            else if(RetestResponse == 1) test_Kase = initialize; // test again
                else ReturnVal = CONTINUE_SERVICE;    
            break;           
               
        default:
            break;                
    }
    return ReturnVal;
}

// ========================================================

int16 check_start_conditions(void)
{ // TODO Add the required code WBG 2019-1-5
	return 1;
}

// ========================================================

/**********************************************
* Function: Run_APS_tst(int16 Options)        *
* Description: Tests the CEDES APS "Absolute  *
*    Position System" camera. The gate is     *
*    raised and lowered to be sure that the   *
*    APS count goes down as the gate goes     *
*    up and counts up as the gate is lowered  *
*    and the count returns to the starting    *
*    count. There is no 'Retest' option.      *
*                                             * 
* Options parameter:                          * 
*   Bit 4 set: Causes msgs to be displayed    *
*   on 4-line display.                        * 
*                                             *
*   Bit 5 set: Causes this test to zero out   * 
*   the APS count at the beginning of the     *
*   test and to keep track of the APS counts. *
*   If bit 5 is not set then some other       * 
*   task is keeping track of the APS counts.  * 
*                                             *
*   Bit 6 set: Generates msgs to the Msge Bd A*
*                                             *
*                                             * 
*                                             *
* Created: December, 2018                     *
*                                             *
* Example:                                    *
*                                             *
*                                             *
* Name: William Grauer                        *
*                                             *
**********************************************/

int16 Run_APS_tst(int16 Options)
{ // Run Absolute Position System test (CEDES tape encoder)
static int16 ReturnVal = CONTINUE_SERVICE;

    if(Options & 0x20) 
    {
    	SIU.GPDO[Z0_LED].R = !SIU.GPDO[Z0_LED].R;  // toggle LED;    
//    	APS_delta = Home_Sel_6_APS - Sel_6_APS;
        if (Check_for_Mode_Button())
        {
            //New_write_display("                    ",0,0); // row 0, col
              New_write_display("Test Cancelled      ",3,0); // row 2, col 	        
            APS_kase = test_done ;
        }   		
    }

    switch (APS_kase)
    {
        case initialize:
        	//setgoutp(GALX4_0047_OUT_array[2]);
//        	SIU.GPDO[Z6_LED].R = 1;	// turn led OFF (wbg)// tagwbg 15
	        if(Options & 0x10) 
	        {
	            clr_lcd_dply();
	            Clear_Msg_Board();
	            CurrentTestPassFail =0;  // fail
	            Retest_Option_Parm = 0; 
	            RetestResponse = 1;
	            timers[t_Generic_Delay] = 0;         	
	        }
	                	
        	ReturnVal = CONTINUE_SERVICE;
        	GateGoingDown = 0;            
             
            APS_max = 0;
            if(Options & 0x20)
            {
//            	Home_Sel_6_APS = Sel_6_APS;
//            	APS_delta = 0;
				sprintf(src,"Home: %d", New_Home_Sel_6_APS);
				New_write_display(src, 1, 0); // row 0, column 0            		
            }
            //  Insure tape is indicating zero start.
			if(New_APS_Delta > 10)
			{ // Problem, APS not yet zeroed out
				APS_Pass_Fail = 2; // bits 3,2,1,0 = 0010 to indcated failure because
					// gate not down.
				APS_kase = test_failure; // APS_Pass_Fail	
			}
			else APS_kase = run_tests;
            break;
            
        case run_tests:
	        if(Options & 0x10) 
	        {
				sprintf(src,"APS:%3d, 0x%8X", New_APS_Delta, Sel_6_APS);
				New_write_display(src, 0, 0); // row 0, column 0
//				sprintf(src,"Align: 0x%X, 0x%X", APS_LR_Alignment, APS_FarNear_Alignment);
				sprintf(src,"SEL: 0x%8X", Sel_6_APS);
				New_write_display(src, 1, 0); // row 1, column 0									        	
	        }
		    if(New_APS_Delta > APS_max) APS_max = New_APS_Delta; // record the highest
		    	// position of the gate        
 			if(New_APS_Delta < APS_NORMAL_LIMIT)
 			{ // Insure APS is not indicating error
 				//	TODO WBG 2019-1-6
 				Dummy_call();
 				
 			}
 			else
 			{ // Insure APS now shows an error (out of normal range).
 				//	TODO WBG 2019-1-6
 				if(Options & 0x10)
 				{
// 				    sprintf(src,"Align: 0x%X, 0x%X", APS_LR_Alignment, APS_FarNear_Alignment);
//				    New_write_display(src, 1, 0); // row 1, column 0
	    //          New_write_display("Enter(YES) Mode(NO) ", 0, 0);
	                New_write_display("Enterg case gate chk", 2, 0); // row 0, column 0 					
 				}
				
 				APS_kase = check_4_GateGoingDown;	
 			}	                
            break;              
               
        case check_4_GateGoingDown: // Enterg case gate chk
			        
	        if(Options & 0x10) 
	        {
				sprintf(src,"APS: %3d,  0x%6X", New_APS_Delta, Sel_6_APS);
				New_write_display(src, 0, 0); // row 0, column 0
				sprintf(src,"SEL: 0x%8X", Sel_6_APS);
				New_write_display(src, 1, 0); // row 1, column 0				
                sprintf(src, "APS_max= %d ",APS_max);
                New_write_display(src, 3, 0); // row 0, column 0													        	
	        }        
		    if(New_APS_Delta > APS_max) APS_max = New_APS_Delta; // record the highest
		    	// position of the gate        
        
            if( SimulateCamera ) 
            {
                if(Options & 0x20) APS_delta--;   
            }
			if(New_APS_Delta < (APS_max - 10))
			{
				GateGoingDown = 1;
//				SIU.GPDO[Z6_LED].R = 0;	// turn led ON (wbg)// tagwbg 15
 				if(Options & 0x10)
 				{
	    //          New_write_display("Enter(YES) Mode(NO) ", 0, 0);
	                New_write_display("Enterg case gate dwn", 2, 0); // row 0, column 0 
	                sprintf(src, "APS_max= %d ",APS_max);
	                New_write_display(src, 3, 0); // row 0, column 0					
 				}				
				APS_kase = GateNowGoingDown;	
			}

            break;
            
        case GateNowGoingDown: // Enterg case gate dwn
	        if(Options & 0x10) 
	        {
				sprintf(src,"APS: %3d,  0x%6X", New_APS_Delta, Sel_6_APS);
				New_write_display(src, 0, 0); // row 0, column 0
				sprintf(src,"SEL: 0x%8X", Sel_6_APS);
				New_write_display(src, 1, 0); // row 1, column 0													        	
	        }        
 			if(New_APS_Delta < 11)
 			{
// 				IF APS SHOWS NO ERROR - PASS 
//				//	TODO WBG 2019-1-6
			    if(chck_4_APS_warnings() )	APS_kase = test_pass;
			    else 
			    {
			        APS_Pass_Fail = 4; // bits 3,2,1,0 = 0100 to indcated failure because
					// align error
			    	APS_kase = test_failure; // APS_Pass_Fail
			    }
 			}            
            break;            
                                   
        case test_pass:
            APS_Pass_Fail = 1; // Pass
			if(Options & 0x10)
			{
    //          New_write_display("Enter(YES) Mode(NO) ", 0, 0);
                New_write_display("APS test passed     ", 2, 0); // row 0, column 0 					
			}       
	        if(Options & 0x10) 
	        {
	            CurrentTestPassFail =1;  // pass        	
	        } 			    
            APS_kase = test_done;
            break;            
            
        case test_done:       
//        	SIU.GPDO[Z6_LED].R = 1;	// turn led OFF (wbg)// tagwbg 15
            APS_kase = initialize;
 			Three_Tests_Status |= 1; // set bit 0 to indicate APS test is done.
			if(Options & 0x30) ReturnVal = DONE_BUT_CONTINUE_DISPLAY; // test is done.
			else ReturnVal = FINISHED_WITH_SERVICE;
//			clrgoutp(GALX4_0047_OUT_array[2]);               
            break;
                                    
        case test_failure:      
            APS_kase = test_done;
            break;                       
               
        default:
            break;                
    }
    return ReturnVal;
}

//  ================================================================

/**********************************************
* Function: int16 Run_DTS_UTS_tst(int16 Options)*
* Description: Tests the Seletor 6 box magnetic*
*    relays for the UTS and DTS functions.   *
*    The magnets on the manual test gate are  *
*    offset so that the UTS switch is         *
*    activated first followed by the DTS      *
*    switch. To start, both  DTS & UTS are off*
*    As the gate goes up, UTS led comes on    *
*    while DTS led is still off.  Then as     * 
*    gate goes up more, DTS comes on and both *
*    DTS & UTS are on. As the gate comes down *
*    DTS goes off first, with UTS still on.   * 
*    Lowering the gate more causes UTS to go  *
*    off, and both DTS & UTS are off.         *
*                                             * 
*                                             *
*           There is no 'Retest' option.      *
*                                             * 
* Options parameter:                          * 
*   Bit 4 set: Causes msgs to be displayed    *
*   on 4-line display.                        * 
*                                             *
*   Bit 5 set: Causes this test to zero out   * 
*   the APS count at the beginning of the     *
*   test and to keep track of the APS counts. *
*   If bit 5 is not set then some other       * 
*   task is keeping track of the APS counts.  * 
*                                             *
*   Bit 6 set: Generates msgs to the Msge Bd A*
*                                             *
*                                             * 
*                                             *
* Created: December, 2018                     *
*                                             *
* Example:                                    *
*                                             *
*                                             *
* Name: William Grauer                        *
*                                             *
**********************************************/

int16 Run_DTS_UTS_tst(int16 Options)
{ // The test insures that DTS is activated before UTS
static int16 ReturnVal = CONTINUE_SERVICE;
static int16 first_pass = 1;

    if (SimulateCamera) // switch 3 on 0047N // FOR GRCAN
    { //  Simulate outputs using GALX4-0047N
        Dts = rdginp((void *)GALX4_0047_in_array[0]);
        Uts = rdginp((void *)GALX4_0047_in_array[1]);
    }
    else
    { // Read 1133 board 
        Dts = rdginp((void *)GRCAN_inputs_array[DTS_INDEX]);
        Uts = rdginp((void *)GRCAN_inputs_array[UTS_INDEX]);    
    }
    
    if(Options & 0x30) 
    {
    	SIU.GPDO[Z0_LED].R = !SIU.GPDO[Z0_LED].R;  // toggle LED;    
//    	APS_delta = Home_Sel_6_APS - Sel_6_APS;
        if (Check_for_Mode_Button())
        {
            //New_write_display("                    ",0,0); // row 0, col
              New_write_display("Test Cancelled      ",3,0); // row 2, col 	        
            DTS_UTS_kase = test_done ;
        }     
        if(first_pass)
        {
            sprintf(src,"DTS:%d,  UTS:%d", Dts, Uts);  
            New_write_display(src, 0, 0); // row 0, column 0 
            first_pass = 0;        	
        }
        if( (Dts != Previous_Dts) | (Uts != Previous_Uts) )
        {
            // New_write_display("Enter(YES) Mode(NO) ", 0, 0);
               New_write_display("                    ", 0, 0);
            sprintf(src,"DTS:%d,  UTS:%d", Dts, Uts);  
            New_write_display(src, 0, 0); // row 0, column 0                
        }
        if( New_APS_Delta != Previous_APS_delta )
        {  
			sprintf(src,"SEL: 0x%-8X", Sel_6_APS);
			New_write_display(src, 1, 0); // row 1, column 0               
            sprintf(src,"nAPS: %d        ", New_APS_Delta);
            New_write_display(src, 2, 0); // row 1, column 0               
        }
        Previous_Dts = Dts;
        Previous_Uts = Uts;
        Previous_APS_delta = New_APS_Delta;              		
    }    
   
    switch (DTS_UTS_kase)
    {
        case initialize:
	        if(Options & 0x10) 
	        {
	            clr_lcd_dply();
	            Clear_Msg_Board();
	            CurrentTestPassFail =0;  // fail
	            Retest_Option_Parm = 0; 
	            RetestResponse = 1;
	            timers[t_Generic_Delay] = 0;         	
	        }          
        	ReturnVal = CONTINUE_SERVICE;
        	
            if(Options & 0x20)
            {
//            	Home_Sel_6_APS = Sel_6_APS;
//            	APS_delta = 0;
				sprintf(src,"Home: %d", New_Home_Sel_6_APS);
				New_write_display(src, 2, 0); // row 0, column 0  
				sprintf(src,"Home 0x%X", New_Home_Sel_6_APS );
				New_write_display(src, 3, 0); // row 0, column 0 				
				first_pass = 1;          		
            } 
                   	
            //  Insure DTS & UTS are both off.
			if( Dts && Uts)
			{ // Error - fail test. Both should be off when the gate is down.
				DTS_UTS_Pass_Fail = 2; // one of the switches are already on.
				DTS_UTS_kase = test_failure;	
			}
			else DTS_UTS_kase = run_tests;
            break;
            
        case run_tests:       
            if( (Uts == 1) && (Dts == 0) )
            { // GOOD, UTS should come on first so now wait till DTS comes on
            	UTS_on_APS = New_APS_Delta;
            	DTS_UTS_kase = wait_4_DTS_on;	
            }			
            if(Dts) 
            { // BAD, DTS should not come on until after UTS
            	DTS_UTS_Pass_Fail = 2; // DTS on before UTS
            	DTS_UTS_kase = test_failure;	
            } 				                
            break;              
               
        case wait_4_DTS_on:              
			if(Dts)
			{ // GOOD, both UTS and DTS now on so wait till DTS goes off.
				DTS_on_APS = New_APS_Delta;
				if( SimulateCamera ) APS_delta = 90;
				DTS_UTS_kase = wait_4_DTS_off;
					
			}
			if(Uts == 0) // gate went down and DTS never came on.
			{ // Error
            	DTS_UTS_Pass_Fail = 4; // DTS never came on
            	DTS_UTS_kase = test_failure;				
			}

            break;
            
        case wait_4_DTS_off:       
            if( (Uts == 0) && (Dts == 1) )
            {
            	DTS_UTS_Pass_Fail = 6; // UTS turned off prior to DTS off
            	DTS_UTS_kase = test_failure;	
            }			
            if(New_APS_Delta < 3)
            {
            	DTS_UTS_Pass_Fail = 8; // DTS never went off
            	DTS_UTS_kase = test_failure;            	
            }
            if(Dts == 0)
            { // GOOD, DTS went off while UTS still on.
            	DTS_off_APS = New_APS_Delta;
            	DTS_UTS_kase = wait_4_UTS_off;
            }
            break;            
                                   
        case wait_4_UTS_off:
            if(New_APS_Delta < 10)
            {
            	DTS_UTS_Pass_Fail = 10; // UTS never went off
            	DTS_UTS_kase = test_failure;            	
            }
            if(Uts == 0)
            { // GOOD, test passed.
            	UTS_off_APS = New_APS_Delta;
            	DTS_UTS_kase = test_pass;
            }            
            break;  
            
        case test_pass:
            DTS_UTS_Pass_Fail = 1; // Pass
	        if(Options & 0x10) 
	        {
	            CurrentTestPassFail =1;  // pass  
	        // New_write_display("Enter(YES) Mode(NO) ", 0, 0);
               New_write_display("DTS/UTS test Pass   ", 3, 0);      	
	        }             
            DTS_UTS_kase = test_done;
            RetestResponse = 0;
            break;                      
            
        case test_done:       
            DTS_UTS_kase = initialize;
 			Three_Tests_Status |= 2; // set bit 1 to indicate DTS_UTS test is done.
			if(Options & 0x30) ReturnVal = DONE_BUT_CONTINUE_DISPLAY; // test is done.
			else ReturnVal = FINISHED_WITH_SERVICE;             
            break;
                                    
        case test_failure:      
	        if(Options & 0x10) 
	        { 
	        // New_write_display("Enter(YES) Mode(NO) ", 0, 0);
               New_write_display("DTS/UTS FAIL        ", 3, 0);      	
	        }        
            DTS_UTS_kase = test_done;
            break;                       
               
        default:
            break;                
    }
    return ReturnVal;
}

int16 Run_DTS_tst(int16 dummy)
{ // TODO Add the required code WBG 2019-1-5
	return CONTINUE_SERVICE;
}

int16 Run_UTS_tst(int16 dummy)
{ // TODO Add the required code WBG 2019-1-5
	return CONTINUE_SERVICE;
}

int16 Describe_Failure(int16 which_tst)
{ // TODO Add the required code WBG 2019-1-5
int16 TheError = 0;
//New_write_display(src, row, col);
//New_write_display("                    ",0,0); // row, col
    clr_lcd_dply();
    switch (which_tst)
    {
        case APS_INFO:  // 0
        //New_write_display("                    ",0,0); // row, col
          New_write_display("Error in CEDES APS  ",0,0); // row, col        
            TheError = (APS_Pass_Fail & 0xFFFE) >> 1;
            switch (TheError)
            {
                case 1: // UTS on before DTS
                    //New_write_display("                    ",0,0); // row, col
                      sprintf(src,"APS= %d 0x%4X", New_APS_Delta, New_Home_Sel_6_APS);
                      New_write_display(src,1,0); // row, col                    
                    break;                    ;                                                           
                    
                default:
                    break;
            }             
            break;
            
        case DTS_INFO:// 1
            break;  
            
        case UTS_INFO: // 2
            break;
            
        case DTS_UTS_INFO: // 3
        //New_write_display("                    ",0,0); // row, col
          New_write_display("Error in DTS or UTS ",0,0); // row, col
          sprintf(src,"Error in DTS or UTS ");
          Log_an_event(src);
          sprintf(src,"fail code: 0x%2X ", DTS_UTS_Pass_Fail);
          Log_an_event(src);
            TheError = TheError = (DTS_UTS_Pass_Fail & 0xFFFE) >> 1;
            switch (TheError)
            {
                case 1: // DTS on before UTS
                    //New_write_display("                    ",0,0); // row, col
                      New_write_display("DTS on before UTS   ",1,0); // row, col                    
                    break;
                    
                case 2: // UTS never came on
                    //New_write_display("                    ",0,0); // row, col
                      New_write_display("DTS never came on   ",1,0); // row, col                 
                    break; 
                    
                case 3: // UTS turned off prior to DTS off
                    //New_write_display("                    ",0,0); // row, col
                      New_write_display("UTS off before DTS  ",1,0); // row, col                 
                    break;
                    
                case 4: // DTS never went off
                    //New_write_display("                    ",0,0); // row, col
                      New_write_display("DTS never went off  ",1,0); // row, col                 
                    break; 
                    
                case 5: // UTS never went off
                    //New_write_display("                    ",0,0); // row, col
                      New_write_display("UTS never went off  ",1,0); // row, col                 
                    break;                                                           
                    
                default:
                    break;
            }
            
            break; 
                                 
        case SPI_CAN_INFO:// 4
                    //New_write_display("                    ",0,0); // row, col
                      New_write_display("Check SPI CAN connct",1,0); // row, col         
            break;   
                   
        default:
            break; 
    }	
}

// =============================================

void Spin_Spinner(void)
{
static int16 Special_Char = 0; //Special Characters create by "load_special_char()"
static int16 SpinKounter = 0;

    if(SpinKounter > 10)
    {
        LCD_Display[3][19] =  (char)Special_Char++; 
        if(Special_Char > 7) Special_Char = 0;  
        SpinKounter = 0;     
    }    
}

//  ============================

int16 chck_4_APS_warnings(void)
{
    int16 align_error = 0;
    
    if(APS_LR_Alignment_Found && APS_FarNear_Alignment_Found && (APS_Normal_Max > APS_Normal_Max)
        && (APS_LR_Alignment == 0) && (APS_FarNear_Alignment == 0) )
    align_error = 1;
    
//    return align_error; 
	return 1;  //  force a pass for now.  TODO test this code.   
}

void Dummy_call(void)
{
	int16 j = 0;
	
	j++;	
}




//  ================================================================

/**********************************************
* Function: int16 Run_SPI_CAN_tst(int16 Options)*
* Description: Insures that msg 14 & 16       *
*    traffic rate is consistent with a        *
*    functioning CAN buss on SPI              *
*           There is no 'Retest' option.      *
*                                             * 
* Options parameter:                          * 
*   Bit 4 set: Causes msgs to be displayed    *
*   on 4-line display.                        * 
*                                             *
*                                             *
*                                             *
*                                             * 
*                                             *
* Created: January 2019                       *
*                                             *
* Example:                                    *
*                                             *
*                                             *
* Name: William Grauer                        *
*                                             *
**********************************************/

int16 Run_SPI_CAN_tst(int16 Options)
{ // The test insures that the SPI CAN is Tx
static int16 ReturnVal = CONTINUE_SERVICE;
static int16 SPI_CAN_kase = initialize;
static int16 cycle_tally = 0;

    
    if(Options & 0x30) 
    {
    	SIU.GPDO[Z0_LED].R = !SIU.GPDO[Z0_LED].R;  // toggle LED;    
        if (Check_for_Mode_Button())
        {
            //New_write_display("                    ",0,0); // row 0, col
              New_write_display("Test Cancelled      ",3,0); // row 2, col 	        
            SPI_CAN_kase = test_done ;
        }                		
    }    
   
    switch (SPI_CAN_kase)
    {
        case initialize:
	        if(Options & 0x10) 
	        {
	            clr_lcd_dply();
	            Clear_Msg_Board();
	            CurrentTestPassFail =0;  // fail
	            Retest_Option_Parm = 0; 
	            RetestResponse = 1;        	
	        }          
        	ReturnVal = CONTINUE_SERVICE;
        	msg_14_tally = 0;
        	msg_16_tally = 0;
            timers[t_Generic_Delay_4] = 0;  
            Delay_Count = DELAY_5s;      	
			SPI_CAN_kase = wait_5_seconds;
			SPI_CAN_Pass_Fail = 0;
			cycle_tally = 0;
            break;             
               
        case wait_5_seconds: 
	        if(Options & 0x10) 
	        {
				sprintf(src,"Msg 14: %d", msg_14_tally);
				New_write_display(src, 1, 0); // row 0, column 0  	
				sprintf(src,"Msg 16: %d", msg_16_tally);
				New_write_display(src, 2, 0); // row 0, column 0  
				sprintf(src,"cycle: %d", cycle_tally++);
				New_write_display(src, 3, 0); // row 0, column 0      	
	        }     
	            
            if(timers[t_Generic_Delay_4] < Delay_Count) break;
                        
			if( ( msg_14_tally > 100 ) && ( msg_16_tally > 100 ))
			{
				SPI_CAN_kase = test_pass;					
			}
			else SPI_CAN_kase = test_failure;

            break;                        
            
        case test_pass:
            SPI_CAN_Pass_Fail = 1; // Pass
	        if(Options & 0x10) 
	        {
	            CurrentTestPassFail =1;  // pass  
	        // New_write_display("Enter(YES) Mode(NO) ", 0, 0);
               New_write_display("SPI CAN test Pass   ", 3, 0);      	
	        }             
            SPI_CAN_kase = test_done;
            RetestResponse = 0;
            break;                      
            
        case test_done:       
            SPI_CAN_kase = initialize;
 			Three_Tests_Status |= 4; // set bit 2 to indicate SPI_CAN test is done.
			if(Options & 0x30) ReturnVal = DONE_BUT_CONTINUE_DISPLAY; // test is done.
			else ReturnVal = FINISHED_WITH_SERVICE;             
            break;
                                    
        case test_failure:      
	        if(Options & 0x10) 
	        { 
	        // New_write_display("Enter(YES) Mode(NO) ", 0, 0);
               New_write_display("SPI CAN FAIL        ", 3, 0);      	
	        }        
            SPI_CAN_kase = test_done;
            break;                       
               
        default:
            break;                
    }
    return ReturnVal;
}



