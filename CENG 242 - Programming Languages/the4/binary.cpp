#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
	bool AddOp::is_add() const
	{
		return true;
	}	

	__expr_t* AddOp::eval(const var_map_t& vars) const
	{
		auto lhs = this->lhs_->eval(vars);
		auto rhs = this->rhs_->eval(vars);

		Const* lhs_con = dynamic_cast<Const*>(lhs);
		Const* rhs_con = dynamic_cast<Const*>(rhs);

		if (lhs_con != nullptr && lhs_con->get_value() == 0.0)
		{
			// if lhs is a zero-constant, return the evaluation of rhs
			// delete lhs;
			return rhs;
		}
		else if (rhs_con != nullptr && rhs_con->get_value() == 0.0)
		{
			// if rhs is a zero-constant, return the evaluation of lhs
			// delete rhs;
			return lhs;
		}
		else if (lhs_con != nullptr && rhs_con != nullptr)
		{
			// if both lhs and rhs are constants, return a new constant equal to their sum
			double sum = lhs_con->get_value() + rhs_con->get_value();
			// delete lhs;
			// delete rhs;
			return new Const(sum);
		}
		else
		{
			// otherwise, return a new AddOp with the evaluated lhs and rhs
			return new AddOp(lhs, rhs);
		}
	}

	__expr_t* AddOp::diff(const std::string& v) const
	{
		// differentiate lhs and rhs and return their sum as a new AddOp
		__expr_t* lhs_diff = this->lhs_->diff(v);
		__expr_t* rhs_diff = this->rhs_->diff(v);
		
		return new AddOp(lhs_diff, rhs_diff);
	}

	std::ostream& AddOp::operator<< (std::ostream &out) const
	{
		// Cast lhs and rhs to Const*
		const Const* lhs_con = dynamic_cast<const Const*>(this->lhs_);
		const Const* rhs_con = dynamic_cast<const Const*>(this->rhs_);

		// Check if lhs or rhs is a constant and its value is 0
		if ((lhs_con && lhs_con->get_value() == 0.0) && (rhs_con && rhs_con->get_value() == 0.0))
		{
			// If both lhs and rhs are 0, print 0
			out << "0";
		}
		else if (lhs_con && lhs_con->get_value() == 0.0)
		{
			// Only print rhs if lhs is 0
			this->rhs_->operator<<(out);
		}
		else if (rhs_con && rhs_con->get_value() == 0.0)
		{
			// Only print lhs if rhs is 0
			this->lhs_->operator<<(out);
		}
		else
		{
			// Print lhs and rhs with parentheses if they are not nullary
			if (!(this->lhs_->is_nullary()))
			{
				out << "(";
			}
			this->lhs_->operator<<(out);
			if (!(this->lhs_->is_nullary()))
			{
				out << ")";
			}
			out << " + ";
			if (!(this->rhs_->is_nullary()))
			{
				out << "(";
			}
			this->rhs_->operator<<(out);
			if (!(this->rhs_->is_nullary()))
			{
				out << ")";
			}
		}
		return out;
	}

	bool AddOp::operator==(const __expr_t& other_) const
	{
		const AddOp* other_add = dynamic_cast<const AddOp*>(&other_);
		if (other_add != nullptr)
		{
			return ((*(this->lhs_) == *(other_add->lhs_)) && (*(this->rhs_) == *(other_add->rhs_))) ||
				   ((*(this->lhs_) == *(other_add->rhs_)) && (*(this->rhs_) == *(other_add->lhs_)));
		}
		else
		{
			return false;
		}
	}
}

namespace sym 
{
	bool MulOp::is_mul() const
	{
		return true;
	}	

	__expr_t* MulOp::eval(const var_map_t& vars) const
	{
		auto lhs = this->lhs_->eval(vars);
		auto rhs = this->rhs_->eval(vars);

		// Dynamically cast lhs and rhs to pointers of Const type
		Const* lhs_con = dynamic_cast<Const*>(lhs);
		Const* rhs_con = dynamic_cast<Const*>(rhs);

		if ((lhs_con != nullptr && lhs_con->get_value() == 0.0) || (rhs_con != nullptr && rhs_con->get_value() == 0.0))
		{
			// if lhs is a zero-constant, return a new zero-constant
			// delete lhs;
			// delete rhs;
			return new Const(0);
		}
		else if (lhs_con != nullptr && lhs_con->get_value() == 1.0)
		{
			// if lhs is a one-constant, return the evaluation of rhs
			// delete lhs;
			return rhs;
		}
		else if (rhs_con != nullptr && rhs_con->get_value() == 1.0)
		{
			// if rhs is a one-constant, return the evaluation of lhs
			// delete rhs;
			return lhs;
		}
		else if (lhs_con != nullptr && rhs_con != nullptr)
		{
			// if both lhs and rhs are constants, return a new constant equal to their product
			double product = lhs_con->get_value() * rhs_con->get_value();
			// delete lhs;
			// delete rhs;
			return new Const(product);
		}
		else
		{
			// otherwise, return a new MulOp with the evaluated lhs and rhs
			return new MulOp(lhs, rhs);
		}
	}

	__expr_t* MulOp::diff(const std::string& v) const
	{
		// differentiate lhs and rhs and return their sum as a new AddOp
		__expr_t* lhs_diff = this->lhs_->diff(v);
		__expr_t* rhs_diff = this->rhs_->diff(v);
		
		return new AddOp(new MulOp(lhs_diff, this->rhs_), new MulOp(this->lhs_, rhs_diff));
	}	

	std::ostream& MulOp::operator<< (std::ostream &out) const
	{
		// Cast lhs and rhs to Const*
		const Const* lhs_con = dynamic_cast<const Const*>(this->lhs_);
		const Const* rhs_con = dynamic_cast<const Const*>(this->rhs_);
		
		// Check if lhs or rhs is a constant and its value is 1 or 0
		if (lhs_con && lhs_con->get_value() == 1.0)
		{
			// Only print rhs if lhs is 1
			this->rhs_->operator<<(out);
		}
		else if (rhs_con && rhs_con->get_value() == 1.0)
		{
			// Only print lhs if rhs is 1
			this->lhs_->operator<<(out);
		}
		else if ((lhs_con && lhs_con->get_value() == 0.0) || (rhs_con && rhs_con->get_value() == 0.0))
		{
			// Print 0 if either lhs or rhs is 0
			out << "0";
		}
		else
		{
			// Print lhs and rhs with parentheses if they are not nullary
			if (!(this->lhs_->is_nullary()))
			{
				out << "(";
			}
			this->lhs_->operator<<(out);
			if (!(this->lhs_->is_nullary()))
			{
				out << ")";
			}
			out << " * ";
			if (!(this->rhs_->is_nullary()))
			{
				out << "(";
			}
			this->rhs_->operator<<(out);
			if (!(this->rhs_->is_nullary()))
			{
				out << ")";
			}
		}
		return out;
	}

	bool MulOp::operator==(const __expr_t& other_) const
	{
		// dynamically cast other_ to a pointer of MulOp type
		const MulOp* other_mul = dynamic_cast<const MulOp*>(&other_);
		if (other_mul != nullptr)
		{
			// if other_ is an MulOp, return true if lhs and rhs are equal
			return ((*(this->lhs_) == *(other_mul->lhs_)) && (*(this->rhs_) == *(other_mul->rhs_))) ||
				   ((*(this->lhs_) == *(other_mul->rhs_)) && (*(this->rhs_) == *(other_mul->lhs_)));
		}
		else
		{
			return false;
		}
	}
}