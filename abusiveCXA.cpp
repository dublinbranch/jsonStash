
/** ***************/
/** POWER SUPREME */
/** ***************/
#include <dlfcn.h>
#include <execinfo.h>
//define the functor
typedef void (*cxa_throw_type)(void*, std::type_info*, void (*)(void*));
//now take the address of the REAL __cxa_throw
static cxa_throw_type orig_cxa_throw = (cxa_throw_type)dlsym(RTLD_NEXT, "__cxa_throw");
extern "C" {
	//And NOW override it
	void __cxa_throw(void*           thrown_exception,
					std::type_info* pvtinfo,
					void (*dest)(void*)) {
		//Implement your reporting logic here.
		static const QString x;
		auto                 v1 = pvtinfo->hash_code();
		auto                 v2 = typeid(x).hash_code();
		if (v1 == v2) {
			//print message and stack trace
			QString* th = static_cast<QString*>(thrown_exception);
			qDebug().noquote() << *th << QStacker(5);
		} else {
			//Just print stack trace
			qDebug().noquote() << QStacker();
		}
		//this will pass tru the exception to the original handler so the program will not catch fire after an exception is thrown
		orig_cxa_throw(thrown_exception, pvtinfo, dest);
	}
} 
