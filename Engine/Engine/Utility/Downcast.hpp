#pragma once

//boost includes
#include "boost\shared_ptr.hpp"

//inherited object includes

#include "../Objects/TestObject.hpp"
#include "../Objects/MovingTestObject.hpp"
#include "../Objects/Squirrel.hpp"
#include "../Objects/ObjectClasses/Platform.hpp"



//^^^ those should be combined into group include files ie "Objects.hpp" or this will get annoying

namespace util	//this is a utility class
{
	template<class T>
	boost::shared_ptr<T> downcast(boost::shared_ptr<objects::Object>& base > )
	{
		return boost::dynamic_cast<boost::shared_ptr<T> >(base);
	}
}
