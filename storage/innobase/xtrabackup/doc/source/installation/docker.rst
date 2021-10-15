.. _pxc.installing/docker.running:

Running Percona XtraBackup in a Docker container
********************************************************************************

You may run Percona XtraBackup in a Docker container without
having to install it. All required libraries come already installed in
the container.

Being a lightweight execution environment, Docker containers enable creating
configurations where each program runs in a separate container. You may run
|percona-server| in one container and Percona XtraBackup in another.

You create a new Docker container based on a Docker image, which works as a
template for newly created containers. Docker images for Percona XtraBackup
are hosted publicly on |docker-hub| at :code:`percona/percona-xtrabackup`.

.. code-block:: bash

   $ sudo docker create ... percona/percona-xtrabackup --name xtrabackup ...

.. rubric:: Scope of this section

Docker containers offer a range of different options effectively allowing
to create quite complex setup. This section demonstrates how to backup data
on a Percona Server for MySQL running in another Docker container.

Installing Docker
================================================================================

Your operating system may already provide a package for |cmd.docker|. However,
the versions of Docker provided by your operating system are likely to be
outdated.

Use the installation instructions for your operating system available from the
Docker site to set up the latest version of |cmd.docker|.

.. seealso::

   Docker Documentation:
      - `How to use Docker <https://docs.docker.com/>`_
      - `Installing <https://docs.docker.com/get-docker/>`_
      - `Getting started <https://docs.docker.com/get-started/>`_

Connecting to a |percona-server| container
================================================================================

Percona XtraBackup works in combination with a database server. When
running a Docker container for Percona XtraBackup, you can make
backups for a database server either installed on the host machine or running
in a separate Docker container.

To set up a database server on a host machine or in Docker
container, follow the documentation of the supported product that you
intend to use with Percona XtraBackup.

.. seealso::

   Percona Server for MySQL Documentation:
      - `Installing on a host machine
	<https://www.percona.com/doc/percona-server/5.7/installation.html>`_
      - `Running in a Docker container
	<https://www.percona.com/doc/percona-server/5.7/installation/docker.html>`_

.. code-block:: bash

   $ sudo docker run -d --name percona-server-mysql-5.7 \
   -e MYSQL_ROOT_PASSWORD=root percona/percona-server:5.7

As soon as Percona Server for MySQL runs, add some data to it. Now, you are
ready to make backups with Percona XtraBackup.

Creating a Docker container from Percona XtraBackup image
================================================================================

You can create a Docker container based on Percona XtraBackup image with
either |cmd.docker-create| or |cmd.docker-run| command. |cmd.docker-create|
creates a Docker container and makes it available for starting later.

Docker downloads the Percona XtraBackup image from the |docker-hub|. If it
is not the first time you use the selected image, Docker uses the image available locally.

.. code-block:: bash

   $ sudo docker create --name percona-xtrabackup-2.4 --volumes-from percona-server-mysql-5.7 \
   percona/percona-xtrabackup:2.4  \
   xtrabackup --backup --datadir=/var/lib/mysql/ --target-dir=/backup \
   --user=root --password=mysql

With |param.name| you give a meaningful name to your new Docker container so
that you could easily locate it among your other containers.

The |param.volumes-from| referring to *percona-server-mysql* indicates that you
indend to use the same data as the *percona-server-mysql* container.

Run the container with exactly the same parameters that were used when the container was created:

.. code-block:: bash

   $ sudo docker start -ai percona-xtrabackup-2.4

This command starts the *percona-xtrabackup* container, attaches to its
input/output streams, and opens an interactive shell.

The |cmd.docker-run| is a shortcut command that creates a Docker container and then immediately runs it.

.. code-block:: bash

   $ sudo docker run --name percona-xtrabackup-2.4 --volumes-from percona-server-mysql-5.7 \
   percona/percona-xtrabackup:2.4
   xtrabackup --backup --data-dir=/var/lib/mysql --target-dir=/backup --user=root --password=mysql

.. seealso::

   More in Docker documentation
      - `Docker volumes as persistent data storage for containers
	<https://docs.docker.com/storage/volumes/>`_
      - `More information about containers
	<https://docs.docker.com/config/containers/start-containers-automatically/>`_

.. include:: ../_res/replace/proper.txt
.. include:: ../_res/replace/command.txt
.. include:: ../_res/replace/parameter.txt
