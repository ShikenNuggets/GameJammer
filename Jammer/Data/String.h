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

		String operator +(const String& str_) const{
			String finalStr = *this;
			finalStr.Append(str_);
		}

		constexpr char operator[](size_t i_) const{
			return data[i_];
		}

		constexpr char& operator[](size_t i_){
			return data[i_];
		}

		constexpr size_t Length() const{ return data.Size() - 1; }
		constexpr bool IsEmpty() const{ return data.Size() == 1 && data[0] == '\0'; }

	private:
		Array<char> data;
	};

	constexpr std::ostream& operator <<(std::ostream& os_, const String& str_){
		for(size_t i = 0; i < str_.Length(); i++){
			os_ << str_[i];
		}

		return os_;
	}
}

#endif //!JAMMER_STRING_H