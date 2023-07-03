#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include "type.h"


#ifndef __SYMBOLIC__BINARY_OPERATOR_H__
#define __SYMBOLIC__BINARY_OPERATOR_H__

namespace sym
{
	// A symbolic binary operation
	class AddOp : public __binary_op_t {
	public:
		AddOp(const __expr_t* lhs, const __expr_t* rhs) : __binary_op_t(lhs, rhs) {}

		// overriden methods for instance check via run-time polymorphism
		bool is_add() const override;
	
		// Evaluate the expression using the provided variable map.
		// Returns a pointer to the resulting expression tree. 
		__expr_t* eval(const var_map_t& vars = var_map_t()) const override;

		// Differentiate the expression with respect to the provided variable.
		// Returns a pointer to the resulting expression tree.
		__expr_t* diff(const std::string& v) const override;

		// Write the expression to the output stream.
		// Returns a reference to the output stream.
		std::ostream& operator<< (std::ostream &out) const override;

		// Compare two expressions for equality.
		// Returns true if the expressions are equal, false otherwise.
		bool operator==(const __expr_t& other) const override;
	};

	// A symbolic binary operation
	class MulOp : public __binary_op_t {
	public:
		MulOp(const __expr_t* lhs, const __expr_t* rhs) : __binary_op_t(lhs, rhs) {}

		// overriden methods for instance check via run-time polymorphism
		bool is_mul() const override;
	
		// Evaluate the expression using the provided variable map.
		// Returns a pointer to the resulting expression tree. 
		__expr_t* eval(const var_map_t& vars = var_map_t()) const override;

		// Differentiate the expression with respect to the provided variable.
		// Returns a pointer to the resulting expression tree.
		__expr_t* diff(const std::string& v) const override;

		// Write the expression to the output stream.
		// Returns a reference to the output stream.
		std::ostream& operator<< (std::ostream &out) const override;

		// Compare two expressions for equality.
		// Returns true if the expressions are equal, false otherwise.
		bool operator==(const __expr_t& other) const override;
	};
}

#endif
