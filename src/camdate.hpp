/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  camdate.hpp
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
#ifndef CAM_MAN_DATE
#define CAM_MAN_DATE

#include <string>
#include <sstream>
#include <iomanip>

class CameraDate
{
	public:
		CameraDate(std::string packedDateString= "");
		int year  (void) const {return(m_year);}
		int month (void) const {return(m_month);}
		int day   (void) const {return(m_day);}
		int hour  (void) const {return(m_hour);}
		int minute(void) const {return(m_minute);}
		int second(void) const {return(m_second);}
		void clear(void);
		bool IsValid(void) const {return(is_valid);}
		friend bool operator <  (const CameraDate& lhs, const CameraDate& rhs);
		friend bool operator <= (const CameraDate& lhs, const CameraDate& rhs);
		friend bool operator >  (const CameraDate& lhs, const CameraDate& rhs);
		friend bool operator == (const CameraDate& lhs, const CameraDate& rhs);
		friend bool operator != (const CameraDate& lhs, const CameraDate& rhs);
		std::string String(bool packed=true) const;
		std::string YearMonthDay(void) const;
		CameraDate& operator = (const std::string& str);
	private:
		int m_year;
		int m_month;
		int m_day;
		int m_hour;
		int m_minute;
		int m_second;
		bool is_valid;
		bool setAndValidate(const std::string& packed);
};
#endif ///#ifndef CAM_MAN_DATE

