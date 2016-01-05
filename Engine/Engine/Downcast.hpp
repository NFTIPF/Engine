#pragma once

//boost includes
#include "boost\shared_ptr.hpp"

//inherited object includes
#include "TestObject.hpp"

//^^^ those should be combined into group include files ie "Objects.hpp" or this will get annoying

namespace util	//this is a utility class
{
	template<class Base>
	class Downcaster
	{
	public:
		Downcaster(){}
		~Downcaster(){}

		//KEEP IN MIND... calling any of these on the wrong downcaster object(incorrect base) will result in catastrophic failure
		//maybe that should be handled somehow?


		boost::shared_ptr<objects::TestObject> downcast(boost::shared_ptr<Base> baseObject)
		{
			return boost::dynamic_pointer_cast<objects::TestObject, Base>(baseObject);	//casts shared_ptr of type Base to type TestObject
		}

		//PYTHONSCRIPT
		//^^comment indicating where python script should insert new downcasts
		//continue overloading for all base children
	private:
	};
}
