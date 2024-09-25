/* -*- mode: c++; tab-width: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

// This file is included into eval.h

// Constants and bindings

// The parser parses constants and adds lists of constant definitions with
// unresolved RHS values to lists in the program and function nodes.
//
// The code generator resolves those constants.  Values that either must be constants
// (identifiers used in 'namespace', 'const', and 'use namespace' definitions)
// or can be constants (identifiers used as the namespace value in qualified
// identifiers) are looked up during code generation by searching the context.
// The 'Program' and 'Function' (and probably 'Package', when we have that)
// ribs have separate lists of constant bindings with their values.  Those value
// lists are populated in a prepass when code generation enters a Program or
// Function, since a statement can reference a later constant binding at the
// same or outer scope.

/*
enum CVTag {
	TAG_cvValue,
	TAG_cvAnonNS,
	TAG_cvNamespace
};

class ConstValue {
public:
	virtual ~ConstValue();
	virtual CVTag tag() const = 0;
};

class CVValue : public ConstValue {
public:
	CVValue(Expr* expr) : expr(expr) {}
	virtual CVTag tag() const { return TAG_cvValue; }
	Expr * const expr;
};

class CVAnonNS : public ConstValue {
public:
	virtual CVTag tag() const { return TAG_cvAnonNS; }
};

class CVNamespace : public ConstValue {
public:
	CVNamespace(Expr* expr) : expr(expr) {}
	virtual CVTag tag() const { return TAG_cvNamespace; }
	Expr * const expr;
};
*/

enum BindingKind {
	TAG_varBinding,		// also used for function (though not for class methods)
	TAG_constBinding,
	TAG_methodBinding,	// methods in classes and interfaces
	TAG_namespaceBinding
};

enum QualifierTag {
	QUAL_none,
	QUAL_private,
	QUAL_protected,
	QUAL_public,
	QUAL_internal,
	QUAL_name
};

class Qualifier {
public:
	Qualifier() : tag(QUAL_none), is_native(false), is_static(false), is_prototype(false), name(NULL) {}
	QualifierTag tag;
	bool is_native;
	bool is_static;
	bool is_prototype;
	Str* name;
};

class Binding {
public:
	Binding(Str* name, QualifiedName* type_name, BindingKind kind)
		: name(name)
		, type_name(type_name)
		, kind(kind)
	{
	}

	Str* const name;
	QualifiedName* const type_name;
	const BindingKind kind;
};


// Program, class, interface, etc nodes

enum CodeType {
	CODE_Program,
	CODE_Class,
	CODE_Function
};

class CodeBlock {
public:
	CodeBlock(CodeType tag, Seq<Binding*>* bindings, Seq<FunctionDefn*>* functions, Seq<NamespaceDefn*>* namespaces, Seq<Stmt*>* stmts)
		: tag(tag)
		, bindings(bindings)
		, functions(functions)
		, namespaces(namespaces)
		, stmts(stmts)
	{
	}

	virtual ~CodeBlock();
	virtual void cogenBody(Cogen* cogen, uint32_t activation) = 0;
	
	void cogen(Cogen* cogen);
	
	CodeType tag;
	Seq<Binding*>* const bindings;
	Seq<FunctionDefn*>* const functions;
	Seq<NamespaceDefn*>* const namespaces;
	Seq<Stmt*>* const stmts;
};

class Program : public CodeBlock {
public:
	Program(Seq<Binding*>* bindings, Seq<FunctionDefn*>* functions, Seq<NamespaceDefn*>* namespaces, Seq<Stmt*>* stmts) 
		: CodeBlock(CODE_Program, bindings, functions, namespaces, stmts)
	{
	}
	
	virtual void cogenBody(Cogen* cogen, uint32_t activation);
};

class ClassDefn {
public:
	ClassDefn(Qualifier* qual, Str* name, Str* extends, Seq<Str*>* implements, Seq<Stmt*>* class_init, Seq<Stmt*>* instance_init)
	{
		// FIXME: elaborate
		(void)qual;
		(void)name;
		(void)extends;
		(void)implements;
		(void)class_init;
		(void)instance_init;
	}
};

