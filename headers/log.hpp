/*
 * log.hpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */

#ifndef LOG_HPP_
#define LOG_HPP_
namespace _log
{

#ifndef COLORED_LOG_OFF

const std::string _err = std::string ("\033[31m");
const std::string _scc = std::string ("\033[32m");
const std::string _inf = std::string ("\033[37m");
const std::string _clr = std::string ("\033[0m");
const std::string _bold = std::string ("\033[1m");

#else

const std::string _err = std::string ("");
const std::string _scc = std::string ("");
const std::string _clr = std::string ("");
const std::string _bold = std::string ("");


#endif	

}

#endif /* LOG_HPP_ */