/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  camfile.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2014 18:47:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CAM_FILE_DOT_H
#define CAM_FILE_DOT_H
#include "common.hpp"
#include "camdate.hpp"
class CameraFile
{
	public:
		CameraFile(void) :is_valid(false) {};
		CameraFile(const bfs::directory_iterator d_itr);
		CameraFile& operator = (const CameraFile& other);
		bool IsValid(void)          const { return is_valid;}
		std::string Prefix(void)    const { return prefix; }
		std::string CamName(void)   const { return camname; }
		std::string Source(void)    const { return source; }
		std::string Date(void)      const { return date.String(); }
		std::string YearMonthDay    (void) const { return date.YearMonthDay(); }
		std::string Sequence(void)  const { return sequence; }
		std::string Extension(void) const { return extension; }
		std::string SourcePath(void)const { return src_path.string(); }
		std::string FixedName(void) const
		{
			std::stringstream ss;
			ss << CamName() << "_" << Date() << "_" << Sequence() << Extension();
			return ss.str();
		}
		friend bool operator < (const CameraFile& lhs, const CameraFile& rhs);
		friend bool operator > (const CameraFile& lhs, const CameraFile& rhs);
	private:
		bool setFileNamePartsFromPath(const bfs::path& path);
		void reset_fields(void);
		bool is_valid;
		std::string prefix;
		std::string camname;
		std::string source;
		CameraDate  date;
		std::string sequence;
		std::string extension;
		bfs::path   src_path;
};

#endif // CAM_FILE_DOT_H
