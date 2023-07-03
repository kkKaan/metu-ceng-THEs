#include "core.h"

#ifndef __SYMBOLIC__TYPE_H__
#define __SYMBOLIC__TYPE_H__

namespace sym 
{
	// A symbolic constant / nullary operator
	class __nullary_op_t : public __expr_t {
	public:
		__nullary_op_t() {}
		virtual ~__nullary_op_t();
	
		// overriden methods for instance check via run-time polymorphism
		bool is_nullary() const override;

		// base methods for instance check via run-time polymorphism
		virtual bool is_con() const;
		virtual bool is_var() const;
	};

	// A symbolic unary operation
	class __unary_op_t : public __expr_t {
	public:
		__unary_op_t(const __expr_t* op) : operand(op) {}
		virtual ~__unary_op_t();
	
		// overriden methods for instance check via run-time polymorphism
		bool is_unary() const override;

		// base methods for instance check via run-time polymorphism
		virtual bool is_neg() const;
		virtual bool is_exp() const;

	protected:
		const __expr_t *operand;
	};

	// A symbolic binary operation
	class __binary_op_t : public __expr_t {
	public:
		__binary_op_t(const __expr_t* lhs, const __expr_t* rhs) : lhs_(lhs), rhs_(rhs) {}
		virtual ~__binary_op_t();
		
		// overriden methods for instance check via run-time polymorphism
		bool is_binary() const override;

		// base methods for instance check via run-time polymorphism
		virtual bool is_add() const;
		virtual bool is_mul() const;

	protected:
		const __expr_t *lhs_, *rhs_;
	};
}

#endif
