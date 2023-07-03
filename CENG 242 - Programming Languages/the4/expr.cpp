#include "expr.h"
#include "nullary.h"
#include "unary.h"
#include "binary.h"

namespace sym 
{
	Expr::Expr(const Const& c)
	{
		this->expr_ = new Const(c.get_value());
	}

	Expr::Expr(const Var& v)
	{
		this->expr_ = new Var(v.get_variable());
	}

	Expr::Expr(const __expr_t* e)
	{
		if(e->is_nullary())
		{
			auto x = dynamic_cast<const Const*>(e);
			if(x)
			{
				this->expr_ = new Const(x->get_value());
			}
			else
			{
				this->expr_ = new Var(dynamic_cast<const Var*>(e)->get_variable());
			}
		}
		else if(e->is_unary())
		{
			auto x = dynamic_cast<const NegOp*>(e);
			if(x)
			{
				this->expr_ = new NegOp(e);
			}
			else
			{
				this->expr_ = new ExpOp(e);
			}
			
		}
		else if(e->is_binary()) //// 
		{
			this->expr_ = e;
		}
	}

	Expr::Expr(const __expr_t& e)
	{
		if(e.is_nullary())
		{
			auto x = dynamic_cast<const Const*>(&e);
			if(x)
			{
				this->expr_ = new Const(x->get_value());
			}
			else
			{
				this->expr_ = new Var(dynamic_cast<const Var*>(&e)->get_variable());
			}
		}
		else if(e.is_unary())
		{
			auto x = dynamic_cast<const NegOp*>(&e);
			if(x)
			{
				this->expr_ = new NegOp(&e);
			}
			else
			{
				this->expr_ = new ExpOp(&e);
			}
			
		}
		else if(e.is_binary()) ///// 
		{
			this->expr_ = &e;
		}
	}

	Expr::Expr(const Expr& e) ////  
	{
		if(e.expr_)
		{
			if(e.expr_->is_nullary())
			{
				auto x = dynamic_cast<const Const*>(e.expr_);
				if(x)
				{
					this->expr_ = new Const(x->get_value());
				}
				else
				{
					this->expr_ = new Var(dynamic_cast<const Var*>(e.expr_)->get_variable());
				}
			}
			else if(e.expr_->is_unary())
			{
				auto x = dynamic_cast<const NegOp*>(e.expr_);
				if(x)
				{
					this->expr_ = new NegOp(e.expr_);
				}
				else
				{
					this->expr_ = new ExpOp(e.expr_);
				}
				
			}
			else if(e.expr_->is_binary())
			{
				this->expr_ = e.expr_;
			}
		}
	}
		
	Expr::~Expr()
	{
		if(this->expr_ != nullptr)
		{
			delete this->expr_;
			this->expr_ = nullptr;
		}
	}

	__expr_t* Expr::eval(const var_map_t& var_map) const
	{
		if(this->expr_)
		{
			return this->expr_->eval(var_map);
		}
		return nullptr;
	}

	__expr_t* Expr::diff(const std::string& v) const
	{
		if(this->expr_)
		{
			return this->expr_->diff(v);
		}
		return nullptr;
	}

	std::ostream& Expr::operator<< (std::ostream &out) const
	{
		if(this->expr_)
		{
			return this->expr_->operator<<(out);
		}
		return out;
	}

	bool Expr::operator==(const Expr& other) const
	{
		if(this->expr_ && other.expr_)
		{
			return this->expr_->operator==(*(other.expr_));
		}
		return false;
	}

	bool Expr::operator==(const __expr_t& other) const
	{
		if(this->expr_)
		{
			return this->expr_->operator==(other);
		}
		return false;
	}
}                                                                  	
