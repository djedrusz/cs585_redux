cmake_minimum_required(VERSION 2.6)
add_definitions("-std=c++11")

project(tests)
find_package(Threads)
include_directories(../gtest/include)
link_directories(../gtest)
set(CMAKE_MODULE_PATH "." ${CMAKE_MODULE_PATH})
find_package(SFML 2.1.0 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
add_executable(tests test_default_allocator.cpp test_counting_allocator.cpp test_dynamic_array.cpp test_map.cpp test_stack_guard.cpp ../src/engine/data/json_value.cpp ../src/engine/data/json_parser.cpp test_json_parser.cpp ../src/engine/input/input.cpp test_input.cpp ../src/engine/rendering/renderable_sprite.cpp test_renderable_sprite.cpp ../src/engine/rendering/renderer.cpp test_renderer.cpp ../src/engine/scene/scene.cpp test_scene.cpp ../src/engine/scene/rectangle_bounds.cpp test_rectangle_bounds.cpp ../src/engine/scene/nxn_scene_graph.cpp test_nxn_scene_graph.cpp tests.cpp
../src/engine/events/event_dispatcher.cpp
test_event_dispatcher.cpp
../src/engine/events/event_bus.cpp
test_event_bus.cpp
../src/engine/events/mapped_event_dispatcher.cpp
test_mapped_event_dispatcher.cpp
../src/engine/assets/texture_manager.cpp
test_smart_map.cpp)
target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(tests ${SFML_LIBRARIES})

project(test_smart_map_visual)
add_executable(test_smart_map_visual
test_smart_map_visual.cpp)

project(test_renderer)
set(CMAKE_MODULE_PATH "." ${CMAKE_MODULE_PATH})
find_package(SFML 2.1.0 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
add_executable(test_renderer ../src/engine/data/json_value.cpp ../src/engine/data/json_parser.cpp ../src/engine/input/input.cpp ../src/engine/rendering/renderable_sprite.cpp ../src/engine/rendering/renderer.cpp ../src/engine/input/input.cpp ../src/engine/scene/scene.cpp test_renderer_visual.cpp
../src/engine/assets/texture_manager.cpp)
target_link_libraries(test_renderer ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_renderer ${SFML_LIBRARIES})

project(test_sound)
set(CMAKE_MODULE_PATH "." ${CMAKE_MODULE_PATH})
find_package(SFML 2.1.0 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
add_executable(test_sound 
../src/engine/input/input.cpp
../src/engine/scene/scene.cpp
../src/engine/events/sound_event.cpp
../src/engine/sound/sounds.cpp
../src/engine/events/mapped_event_dispatcher.cpp
../src/engine/events/event_bus.cpp
test_sound.cpp)
target_link_libraries(test_sound ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_sound ${SFML_LIBRARIES})

project(test_actor_controller)
set(CMAKE_MODULE_PATH "." ${CMAKE_MODULE_PATH})
find_package(SFML 2.1.0 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
add_executable(test_actor_controller
../src/engine/rendering/renderable_sprite.cpp
../src/engine/rendering/renderer.cpp
../src/engine/scene/scene.cpp
../src/engine/input/input.cpp
../src/engine/events/mapped_event_dispatcher.cpp
../src/engine/events/event_bus.cpp
../src/engine/assets/texture_manager.cpp
test_actor_controller.cpp)
target_link_libraries(test_actor_controller ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_actor_controller ${SFML_LIBRARIES})

project(test_scene_graph)
add_definitions(-DNXN_SCENE_GRAPH_TESTING)
add_executable(test_scene_graph
../src/engine/scene/rectangle_bounds.cpp
../src/engine/scene/nxn_scene_graph.cpp
test_scene_graph_visual.cpp)

project(assignment8)
set(CMAKE_MODULE_PATH "." ${CMAKE_MODULE_PATH})
find_package(SFML 2.1.0 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
add_executable(assignment8
../src/engine/assets/texture_manager.cpp

../src/engine/events/collision_event.cpp
../src/engine/events/mapped_event_dispatcher.cpp

../src/engine/input/input.cpp

../src/engine/rendering/renderable_sprite.cpp
../src/engine/rendering/renderer.cpp
../src/engine/rendering/render_manager.cpp

../src/engine/scene/nxn_scene_graph.cpp
../src/engine/scene/rectangle_bounds.cpp
../src/engine/scene/scene.cpp
../src/engine/scene/scene_manager.cpp

../src/game/actors/move_to_box.cpp
../src/game/actors/player_controlled_box.cpp

../src/game/collidables/collidable_box.cpp

../src/game/controllers/move_to_controller.cpp
../src/game/controllers/player_controller.cpp

../src/game/factories/move_to_factory.cpp
../src/game/factories/player_controlled_factory.cpp

assignment8.cpp)
target_link_libraries(assignment8 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(assignment8 ${SFML_LIBRARIES})