class InterfaceDefn {
public:
	InterfaceDefn(Qualifier* qual, Str* name, Seq<Str*>* extends)
	{
		// FIXME: elaborate
		(void)qual;
		(void)name;
		(void)extends;
	}
};

// Somewhat mis-named, also used for function expressions (see LiteralFunction below), where name may be NULL

class FunctionParam {
public:
	FunctionParam(Str* name, QualifiedName* type_name, Expr* default_value) : name(name), type_name(type_name), default_value(default_value) {}
	Str * const name;
	QualifiedName * const type_name;
	Expr * const default_value;
};

class FunctionDefn : public CodeBlock {
public:
	FunctionDefn(Str* name, Seq<Binding*>* bindings, 
				 Seq<FunctionParam*>* params, uint32_t numparams, FunctionParam* rest_param, QualifiedName* return_type_name,
				 Seq<FunctionDefn*>* functions, Seq<NamespaceDefn*>* namespaces, Seq<Stmt*>* stmts, 
				 bool uses_arguments,
				 bool uses_dxns,
				 bool optional_arguments)
		: CodeBlock(CODE_Function, bindings, functions, namespaces, stmts)
		, name(name)
		, params(params)
		, numparams(numparams)
		, rest_param(rest_param)
		, return_type_name(return_type_name)
		, uses_arguments(uses_arguments)
		, uses_dxns(uses_dxns)
		, optional_arguments(optional_arguments)
	{
	}

	virtual void cogenBody(Cogen* cogen, uint32_t activation);

	// Common code for function code generation.  Create MethodInfo and MethodBodyInfo;
	// generate code for the function; set the function's flags properly.
	void cogenGuts(Compiler* compiler, ABCMethodInfo** info, ABCMethodBodyInfo** body);

	Str* name;							// Name of function or NULL.  Not const because we sometimes need to set it to NULL.
	Seq<FunctionParam*>* const params;	// List of fixed parameters
	const uint32_t numparams;			// Number of fixed parameters
	FunctionParam* rest_param;			// non-NULL iff we have a ... rest argument; name+type of that argument
	QualifiedName* return_type_name;	// may be NULL
	const bool uses_arguments;			// true iff rest_name == NULL and the ident 'arguments' is used in the function
	const bool uses_dxns;				// true iff 'default xml namespace' is used in the function
	const bool optional_arguments;		// true iff any of the parameters have default values
};

class NamespaceDefn {
public:
	NamespaceDefn(Str* name, Expr* value) : name(name), value(value) {}
	Str* const name;
	Expr* const value;	// NULL for anonymous ones; TAG_literalString for string values; otherwise a NameExpr
};

// Tags returned from Expr::tag()

enum Tag {
	TAG_expr,					// generic expr
	TAG_objectRef,				// instance of ObjectRef
	TAG_qualifiedName,			// instance of QualifiedName
	TAG_literalString,			// instance of LiteralString
};

// Tags returned from NameComponent::tag()

enum NameTag {
	TAG_simpleName,				// instance of SimpleName
	TAG_wildcardName,			// instance of WildcardName
	TAG_computedName,			// instance of ComputedName
};


// Expression nodes

// Binary operators are used in the table binopMapping in eval-cogen.cpp.
// So keep these in order, and if you add any you *must* add entries to
// that table.

enum Binop {
	// 0 is not used
	OPR_as=1,
	OPR_plus,
	OPR_assign,
	OPR_init,
	OPR_comma,
	OPR_minus,
	OPR_multiply,
	OPR_divide,
	OPR_remainder,
	OPR_leftShift,
	OPR_rightShift,
	OPR_rightShiftUnsigned,
	OPR_instanceof,
	OPR_in,
	OPR_is,
	OPR_bitwiseAnd,
	OPR_bitwiseOr,
	OPR_bitwiseXor,
	OPR_logicalAnd,
	OPR_logicalOr,
	OPR_less,
	OPR_lessOrEqual,
	OPR_greater,
	OPR_greaterOrEqual,
	OPR_equal,
	OPR_notEqual,
	OPR_strictEqual,
	OPR_strictNotEqual,
	OPR_to
};

