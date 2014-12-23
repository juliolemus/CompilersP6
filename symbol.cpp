#include "symbol.hpp"

// Symbol Visitor Functions: These are the functions you will
// complete to build the symbol table. Not all functions must
// have code, many may be left empty.
int sizeOfLocVar;

void Symbol::visitProgramNode(ProgramNode* node) 
{
    classTable=new ClassTable();
    node->visit_children(this);
}

void Symbol::visitClassNode(ClassNode* node) 
{
    ClassInfo classinfo;
    currentMemberOffset=0; 
    currentLocalOffset=0;
    if(node->identifier_2==NULL)
    {
        classinfo.superClassName="";
    }
    else
    {
        classinfo.superClassName=node->identifier_2->name;
        for (VariableTable::iterator it=((*classTable)[classinfo.superClassName].members).begin(); it != ((*classTable)[classinfo.superClassName].members).end(); it++)
        {
            currentMemberOffset+=4;
            classinfo.members.insert(std::pair<std::string,VariableInfo>(it->first,it->second));
        }
    }
    currentMethodTable=&(classinfo.methods);
    currentVariableTable=&(classinfo.members);
    node->visit_children(this);
    classinfo.membersSize=classinfo.members.size();
    classTable->insert(std::make_pair(node->identifier_1->name,classinfo));


} 

void Symbol::visitMethodNode(MethodNode* node)
{
    MethodInfo methodinfo;
    currentVariableTable=&(methodinfo.variables);
    currentParameterOffset=12;
    sizeOfLocVar=0;
    node->visit_children(this);
    methodinfo.localsSize=sizeOfLocVar; //set the number of local variables
    methodinfo.returnType.baseType=node->type->basetype;
    if(methodinfo.returnType.baseType==bt_object)
    {
        ObjectTypeNode* castptr=(ObjectTypeNode*)(node->type);
        methodinfo.returnType.objectClassName=castptr->identifier->name;
    }
    currentMethodTable->insert(std::make_pair(node->identifier->name,methodinfo));
}

void Symbol::visitMethodBodyNode(MethodBodyNode* node) 
{
    currentLocalOffset=-4;
    node->visit_children(this);

}

void Symbol::visitParameterNode(ParameterNode* node) 
{
    VariableInfo varinfo;
    node->visit_children(this);
    varinfo.offset=currentParameterOffset;
    varinfo.size=4;
    currentParameterOffset+=4;
    varinfo.type.baseType=node->type->basetype;
    if(varinfo.type.baseType==bt_object)
    {
        ObjectTypeNode* castptr=(ObjectTypeNode*)(node->type);
        varinfo.type.objectClassName=castptr->identifier->name;
    }
    currentVariableTable->insert(std::make_pair(node->identifier->name,varinfo));
}

void Symbol::visitDeclarationNode(DeclarationNode* node)
{
    VariableInfo varinfo2;
    node->visit_children(this);
    varinfo2.size=4;
    varinfo2.type.baseType=node->type->basetype;
    if(varinfo2.type.baseType==bt_object)
    {
        ObjectTypeNode* castptr=(ObjectTypeNode*)(node->type);
        varinfo2.type.objectClassName=castptr->identifier->name;
    }
    for (std::list<IdentifierNode*>::iterator it = node->identifier_list->begin(); it != node->identifier_list->end(); it++) 
    {
       if(currentLocalOffset==0)  //use the currentLocalOffset as a boolean in classNode since it will always be reset to zero there if the value is not zero, then we know it got reset at methodbody so this helps differentiate between updating local offset and member offset
       {
          varinfo2.offset=currentMemberOffset; //have to put both cases in if because we can increment both at the same time we have to be able to chose the right one
          currentMemberOffset+=4;
       }
      else
      {
        varinfo2.offset=currentLocalOffset;
        currentLocalOffset-=4;
        sizeOfLocVar+=4;  //keep track of the number of local variables 
        //changed from 1 to 4 because error in code gen
      }
       IdentifierNode* idptr=*it;
       currentVariableTable->insert(std::make_pair(idptr->name,varinfo2));
    }
}

void Symbol::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerTypeNode(IntegerTypeNode* node) {
    node->basetype=bt_integer;
}

void Symbol::visitBooleanTypeNode(BooleanTypeNode* node) {
    node->basetype=bt_boolean;
}

void Symbol::visitObjectTypeNode(ObjectTypeNode* node) {
    node->basetype=bt_object;
}

void Symbol::visitNoneNode(NoneNode* node) {
    node->basetype=bt_none;
}

void Symbol::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
