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
#include "camman.hpp"
#include "camopts.hpp"
int main (int argc, char** argv)
{
	Options options(argc, argv);
	bfs::path path(options.Incoming());
	CameraManager camManager;
	camManager.FindFiles(path, options.Verbose());
	if (options.Verbose())
		camManager.DumpToStdOut();
	if (!options.Quiet())
	{
		std::cout << "     Total File Count: " << camManager.FileCount() << std::endl;
		std::cout << "   Total File Rejects: " << camManager.FileRejects() << std::endl;
		std::cout << "Total File Duplicates: " << camManager.FileDuplicates() << std::endl;
	}
	return 0;
}
