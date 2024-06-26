#ifndef JAMMER_UTILS_H
#define JAMMER_UTILS_H

namespace Jammer{
	namespace Utils{
		constexpr size_t StringMax = 65536; //https://learn.microsoft.com/en-us/cpp/c-language/maximum-string-length

		template <class T> constexpr T Min(T a_, T b_){ return (a_ < b_) ? a_ : b_; }
		template <class T> constexpr T Max(const T& a_, const T& b_){ return (a_ < b_) ? b_ : a_; }

		int32_t constexpr CStrLength(const char* str_){
			for(int32_t i = 0; i < 65536; i++){
				if(str_[i] == '\0'){
					return i;
				}
			}

			return -1; //String is invalid, could not find a null terminator
		}
	}
}

#endif //!JAMMER_UTILS_H