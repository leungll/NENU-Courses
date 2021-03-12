/*
 * Utility Library: Options
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "optionsc.h"

#include "custredc.h"

/**** NextTask **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * procedure to give a list of options to the user and get the option chosen by the
 * user which is returned
 *
 * the list of available options is defined by a function pointer given with the 
 * addition of quitting the program
 *
 * Inputs
 * ------
 *   numberOptions
 *   - the number of possible options other than exiting the program
 *     numberOptions is the end of the range 1..numberOptions
 *   Menu
 *   - a pointer to the procedure Menu which is called to print the menu of available
 *     options for the user to select from
 *     procedure takes one input - numberOptions - and returns no values
 *     it should solely print a list of options available to the end user which does 
 *     not include 0 to exit the program, that being printed after the other options
 *     by this procedure when Menu has returned  
 * Return Values
 * ------ ------
 *     unsigned int - option chosen by the user which will be between 0 and numberOptions
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int NextTask( unsigned int numberOptions, void ( *Menu )( unsigned int numberOptions ) )
{
	unsigned int option ;
	
	printf( "What do you want to do next?\n\n" ) ;

	Menu( numberOptions ) ;

	printf( "\n" ) ;
	printf( " 0. Exit the program.\n\n" ) ;

	while( 1 ) {
		printf( "Please enter your choice (0 to %d) : ", numberOptions ) ;
		option = ( int )ReadDouble( ) ;
	
		if( ( option <= numberOptions ) || ( option == 666 ) ) {
			break ;
		}
		fprintf( stderr, "That was not a valid option, please try again!\n\n" ) ;
	}

	if( option == 0 ) {
		printf( "The program will now terminate.\n\n" ) ;
	}

	return option ;
}

/**** SetStatus *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the user's choice for state of a given option and update the choice based on
 * the previous state (if exists)
 *
 * the state is either "ON" or "OFF" (1 or 0) and the procedure allows the user to 
 * enter incorrect choices in which case the previous state is maintained (if set) 
 * and default choices by hitting <return> which sets the state to "ON" if state
 * not previously set or maintains previous state is set
 *
 * Inputs
 * ------
 *   typeString
 *   - the type for the state that is being set
 *   statusString
 *   - a string that should hold the current state for the type in statusString[ 0 ]
 *     if statusString[ 0 ] == '1' the current state is on
 *     if statusString[ 0 ] == '0' the current state is off
 *     if no state has been set currently, set to anything other than '0' or '1'
 *     all other entries in string statusString are ignored
 *   limit
 *   - the length of statusString that can be used for reading in users choice
 * Outputs
 * -------
 *   statusString
 *   - the status that has been given by the user (or previous state if no change)
 *     statusString[ 0 ] == '1' indicates the state is on
 *     statusString[ 0 ] == '0' indicates the state is off
 *     all other entries in string statusString should be ignored
 * Return Values
 * ------ ------
 *     0  - the state is set to off
 *     1  - the state is set to on
 *     -1 - some error occurred (invalid input arguments)
 *          statusString[ 0 ] may still be valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int SetStatus( char typeString[ ], char *statusString, unsigned int limit )
{
    char current = statusString[ 0 ] ;
    
    if( ( !statusString ) || ( !typeString ) ) {
		fprintf( stderr, "[SetStatus] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return -1 ;
	}
	
    printf( "Please enter your choice for %s (0 = OFF, 1 = ON) : ", typeString ) ;
    ReadInString( stdin, statusString, limit ) ;
    /* read a string so that <return> can be used for default choice */
    printf( "\n" ) ;
    
    if( ( ( statusString[ 0 ] ) != '0' ) && ( ( statusString[ 0 ] ) != '1' ) ) {
        fprintf( stderr, "That was not a valid choice.\n\n" ) ;
        if( current == '1' ) {	/* keeps previous state of ON */
            fprintf( stderr, "The %s has been left as ON.\n\n", typeString ) ;
            statusString[ 0 ] = '1' ;	/* was overwritten so re-assign */
        }
        else if( current == '0' ) {	/* keeps previous state of OFF */
             fprintf( stderr, "The %s has been left as OFF.\n\n", typeString ) ;
             statusString[ 0 ] = '0' ;	/* was overwritten so re-assign */
        }
        else {	/* default */
            fprintf( stderr, "The default option for %s has been set as ON.\n\n", typeString ) ;
            statusString[ 0 ] = '1' ;
        }
    }
    else {
        if( current == statusString[ 0 ] ) {    /* state chosen same as previous */
            printf( "The %s has not been changed from its previous state of ", typeString ) ;
        }
        else { /* status changed */
            printf( "The %s has been set to ", typeString ) ;
        }
        if( statusString[ 0 ] == '1' ) {
        	printf( "ON" ) ;
        }
        else {
        	printf( "OFF" ) ;
        }
        printf( ".\n\n" ) ;
    }
    
    return( ( int )statusString[ 0 ] - 30 ) ;
}

/**** YesNo *************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * loop until the user gives a yes or no answer to a question and return the answer
 *
 * Inputs
 * ------
 *   question
 *   - an optional string that gives the question to ask the user
 *     if the string is given it is printed to the screen with a terminating '?'
 *   yes
 *   - an optional string that describes what choosing yes relates to
 *   no
 *   - an optional string that describes what no relates to
 * Return Values
 * ------ ------
 *     1 - yes
 *     0 - no
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int YesNo( char *question, char *yes, char *no )
{
	char	yesno[ 2 ] ;
	
	do {
		if( question ) {
			printf( "%s?\n\n", question ) ;
		}

        printf( "Please enter your choice (y " ) ;
        if( yes ) {
        	printf( "= '%s' ", yes ) ;
        }
        printf( "or n" ) ;
        if( no ) {
        	printf( " = '%s'", no ) ;
        }
        printf( ") : " ) ;
        ReadInString( stdin, yesno, 2 ) ;
        printf( "\n" ) ;
        
        switch( tolower( yesno[ 0 ] ) ) {
            case 'y' :
            	return 1 ;
            case 'n' :
            	return 0 ;
            default :
            	fprintf( stderr, "That was not a valid choice, choose again.\n\n" ) ;
            	break ;
        }
	} while( 1 ) ;
}

