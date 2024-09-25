/* -*- tab-width: 4 -*- */
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

#include "avmplus.h"

#ifdef VMCFG_EVAL

#include "eval.h"

namespace avmplus
{
	namespace RTC
	{
		using namespace ActionBlockConstants;

		// Context management
		
		enum CtxType {
			CTX_Activation,
			CTX_Break,
			CTX_Catch,
			CTX_Continue,
			CTX_Finally,
			CTX_Function,
			CTX_ClassMethod,
			CTX_Program,
			CTX_With
		};
		
		class Ctx {
		public:
			Ctx(CtxType tag, Ctx* next)
				: tag(tag)
				, next(next)
			{
			}
			
			const CtxType  tag;
			Ctx * const    next;
		};

		class ControlFlowCtx : public Ctx {
		public:
			ControlFlowCtx(CtxType tag, Label* label, Ctx* ctx0)
				: Ctx(tag, ctx0)
				, label(label)
			{
			}
			Label * const label;
		};
		
		class BreakCtx : public ControlFlowCtx {
		public:
			BreakCtx(Label* label, Ctx* ctx0, Str* label_name=NULL)
				: ControlFlowCtx(CTX_Break, label, ctx0)
				, label_name(label_name)
			{
			}
			Str * const label_name;
		};
		
		class ContinueCtx : public ControlFlowCtx {
		public:
			ContinueCtx(Label* label, Seq<Str*>* label_names, Ctx* ctx0) 
				: ControlFlowCtx(CTX_Continue, label, ctx0)
				, label_names(label_names)
			{
			}
			Seq<Str*>* const label_names;
		};
	
		class ScopeCtx : public Ctx {
		public:
			ScopeCtx(CtxType tag, uint32_t scope_reg, Ctx* ctx0)
				: Ctx(tag, ctx0)
				, scope_reg(scope_reg)
			{
			}
			const uint32_t scope_reg;
		};
		
		class WithCtx : public ScopeCtx {
		public:
			WithCtx(uint32_t scope_reg, Ctx* ctx0)
				: ScopeCtx(CTX_With, scope_reg, ctx0)
			{
			}
		};
		
		struct CatchCtx : public ScopeCtx {
			CatchCtx(uint32_t scope_reg, Ctx* ctx0)
				: ScopeCtx(CTX_Catch, scope_reg, ctx0)
			{
			}
		};
		
		class ActivationCtx : public ScopeCtx {
		public:
			ActivationCtx(uint32_t scope_reg, Ctx* ctx0)
				: ScopeCtx(CTX_Activation, scope_reg, ctx0)
			{
			}
		};
		
		class FinallyCtx : public Ctx {
		public:
			FinallyCtx(Allocator* allocator, Label* Lfinally, uint32_t returnreg, Ctx* ctx0)
				: Ctx(CTX_Finally, ctx0)
				, Lfinally(Lfinally)
				, returnreg(returnreg)
				, nextLabel(0)
				, returnLabels(allocator)
			{
			}
			
			uint32_t addReturnLabel(Label* l);
			
			Label * const Lfinally;
			const uint32_t returnreg;
			uint32_t nextLabel;
			SeqBuilder<Label*> returnLabels;
		};
		
		uint32_t FinallyCtx::addReturnLabel(Label* l)
		{
			returnLabels.addAtEnd(l);
			return nextLabel++;
		}
		
		class FunctionCtx : public Ctx {
		public:
			FunctionCtx(Allocator* allocator)
				: Ctx(CTX_Function, NULL)
				, namespaces(allocator)
			{
			}
			SeqBuilder<NamespaceDefn*> namespaces;
		};
		
		class ProgramCtx : public Ctx {
		public:
			ProgramCtx(Allocator* allocator, uint32_t capture_reg) 
				: Ctx(CTX_Program, NULL)
				, namespaces(allocator)
				, capture_reg(capture_reg)
			{
			}
			SeqBuilder<NamespaceDefn*> namespaces;
			const uint32_t capture_reg;
		};
		
		static bool matchLabel(Ctx* ctx, Str* label)
		{
			if (label == NULL)
				return true;
			switch (ctx->tag) {
				case CTX_Continue: {
					Seq<Str*>* labels = ((ContinueCtx*)ctx)->label_names;
					while (labels != NULL)
						if (label == labels->hd)
							return true;
					return false;
				}
				case CTX_Break:
					return label == ((BreakCtx*)ctx)->label_name;
				default:
					return false;
			}
		}

