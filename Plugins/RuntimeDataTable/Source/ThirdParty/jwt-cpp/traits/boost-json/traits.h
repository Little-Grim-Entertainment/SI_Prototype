#ifndef JWT_CPP_BOOSTJSON_TRAITS_H
#define JWT_CPP_BOOSTJSON_TRAITS_H

#define JWT_DISABLE_PICOJSON
#include "jwt-cpp/jwt.h"

#include <boost/json.hpp>
// if not boost JSON standalone then error...

namespace jwt {
	namespace traits {
		namespace json = boost::json;
		struct boost_json {
			using value_type = json::value;
			using object_type = json::object;
			using array_type = json::array;
			using string_type = std::string;
			using number_type = double;
			using integer_type = std::int64_t;
			using boolean_type = bool;

			static jwt::json::type get_type(const value_type& val) {
				using jwt::json::type;

				if (val.kind() == json::kind::bool_) return type::boolean;
				if (val.kind() == json::kind::int64) return type::integer;
				if (val.kind() == json::kind::uint64) // boost internally tracks two types of integers
					return type::integer;
				if (val.kind() == json::kind::double_) return type::number;
				if (val.kind() == json::kind::string) return type::string;
				if (val.kind() == json::kind::array) return type::array;
				if (val.kind() == json::kind::object) return type::object;

				UE_LOG(LogTemp, Warning, TEXT("invalid type"));
			}

			static object_type as_object(const value_type& val) {
				if (val.kind() != json::kind::object) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get_object();
			}

			static array_type as_array(const value_type& val) {
				if (val.kind() != json::kind::array) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get_array();
			}

			static string_type as_string(const value_type& val) {
				if (val.kind() != json::kind::string) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return string_type{val.get_string()};
			}

			static integer_type as_int(const value_type& val) {
				switch (val.kind()) {
				case json::kind::int64: return val.get_int64();
				case json::kind::uint64: return static_cast<int64_t>(val.get_uint64());
				default: UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				}
			}

			static boolean_type as_bool(const value_type& val) {
				if (val.kind() != json::kind::bool_) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get_bool();
			}

			static number_type as_number(const value_type& val) {
				if (val.kind() != json::kind::double_) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get_double();
			}

			static bool parse(value_type& val, string_type str) {
				val = json::parse(str);
				return true;
			}

			static std::string serialize(const value_type& val) { return json::serialize(val); }
		};
	} // namespace traits
} // namespace jwt

#endif // JWT_CPP_BOOSTJSON_TRAITS_H
