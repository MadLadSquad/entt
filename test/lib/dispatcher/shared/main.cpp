#include <gtest/gtest.h>
#include <common/boxed_type.h>
#include <entt/core/attribute.h>
#include <entt/core/utility.hpp>
#include <entt/signal/dispatcher.hpp>

ENTT_API void trigger(entt::dispatcher &);

struct listener {
    void on(test::boxed_int msg) {
        value = msg.value;
    }

    int value{};
};

TEST(Lib, Dispatcher) {
    entt::dispatcher dispatcher;
    listener listener;

    ASSERT_EQ(listener.value, 0);

    dispatcher.sink<test::boxed_int>().connect<entt::overload<void(test::boxed_int)>(&listener::on)>(listener);
    trigger(dispatcher);

    ASSERT_EQ(listener.value, 2);
}
