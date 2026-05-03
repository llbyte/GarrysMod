#pragma once

#include <utility>
#include <type_traits>

#define OFFSET(type, offset, name) \
    type& name() { return *reinterpret_cast<type*>(reinterpret_cast<char*>(this) + offset); }

template<typename T, typename... Args>
decltype(auto) Call( void* instance, const std::size_t index, Args&&... args ) {
    auto vtable = *static_cast<void***>(instance);

    if constexpr (std::is_pointer_v<T> && std::is_function_v<std::remove_pointer_t<T>>) {
        using Fn = T;
        auto fn = reinterpret_cast<Fn>(vtable[index]);
        return fn(instance, std::forward<Args>(args)...);
    } else {
        using Fn = T(*)(void*, Args...);
        auto fn = reinterpret_cast<Fn>(vtable[index]);

        if constexpr (std::is_void_v<T>) {
            fn(instance, std::forward<Args>(args)...);
        } else {
            return fn(instance, std::forward<Args>(args)...);
        }
    }
}