#include "codegeneration.hpp"

// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.
//
// NOTE: You only need to complete code for expressions,
// assignments, returns, and local variable space allocation.
// Refer to project description for exact details.

void CodeGenerator::visitProgramNode(ProgramNode* node) 
{
     std::cout << ".data" << std::endl;
     std::cout << "printstr: .asciz \"%d\\n\"" << std::endl;
     std::cout << ".text" << std::endl;
                 #if __APPLE_
     std::cout << "   .globl _"<< "Main" <<"_"<< "main" << std::endl;
                 #else  
     std::cout << "   .globl "<< "Main" <<"_"<< "main" << std::endl;
                 #endif
     node->visit_children(this); 
 
}

void CodeGenerator::visitClassNode(ClassNode* node) 
{
    currentClassName=node->identifier_1->name;
    currentClassInfo=(*classTable)[currentClassName];
    node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) 
{
    currentMethodName=node->identifier->name;
    currentMethodInfo=currentClassInfo.methods[currentMethodName];
                 #if __APPLE__
    std::cout << " _"<< currentClassName <<"_"<< currentMethodName <<":" << std::endl; 
                 #else
    std::cout << " "<< currentClassName <<"_"<< currentMethodName <<":" << std::endl;
                 #endif
    node->visit_children(this);
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node)
{
    std::cout << "push %ebp" << std::endl; //prologue
    std::cout << "mov %esp,%ebp" << std::endl;
    std::cout << "sub " << "$" << currentMethodInfo.localsSize << ",%esp"<<std::endl;	    
    node->visit_children(this);
    std::cout << "mov %ebp,%esp" << std::endl; //epilogue
    std::cout << "pop %ebp" << std::endl;
    std::cout << "ret" << std::endl;	 
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {

}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %eax" << std::endl;
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %eax" << std::endl;
    if(currentClassInfo.members.find(node->identifier->name)!=currentClassInfo.members.end())
    {
        std::cout << "mov 8(%ebp),%ebx" << std::endl;
        std::cout << "mov %eax, " << currentClassInfo.members[node->identifier->name].offset << "(%ebx)" << std::endl;
    }
    else
    {
        std::cout << "mov %eax, " << currentMethodInfo.variables[node->identifier->name].offset << "(%ebp)" << std::endl;
    }
}
void CodeGenerator::visitCallNode(CallNode* node) 
{
    node->visit_children(this);
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) 
{
    int label=nextLabel();
    node->expression->accept(this);                
    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $1,%ebx" << std::endl;
    std::cout << "cmp %eax,%ebx" << std::endl;
    std::cout << "je IFTrue_" << label << std::endl;
    std::cout << "jmp Else_" << label << std::endl;
    std::cout << "IFTrue_" << label << ":" << std::endl;
    if (node->statement_list_1) {
    for(std::list<StatementNode*>::iterator iter = node->statement_list_1->begin();
        iter != node->statement_list_1->end(); iter++) {
      (*iter)->accept(this);
     }
    }
    std::cout << "jmp EndIFELSE_" << label << std::endl;
    std::cout << "Else_" << label << ":" << std::endl;
    if (node->statement_list_2) {
    for(std::list<StatementNode*>::iterator iter = node->statement_list_2->begin();
        iter != node->statement_list_2->end(); iter++) {
      (*iter)->accept(this);
     }
    }
    std::cout << "jmp EndIFELSE_" << label << std::endl;
    std::cout << "EndIFELSE_" << label << ":" << std::endl;
}

void CodeGenerator::visitForNode(ForNode* node) 
{
    int label=nextLabel();
    node->assignment_1->accept(this);
    std::cout << "For_" << label << ":"  << std::endl;
    node->expression->accept(this);
    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $1,%ebx" << std::endl;
    std::cout << "cmp %eax,%ebx" << std::endl;
    std::cout << "je Body_" << label << std::endl;
    std::cout << "jmp Break_" << label << std::endl;
    std::cout << "Body_" << label << ":" << std::endl;
    if (node->statement_list) {
    for(std::list<StatementNode*>::iterator iter = node->statement_list->begin();
        iter != node->statement_list->end(); iter++) {
      (*iter)->accept(this);
     }
    }
    node->assignment_2->accept(this);
    std::cout <<"jmp For_" << label << std::endl;
    std::cout << "Break_"<< label<<":"<<std::endl;

}

void CodeGenerator::visitPrintNode(PrintNode* node) 
{
    node->visit_children(this);
    std::cout << "push $printstr" << std::endl;
    std::cout << "call printf" << std::endl;    
}

void CodeGenerator::visitPlusNode(PlusNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;                       
    std::cout << "pop %eax" << std::endl;
    std::cout << "add %ebx,%eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "sub %ebx,%eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "imul %ebx,%eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $0,%edx"<< std::endl;
    std::cout << "cdq" << std::endl;
    std::cout << "idiv %ebx" << std::endl;
    std::cout << "push %eax" << std::endl;  
}

