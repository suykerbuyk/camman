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
#include "camopts.hpp"
Options::Options(int argc, char** argv)
{
	m_do_load = false;
	m_do_save = false;
	bpo::options_description cmd_line("Camera Manager Options");
	try
	{
		cmd_line.add_options()
			("help,h", "Display this help message")
			("incoming,i", bpo::value<std::string>(&m_pic_path)->default_value("./incoming"),
				"Path to incoming camera files")
			("outgoing,o", bpo::value<std::string>(&m_out_path)->default_value("./"),
				"Base path outgoing camera files")
			("save,s", bpo::value<std::string>(&m_conf_path)->implicit_value("camman.conf"),
				"Parse all provided options, save to named file and exit without action")
			("load,l", bpo::value<std::string>(&m_conf_path)->implicit_value("camman.conf"),
				"Parse all provided options, save to named file and exit without action")
			("move,m", bpo::value<bool>(&m_move)->default_value(false)->implicit_value(true),
				"Move incoming camera files to date/cam directory structure.")
			("quiet,q", bpo::value<bool>(&m_quiet)->default_value(false)->implicit_value(true),
				"Suppress (most) informational output")
			("verbose,v", bpo::value<bool>(&m_verbose)->default_value(false)->implicit_value(true),
				"Disaplay extra information.");
		bpo::store(bpo::parse_command_line(argc, argv, cmd_line), vm);
		if (vm.count("help"))
		{
			std::cout << cmd_line << std::endl;
			exit(0);
		}
		if (vm["verbose"].as<bool>() && vm["quiet"].as<bool>())
		{
			std::cerr << "ERROR:  Can not specify both quiet and verbose!" << std::endl;
			exit(1);
		}
		bpo::notify(vm);
		if (!m_conf_path.empty())
		{
			if (vm.count("load"))
				m_do_load = true;
			else if (vm.count("save"))
				m_do_save = true;
			assert((m_do_load ^ m_do_save) == true);
		}
	}
	catch (bpo::error& err)
	{
		std::cerr << "ERROR: " << err.what() << std::endl;
		std::cerr << cmd_line << std::endl;
		exit(1);
	}
}