enum Unop {
	// 0 is not used
	OPR_deleteVar=1,
	OPR_delete,
	OPR_typeofVar,
	OPR_typeof,
	OPR_postIncr,
	OPR_preIncr,
	OPR_postDecr,
	OPR_preDecr,
	OPR_postIncrVar,
	OPR_preIncrVar,
	OPR_postDecrVar,
	OPR_preDecrVar,
	OPR_bitwiseNot,
	OPR_unminus,
	OPR_unplus,
	OPR_not,
	OPR_void
};

class Expr {
public:
	Expr(uint32_t pos=0) : pos(pos) {}
	virtual ~Expr() {}  // Not really, but otherwise gcc drowns us in warnings
	virtual void cogen(Cogen* cogen) = 0;	// override for value computation
	virtual Tag tag() const { return TAG_expr; }
	const uint32_t pos;
};

class LiteralObject : public Expr {
public:
	LiteralObject(Seq<LiteralField*>* fields, uint32_t pos) : Expr(pos), fields(fields) {}
	virtual void cogen(Cogen* cogen);
	Seq<LiteralField*>* const fields;
};

class LiteralField {
public:
	LiteralField(Str* name, Expr* value) : name(name), value(value) {}
	Str* const name;
	Expr* const value;
};

class LiteralArray : public Expr {
public:
	LiteralArray(Seq<Expr*>* elements, uint32_t pos) : Expr(pos), elements(elements) {}
	virtual void cogen(Cogen* cogen);
	Seq<Expr*>* const elements;
};

class LiteralUndefined : public Expr {
public:
	LiteralUndefined(uint32_t pos) : Expr(pos) {}
	virtual void cogen(Cogen* cogen);
};

class LiteralNull : public Expr {
public:
	LiteralNull(uint32_t pos) : Expr(pos) {}
	virtual void cogen(Cogen* cogen);
};

class LiteralInt : public Expr {
public:
	LiteralInt(int32_t value, uint32_t pos) : Expr(pos), value(value) {}
	virtual void cogen(Cogen* cogen);
	const int32_t value;
};

class LiteralUInt : public Expr {
public:
	LiteralUInt(uint32_t value, uint32_t pos) : Expr(pos), value(value) {}
	virtual void cogen(Cogen* cogen);
	const uint32_t value;
};

class LiteralDouble : public Expr {
public:
	LiteralDouble(double value, uint32_t pos) : Expr(pos), value(value) {}
	virtual void cogen(Cogen* cogen);
	const double value;
};

class LiteralBoolean : public Expr {
public:
	LiteralBoolean(bool value, uint32_t pos) : Expr(pos), value(value) {}
	virtual void cogen(Cogen* cogen);
	const bool value;
};

class LiteralString : public Expr {
public:
	LiteralString(Str* value, uint32_t pos) : Expr(pos), value(value) {}
	virtual void cogen(Cogen* cogen);
	virtual Tag tag() const { return TAG_literalString; }
	Str* const value;
};

class LiteralRegExp : public Expr {
public:
	LiteralRegExp(Str* value, uint32_t pos) : Expr(pos), value(value) {}
	virtual void cogen(Cogen* cogen);
	Str* const value;
};

class LiteralFunction : public Expr {
public:
	LiteralFunction(FunctionDefn* function) : function(function) {}
	virtual void cogen(Cogen* cogen);
	FunctionDefn* const function;
};

class XmlInitializer : public Expr {
public:
	XmlInitializer(Seq<Expr*>* exprs, bool is_list, uint32_t pos)
		: Expr(pos)
		, exprs(exprs)
		, is_list(is_list)
	{
	}
	virtual void cogen(Cogen* cogen);
	Seq<Expr*>* const exprs;
	const bool is_list;
};

class ThisExpr : public Expr {
public:
	virtual void cogen(Cogen* cogen);
};

