.. _working_with_binlogs:

Working with Binary Logs
========================

The ``xtrabackup`` binary integrates with information that |InnoDB|
stores in its transaction log about the corresponding binary log
position for committed transactions. This enables it to print out the
binary log position to which a backup corresponds, so you can use it
to set up new replication replicas or perform point-in-time recovery.

Finding the Binary Log Position
--------------------------------

You can find the binary log position corresponding to a backup once
the backup has been prepared. This can be done by either running the
|xtrabackup| with the :option:`--prepare` or
:option:`--apply-log-only` option. If your backup is from a server
with binary logging enabled, |xtrabackup| will create a file named
:file:`xtrabackup_binlog_info` in the target directory. This file
contains the binary log file name and position of the exact point in
the binary log to which the prepared backup corresponds.

You will also see output similar to the following during the prepare stage: ::

  InnoDB: Last MySQL binlog file position 0 3252710, file name ./mysql-bin.000001
  ... snip ...
  [notice (again)]
    If you use binary log and don't use any hack of group commit, 
    the binary log position seems to be:
  InnoDB: Last MySQL binlog file position 0 3252710, file name ./mysql-bin.000001

This output can also be found in the :file:`xtrabackup_binlog_pos_innodb` file, but **it is only correct** when no other than |XtraDB| or |InnoDB| are used as storage engines.

If other storage engines are used (i.e. |MyISAM|), you should use the :file:`xtrabackup_binlog_info` file to retrieve the position.

The message about hacking group commit refers to an early implementation of emulated group commit in |Percona Server|.

Point-In-Time Recovery
-----------------------

To perform a point-in-time recovery from an ``xtrabackup`` backup, you should prepare and restore the backup, and then replay binary logs from the point shown in the :file:`xtrabackup_binlog_info` file. 

A more detailed procedure is found :ref:`here <pxb.xtrabackup.point-in-time-recovery>`.


Setting Up a New Replication Replica
-------------------------------------

To set up a new replica, you should prepare the backup, and restore it to the data directory of your new replication replica. If you are using version 8.0.22 or earlier, in your ``CHANGE MASTER TO`` command, use the binary log filename and position shown in the :file:`xtrabackup_binlog_info` file to start replication. 

If you are using 8.0.23 or later, use the `CHANGE_REPLICATION_SOURCE_TO and the appropriate options <https://dev.mysql.com/doc/refman/8.0/en/change-replication-source-to.html>`__. ``CHANGE_MASTER_TO`` is deprecated. 

A more detailed procedure is found in  :doc:`../howtos/setting_up_replication`.
