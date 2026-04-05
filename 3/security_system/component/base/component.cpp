#include "component.hpp"
#include "../../environment/environment.hpp"
namespace Security_system
{
    void Component::set_pos(std::pair<size_t, size_t> new_pos, std::shared_ptr<Environment> env)
    {
        if (env->is_empty(new_pos.first, new_pos.second))
        {
            env->change_pos(new_pos, position);
            position = new_pos;
        }
    }
}