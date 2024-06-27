#ifndef JAMMER_STRING_H
#define JAMMER_STRING_H

#include <iostream>

#include "Utils.h"
#include "Data/Array.h"

namespace Jammer{
	class String{
	public:
		String(const char* str_ = "") : data(Utils::Max<size_t>(16, Utils::CStrLength(str_))){
			data.Add('\0');
			Append(str_);
		}

		void Append(const char* str_){
			data.Reserve(data.Size() + Utils::CStrLength(str_));

			data.Pop();
			data.Add(str_, Utils::CStrLength(str_));
			data.Add('\0');
		}

		void Append(const String& str_){
			Append(&str_.data[0]);
		}

		void Append(char c_){
			data.Reserve(data.Size() + 1);

			data.Pop();
			data.Add(c_);
			data.Add('\0');
		}

		void AppendInt(int32_t number_){
			char buffer[10]{};
			_itoa_s(number_, buffer, 10);
			Append(buffer);
		}

		String operator +(const char* str_) const{
			String finalStr = *this;
			finalStr.Append(str_);
			return finalStr;
		}

		String operator +(const String& str_) const{
			String finalStr = *this;
			finalStr.Append(str_);
		}

		String operator +(char c_) const{
			String finalStr = *this;
			finalStr.Append(c_);
		}

		String operator +(int32_t number_) const{
			String finalStr = *this;
			finalStr.AppendInt(number_);
		}

		void operator +=(const char* str_){ Append(str_); }
		void operator +=(const String& str_){ Append(str_); }
		void operator +=(char c_){ Append(c_); }
		void operator +=(int32_t number_){ AppendInt(number_); }

		constexpr char operator[](size_t i_) const{ return data[i_]; }
		constexpr char& operator[](size_t i_){ return data[i_]; }

		constexpr size_t Length() const{ return data.Size() - 1; }
		constexpr bool IsEmpty() const{ return data.Size() == 1 && data[0] == '\0'; }
		constexpr const char* CStr() const{ return &data[0]; }

	private:
		Array<char> data;
	};

	constexpr inline std::ostream& operator <<(std::ostream& os_, const String& str_){
		for(size_t i = 0; i < str_.Length(); i++){
			os_ << str_[i];
		}

		return os_;
	}

	inline String operator +(const char* str1_, const String& str2_){
		String str = String(str1_);
		str.Append(str2_);
		return str;
	}
}

#endif //!JAMMER_STRING_H