class NewExpr : public Expr {
public:
	NewExpr(Expr* fn, Seq<Expr*>* arguments) : fn(fn), arguments(arguments) {}
	virtual void cogen(Cogen* cogen);
	Expr* const fn;
	Seq<Expr*>* const arguments;
};

class CallExpr : public Expr {
public:
	CallExpr(Expr* fn, Seq<Expr*>* arguments, uint32_t pos) : Expr(pos), fn(fn), arguments(arguments) {}
	virtual void cogen(Cogen* cogen);
	Expr* const fn;
	Seq<Expr*>* const arguments;
};

class ConditionalExpr : public Expr {
public:
	ConditionalExpr(Expr* e1, Expr* e2, Expr* e3) : e1(e1), e2(e2), e3(e3) {}
	virtual void cogen(Cogen* cogen);
	Expr* const e1;
	Expr* const e2;
	Expr* const e3;
};

class AssignExpr : public Expr {
public:
	AssignExpr(Binop op, Expr* lhs, Expr* rhs) : op(op), lhs(lhs), rhs(rhs) {}
	virtual void cogen(Cogen* cogen);
	const Binop op;
	Expr* const lhs;
	Expr* const rhs;
};
	
class BinaryExpr : public Expr {
public:
	BinaryExpr(Binop op, Expr* lhs, Expr* rhs) : op(op), lhs(lhs), rhs(rhs) {}
	virtual void cogen(Cogen* cogen);
	const Binop op;
	Expr* const lhs;
	Expr* const rhs;
};

class UnaryExpr : public Expr {
public:
	UnaryExpr(Unop op, Expr* expr) : op(op), expr(expr) {}
	virtual void cogen(Cogen* cogen);
	void incdec(Cogen* cogen, bool pre, bool inc);
	Unop const op;
	Expr* const expr;
};

class RefLocalExpr : public Expr {
public:
	RefLocalExpr(uint32_t local) : local(local) {}
	virtual void cogen(Cogen* cogen);
	const uint32_t local;
};

class FilterExpr : public Expr {
public:
	FilterExpr(Expr* obj, Expr* filter, uint32_t pos) : Expr(pos), obj(obj), filter(filter) {}
	virtual void cogen(Cogen* cogen);
	Expr * const obj;
	Expr * const filter;
};

class DescendantsExpr : public Expr {
public:
	DescendantsExpr(Expr* obj, QualifiedName* name, uint32_t pos) : Expr(pos), obj(obj), name(name) {}
	virtual void cogen(Cogen* cogen);
	Expr * const obj;
	QualifiedName * const name;
};

enum Escapement {
	ESC_none,
	ESC_elementValue,
	ESC_attributeValue
};
	
class EscapeExpr : public Expr {
public:
	EscapeExpr(Expr* expr, Escapement esc) : Expr(0), expr(expr), esc(esc) {}
	virtual void cogen(Cogen* cogen);
	Expr * const expr;
	const Escapement esc;
};

// Anything that is a name is a NameExpr.  There are three kinds:
//
//    QualifiedName for id, ns::id, ns::[E], ditto with '@' prefix
//
//    ObjectRef for obj.<QualifiedName>
//
// Notes:
//   ns::@... is not legal syntax and need not be supported


class NameExpr : public Expr {
public:
	NameExpr(uint32_t pos) : Expr(pos) {}
};

class QualifiedName : public NameExpr {
public:
	QualifiedName(NameComponent* qualifier, NameComponent* name, bool is_attr, uint32_t pos)
		: NameExpr(pos)
		, qualifier(qualifier)
		, name(name)
		, is_attr(is_attr)
	{
		AvmAssert(name != NULL);
	}
	virtual void cogen(Cogen* cogen);
	virtual Tag tag() const { return TAG_qualifiedName; }
	NameComponent * const qualifier;
	NameComponent * const name;
	const bool is_attr;
};

class ObjectRef : public NameExpr {
public:
	ObjectRef(Expr* obj, QualifiedName* name, uint32_t pos) 
		: NameExpr(pos)
		, obj(obj)
		, name(name)
	{
		AvmAssert(obj != NULL && name != NULL);
	}
	virtual void cogen(Cogen* cogen);
	virtual Tag tag() const { return TAG_objectRef; }
	Expr * const obj;
	QualifiedName * const name;
};