		void Cogen::unstructuredControlFlow(Ctx* ctx, bool (hit)(Ctx*,void*), void* package, bool jump, const char* msg, uint32_t pos) 
		{
			while (ctx != NULL) {
				if (hit(ctx, package)) {
					if (jump)
						I_jump(((ControlFlowCtx*)ctx)->label);
					return;
				}
				
				if(ctx->tag == CTX_With || ctx->tag == CTX_Catch) {
					ScopeCtx* ctx1 = (ScopeCtx*)ctx;
					I_popscope();
					I_kill(ctx1->scope_reg);
				}
				
				if (ctx->tag == CTX_Finally) {
					// FIXME: unstructured control flow past 'finally' clauses
					/* The verifier can't deal with all these combinations, it appears to
					 be a limitation of how it does control flow analysis.  So throw
					 a SyntaxError here until the verifier can be fixed.
					 
					 let myreturn = stk.nextReturn++;
					 asm.I_pushint(ctx.cp.int32(myreturn));
					 asm.I_setlocal(stk.returnreg);
					 asm.I_jump(stk.label);
					 stk.returnAddresses[myreturn] = asm.I_label(undefined);
					 
					 */
					compiler->internalError(pos, "Limitation: Can't generate code for break/continue/return past 'finally' block yet.");
				}
				ctx = ctx->next;
			}
			compiler->syntaxError(pos, "%s", msg);
		}

		inline bool mustPushThis(CtxType tag) {
			return tag == CTX_ClassMethod || tag == CTX_Program;
		}

		inline bool mustPushScopeReg(CtxType tag) {
			return tag == CTX_With || tag == CTX_Catch || tag == CTX_Activation;
		}
		
		static void restoreScopes(Cogen* cogen, Ctx* ctx) 
		{
			if (ctx == NULL)
				return;
			if (ctx->tag != CTX_Function && ctx->tag != CTX_ClassMethod)
				restoreScopes(cogen, ctx->next);
			if (mustPushThis(ctx->tag)) {
				cogen->I_getlocal(0);
				cogen->I_pushscope();
			}
			if (mustPushScopeReg(ctx->tag)) {
				ScopeCtx* ctx1 = (ScopeCtx*)ctx;
				cogen->I_getlocal(ctx1->scope_reg);
				if (ctx1->tag == CTX_With)
					cogen->I_pushwith();
				else
					cogen->I_pushscope();
			}
		}		
		
		// Statement code generators

		void Program::cogenBody(Cogen* cogen, uint32_t activation_reg)
		{
			(void)activation_reg;
			AvmAssert(activation_reg == 0);
			uint32_t capture_reg = cogen->getTemp();
			cogen->I_pushundefined();
			cogen->I_coerce_a();
			cogen->I_setlocal(capture_reg);
			ProgramCtx ctx(cogen->allocator, capture_reg);
			for ( Seq<Stmt*>* stmts = this->stmts ; stmts != NULL ; stmts = stmts->tl )
				stmts->hd->cogen(cogen, &ctx);
			cogen->I_getlocal(capture_reg);
			cogen->I_returnvalue();
		}

		void FunctionDefn::cogenBody(Cogen* cogen, uint32_t activation_reg)
		{
			FunctionCtx ctx0(cogen->allocator);
			ActivationCtx ctx1(activation_reg, &ctx0);
			Ctx* ctx = activation_reg == 0 ? (Ctx*)&ctx0 : (Ctx*)&ctx1;
			
			for ( Seq<Stmt*>* stmts = this->stmts ; stmts != NULL ; stmts = stmts->tl )
				stmts->hd->cogen(cogen, ctx);
			cogen->I_returnvoid();
		}
		
		void EmptyStmt::cogen(Cogen*, Ctx*)
		{
			// nothing
		}
		
		void BlockStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			for ( Seq<Stmt*>* ss = stmts ; ss != NULL ; ss = ss->tl )
				ss->hd->cogen(cogen, ctx);
		}
		
		void LabeledStmt::cogen(Cogen* cogen, Ctx* ctx) 
		{
			Label* L0 = cogen->newLabel();
			BreakCtx ctx1(L0, ctx, label);
			stmt->cogen(cogen, &ctx1);
			cogen->I_label(L0);
		}

