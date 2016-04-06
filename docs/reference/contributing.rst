Contributing to Beanspeak
=========================

Beanspeak is an open source project and a volunteer effort.
Beanspeak welcomes contribution from everyone.

Contributions
-------------

Contributions to Beanspeak should be made in the form of GitHub pull requests.
Each pull request will be reviewed by a core contributor (someone with permission
to land patches) and either landed in the main tree or given feedback for changes
that would be required before it can be merged. All contributions should follow
this format, even those from core contributors.

Bug Report Checklist
--------------------

* Make sure you are using the latest released version of Beanspeak before
  submitting a bug report. Bugs in versions older than the latest released one
  will not be addressed by the core team.
* If you have found a bug it is important to add relevant reproducibility
  information to your issue to allow us to reproduce the bug and fix it quicker.
  Add a script, small program or repository providing the necessary code to make
  everyone reproduce the issue reported easily. If a bug cannot be reproduced by
  the development it would be difficult provide corrections and solutions.
* Be sure that information such as OS, Beanspeak version and PHP version are
  part of the bug report. You can get Beanspeak version by using
  :code:`php --ri beanspeak` command.
* If you're submitting a Segmentation Fault error, we would require a backtrace,
  please see :doc:`Generating a Backtrace <gdb>`.

Pull Request Checklist
----------------------

* Don't submit your pull requests to the `master` branch. Branch from the required
  branch and, if needed, rebase to the proper branch before submitting your pull
  request. If it doesn't merge cleanly with master you may be asked to rebase your
  changes.
* Don't put submodule updates in your pull request unless they are to landed commits.
* Add tests relevant to the fixed bug or new feature.
* Beanspeak is written in `Zephir`_, please
  do not submit commits that modify C generated files directly or those whose
  functionality/fixes are implemented in the C programming language.
* Remove any change to :code:`ext/kernel`, :code:`*.zep.c`, :code:`*.zep.h` files
  before submitting the pull request.

Getting Support
---------------

Feel free to ask any question at `Beanspeak issues`_ page.

Related Guides
--------------
.. toctree::
    :maxdepth: 1

    gdb

.. _Zephir: https://github.com/phalcon/zephir/
.. _Beanspeak issues: https://github.com/phalcongelist/beanspeak/issues