class NameComponent {
public:
	virtual ~NameComponent();
	virtual NameTag tag() const = 0;
};

// simple identifier 
class SimpleName : public NameComponent {
public:
	SimpleName(Str* name) : name(name) { AvmAssert(name != NULL); }
	virtual NameTag tag() const { return TAG_simpleName; }
	Str* const name;
};

// the '*' identifier
class WildcardName : public NameComponent {
public:
	WildcardName() {}
	virtual NameTag tag() const { return TAG_wildcardName; }
};

// a [E] name
class ComputedName : public NameComponent {
public:
	ComputedName(Expr* expr) : expr(expr) {}
	virtual NameTag tag() const { return TAG_computedName; }
	Expr* const expr;
};


// Statement nodes

class Stmt {
public:
	Stmt(uint32_t pos=0) : pos(pos) {}
	virtual ~Stmt() {}
	virtual void cogen(Cogen* cogen, Ctx*) = 0;
	virtual bool isLabeledStmt() { return false; }
	virtual bool isLabelSetStmt() { return false; }
	uint32_t pos;

	static void cogenProgramBody(Cogen* cogen, Seq<Stmt*>* stmts);
	static void cogenFunctionBody(Cogen* cogen, Seq<Stmt*>* stmts);
};

class EmptyStmt : public Stmt {
public:
	virtual void cogen(Cogen* cogen, Ctx* ctx);
};

class BlockStmt : public Stmt {
public:
	BlockStmt(Seq<Stmt*>* stmts) : stmts(stmts) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Seq<Stmt*>* const stmts;
};

class ExprStmt : public Stmt {
public:
	ExprStmt(uint32_t pos, Expr* expr) : Stmt(pos), expr(expr) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
};

class LabeledStmt : public Stmt {
public:
	LabeledStmt(Str* label, Stmt* stmt) : label(label), stmt(stmt) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	virtual bool isLabeledStmt() { return true; }
	Str* const label;
	Stmt* const stmt;
};

class ReturnStmt : public Stmt {
public:
	ReturnStmt(uint32_t pos, Expr* expr) : Stmt(pos), expr(expr) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;  // or NULL
};

class BreakStmt : public Stmt {
public:
	BreakStmt(uint32_t pos, Str* label) : Stmt(pos), label(label) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Str* const label;   // or NULL
};

class ContinueStmt : public Stmt {
public:
	ContinueStmt(uint32_t pos, Str* label) : Stmt(pos), label(label) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Str* const label;   // or NULL
};

class IfStmt : public Stmt {
public:
	IfStmt(uint32_t pos, Expr* expr, Stmt* consequent, Stmt* alternate) 
		: Stmt(pos)
		, expr(expr)
		, consequent(consequent)
		, alternate(alternate)
	{
	}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
	Stmt* const consequent;
	Stmt* const alternate;  // or NULL
};

class LabelSetStmt : public Stmt {
public:
	LabelSetStmt(uint32_t pos=0) : Stmt(pos), labels(NULL) {}
	virtual bool isLabelSetStmt() { return true; }
	Seq<Str*>* labels;
};

class WhileStmt : public LabelSetStmt {
public:
	WhileStmt(uint32_t pos, Expr* expr, Stmt* body) : LabelSetStmt(pos), expr(expr), body(body) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
	Stmt* const body;
};

class DoWhileStmt : public LabelSetStmt {
public:
	// pos should be the position of the "while" keyword, roughly, because it's the expression
	// that will go wrong if anything
	DoWhileStmt(uint32_t pos, Expr* expr, Stmt* body) : LabelSetStmt(pos), expr(expr), body(body) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
	Stmt* const body;
};

class ForStmt : public LabelSetStmt {
public:
	ForStmt(uint32_t pos, Expr* init, Expr* test, Expr* update, Stmt* body) 
		: LabelSetStmt(pos)
		, init(init)
		, test(test)
		, update(update)
		, body(body)
	{
	}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr * const init;
	Expr * const test;
	Expr * const update;
	Stmt * const body;
};

