#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	bool NegOp::is_neg() const
	{
		return true;
	}

	__expr_t* NegOp::eval(const var_map_t& vars) const
	{
		__expr_t* evaluated_op = this->operand->eval(vars);
		if (auto const_op = dynamic_cast<Const*>(evaluated_op))
		{
			return new Const(-(const_op->get_value()));
		}
		else
		{
			return new NegOp(this->operand);
		}
	}

	__expr_t* NegOp::diff(const std::string& v) const
	{
		return new NegOp(this->operand->diff(v));
	}

	std::ostream& NegOp::operator<< (std::ostream &out) const
	{
		out << "-";
		if (!(this->operand->is_nullary()))
		{
			out << "(";
		}
		out << *(this->operand);
		if (!(this->operand->is_nullary()))
		{
			out << ")";
		}
		return out;
	}

	bool NegOp::operator==(const __expr_t& other) const
	{
		if (const NegOp* other_neg = dynamic_cast<const NegOp*>(&other))
		{
			return *(this->operand) == *other_neg->operand;
		}
		else
		{
			return false;
		}
	}
}

namespace sym 
{
	bool ExpOp::is_exp() const
	{
		return true;
	}

	__expr_t* ExpOp::eval(const var_map_t& vars) const
	{
		__expr_t* evaluated_op = this->operand->eval(vars);
		if (auto const_op = dynamic_cast<Const*>(evaluated_op))
		{
			return new Const(std::exp(const_op->get_value()));
		}
		else
		{
			return new ExpOp(this->operand);
		}
	}

	__expr_t* ExpOp::diff(const std::string& v) const
	{
		return new MulOp(this->operand->diff(v), new ExpOp(this->operand));
	}

	std::ostream& ExpOp::operator<< (std::ostream &out) const
	{
		out << "e^";
		if(!(this->operand->is_nullary()))
		{
			out << "(";
		}
		out << *this->operand;
		if(!(this->operand->is_nullary()))
		{
			out << ")";
		}		
		return out;
	}

	bool ExpOp::operator==(const __expr_t& other_) const
	{
		if (const ExpOp* other_exp = dynamic_cast<const ExpOp*>(&other_))
		{
			return *(this->operand) == *other_exp->operand;
		}
		else
		{
			return false;
		}	
	}	
}