#include "nullary.h"
#include "unary.h"
#include "binary.h"

namespace sym
{
	__expr_t& operator-(const __expr_t &op)
	{
		return *(new sym::NegOp(&op));
	}	
	__expr_t& exp(const __expr_t &op)
	{
		return *(new sym::ExpOp(&op));
	}

	__expr_t& operator+(const __expr_t &lhs, const __expr_t &rhs)
	{
		return *(new sym::AddOp(&lhs, &rhs));
	}

	__expr_t& operator+(double lhs, const __expr_t &rhs)
	{
		return *(new sym::AddOp(new sym::Const(lhs), &rhs));
	}

	__expr_t& operator+(const __expr_t &lhs, double rhs)
	{
		return *(new sym::AddOp(&lhs, new sym::Const(rhs)));
	}

	__expr_t& operator*(const __expr_t &lhs, const __expr_t &rhs)
	{
		return *(new sym::MulOp(&lhs, &rhs));
	}

	__expr_t& operator*(double lhs, const __expr_t &rhs)
	{
		return *(new sym::MulOp(new sym::Const(lhs), &rhs));
	}

	__expr_t& operator*(const __expr_t &lhs, double rhs)
	{
		return *(new sym::MulOp(&lhs, new sym::Const(rhs)));
	}
}
