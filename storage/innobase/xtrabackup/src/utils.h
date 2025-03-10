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

#ifndef XTRABACKUP_UTILS_H
#define XTRABACKUP_UTILS_H
#include <my_getopt.h>
namespace xtrabackup {
namespace utils {

/**
  Reads list of options from backup-my.cnf at a given path

  @param [in]  options       list of options to read
  @param [in]  path       path where backup-my.cnf is located

  @return false in case of error, true otherwise
*/
extern bool load_backup_my_cnf(my_option *options, char *path);
}  // namespace utils
}  // namespace xtrabackup
#endif  // XTRABACKUP_UTILS_H