		void ExprStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			cogen->I_debugline(pos);
			expr->cogen(cogen);
			Ctx* c;
			for ( c = ctx ; c->tag != CTX_Program && c->tag != CTX_Function && c->tag != CTX_ClassMethod ; c = c->next )
				;
			if (c->tag == CTX_Program) {
				cogen->I_coerce_a();
				cogen->I_setlocal(((ProgramCtx*)c)->capture_reg);
			}
			else
				cogen->I_pop();
		}

		void IfStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			Label* L1 = cogen->newLabel();
			cogen->I_debugline(pos);
			expr->cogen(cogen);
			cogen->I_iffalse(L1);
			consequent->cogen(cogen, ctx);
			if (alternate != NULL) {
				Label* L2 = cogen->newLabel();
				cogen->I_jump(L2);
				cogen->I_label(L1);
				alternate->cogen(cogen, ctx);
				cogen->I_label(L2);
			}
			else
				cogen->I_label(L1);
		}

		void WhileStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			Label* Lbreak = cogen->newLabel();
			Label* Lcont  = cogen->newLabel();
			cogen->I_label(Lcont);
			cogen->I_debugline(pos);
			expr->cogen(cogen);
			cogen->I_iffalse(Lbreak);
			BreakCtx ctx1(Lbreak, ctx);
			ContinueCtx ctx2(Lcont, labels, &ctx1);
			body->cogen(cogen, &ctx2);
			cogen->I_jump(Lcont);
			cogen->I_label(Lbreak);
		}

		void DoWhileStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			Label* Lbreak = cogen->newLabel();
			Label* Lcont  = cogen->newLabel();
			Label* Ltop   = cogen->newLabel();
			cogen->I_label(Ltop);
			BreakCtx ctx1(Lbreak, ctx);
			ContinueCtx ctx2(Lcont, labels, &ctx1);
			body->cogen(cogen, &ctx2);
			cogen->I_label(Lcont);
			cogen->I_debugline(pos);
			expr->cogen(cogen);
			cogen->I_iftrue(Ltop);
			cogen->I_label(Lbreak);
		}

		void ForStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			Label* Lbreak = cogen->newLabel();
			Label* Lcont = cogen->newLabel();
			Label* Ltop = cogen->newLabel();
			if (init != NULL) {
				init->cogen(cogen);
				cogen->I_pop();
			}
			cogen->I_label(Ltop);
			if (test != NULL) {
				test->cogen(cogen);
				cogen->I_iffalse(Lbreak);
			}
			BreakCtx ctx1(Lbreak, ctx);
			ContinueCtx ctx2(Lcont, labels, &ctx1);
			body->cogen(cogen, &ctx2);
			cogen->I_label(Lcont);
			if (update != NULL) {
				update->cogen(cogen);
				cogen->I_pop();
			}
			cogen->I_jump(Ltop);
			cogen->I_label(Lbreak);
		}
		
		// Instruction set bug workaround.
		//
		// In hasnext2, the second argument reg must be known to be 'int', but this 
		// means that if we want to kill it below the loop then all paths past that
		// kill (from statements enclosing this statement) must have a kill for the
		// register too.  This is just needless complexity.  Yet if there is not a
		// kill at the end of the loop, any enclosing loop will get into trouble
		// with the verifier because the types along the backward edge to the top of
		// the loop will not match the initial values into that loop.
		//
		// To work around this we use two index registers here, and one has a very short
		// lifetime, just across the hasnext2 instruction, to keep the verifier happy.

		void ForInStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			Allocator* allocator = cogen->allocator;
			Label* Lbreak = cogen->newLabel();
			Label* Lcont = cogen->newLabel();
			Label* Ltop = cogen->newLabel();
			
			uint32_t T_obj = cogen->getTemp();
			uint32_t T_idx = cogen->getTemp();
			uint32_t T_idx2 = cogen->getTemp();
			uint32_t T_val = cogen->getTemp();
			
			if (init != lhs) {
				init->cogen(cogen);
				cogen->I_pop();
			}
			obj->cogen(cogen);

			cogen->I_coerce_a();
			cogen->I_setlocal(T_obj);
			cogen->I_pushbyte(0);
			cogen->I_coerce_a();
			cogen->I_setlocal(T_idx);
			
			cogen->I_label(Ltop);
			
			cogen->I_getlocal(T_idx);
			cogen->I_coerce_i();
			cogen->I_setlocal(T_idx2);
			cogen->I_hasnext2(T_obj, T_idx2);
			cogen->I_getlocal(T_idx2);
			cogen->I_coerce_a();
			cogen->I_setlocal(T_idx);
			cogen->I_kill(T_idx2);
			cogen->I_iffalse(Lbreak);
			cogen->I_getlocal(T_obj);
			cogen->I_getlocal(T_idx);
			cogen->I_coerce_i();

			if (is_each)
				cogen->I_nextvalue();
			else 
				cogen->I_nextname();
			cogen->I_setlocal(T_val);
			(ALLOC(AssignExpr, (OPR_assign, lhs, ALLOC(RefLocalExpr, (T_val)))))->cogen(cogen);
			cogen->I_pop();
			
			BreakCtx ctx1(Lbreak, ctx);
			ContinueCtx ctx2(Lcont, labels, &ctx1);
			body->cogen(cogen, &ctx2);
			
			cogen->I_label(Lcont);
			cogen->I_jump(Ltop);
			
			cogen->I_label(Lbreak);
			cogen->I_kill(T_val);
			cogen->I_kill(T_idx);
			cogen->I_kill(T_obj);
		}
		
		static bool hitBreak(Ctx* ctx, void* package) 
		{
			return ctx->tag == CTX_Break && matchLabel(ctx, (Str*)package);
		}
		
		void BreakStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			cogen->unstructuredControlFlow(ctx,
										   hitBreak,
										   (void*)label,
										   true,
										   (label == NULL ? "No 'break' allowed here" : "'break' to undefined label"),
										   pos);
		}

		static bool hitContinue(Ctx* ctx, void* package) 
		{
			return ctx->tag == CTX_Continue && matchLabel(ctx, (Str*)package);
		}
			
		void ContinueStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			cogen->unstructuredControlFlow(ctx,
										   hitContinue,
										   (void*)label,
										   true,
										   (label == NULL ? "No 'continue' allowed here" : "'continue' to undefined label"),
										   pos);
		}
		
		void ThrowStmt::cogen(Cogen* cogen, Ctx*)
		{
			cogen->I_debugline(pos);
			expr->cogen(cogen);
			cogen->I_throw();
		}

		static bool hitFunction(Ctx* ctx, void*)
		{
			return ctx->tag == CTX_Function;
		}
		
		void ReturnStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			uint32_t tmp = 0;
			
			if (expr != NULL) {
				cogen->I_debugline(pos);
				expr->cogen(cogen);
				tmp = cogen->getTemp();
				cogen->I_coerce_a();
				cogen->I_setlocal(tmp);
			}
			
			cogen->unstructuredControlFlow(ctx,
										   hitFunction,
										   NULL,
										   false,
										   "No 'return' allowed here.");
			
			if (expr == NULL)
				cogen->I_returnvoid();
			else {
				cogen->I_getlocal(tmp);
				cogen->I_kill(tmp);
				cogen->I_returnvalue();
			}
		}
		
		void WithStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			uint32_t scopereg = cogen->getTemp();
			
			cogen->I_debugline(pos);
			expr->cogen(cogen);
			cogen->I_dup();
			cogen->I_setlocal(scopereg);
			cogen->I_pushwith();
			WithCtx ctx1(scopereg, ctx);
			body->cogen(cogen, &ctx1);
			cogen->I_popscope();
			cogen->I_kill(scopereg);
		}

		void SwitchStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			int32_t low, high;
			bool has_default;
			if (analyze(&low, &high, &has_default))
				cogenFast(cogen, ctx, low, high, has_default);
			else
				cogenSlow(cogen, ctx);
		}
		
		// FIXME: implement switch statement analysis and fast switch generation
		// (Expand the use of tags on expr nodes to enable analysis; implement I_lookupswitch in the back-end too.)

		bool SwitchStmt::analyze(int32_t* /* low*/, int32_t* /* high*/, bool* /* has_default*/)
		{
			return false;
			/*
			let cases = s.cases;
			uint32_t count = 0;
			*low = 0x7FFFFFFF;
			*high = (-0x7FFFFFFF - 1);
			*has_default = false;
			
			for ( let i=0, limit=cases.length ; i < limit ; i++ ) {
				let e = cases[i].expr;
				if (e == NULL)
					*has_default = true;
				else if (e is LiteralInt) {
					low = Math.min(low, e.intValue);
					high = Math.max(high, e.intValue);
					count++;
				}
				else
					return false;
			}
			if (count < 4)
				return false;
			if (count * 3 < ((high - low) + 1))
				return false;
			return [low,high,has_default];
			 */
		}
		
		void SwitchStmt::cogenFast(Cogen*, Ctx*, int32_t /*low*/, int32_t /*high*/, bool /*has_default*/)
		{
			// No-op until the analyze() method is implemented
			/*
			let count = 0;
			let {expr, cases} = s;
			let {asm, cp} = ctx;
			let t = asm.getTemp();
			
			let Ldef = asm.newLabel();
			let Lcases = new Array(high-low+1);
			let Lbreak = asm.newLabel();
			let nctx = pushBreak(ctx, Lbreak);
			let ldef_emitted = false;
			
			cgExpr(ctx, expr);                    // switch value
			asm.I_pushint(cp.int32(low));         // offset
			asm.I_subtract();                     // bias it
			asm.I_dup();
			asm.I_convert_i();                    // convert to int
			asm.I_dup();
			asm.I_setlocal(t);                    //   and save
			asm.I_equals();                       // if computed value and int value are 
			asm.I_getlocal(t);                    // otherwise dispatch
			asm.killTemp(t);
			asm.I_swap();
			asm.I_iffalse(Ldef);                  //   not the same then default case
			
			let Ldefault = asm.I_lookupswitch(undefined, Lcases);
			
			// Make a prepass to find all the case labels that do not have a
			// case (except maybe the default case).  If Lcases[i] is not
			// handled then Lhandled[i] will be false.
			
			let Lhandled = new Array(Lcases.length);
			for ( let i=0, limit=cases.length ; i < limit ; i++ ) {
				let c = cases[i];
				let e = c.expr;
				
				if (e != null) {
					assert(e is LiteralInt);
					Lhandled[e.intValue - low] = true;
				}
			}
			
			// Now emit code for all the cases.  If there is a default
			// case then all unhandled labels are emitted there.
			
			for ( let i=0, limit=cases.length ; i < limit ; i++ ) {
				let c = cases[i];
				let e = c.expr;
				
				if (e == null) {
					asm.I_label(Ldef);
					asm.I_pop();
					asm.I_label(Ldefault);
					ldef_emitted = true;
					for ( let j=0, jlimit=Lhandled.length ; j < jlimit ; j++ )
						if (!Lhandled[j])
							asm.I_label(Lcases[j]);
				}
				else {
					assert(e is LiteralInt);
					
					// There might be duplicate case selector values, but only the first one counts.
					if (Lcases[e.intValue - low] !== false) {
						asm.I_label(Lcases[e.intValue - low]);
						Lcases[e.intValue - low] = false;
					}
				}
				
				let stmts = c.stmts;
				for ( let j=0, jlimit=stmts.length ; j < jlimit ; j++ )
					cgStmt(nctx, stmts[j] );
			}
			
			// If there was not a default case then map unhandled case
			// values to this point.
			
			if (!has_default) {
				for ( let j=0, jlimit=Lhandled.length ; j < jlimit ; j++ )
					if (!Lhandled[j])
						asm.I_label(Lcases[j]);
			}
			
			if (!ldef_emitted) {
				asm.I_label(Ldef);
				asm.I_pop();
			}
			asm.I_label(Lbreak);
			 */
		}
		
		void SwitchStmt::cogenSlow(Cogen* cogen, Ctx* ctx)
		{
			uint32_t tmp = cogen->getTemp();
			
			Label* Ldefault = NULL;
			Label* Lnext = cogen->newLabel();
			Label* Lfall = NULL;
			Label* Lbreak = cogen->newLabel();
			
			cogen->I_debugline(pos);
			expr->cogen(cogen);
			cogen->I_coerce_a();
			cogen->I_setlocal(tmp);
			cogen->I_jump(Lnext);

			BreakCtx ctx1(Lbreak, ctx);
			
			for ( Seq<CaseClause*>* cases=this->cases ; cases != NULL ; cases = cases->tl ) {
				CaseClause* c = cases->hd;
				
				if (c->expr == NULL) {
					AvmAssert(Ldefault == NULL);
					Ldefault = cogen->newLabel();
					cogen->I_label(Ldefault);				// label default pos
				}
				else {
					if (Lnext != NULL) {
						cogen->I_label(Lnext);			    // label next pos
						Lnext = NULL;
					}
					cogen->I_debugline(c->pos);
					c->expr->cogen(cogen);					// check for match
					cogen->I_getlocal(tmp);
					cogen->I_strictequals();
					Lnext = cogen->newLabel();
					cogen->I_iffalse(Lnext);
				}
				
				if (Lfall != NULL) {					// label fall through pos
					cogen->I_label(Lfall);
					Lfall = NULL;
				}
				
				for ( Seq<Stmt*>* stmts = c->stmts ; stmts != NULL ; stmts = stmts->tl )
					stmts->hd->cogen(cogen, &ctx1);
				
				Lfall = cogen->newLabel();
				cogen->I_jump(Lfall);			// fall through
			}
			
			if (Lnext != NULL)
				cogen->I_label(Lnext);
			if (Ldefault != NULL)
				cogen->I_jump(Ldefault);
			if (Lfall != NULL)
				cogen->I_label(Lfall);
			cogen->I_label(Lbreak);
			cogen->I_kill(tmp);
		}
		
		void TryStmt::cogen(Cogen* cogen, Ctx* ctx)
		{
			if (finallyblock != NULL)
				cogenWithFinally(cogen, ctx);
			else
				cogenNoFinally(cogen, ctx);
		}
		
		// If there's a finally block then:
		//
		// - there is a generated catch around the try-catch complex with a handler that
		//   handles any exception type
		// - the handler in that block must visit the finally code and then re-throw if
		//   the finally code returns normally
		// - code in the try block or the catch block(s) is compiled with a ctx that
		//   records the fact that there is a finally block, so that exits to the outside of 
		//   the try/catch block by means of break/continue (labelled or not) must visit 
		//   the finally block (in inside-out order if there are several)
		// - break, continue, and return must look for finally blocks
		//
		// Visiting the finally block may thus be done from various places.  To avoid
		// code bloat it is generated out-of-line.  Visiting is done by setting a register
		// to the "return" address, then jumping to the finally code, which ends with a
		// switch statement that jumps back to all the possible return points.
		//
		// Each finally block gets its own register, it's recorded in the ctx rib.
		//
		// The code for the finally block's "switch" can't be generated until we've seen
		// all the code that can visit it (represented as a list of id/labels in the ctx rib).
		//
		// There is a counter in the ctx, and id's for the switch are generated from it.
		// Its initial value is 0.  lookupswitch can be used.
		
		void TryStmt::cogenWithFinally(Cogen* cogen, Ctx* ctx)
		{
			uint32_t returnreg = cogen->getTemp();	// the local that records the index of the label this finally block should return to
			Label* Lfinally = cogen->newLabel();	// the address of the finally block body
			
			FinallyCtx fctx(cogen->allocator, Lfinally, returnreg, ctx);
			
			// Lreturn is the address in this finally block that visited, outer finally blocks return to
			// after executing to completion.
			Label* Lreturn = cogen->newLabel();
			uint32_t myreturn = fctx.addReturnLabel(Lreturn);

			// Lend is the address to branch to to get out of the finally block after entering the
			// finally block normally and executing it without throwing any exceptions.
			Label* Lend = cogen->newLabel();
			uint32_t myend = fctx.addReturnLabel(Lend);
			
			uint32_t code_start = cogen->getCodeLength();
			cogenNoFinally(cogen, &fctx);
			uint32_t code_end = cogen->getCodeLength();

			// Fallthrough from try-catch: visit the finally block.  This code must not be in the
			// scope of the generated exception handler.
			
			cogen->I_pushuint(cogen->emitUInt(myend));	// return to Lend
			cogen->I_setlocal(returnreg);
			cogen->I_jump(Lfinally);                    // control continues at Lend below
			
			// Generated catch block to handle throws out of try-catch:
			// capture the exception, visit the finally block with return
			// to Lreturn, then re-throw the exception at Lreturn.
			//
			// Use a lightweight exception handler; always store the value
			// in a register.
			
			uint32_t savedExn = cogen->getTemp();
			/*uint32_t catch_idx =*/ cogen->emitException(code_start, code_end, cogen->getCodeLength(), 0, 0);

			cogen->startCatch();				// push 1 item
			cogen->I_setlocal(savedExn);		// pop and save it
			
			restoreScopes(cogen, ctx);			// finally block needs correct scopes
			
			cogen->I_pushuint(cogen->emitUInt(myreturn));
			cogen->I_setlocal(returnreg);
			cogen->I_jump(Lfinally);			// control continues at Lreturn directly below
			cogen->I_label(Lreturn);
			cogen->I_getlocal(savedExn);
			cogen->I_kill(savedExn);
			cogen->I_throw();
			
			// Finally block
			
			cogen->I_label(Lfinally);
			for ( Seq<Stmt*>* stmts = this->finallyblock ; stmts != NULL ; stmts = stmts->tl )
				stmts->hd->cogen(cogen, ctx);

			// The return-from-subroutine code at the end of the finally block
			// From the above it may seem that there are at most two labels in the list,
			// but this is not so: unstructuredControlFlow can place more labels into it.

			Seq<Label*>* labels;
			uint32_t i;
			for ( i=0, labels = fctx.returnLabels.get() ; labels != NULL ; i++, labels = labels->tl ) {
				cogen->I_getlocal(returnreg);
				cogen->I_pushuint(cogen->emitUInt(i));
				cogen->I_ifeq(labels->hd);
			}
				
			cogen->I_label(Lend);
			cogen->I_kill(returnreg);
		}
		
		void TryStmt::cogenNoFinally(Cogen* cogen, Ctx* ctx)
		{
			uint32_t code_start = cogen->getCodeLength();
			for ( Seq<Stmt*>* stmts = this->tryblock ; stmts != NULL ; stmts = stmts->tl )
				stmts->hd->cogen(cogen, ctx);
			uint32_t code_end = cogen->getCodeLength();
			
			Label* Lend = cogen->newLabel();
			cogen->I_jump(Lend);

			// More general than we need it or indeed can support for ES3, so catch the problem
			// in debug mode at least.
			AvmAssert(this->catches == NULL || this->catches->tl == NULL);

			for( Seq<CatchClause*>* catches = this->catches ; catches != NULL ; catches = catches->tl )
				cgCatch(cogen, ctx, code_start, code_end, Lend, catches->hd);
			
			cogen->I_label(Lend);
		}
		
		void TryStmt::cgCatch(Cogen* cogen, Ctx* ctx, uint32_t code_start, uint32_t code_end, Label* Lend, CatchClause* catchClause)
		{
			Compiler* compiler = cogen->compiler;
			uint32_t catch_idx = cogen->emitException(code_start,
													  code_end,
													  cogen->getCodeLength(),
													  0, 
													  cogen->abc->addQName(compiler->NS_public, cogen->emitString(catchClause->name)));
			
			cogen->startCatch();
			
			uint32_t t = cogen->getTemp();
			restoreScopes(cogen, ctx);
			CatchCtx ctx1(t, ctx);
			
			cogen->I_newcatch(catch_idx);
			cogen->I_dup();
			cogen->I_setlocal(t);	// Store catch scope in register so it can be restored later
			cogen->I_dup();
			cogen->I_pushscope();
			
			// Store the exception object in the catch scope.
			cogen->I_swap();
			cogen->I_setproperty(cogen->abc->addQName(compiler->NS_public, cogen->emitString(catchClause->name)));
			
			// catch block body
			for ( Seq<Stmt*>* stmts = catchClause->stmts ; stmts != NULL ; stmts = stmts->tl )
				stmts->hd->cogen(cogen, &ctx1);
			
			cogen->I_kill(t);
			
			cogen->I_popscope();
			cogen->I_jump(Lend);
		}
		
		void UseNamespaceStmt::cogen(Cogen* /* cogen*/, Ctx* /* ctx*/)
		{
			AvmAssert(!"Not implemented: UseNamespaceStmt");
		}

		void ImportStmt::cogen(Cogen* /* cogen */, Ctx* /* ctx */)
		{
			AvmAssert(!"Not implemented: ImportStmt");
		}

		void DefaultXmlNamespaceStmt::cogen(Cogen* cogen, Ctx*)
		{
			expr->cogen(cogen);
			cogen->I_dxnslate();
		}
	}
}

#endif // VMCFG_EVAL
