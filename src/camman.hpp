/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  camman.hpp
 *
 *    Description:  Cam Manager Header
 *
 *        Version:  1.0
 *        Created:  04/29/2014 14:28:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CAM_MAN_HDR
#define CAM_MAN_HDR

#include "common.hpp"
#include "camfile.hpp"

typedef std::map<std::string, std::map<std::string, std::set<CameraFile>>> CameraFiles;

class CameraManager
{
	public:
		CameraManager(void) {reset();};
		size_t FindFiles(const std::string& path, bool verbose=false);
		size_t FindFiles(const bfs::path path, bool verbose=false);
		size_t MoveFiles(bool verbose=false);
		void DumpToStdOut(void);
		size_t& FileCount(void)      {return cam_file_count;}
		size_t& FileDuplicates(void) {return cam_file_duplicates;}
		size_t& FileRejects(void)    {return cam_file_rejects;}
	private:
		void reset(void)
		{
			camFiles.clear();
			cam_file_count = 0;
			cam_file_rejects = 0;
			cam_file_duplicates = 0;
		}
		CameraFiles camFiles;
		size_t cam_file_count;
		size_t cam_file_duplicates;
		size_t cam_file_rejects;
};




#endif //CAM_MAN_HDR
