#ifndef JWT_CPP_NLOHMANN_JSON_TRAITS_H
#define JWT_CPP_NLOHMANN_JSON_TRAITS_H

#include "jwt-cpp/jwt.h"
#include "nlohmann/json.hpp"

namespace jwt {
	namespace traits {
		struct nlohmann_json {
			using json = nlohmann::json;
			using value_type = json;
			using object_type = json::object_t;
			using array_type = json::array_t;
			using string_type = std::string; // current limitation of traits implementation
			using number_type = json::number_float_t;
			using integer_type = json::number_integer_t;
			using boolean_type = json::boolean_t;

			static jwt::json::type get_type(const json& val) {
				using jwt::json::type;

				if (val.type() == json::value_t::boolean) return type::boolean;
				// nlohmann internally tracks two types of integers
				if (val.type() == json::value_t::number_integer) return type::integer;
				if (val.type() == json::value_t::number_unsigned) return type::integer;
				if (val.type() == json::value_t::number_float) return type::number;
				if (val.type() == json::value_t::string) return type::string;
				if (val.type() == json::value_t::array) return type::array;
				if (val.type() == json::value_t::object) return type::object;

				UE_LOG(LogTemp, Warning, TEXT("invalid type"));
			}

			static json::object_t as_object(const json& val) {
				if (val.type() != json::value_t::object) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get<json::object_t>();
			}

			static std::string as_string(const json& val) {
				if (val.type() != json::value_t::string) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get<std::string>();
			}

			static json::array_t as_array(const json& val) {
				if (val.type() != json::value_t::array) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get<json::array_t>();
			}

			static int64_t as_int(const json& val) {
				switch (val.type()) {
				case json::value_t::number_integer:
				case json::value_t::number_unsigned: return val.get<int64_t>();
				default: UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				}
			}

			static bool as_bool(const json& val) {
				if (val.type() != json::value_t::boolean) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get<bool>();
			}

			static double as_number(const json& val) {
				if (val.type() != json::value_t::number_float) UE_LOG(LogTemp, Warning, TEXT("bad cast"));
				return val.get<double>();
			}

			static bool parse(json& val, std::string str) {
				val = json::parse(str.begin(), str.end());
				return true;
			}

			static std::string serialize(const json& val) { return val.dump(); }
		};
	} // namespace traits
} // namespace jwt

#endif
