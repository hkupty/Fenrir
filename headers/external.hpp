/*
 * external.hpp
 *
 *  Created on: 10 Jun 2013
 *      Author: Henry J Kupty
 */

 #ifndef EXTERNAL_
 #define EXTERNAL_

 #include <boost/unordered_map.hpp>

 namespace external
 {

 	class external
 	{
 	public:
 		virtual void configure(boost::unordered_map<std::string, std::string>) = 0;
 	};


 	template<class T>
 	struct API
	{
		T* 	(*create)	(void);
		void 			(*destroy)	(T*);
	};
 }

 #endif  /* EXTERNAL_ */