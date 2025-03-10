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
#include <my_alloc.h>
#include <my_default.h>
#include <mysqld.h>

namespace xtrabackup {
namespace utils {

bool load_backup_my_cnf(my_option *options, char *path) {
  static MEM_ROOT argv_alloc{PSI_NOT_INSTRUMENTED, 512};
  const char *groups[] = {"mysqld", NULL};

  char *exename = (char *)"xtrabackup";
  char **backup_my_argv = &exename;
  int backup_my_argc = 1;
  char config_file[FN_REFLEN];

  /* we need full name so that only backup-my.cnf will be read */
  if (fn_format(config_file, "backup-my.cnf", path, "",
                MY_UNPACK_FILENAME | MY_SAFE_PATH) == NULL) {
    return (false);
  }

  if (my_load_defaults(config_file, groups, &backup_my_argc, &backup_my_argv,
                       &argv_alloc, NULL)) {
    return (false);
  }

  if (handle_options(&backup_my_argc, &backup_my_argv, options, NULL)) {
    return (false);
  }

  return (true);
}

}  // namespace utils
}  // namespace xtrabackup
