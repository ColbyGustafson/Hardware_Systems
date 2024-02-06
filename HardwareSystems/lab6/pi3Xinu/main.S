/* TA-BOT:MAILTO your.email your.partner's.email */
/* Main program template for ARM Playground 3.2 */
/* Marquette University 2019, Department of Computer Science */

#include <arm.h>

/* Main program starts here. Put nothing before _main_:.  */
.section .text
.globl _main_
_main_:
        /* Function prolog.                                  */
       	/* Sets up environment for user program to execute.  */
        /* Push O/S state on Stack.  */
	push	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
        sub	sp, sp, #32	/* Make stack frame.  */
        /* Function prolog ends. */
        /* Start your program.   */
	bl getnum
	mov r4,r0
	mov r5,#0
	b TEST

TEST:	cmp r5,r4
	blt LOOP
	b EXIT

LOOP: 	bl getnum
	add r6,r6,r0
	add r5,r5,#1
	b TEST
	
EXIT:	mov r0,r6
	bl printnum
        /* End of your program.         */
        /* Function epilogue.           */
        /* Restores the environment from the O/S. */
done:
        add	sp, sp, #32	/* Destroy stack frame.     */
        /* Pop O/S state from stack.*/
	pop	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
        bx      lr              /* Return to O/S.           */
