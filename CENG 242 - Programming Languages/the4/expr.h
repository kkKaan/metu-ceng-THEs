#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <memory>
#include "type.h"
#include "nullary.h"


#ifndef __SYMBOLIC__EXPRESSION_H__
#define __SYMBOLIC__EXPRESSION_H__

namespace sym
{
	class Expr : public __expr_t {
	public:
		Expr(const Const& c);
		Expr(const Var& v);
		Expr(const __expr_t* expr_);
		Expr(const __expr_t& expr_);
		Expr(const Expr& other);

		~Expr();

		// derived methods for instance check via run-time polymorphism

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
		bool operator==(const Expr& other) const;

	private:
		const __expr_t *expr_;
	};

}

#endif
