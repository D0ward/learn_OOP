find_package(yaml-cpp REQUIRED)

add_library(security_system

    suciruty_system.hpp

    ai/ai.cpp
    ai/ai.hpp
    
    component/base/component.cpp
    component/base/component.hpp
    component/intruder/intruder.cpp
    component/intruder/intruder.hpp
    component/platform/base/platform.cpp
    component/platform/base/platform.hpp
    component/platform/mobile/mobile.cpp
    component/platform/mobile/mobile.hpp
    component/platform/static/static.hpp
    component/wall/wall.hpp
    
    environment/environment.cpp
    environment/environment.hpp
    
    module/base/module.cpp
    module/base/module.hpp
    module/military/military.cpp
    module/military/military.hpp
    module/network/network.cpp
    module/network/network.hpp
    module/sensor/sensor.cpp
    module/sensor/sensor.hpp

    table/table.hpp

    ui/controller.cpp
    ui/controller.hpp
    ui/app.cpp
    ui/app.hpp
    
)

target_link_libraries(security_system yaml-cpp)

