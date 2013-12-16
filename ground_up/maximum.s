#PURPOSE: This program will find the maximum number of a set of data itens

#VARIABLES:  The registers have the following uses:
#	%edi - Holds the index of the data item being examined 
#	%ebx - Largest data item found
#	%eax - Current data item
#
# The following memory locations are used:
# data_itens - contains the item data. A 0 is used to terminate the data.

.section .data
data_itens: 	#These are the data itens
.long 3,67,34,222,45,75,54,34,44,33,22,11,66,0

.section .text

.globl _start
_start:
movl $0, %edi	#Move 0 into the index register
movl data_itens(,%edi,4), %eax #Load the first bye of data
movl %eax, %ebx	#since this is the first item %eax is the biggest.

start_loop:
cmpl $0, %eax #check to see if we've hit the end.
je loop_exit
incl %edi
movl data_itens(,%edi,4), %eax
cmpl %ebx, %eax	#compare values
jle start_loop #jump to the beginning if the new one isn't bigger
movl %eax, %ebx #move the value as the largest 
jmp start_loop #jump to the loop beginning

loop_exit:
#%ebx is the status code for the exit system call and it already has the maximum number
movl $1, %eax #1 is the exit() syscall
int $0x80