class ForInStmt : public LabelSetStmt {
public:
	ForInStmt(uint32_t pos, Expr* lhs, Expr* init, Expr* obj, Stmt* body, bool is_each) 
		: LabelSetStmt(pos)
		, is_each(is_each)
		, lhs(lhs)
		, init(init)
		, obj(obj)
		, body(body)
	{
	}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	const bool is_each;
	Expr * const lhs;
	Expr * const init;
	Expr * const obj;
	Stmt * const body;
};

class SwitchStmt : public Stmt {
public:
	SwitchStmt(uint32_t pos, Expr* expr, Seq<CaseClause*>* cases) : Stmt(pos), expr(expr), cases(cases) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	bool analyze(int32_t* low, int32_t* high, bool* has_default);
	void cogenFast(Cogen* cogen, Ctx* ctx, int32_t low, int32_t high, bool has_default);
	void cogenSlow(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
	Seq<CaseClause*>* const cases;
};

class CaseClause {
public:
	CaseClause(uint32_t pos, Expr* expr) : pos(pos), expr(expr), stmts(NULL) {}
	uint32_t pos;
	Expr* const expr;
	Seq<Stmt*>* stmts;
};

class ThrowStmt : public Stmt {
public:
	ThrowStmt(uint32_t pos, Expr* expr) : Stmt(pos), expr(expr) {};
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
};

class TryStmt : public Stmt {
public:
	TryStmt(Seq<Stmt*>* tryblock, Seq<CatchClause*>* catches, Seq<Stmt*>* finallyblock) : tryblock(tryblock), catches(catches), finallyblock(finallyblock) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	void cogenWithFinally(Cogen* cogen, Ctx* ctx);
	void cogenNoFinally(Cogen* cogen, Ctx* ctx);
	void cgCatch(Cogen* cogen, Ctx* ctx, uint32_t code_start, uint32_t code_end, Label* Lend, CatchClause* catchClause);
	Seq<Stmt*>* const tryblock;
	Seq<CatchClause*>* const catches;
	Seq<Stmt*>* const finallyblock;
};

class CatchClause {
public:
	CatchClause(Str* name, QualifiedName* type_name, Seq<Stmt*>* stmts) : name(name), type_name(type_name), stmts(stmts) {}
	Str* const name;
	QualifiedName* const type_name;
	Seq<Stmt*>* const stmts;
};

class UseNamespaceStmt : public Stmt {
public:
	UseNamespaceStmt(uint32_t pos, Str* name) : Stmt(pos), name(name) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Str * const name;
};

class ImportStmt : public Stmt {
public:
	// The last component of 'name' is NULL if the name ends with '*'
	ImportStmt(uint32_t pos, Seq<Str*>* name) : Stmt(pos), name(name) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Seq<Str*> * const name;
};

class WithStmt : public Stmt {
public:
	WithStmt(uint32_t pos, Expr* expr, Stmt* body) : Stmt(pos), expr(expr), body(body) {}
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
	Stmt* const body;
};

class DefaultXmlNamespaceStmt : public Stmt {
public:
	DefaultXmlNamespaceStmt(uint32_t pos, Expr* expr) : Stmt(pos), expr(expr) {};
	virtual void cogen(Cogen* cogen, Ctx* ctx);
	Expr* const expr;
};

class Parser {
public:
	Parser(Compiler* compiler, Lexer* lexer, uint32_t first_line=1);
	
	Program* parse();
	Token onEOS(uint32_t* , TokenValue* valuep);
	
private:
	Compiler * const compiler;
	Allocator * const allocator;
	const uint32_t line_offset;

	// Parser attributes as bit vectors.  A bit vector of all 0s is the "normal"
	// case, the flags modify that.
	
	enum {
		EFLAG_NoIn = 1,		// Expression parsing: do not allow the use of the "in" operator
	};
	