void CodeGenerator::visitLessNode(LessNode* node) 
{
    int label = nextLabel();
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "cmp %ebx,%eax" << std::endl;
    std::cout << "jl Eval_"<< label << std::endl;
    std::cout << "push $0" << std::endl;
    std::cout << "jmp continueLess_" << label << std::endl;
    std::cout <<""<< std::endl; 
    std::cout << "Eval_" << label << ":" << std::endl;
    std::cout << "push $1" << std::endl;
    std::cout <<""<< std::endl;
    std::cout << "continueLess_" << label << ":" << std::endl; 
    
}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) 
{
    int label = nextLabel();
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "cmp %ebx,%eax" << std::endl;
    std::cout << "jle Eval_"<< label << std::endl;
    std::cout << "push $0" << std::endl;
    std::cout << "jmp continue_" << label << std::endl;
    std::cout <<""<< std::endl; 
    std::cout << "Eval_" << label << ":" << std::endl;
    std::cout << "push $1" << std::endl;
    std::cout <<""<< std::endl;
    std::cout << "continue_" << label << ":" << std::endl; 
    
}

void CodeGenerator::visitEqualNode(EqualNode* node) 
{
    int label=nextLabel();
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "cmp %ebx,%eax" << std::endl;
    std::cout << "je Eval_"<< label << std::endl;
    std::cout << "push $0" << std::endl; //if condition is false
    std::cout << "jmp continueEq_" << label << std::endl;
    std::cout <<""<< std::endl; 
    std::cout << "Eval_" << label << ":" << std::endl;
    std::cout << "push $1" << std::endl;
    std::cout <<""<< std::endl;
    std::cout << "continueEq_" << label << ":" << std::endl; 
}

void CodeGenerator::visitAndNode(AndNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "and %ebx,%eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %ebx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "or %ebx,%eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) 
{
    node->visit_children(this);
    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $1,%ebx" << std::endl;
    std::cout << "xor %ebx,%eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) 
{
    node->visit_children(this); 
    std::cout << "pop %eax" << std::endl;
    std::cout << "neg %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}
 
void CodeGenerator::visitMethodCallNode(MethodCallNode* node) 
{
   int paramcount=4;
   if (node->expression_list) 
   {
      for(std::list<ExpressionNode*>::reverse_iterator iter = node->expression_list->rbegin();
        iter != node->expression_list->rend(); iter++) {
        paramcount+=4;
      (*iter)->accept(this);
    }
   }
   if (node->identifier_2==NULL)
   {
       std::cout << "push 8(%ebp)" << std::endl;
       std::cout << "call " << currentClassName << "_" << node->identifier_1->name << std::endl;
   }
   else
   {
       
       std::cout << "push " << currentMethodInfo.variables[node->identifier_1->name].offset << "(%ebp)" << std::endl;  
       std::string classobj=currentMethodInfo.variables[node->identifier_1->name].type.objectClassName;
       while((*classTable)[classobj].methods.find(node->identifier_2->name)==(*classTable)[classobj].methods.end())
       {
          classobj=(*classTable)[classobj].superClassName;
       }                                                                                                                                                                                                                                                                                                                                                             std::cout << "call " << classobj << "_" << node->identifier_2->name << std::endl;
   }

   std::cout << "add $" << paramcount << ", %esp" << std::endl; 
   std::cout << "push %eax" << std::endl; //return from the function 
   
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) 
{
    node->visit_children(this);
    if(currentClassInfo.members.find(node->identifier_1->name)!=currentClassInfo.members.end())
    {
        VariableInfo objinfo=currentClassInfo.members[node->identifier_1->name];
        std::cout << "mov 8(%ebp),%ebx" << std::endl; // get the this pointer for class which has all the class's vars, and members
        std::cout << "mov " << objinfo.offset << "(%ebx)" << ",%ebx" << std::endl; //access the member we are looking for using its offset
        std::cout << "push " << (*classTable)[objinfo.type.objectClassName].members[node->identifier_2->name].offset << "(%ebx)" << std::endl; //get the class info that the memeber belongs to and grab the memeber its accessing ex B b, b.c grabs c 
    }
    else
    {
        VariableInfo objinfo=currentMethodInfo.variables[node->identifier_1->name];
        std::cout << "mov " << objinfo.offset << "(%ebp)" << ",%ebx" << std::endl; //since the member isnt declared in the current class and is declared in the curretn Method, we dont need the self pointer because we can access the object from the method info using its offset from objinfo which contains the variable info for the current method. 
        std::cout << "push "<< (*classTable)[objinfo.type.objectClassName].members[node->identifier_2->name].offset << "(%ebx)" << std::endl;
    }
}

void CodeGenerator::visitVariableNode(VariableNode* node) 
{
    if(currentClassInfo.members.find(node->identifier->name)!=currentClassInfo.members.end())
    {
        std::cout << "mov 8(%ebp),%ebx" << std::endl;
        std::cout << "push " << currentClassInfo.members[node->identifier->name].offset << "(%ebx)" << std::endl;
    }
    else
    {
        std::cout << "push " << currentMethodInfo.variables[node->identifier->name].offset << "(%ebp)" << std::endl;
    }
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node)
{
    std::cout << "push " << "$" << node->integer->value << std::endl;
    std::cout <<""<<std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) 
{
    std::cout << "push " << "$" << node->integer->value << std::endl;
}

void CodeGenerator::visitNewNode(NewNode* node) 
{
    std::cout << "push $" << (*classTable)[node->identifier->name].membersSize << std::endl;
    std::cout << "call malloc" << std::endl;
    std::cout << "add $4,%esp" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    
}
