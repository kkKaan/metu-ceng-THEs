#include "type.h"
#include "nullary.h"

namespace sym 
{
	double Const::get_value() const
	{
		return this->value_;
	}

	Const::operator double() const
	{
		return this->value_;
	}

	bool Const::is_con() const
	{
		return true;
	}

	__expr_t* Const::eval(const var_map_t& var_map) const
	{
		return new Const(this->value_);
	}

	__expr_t* Const::diff(const std::string& v) const
	{
		return new Const(0);
	}

	std::ostream& Const::operator<< (std::ostream &out) const
	{
		out << this->value_;
		return out;
	}

	bool Const::operator==(const __expr_t& other) const
	{
		// Attempt to dynamic cast the other __expr_t reference to a Const reference.
		// If the cast is successful, `other` is of type Const and the pointers will be non-null.
		const Const* otherConst = dynamic_cast<const Const*>(&other);
		// If the dynamic_cast failed, otherConst will be nullptr
		if(otherConst == nullptr)
		{
			return false;
		}
		// If dynamic_cast was successful, compare the values.
		return this->get_value() == otherConst->get_value();
	}
}

namespace sym 
{
	std::string Var::get_variable() const 
	{
		return this->var_;
	}

	Var::operator std::string () const
	{
		return this->var_;
	}

	bool Var::is_var() const
	{
		return true;
	}

	__expr_t* Var::eval(const var_map_t& vars) const
	{
		if(!(vars.empty()))
		{
			auto search = vars.find(this->var_);
			if (search != vars.end())
			{
				// If var_ is found in vars, return new Const with corresponding value
				// std::cout << "Found " << search->second << " in vars" << std::endl;
				return new Const(search->second);
			}
		}
		// If var_ is not found in vars, return new Var with same variable
		// std::cout << "Did not find " << this->var_ << " in vars" << std::endl;
		return new Var(this->var_);
	}	

	__expr_t* Var::diff(const std::string& v) const
	{
		if (this->get_variable() == v)
		{
			return new Const(1);
		}
		return new Const(0);
	}

	std::ostream& Var::operator<< (std::ostream &out) const
	{
		out << this->var_;
		return out;
	}

    bool Var::operator==(const __expr_t& other) const
    {
        // Check if the other object is a Var object
		auto otherVar = dynamic_cast<const Var*>(&other);
        if (otherVar)
        {
            // Compare the variables
            return this->get_variable() == otherVar->get_variable();
        }
        return false;
    }
}
