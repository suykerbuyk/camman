/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  cameras.cpp
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
#include "camfile.hpp"
#include "camdate.hpp"
#include "camman.hpp"

typedef std::map<std::string, std::map<std::string, std::set<CameraFile>>> CameraFiles;

size_t CameraManager::FindFiles(const std::string& path, bool verbose)
{
	bfs::path _path(path);
	return(FindFiles(_path, verbose));
}
size_t CameraManager::FindFiles(const bfs::path path, bool verbose)
{
	reset();
	if ((!bfs::exists (path)) || (!bfs::is_directory(path)))
		return cam_file_count;
	bfs::directory_iterator dir_end;
	for(bfs::directory_iterator itr(path); itr != dir_end; ++itr)
	{
		CameraFile camFile(itr);
		if (!camFile.IsValid())
		{
			cam_file_rejects++;
		}
		else
		{
			auto ret_itr = camFiles[camFile.YearMonthDay()][camFile.CamName()].insert(camFile);
			if (ret_itr.second)
				cam_file_count++;
			else
			{
				cam_file_duplicates++;
				if (verbose)
				{
					std::cerr << "Duplicate file: " << camFile.SourcePath() << std::endl;
					std::cerr << "Duplicate file: " << ret_itr.first->SourcePath() << std::endl;
				}
			}
		}
	}
	return cam_file_count;
}
void CameraManager::DumpToStdOut(void)
{
	if (!cam_file_count)
	{
		std::cerr << "ERR: No files found" << std::endl;
	}
	else
	{
		auto date_itr = camFiles.cbegin();
		while(date_itr!=camFiles.cend())
		{
			auto cam_itr = date_itr->second.cbegin();
			while (cam_itr != date_itr->second.cend())
			{
				auto file_itr = cam_itr->second.cbegin();
				while (file_itr != cam_itr->second.cend())
				{
					std::cout << date_itr->first << "  " << file_itr->FixedName() << std::endl;
					++file_itr;
				}
				++cam_itr;
			}
			++date_itr;
		}
	}
}
