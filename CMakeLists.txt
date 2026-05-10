cmake_minimum_required(VERSION 3.20)

project(RISCV_DOOM LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RISCV_ARCH rv32imac CACHE STRING "RISC-V ISA")
set(RISCV_ABI ilp32 CACHE STRING "RISC-V ABI")

set(COMMON_COMPILE_OPTIONS
    -march=${RISCV_ARCH}
    -mabi=${RISCV_ABI}
    -ffreestanding
    -fno-builtin
    -fdata-sections
    -ffunction-sections
    -Wall
    -Wextra
)

set(COMMON_LINK_OPTIONS
    -march=${RISCV_ARCH}
    -mabi=${RISCV_ABI}
    # -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
    -nostartfiles
    -Wl,--gc-sections
    # -Wl,-Map=doomgeneric.map
)

add_library(libsyscall STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/syscall.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/syscall.s
)

target_compile_options(libsyscall PRIVATE
    ${COMMON_COMPILE_OPTIONS}
    -fno-exceptions
    -fno-rtti
)

set(DOOM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/dummy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/am_map.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/doomdef.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/doomstat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/dstrings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/d_event.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/d_items.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/d_iwad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/d_loop.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/d_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/d_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/d_net.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/f_finale.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/f_wipe.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/g_game.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/hu_lib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/hu_stuff.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/info.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_cdmus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_endoom.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_joystick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_scale.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_sound.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_system.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/memio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_argv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_bbox.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_cheat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_config.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_controls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_fixed.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_menu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_misc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/m_random.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_ceilng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_doors.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_enemy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_floor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_inter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_lights.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_map.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_maputl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_mobj.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_plats.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_pspr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_saveg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_setup.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_sight.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_spec.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_switch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_telept.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_tick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/p_user.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_bsp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_data.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_draw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_plane.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_segs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_sky.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/r_things.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/sha1.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/sounds.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/statdump.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/st_lib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/st_stuff.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/s_sound.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/tables.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/v_video.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/wi_stuff.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/w_checksum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/w_file.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/w_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/w_wad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/z_zone.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/w_file_stdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_input.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/i_video.c
    ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/doomgeneric.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/doomgeneric_riscv.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/startup.s
)

add_executable(doomgeneric.elf)

target_compile_options(doomgeneric.elf PRIVATE
    ${COMMON_COMPILE_OPTIONS}
)

target_sources(doomgeneric.elf PRIVATE
    ${DOOM_SOURCES}
)

target_include_directories(doomgeneric.elf PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_options(doomgeneric.elf PRIVATE
    ${COMMON_LINK_OPTIONS}
)

target_link_libraries(doomgeneric.elf PRIVATE
    libsyscall
    m
    c
    gcc
)

add_custom_command(TARGET doomgeneric.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary doomgeneric.elf doomgeneric.bin
    COMMAND ${CMAKE_OBJDUMP} -d doomgeneric.elf > doomgeneric.dump
    COMMENT "Generating doomgeneric.bin and doomgeneric.dump"
)