file(GLOB_RECURSE SOURCES ./*.c )
idf_component_register(SRCS ${SOURCES}
                   INCLUDE_DIRS 
                                .
                    INCLUDE_DIRS "../../main/lvgl_file"
                    REQUIRES  lvgl
                              lvgl_esp32_drivers
                              )