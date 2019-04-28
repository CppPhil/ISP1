#include <position_kind.hpp>

namespace isp1 {
std::ostream& operator<<(std::ostream& os, position_kind kind)
{
    switch (kind) {
    case position_kind::start: os << 'S'; break;
    case position_kind::goal: os << 'G'; break;
    case position_kind::empty: os << 'E'; break;
    case position_kind::wall: os << 'W'; break;
    case position_kind::on_path: os << 'P'; break;
    }

    return os;
}
} // namespace isp1
