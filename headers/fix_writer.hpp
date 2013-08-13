/*
 * fix_writer.hpp
 *
 *  Created on: 12 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef FIX_WRITER_HPP_
#define FIX_WRITER_HPP_

class fix_writer
{
public:
	fix_writer();
	virtual ~fix_writer() = 0;
};

typedef fix_writer* create_t();
typedef void destroy_t(fix_writer*);

#endif /* FIX_WRITER_HPP_ */
