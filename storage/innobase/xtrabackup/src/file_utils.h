/******************************************************
Copyright (c) 2021 Percona LLC and/or its affiliates.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA

*******************************************************/

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "my_inttypes.h"

/** Return a safer suffix of file_name, or "." if it has no safer
suffix. Check for fully specified file names and other atrocities.
Warn the user if we do not return file_name.
@param[in]  file_name            file_name to check
@param[out] prefix_len_out       the length of the unsafe prefix
@return ptr to a safer suffix of file_nam. */
const char *safer_name_suffix(char const *file_name, int *prefix_len_out);

bool file_exists(const char *filename);

bool is_path_separator(char c);

int mkdirp(const char *pathname, int Flags, myf MyFlags);

#endif
