#
#  cmake/FindDISCORD.cmake
#
#  Copyright 2021 ROllerozxa
#
#  This file is part of MilkyTracker.
#
#  MilkyTracker is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  MilkyTracker is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with MilkyTracker.  If not, see <http://www.gnu.org/licenses/>.
#

# - Try to find Discord RPC
# Once done this will define
#  DISCORD_FOUND - System has Discord RPC
#  DISCORD_INCLUDE_DIRS - The Discord RPC include directories
#  DISCORD_LIBRARIES - The libraries needed to use DISCORD
#  DISCORD_DEFINITIONS - Compiler switches required for using DISCORD
#  DISCORD_VERSION_STRING - The version of DISCORD

find_package(PkgConfig QUIET)
pkg_check_modules(PC_DISCORD QUIET discord-rpc)
set(DISCORD_DEFINITIONS ${PC_DISCORD_CFLAGS_OTHER})

find_path(
    DISCORD_INCLUDE_DIR discord_rpc.h
    HINTS ${PC_DISCORD_INCLUDEDIR} ${PC_DISCORD_INCLUDE_DIRS}
)

find_library(DISCORD_LIBRARY NAMES discord-rpc
    HINTS ${PC_DISCORD_LIBDIR} ${PC_DISCORD_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    DISCORD
    REQUIRED_VARS DISCORD_LIBRARY DISCORD_INCLUDE_DIR
    VERSION_VAR DISCORD_VERSION_STRING
)

mark_as_advanced(DISCORD_INCLUDE_DIR DISCORD_LIBRARY)

if(DISCORD_FOUND)
	set(DISCORD_FOUND true)
    set(DISCORD_LIBRARIES ${DISCORD_LIBRARY})
    set(DISCORD_INCLUDE_DIRS ${DISCORD_INCLUDE_DIR})
endif()
