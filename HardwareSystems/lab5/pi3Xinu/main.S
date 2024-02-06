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
	mov r5,#16
	mul r0,r0,r5
	mov r1,#10
	bl divide
	bl printnum
        /* End of your program.         */
        /* Function epilogue.           */
        /* Restores the environment from the O/S. */
done:
        add	sp, sp, #32	/* Destroy stack frame.     */
        /* Pop O/S state from stack.*/
	pop	{r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
        bx      lr              /* Return to O/S.           */
