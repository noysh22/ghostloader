#pragma once

#include <exception>
#include <cstdint>
#include <string>


class Exception : public std::exception
{
public:
	explicit Exception(const std::wstring& msg, const uint32_t error_code) :
		m_msg(msg), m_error_code(error_code)
	{ }

	virtual ~Exception() throw () { }

	const std::wstring& get_message() const { return m_msg; }
	uint32_t get_error_code() const { return m_error_code; }

protected:
	const std::wstring m_msg;
	uint32_t m_error_code;
};