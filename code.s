.data
printstr: .asciz "%d\n"
.text
   .globl Main_main
 LinkedListNode_setIsNull:
push %ebp
mov %esp,%ebp
sub $0,%esp
push 12(%ebp)
pop %eax
mov 8(%ebp),%ebx
mov %eax, 8(%ebx)
mov %ebp,%esp
pop %ebp
ret
 LinkedListNode_setNext:
push %ebp
mov %esp,%ebp
sub $0,%esp
push 12(%ebp)
pop %eax
mov 8(%ebp),%ebx
mov %eax, 4(%ebx)
mov %ebp,%esp
pop %ebp
ret
 LinkedListNode_setValue:
push %ebp
mov %esp,%ebp
sub $0,%esp
push 12(%ebp)
pop %eax
mov 8(%ebp),%ebx
mov %eax, 0(%ebx)
mov %ebp,%esp
pop %ebp
ret
 LinkedList_construct:
push %ebp
mov %esp,%ebp
sub $4,%esp
push $3
call malloc
add $4,%esp
push %eax
pop %eax
mov %eax, -4(%ebp)
push $1
push -4(%ebp)
call LinkedListNode_setIsNull
add $8, %esp
push %eax
push -4(%ebp)
pop %eax
mov 8(%ebp),%ebx
mov %eax, 4(%ebx)
push -4(%ebp)
pop %eax
mov 8(%ebp),%ebx
mov %eax, 0(%ebx)
mov %ebp,%esp
pop %ebp
ret
 LinkedList_insert:
push %ebp
mov %esp,%ebp
sub $4,%esp
mov 8(%ebp),%ebx
mov 0(%ebx),%ebx
push 8(%ebx)
pop %eax
mov $1,%ebx
cmp %eax,%ebx
je IFTrue_0
jmp Else_0
IFTrue_0:
push 12(%ebp)
push 8(%ebp)
call LinkedList_makeNewNode
add $8, %esp
push %eax
pop %eax
mov 8(%ebp),%ebx
mov %eax, 0(%ebx)
jmp EndIFELSE_0
Else_0:
mov 8(%ebp),%ebx
push 0(%ebx)
push 12(%ebp)
push 8(%ebp)
call LinkedList_insert2
add $12, %esp
push %eax
jmp EndIFELSE_0
EndIFELSE_0:
mov %ebp,%esp
pop %ebp
ret
 LinkedList_makeNewNode:
push %ebp
mov %esp,%ebp
sub $4,%esp
push $3
call malloc
add $4,%esp
push %eax
pop %eax
mov %eax, -4(%ebp)
push $0
push -4(%ebp)
call LinkedListNode_setIsNull
add $8, %esp
push %eax
push 12(%ebp)
push -4(%ebp)
call LinkedListNode_setValue
add $8, %esp
push %eax
mov 8(%ebp),%ebx
push 4(%ebx)
push -4(%ebp)
call LinkedListNode_setNext
add $8, %esp
push %eax
push -4(%ebp)
pop %eax
mov %ebp,%esp
pop %ebp
ret
 LinkedList_insert2:
push %ebp
mov %esp,%ebp
sub $4,%esp
mov 16(%ebp),%ebx
push 4(%ebx)
pop %eax
mov %eax, -4(%ebp)
mov -4(%ebp),%ebx
push 8(%ebx)
pop %eax
mov $1,%ebx
cmp %eax,%ebx
je IFTrue_1
jmp Else_1
IFTrue_1:
push 12(%ebp)
push 8(%ebp)
call LinkedList_makeNewNode
add $8, %esp
push %eax
push 16(%ebp)
call LinkedListNode_setNext
add $8, %esp
push %eax
jmp EndIFELSE_1
Else_1:
mov 16(%ebp),%ebx
push 4(%ebx)
push 12(%ebp)
push 8(%ebp)
call LinkedList_insert2
add $12, %esp
push %eax
jmp EndIFELSE_1
EndIFELSE_1:
mov %ebp,%esp
pop %ebp
ret
 LinkedList_traverse:
push %ebp
mov %esp,%ebp
sub $0,%esp
mov 8(%ebp),%ebx
push 0(%ebx)
push 8(%ebp)
call LinkedList_traverse2
add $8, %esp
push %eax
mov %ebp,%esp
pop %ebp
ret
 LinkedList_traverse2:
push %ebp
mov %esp,%ebp
sub $0,%esp
mov 12(%ebp),%ebx
push 8(%ebx)
pop %eax
mov $1,%ebx
xor %ebx,%eax
push %eax
pop %eax
mov $1,%ebx
cmp %eax,%ebx
je IFTrue_2
jmp Else_2
IFTrue_2:
mov 12(%ebp),%ebx
push 0(%ebx)
push $printstr
call printf
mov 12(%ebp),%ebx
push 4(%ebx)
push 8(%ebp)
call LinkedList_traverse2
add $8, %esp
push %eax
jmp EndIFELSE_2
Else_2:
jmp EndIFELSE_2
EndIFELSE_2:
mov %ebp,%esp
pop %ebp
ret
 Main_main:
push %ebp
mov %esp,%ebp
sub $4,%esp
push $2
call malloc
add $4,%esp
push %eax
pop %eax
mov %eax, -4(%ebp)
push -4(%ebp)
call LinkedList_construct
add $4, %esp
push %eax
push $5

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $7

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $1

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $3

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $2

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $8

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $6

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $9

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $4

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push $10

push -4(%ebp)
call LinkedList_insert
add $8, %esp
push %eax
push -4(%ebp)
call LinkedList_traverse
add $4, %esp
push %eax
push $0

pop %eax
mov %ebp,%esp
pop %ebp
ret
