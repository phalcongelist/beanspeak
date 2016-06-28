Installation
============

PHP extensions require a slightly different installation method to a traditional
PHP-based library or framework. You can either download a binary package for the
system of your choice or build it from the sources.

Linux/Solaris
-------------

On a Linux/Solaris system you can easily compile and install the extension from the source code:

Requirements
^^^^^^^^^^^^

Prerequisite packages are:

* PHP >= 5.4 development resources
* GCC compiler (Linux/Solaris)
* Git (if not already installed in your system - unless you download the package from GitHub and upload it on your server via FTP/SFTP)
* `Zephir`_ >= 0.9.3a-dev

Specific packages for common platforms:

.. code-block:: bash

    # Ubuntu
    sudo apt-get install php5-dev gcc make

    # Suse
    sudo yast -i php5-devel gcc make autoconf

    # CentOS/RedHat/Fedora
    sudo yum install php-devel gcc make

    # Solaris
    pkg install php-54 apache-php54 gcc-45

Of course, you need to install PHP development headers and tools appropriate for your current PHP version.

Compilation
^^^^^^^^^^^

Creating the extension:

.. code-block:: bash

    git clone --depth=1 https://github.com/phalcongelist/beanspeak.git
    cd beanspeak
    zephir build
    # Or, for PHP 7 use
    zephir build --ZendEngine3

.. highlights::

   **Important:** After that, the compiled extension will be placed in the appropriate directory.
   If the automatic installer failed to do this try moving extension manually.

   .. code-block:: bash

      # Use right path to the PHP extensions dir here
      sudo cp ext/modules/beanspeak.so /usr/lib/php5/20121212

Add extension to your PHP configuration:

.. code-block:: bash

    # Suse: Add a file called beanspeak.ini in /etc/php5/conf.d/ with this content:
    extension=beanspeak.so

    # CentOS/RedHat/Fedora: Add a file called beanspeak.ini in /etc/php.d/ with this content:
    extension=beanspeak.so

    # Ubuntu/Debian with apache2: Add a file called 50-beanspeak.ini in /etc/php5/apache2/conf.d/ with this content:
    extension=beanspeak.so

    # Ubuntu/Debian with php5-fpm: Add a file called 50-beanspeak.ini in /etc/php5/fpm/conf.d/ with this content:
    extension=beanspeak.so

    # Ubuntu/Debian with php5-cli: Add a file called 50-beanspeak.ini in /etc/php5/cli/conf.d/ with this content:
    extension=beanspeak.so

Restart the webserver.

.. _Zephir: https://github.com/phalcon/zephir/
