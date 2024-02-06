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
	bl addArray
	bl printnum

addArray:
	sub sp, sp, #40
	mov r6, #0 //sp location
	mov r7, #0 //loop counter
	mov r8, #0 //sum

CREATE:
	bl getnum
	str r0, [sp, r6]
	add r6, r6, #4
	add r7, r7, #1
	cmp r7, #9
	ble CREATE	

	sub r7, r7, #1
	sub r6, r6, #4

SUM:	ldr r0, [sp, r6]
	add r8, r8, r0
	mov r0, r8
	sub r7, r7, #1
	sub r6, r6, #4
	cmp r7, #0
	bge SUM
	bl printnum

        /* End of your program.         */
        /* Function epilogue.           */
        /* Restores the environment from the O/S. */


done:
        add	sp, sp, #32	/* Destroy stack frame.     */
        /* Pop O/S state from stack.*/
	pop	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
        bx      lr              /* Return to O/S.           */
