
/*
 * exec_environment.cpp
 *
 *  Created on: 16 Jun 2013
 *      Author: Henry J Kupty
 */

#include "../headers/exec_environment.hpp"
#include "../headers/log.hpp"

const std::string k_env = std::string(_log::_bold + "[EXEC ENV  ]" + _log::_clr);

void exec::exec_environment::start()
{
	std::cout << _log::_inf <<  k_env << "CONFIG LOAD" << std::endl;

	cfg::config_t cfg = this->cfg_.get_config();

	std::cout << _log::_scc << k_env << "CONFIG LOADED" << std::endl;

	this->server_name_ = cfg._name;

	std::cout << _log::_inf << k_env << "STARTING SERVER AS " << this->server_name_ << std::endl;

	this->current_runtime_ = new runtime_container;

	if (current_runtime_->load(cfg))
		std::cout << _log::_scc << k_env << "LOADED RUNTIME CONTAINER SUCCESSFULLY" << std::endl;
	else
		std::cout << _log::_err << k_env << "PROBLEMS LOADING RUNTIME CONTAINER.. ABORT" << std::endl;

	this->current_network_ = new network_container;

	this->current_runtime_->register_network(this->current_network_);

	std::cout << _log::_inf << k_env << "DONE!" << std::endl;
}

exec::exec_environment::~exec_environment() 
{
	delete this->current_network_;
	delete this->current_runtime_;
}