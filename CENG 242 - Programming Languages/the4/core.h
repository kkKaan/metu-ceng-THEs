#include<iostream>
#include <map>
#include <string>
#include <cmath>
#include <iostream>

#ifndef __SYMBOLIC__CORE_H__
#define __SYMBOLIC__CORE_H__

namespace sym {
	typedef std::map<std::string, double> var_map_t;

	// A class for representing symbolic expressions
	class __expr_t {
	public:
		virtual ~__expr_t() { }

		// base methods for instance check via run-time polymorphism
		virtual bool is_unary() const;
		virtual bool is_binary() const;
		virtual bool is_nullary() const;
		
		// pure classes for interface by inheritance
		
		// Evaluate the expression using the provided variable map.
		// Returns a pointer to the resulting expression tree.
		virtual __expr_t* eval(const var_map_t& var_map = var_map_t()) const = 0;
		
		// Differentiate the expression with respect to the provided variable.
		// Returns a pointer to the resulting expression tree.
		virtual __expr_t* diff(const std::string& v) const = 0;

		// Write the expression to the output stream.
		// Returns a reference to the output stream.
		virtual std::ostream& operator<< (std::ostream &out) const = 0;

		// Compare two expressions for equality.
		// Returns true if the expressions are equal, false otherwise.
		friend std::ostream& operator<< (std::ostream &out, const __expr_t &expr)
		{ return expr.operator<<(out); }

		// some comparison operators for GoogleTests macros
		virtual bool operator==(const __expr_t& other) const = 0;
		// there is no need to expect this operator to be oveerloaded
		bool operator!=(const __expr_t& other) const { return !operator==(other); }

		friend __expr_t& operator-(const __expr_t &op);

		friend __expr_t& operator+(const __expr_t &lhs, const __expr_t &rhs);
		friend __expr_t& operator+(const double lhs, const __expr_t &rhs);
		friend __expr_t& operator+(const __expr_t &lhs, const double rhs);

		friend __expr_t& operator*(const __expr_t &lhs, const __expr_t &rhs);
		friend __expr_t& operator*(const double lhs, const __expr_t &rhs);
		friend __expr_t& operator*(const __expr_t &lhs, const double rhs);
    };

	__expr_t& exp(const __expr_t &op);
}

#endif
