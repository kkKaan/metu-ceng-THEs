#include <iostream>
#include "expr.h"
#include "nullary.h"
#include "unary.h"	
#include "binary.h"
#include "core.h"


int main()
{
	// sample 1 -> 2 * y

    // sym::Var y="y";
    // sym::Const c=2.0;
    // sym::MulOp op(c.eval(), y.eval());
    // std::cout << op << std::endl;

	// sample 2 ->  --1 and 1 are structurally different \n 1 and 1 are structurally equal

	// sym::Const c1 = -1.0;
    // sym::Const c2 = +3.0;
	// sym::Var x = "x", y = "y";

    // sym::NegOp op(c1.eval({{"x", 5.0}, {"y", 2.0}}));
	// sym::MulOp op2(c2.eval({{"x", 5.0}, {"y", 2.0}}), x.eval({{"x", 5.0}, {"y", 2.0}}));
	// sym::MulOp op3(y.eval({{"x", 5.0}, {"y", 2.0}}), x.eval({{"x", 5.0}, {"y", 2.0}}));
	// sym::ExpOp op4(x.eval({{"x", 5.0}, {"y", 2.0}}));
	// sym::MulOp op5(op3.eval({{"x", 5.0}, {"y", 2.0}}), op4.eval({{"x", 5.0}, {"y", 2.0}}));
    // sym::Const res = *dynamic_cast<sym::Const *>(op.eval());

	// std::cout << "op2 = " << op2 << std::endl;
	// std::cout << "op3 = " << op3 << std::endl;
	// std::cout << "op4 = " << op4 << std::endl;
	// std::cout << "op5 = " << op5 << std::endl;

   	// std::cout << op << " and " << res << " are structurally " << (op == res ? "equal" : "different") << std::endl;
    // std::cout << c2 << " and " << res << " are structurally " << (c2 == res ? "equal" : "different") << std::endl;

	// sample 3 -> expression: e^x \n differention: 0

	// sym::Const c1 = 2.0;
	// sym::Var x = "x", y = "y";

	// sym::ExpOp op(x.eval());
	// sym::Expr de = op.diff( y );

	// std::cout << "expr = " << de.is_unary() << std::endl;
	// std::cout << "expression: " << op << std::endl;
	// std::cout << "differention: " << de << std::endl;

	// sample 4 -> expression: (2 * x) + y \n differentiation: 2 \n equality with 2: true
	
    // sym::Const c = 2.0;
    // sym::Var x = "x", y = "y";

    // sym::Expr e = c * x + y;
    // sym::Expr de = e.diff(x);

   	// std::cout << "expression: " << e << std::endl;
  	// std::cout << "differention: " << de << std::endl;
   	// std::cout << "equality with " << c << ": " << (de == c ? "true" : "false") << std::endl;

	// sample 5

	sym::Var x="x";
    sym::ExpOp op(x.eval());
    sym::__expr_t * diff = op.diff(x);

	std::cout << "diff " << diff << std::endl;
	std::cout << "var: " << x.eval() << std::endl;	
    std::cout << op << std::endl;
    diff->operator<<(std::cout).operator<<(std::endl);
   
    delete diff;

	std::cout << "diff " << diff << std::endl;

	return 0;
}
