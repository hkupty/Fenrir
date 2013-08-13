/*
 * session.hpp
 *
 *  Created on: 12 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include "message_buffer.hpp"
#include <string>

namespace sessions
{

	const short READ_ACCESS 	= 0x01 << 0;
	const short WRITE_ACCESS 	= 0x01 << 1;

	class session
	{
	protected:
		std::string		session_name;
		int				session_id;
		short			session_accesslevel;
		short			session_mbuffer_qtd;

	public:
				session () {};
		virtual ~session() {};

		virtual void register_mbuffer(buffers::message_buffer*) = 0;
		virtual void deregister_mbuffer(buffers::message_buffer*) = 0;

	};

	struct API
		{
			session* (*create)	(void);
			void 	 (*destroy)	(session*);
		};
}
#endif /* SESSION_HPP_ */
