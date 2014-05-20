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

#include "common.hpp"
#include "camfile.hpp"
CameraFile::CameraFile(const bfs::directory_iterator d_itr) : is_valid(false)
{
	reset_fields();
	src_path = d_itr->path();
	if (!setFileNamePartsFromPath(src_path))
	{
		std::cerr << "NOT VALID: " << src_path << std::endl;
	}
}
CameraFile& CameraFile::operator = (const CameraFile& other)
{
	if (this != &other)
	{
		src_path = other.src_path;
		prefix = other.prefix;
		camname = other.camname;
		source = other.source;
		date = other.date;
		sequence = other.sequence;
		extension = other.extension;
		is_valid = other.is_valid;
	}
	return (*this);
}
bool CameraFile::setFileNamePartsFromPath(const bfs::path& path)
{
	typedef boost::tokenizer<boost::char_separator<char> > name_tokenizer;
	const boost::char_separator<char> sep = boost::char_separator<char>("_()");
	name_tokenizer tokens(src_path.stem().string(), sep);
	name_tokenizer::iterator tokens_end = tokens.end();
	name_tokenizer::iterator tokens_itr = tokens.begin();
	do
	{
		if (tokens_itr != tokens_end) prefix   = *tokens_itr++; else break;
		if (tokens_itr != tokens_end) camname  = *tokens_itr++; else break;
		if (tokens_itr != tokens_end) source   = *tokens_itr++; else break;
		if (tokens_itr != tokens_end) date     = *tokens_itr++; else break;
		if (tokens_itr != tokens_end) sequence = *tokens_itr++; else break;
		sequence = sequence.insert(0, "0000000000").substr(sequence.length() - 7);
		std::string ext = path.extension().string();
		if ((boost::iequals(ext, ".jpg")) || (boost::iequals(ext,".jpeg")))
		{
			extension = ext;
			is_valid = date.IsValid();
		}
	} while (0);
	return is_valid;
}
void CameraFile::reset_fields(void)
{
	prefix.clear();
	camname.clear();
	source.clear();
	date.clear();
	sequence.clear();
	src_path.clear();
	extension.clear();
	is_valid = false;
}
bool operator < (const CameraFile& lhs, const CameraFile& rhs)
{
	if (lhs.camname != rhs.camname) return (lhs.camname < rhs.camname);
	if (lhs.date    != rhs.date)    return (lhs.date    < rhs.date);
	return (lhs.sequence < rhs.sequence);
}
bool operator > (const CameraFile& lhs, const CameraFile& rhs)
{
	if (lhs.camname != rhs.camname) return (lhs.camname > rhs.camname);
	if (lhs.date    != rhs.date)    return (lhs.date    > rhs.date);
	return (lhs.sequence > rhs.sequence);
}
