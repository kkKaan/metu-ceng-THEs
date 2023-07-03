#include "type.h"
#include "nullary.h"
#include "unary.h"
#include "binary.h"	

namespace sym 
{
	__nullary_op_t::~__nullary_op_t() {}

	bool __nullary_op_t::is_nullary() const
	{
		return true;
	}	

	bool __nullary_op_t::is_con() const
	{
		return false;
	}

	bool __nullary_op_t::is_var() const
	{
		return false;
	}
}

namespace sym 
{
	__unary_op_t::~__unary_op_t()
	{
		if(this->operand != nullptr)
		{
			delete this->operand;
			this->operand = nullptr;
		}
	}

	bool __unary_op_t::is_unary() const
	{
		return true;
	}

	bool __unary_op_t::is_neg() const
	{	
		return false;
	}
	bool __unary_op_t::is_exp() const
	{
		return false;
	}
}

namespace sym 
{
	__binary_op_t::~__binary_op_t() 
	{
		if(this->lhs_ != nullptr)
		{
			delete this->lhs_;
			this->lhs_ = nullptr;
		}

		if(this->rhs_ != nullptr)
		{
			delete this->rhs_;
			this->rhs_ = nullptr;
		}
	}

	bool __binary_op_t::is_binary() const
	{
		return true;
	}

	bool __binary_op_t::is_add() const
	{
		return false;
	}

	bool __binary_op_t::is_mul() const
	{
		return false;
	}
}