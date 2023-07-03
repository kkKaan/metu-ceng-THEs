#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include "type.h"


#ifndef __SYMBOLIC__NULLARY_OPERATOR_H__
#define __SYMBOLIC__NULLARY_OPERATOR_H__

namespace sym
{
	// A symbolic constant
	class Const : public __nullary_op_t {
	public:
		Const(double value) : value_(value) {}
		
		// getter and setter methods for class attributes
		double get_value() const;
		operator double() const;

		// overriden methods for instance check via run-time polymorphism
		bool is_con() const override;
	
		
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

	private:
		double value_;
	};

	// A symbolic variable
	class Var : public __nullary_op_t {
	public:
		Var(const char* name) : var_(name) {}
		Var(const std::string& name) : var_(name) {}

		// getter and setter methods for class attributes
		std::string get_variable() const;
		operator std::string() const;
	
		// overriden methods for instance check via run-time polymorphism
		bool is_var() const override;

		
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
  
	private:
		const std::string var_;
	};
}

#endif