	enum {
		SFLAG_Toplevel = 1,	// Statement and directive parsing: at top level
		SFLAG_Package = 2,	// Statement and directive parsing: at package level
		SFLAG_Function = 4,	// Statement and directive parsing: at function level
		SFLAG_Class = 8,
		SFLAG_Interface = 16,
		SFLAG_Block = 32,	// Statement and directive parsing: at block level inside one of the above
	};

	// Program, etc parser
	
	Program* program();
	void package();
	// In a class body, this returns the class init statements; instance init statements
	// are returned through the result parameter out_instance_init.
	Seq<Stmt*>* directives(int flags, Seq<Stmt*>** out_instance_init=NULL);
	void includeDirective();
	void classDefinition(int flags, Qualifier* qual);
	void interfaceDefinition(int flags, Qualifier* qual);
	void namespaceDefinition(int flags, Qualifier* qualifier);
	void functionDefinition(Qualifier* qualifier);
	Stmt* variableDefinition(Qualifier* qualifier);
	FunctionDefn* functionGuts(Qualifier* qual, bool require_name);
	Expr* varBindings(uint32_t* pos, bool is_const=false, int flags=0, uint32_t* numbindings=NULL, Expr** firstName=NULL);
	bool namespaceQualifier(int flags, Qualifier* qualifier);
	
	Seq<Stmt*>* statementBlock();
	
	// Expression parser
	//
	// OPTIMIZEME: Make the parser work by operator precedence so that we have only
	// a small number of recursive levels from "commaExpression" to "nameExpression"
	// or "primaryExpression" (the common paths).
	
	QualifiedName* typeExpression();
	Expr* functionExpression();
	QualifiedName* nameExpression(bool is_attr=false);
	Expr* propertyOperator(Expr* obj);
	Expr* objectInitializer();
	Seq<LiteralField*>* fieldList();
	LiteralField* literalField() ;
	Expr* arrayInitializer();
	Seq<Expr*>* elementList();
	Expr* primaryExpression();
	QualifiedName* attributeIdentifier();
	QualifiedName* propertyIdentifier();
	Seq<Expr*>* argumentList();
	Expr* memberExpression();
	Expr* memberExpressionPrime(Expr* expr);
	Expr* callExpression();
	Expr* callExpressionPrime(Expr* call_expr);
	Expr* newExpression (int new_count=0);
	Expr* leftHandSideExpression();
	Expr* postfixExpression();
	Expr* unaryExpression();
	Expr* multiplicativeExpression();
	Expr* additiveExpression();
	Expr* shiftExpression();
	Expr* relationalExpression(int flags);
	Expr* equalityExpression(int flags);
	Expr* bitwiseAndExpression(int flags);
	Expr* bitwiseXorExpression(int flags);
	Expr* bitwiseOrExpression(int flags);
	Expr* logicalAndExpression(int flags);
	Expr* logicalOrExpression(int flags);
	Expr* nonAssignmentExpression(int flags);
	Expr* conditionalExpression(int flags);
	Expr* assignmentExpression(int flags);
	Expr* commaExpression(int flags);
	
	Expr* exprListToCommaExpr(Seq<Expr*>* es);
	Expr* parenExpression();
	
	// Statement parser
	
	Stmt* statement();
	Stmt* useStatement();
	Stmt* importStatement();
	Stmt* labeledStatement();
	Stmt* returnStatement();
	Stmt* breakStatement();
	Stmt* continueStatement();
	Str* breakOrContinueLabel(Token t);
	Stmt* defaultXmlNamespaceStatement();
	Stmt* ifStatement();
	Stmt* whileStatement();
	Stmt* doStatement();
	Stmt* forStatement();
	Stmt* switchStatement();
	Seq<CaseClause*>* caseElements();
	Stmt* throwStatement();
	Stmt* tryStatement();
	Seq<CatchClause*>* catches();
	CatchClause* catchClause();
	Stmt* varStatement(bool is_const);
	Stmt* withStatement();

	// Xml initializers
	
