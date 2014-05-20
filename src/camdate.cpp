/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  camdate.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2014 18:41:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  
 *
 * =====================================================================================
 */
#include "camdate.hpp"

CameraDate::CameraDate(std::string packedDateString)
{
	setAndValidate(packedDateString);
}
void CameraDate::clear(void)
{
	is_valid = false;
	m_year = m_month = m_day = 0;
	m_hour = m_minute = m_second = 0;
}
std::string CameraDate::String(bool packed) const
{
	std::stringstream ss;
	if (!packed)
	{
		ss << std::setw(4) << std::setfill('0')<< m_year;
		ss << '-';
		ss << std::setw(2) << std::setfill('0')<< m_month;
		ss << '-';
		ss << std::setw(2) << std::setfill('0')<< m_day;
		ss << '-';
		ss << std::setw(2) << std::setfill('0')<< m_hour;
		ss << '_';
		ss << std::setw(2) << std::setfill('0')<< m_minute;
		ss << '_';
		ss << std::setw(2) << std::setfill('0')<< m_second;
	}
	else
	{
		ss << std::setw(4) << std::setfill('0')<< m_year;
		ss << std::setw(2) << std::setfill('0')<< m_month;
		ss << std::setw(2) << std::setfill('0')<< m_day;
		ss << std::setw(2) << std::setfill('0')<< m_hour;
		ss << std::setw(2) << std::setfill('0')<< m_minute;
		ss << std::setw(2) << std::setfill('0')<< m_second;
	}
	return ss.str();
}
std::string CameraDate::YearMonthDay(void) const
{
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0')<< m_year;
	ss << std::setw(2) << std::setfill('0')<< m_month;
	ss << std::setw(2) << std::setfill('0')<< m_day;
	return ss.str();
}

bool CameraDate::setAndValidate(const std::string& packed)
{
	is_valid = false;
	if (packed.length() >= 14)
	{
		std::string temp = packed.substr(0, 4);
		m_year = std::stoi(temp);
		temp=packed.substr(4,2);
		m_month = std::stoi(temp);
		temp=packed.substr(6,2);
		m_day = std::stoi(temp);
		temp=packed.substr(8,2);
		m_hour = std::stoi(temp);
		temp=packed.substr(10,2);
		m_minute = std::stoi(temp);
		temp=packed.substr(12,2);
		m_second = std::stoi(temp);
		is_valid =
			(m_year > 2012)  && (m_year < 2100) &&
			(m_month > 0)    && (m_month < 13) &&
			(m_day > 0)      && (m_day < 32) &&
			(m_hour >= 0 )   && (m_hour < 24) &&
			(m_minute >= 0 ) && (m_minute < 60) &&
			(m_second >= 0 ) && (m_second < 60);
	}
	return(is_valid);
}
CameraDate& CameraDate::operator = (const std::string& str)
{
	setAndValidate(str);
	return (*this);
}
bool operator < (const CameraDate& lhs, const CameraDate& rhs)
{
	if (lhs.m_year   != rhs.m_year)   return (lhs.m_year   < rhs.m_year);
	if (lhs.m_month  != rhs.m_month)  return (lhs.m_month  < rhs.m_month);
	if (lhs.m_day    != rhs.m_day)    return (lhs.m_day    < rhs.m_day);
	if (lhs.m_hour   != rhs.m_hour)   return (lhs.m_hour   < rhs.m_hour);
	if (lhs.m_minute != rhs.m_minute) return (lhs.m_minute < rhs.m_minute);
	return (lhs.m_second < rhs.m_second);
}
bool operator <= (const CameraDate& lhs, const CameraDate& rhs)
{
	if (lhs == rhs)
		return true;
	else
		return (lhs < rhs);
}

bool operator > (const CameraDate& lhs, const CameraDate& rhs)
{
	if (lhs.m_year   != rhs.m_year)   return (lhs.m_year   > rhs.m_year);
	if (lhs.m_month  != rhs.m_month)  return (lhs.m_month  > rhs.m_month);
	if (lhs.m_day    != rhs.m_day)    return (lhs.m_day    > rhs.m_day);
	if (lhs.m_hour   != rhs.m_hour)   return (lhs.m_hour   > rhs.m_hour);
	if (lhs.m_minute != rhs.m_minute) return (lhs.m_minute > rhs.m_minute);
	return (lhs.m_second > rhs.m_second);
}

bool operator == (const CameraDate& lhs, const CameraDate& rhs)
{
	if (lhs.m_year   != rhs.m_year)   return false;
	if (lhs.m_month  != rhs.m_month)  return false;
	if (lhs.m_day    != rhs.m_day)    return false;
	if (lhs.m_hour   != rhs.m_hour)   return false;
	if (lhs.m_minute != rhs.m_minute) return false;
	if (lhs.m_second != rhs.m_second) return false;
	return(true);
}
bool operator != (const CameraDate& lhs, const CameraDate& rhs)
{
	if (lhs == rhs)
		return false;
	else
		return true;
}
