/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  A tool to manage zmodo camera data
 *
 *        Version:  1.0
 *        Created:  04/27/2014 18:29:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk (2014)
 *
 * =====================================================================================
 */
#include "common.hpp"
class Options
{
	public:
		Options(int argc, char** argv);
		const std::string& Incoming(void) {return m_pic_path;}
		const std::string& Outgoing(void) {return m_out_path;}
		bool Quiet(void)   {return m_quiet;}
		bool Verbose(void) {return m_verbose;}
		bool Move(void)    {return m_move;}
	private:
		bpo::variables_map vm;
		std::string m_pic_path;
		std::string m_out_path;
		std::string m_conf_path;
		bool m_quiet;
		bool m_verbose;
		bool m_move;
		bool m_do_load;
		bool m_do_save;
};