	Expr* xmlInitializer();
	void xmlListInitializer(XmlContext* ctx);
	void xmlMarkup(XmlContext* ctx);
	void xmlElement(XmlContext* ctx);
	void xmlTagName(XmlContext* ctx);
	void xmlAttributes(XmlContext* ctx);
	void xmlElementContent(XmlContext* ctx);
	void xmlExpression(XmlContext* ctx, Escapement esc);
	void xmlAssert(XmlContext* ctx, Token t, Escapement esc=ESC_none);
	void xmlEscape(XmlContext* ctx, const wchar* cs, const wchar* limit, bool is_attr);
	void xmlPushback(wchar c);
	void xmlAtom();
	void xmlAtomSkipSpace();

	// Sundry low-level parsers
	
	Str* identifier();
	void semicolon();
	bool noNewline();
	bool newline();
	uint32_t position();
	
	// Sundry utilities
	
	bool isAdditive(Token t);
	bool isRelational(Token t, bool in_allowed);
	bool isShift(Token t);
	bool isRelationalType(Token t);
	bool isOpAssign(Token t);
	bool isMultiplicative(Token t);
	bool isEquality(Token t);
	Unop tokenToUnaryOperator(Token t);
	Binop tokenToBinaryOperator(Token t);
	Str* doubleToStr(double d);
	
	// Binding management
	
	enum RibType {
		RIB_Program,
		RIB_Class,
		RIB_Instance,
		RIB_Function
	};
	
	class BindingRib {
	public:
		BindingRib(Allocator* allocator, BindingRib* next, RibType tag);
		SeqBuilder<Binding*> bindings;
		SeqBuilder<FunctionDefn*> functionDefinitions;
		SeqBuilder<NamespaceDefn*> namespaces;
		const RibType tag;
		bool uses_finally;
		bool uses_catch;
		bool uses_arguments;
		bool uses_dxns;
		bool is_void;
		bool optional_arguments;
		BindingRib* next;
	};
	
	BindingRib* topRib;
	
	Binding* findBinding(Str* name, BindingKind kind, BindingRib* rib=NULL);
	void pushBindingRib(RibType tag);
	void popBindingRib();
	void addBinding(Str* name, BindingKind kind);
	void addVarBinding(Str* name, QualifiedName* type_name);
	void addConstBinding(Str* name, QualifiedName* type_name);
	void addNamespaceBinding(Str* name, Expr* expr);
	void addFunctionBinding(FunctionDefn* fn);
	void addMethodBinding(FunctionDefn* fn, BindingRib* rib);
	void addClass(ClassDefn* cls);
	void addInterface(InterfaceDefn* iface);
	void setUsesFinally();
	void setUsesCatch();
	void setUsesArguments();
	void setUsesDefaultXmlNamespace();

	// Lexer can be updated by "include" processing, suspended lexers are
	// pushed onto the lexerStack.
	
	class LexerState {
	public:
		Lexer* lexer;
		Token T0, T1;
		TokenValue V0, V1;
		uint32_t LP, L0, L1;
		const wchar* included_input;
		LexerState* next;
	};
	
	void pushLexerState();
	void popLexerState();
	
	LexerState* lexerStack;

	// Token queue, see implementation for extensive comments
	
	Lexer * lexer;
	
	Token T0, T1;
	TokenValue V0, V1;
	uint32_t LP;
	uint32_t L0;
	uint32_t L1;
	const wchar* included_input;

	void start();
	Token divideOperator();
	Token regexp();
	Token rightAngle();
	Token rightShiftOrRelationalOperator();
	Token hd();
	Token hd2();
	void next();
	void eat(Token t);
	bool match(Token t);
	Str* xmlValue();
	Str* stringValue();
	Str* identValue();
	Str* regexValue();
	int32_t intValue();
	uint32_t uintValue();
	double doubleValue();
	
	// Mapping from subset of tokens to attributes and operator values
	static const struct TokenMapping {
		unsigned isOpAssign:1;
		unsigned isMultiplicative:1;
		unsigned isAdditive:1;
		unsigned isRelational:1;
		unsigned isEquality:1;
		unsigned isShift:1;
		unsigned unaryOp:8;
		unsigned binaryOp:8;
	} tokenMapping[];
};

