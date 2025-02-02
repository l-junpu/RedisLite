#ifndef SOBA_RESP_TYPES_H
#define SOBA_RESP_TYPES_H

#include <string>
#include <vector>
#include <memory>

namespace soba
{
	enum class RespType
	{
		ARRAY = 0,
		BULK_STRING,
		EXIT
	};

	// RESP element interface
	struct RespElement
	{
		RespElement(const RespType type) : Type{ type } {}
		virtual ~RespElement() = default;
		virtual std::string ToString() const { return {}; };

		RespType Type;
	};

	// RESP actual type definition
	struct RespArray : public RespElement
	{
		RespArray(const RespType type) : RespElement(type) {}

		std::string ToString() const override
		{
			std::string result;
			for (const auto& e : Elements) {
				result += e->ToString() + " ";
			}
			return result;
		}

		std::vector<std::shared_ptr<RespElement>> Elements;
	};

	struct RespBulkString : public RespElement
	{
		RespBulkString(const RespType type, const std::string& data) : RespElement(type), Data{ data } {}

		std::string ToString() const override
		{
			return Data;
		}

		std::string Data;
	};
}

#endif