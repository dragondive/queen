Queen Problem Solution and Analysis
===================================

This repository contains the solutions to the `Queen problem`_ in multiple
languages, and compares their execution runtimes. Contributions to improve these
solutions or provide solutions in other languages are welcome.

.. contents:: **Table of Contents**

Motivation and Background
-------------------------

I have not (yet?) formally studied Computer Science. I gained knowledge, skills, and
experience through self-learning during my professional career. I discovered the Queen
problem about 15 years ago. However, for several years, I struggled to understand the
backtracking mentioned in the solutions.

That changed one fateful day in 2018 when I found Abdul Bari's YouTube video
`6.1 N Queens Problem using Backtracking`_. His clear explanation helped me easily grasp
the "backtracking" solution, and I quickly prototyped it in C++.
[side-note: I used the online compiler `ideone`_ at the time to compile `my solution`_.
Interestingly, it ran successfully back then. However, when I accidentally submitted it
again recently without any code changes, it failed to compile due to the ``constexpr``
in the template parameter!]

I did not revisit the problem until mid-2024. In the interim, I gained more experience
with Python. I also self-learned CI/CD pipelines: Github Actions and Gitlab CI/CD. A few
weeks ago, I also started learning Rust. Putting together all these skills seemed like a
fun project, and that's how this project began.

Solution Structure
------------------

* Solutions are developed on the ``develop/queen`` branch, with a separate directory
  for each language.
* Github Actions workflows are developed directly on the ``main`` branch for now.
  This will change when this project has other contributors.
* Artifacts from the solution runs are stored on the ``artifacts`` branch in the
  ``artifacts`` directory.
* `Conventional commits`_ and squashed commits are used for a clean commit history.
* Tagging the solution versions and running the pipeline jobs is done manually for now.

Working Plan
------------

* **Step 1**: Move my 2018 C++ prototype here, fix bugs, reworked the solution to accept
  ``N`` as a command-line input, and write code documentation. :white_check_mark:
* **Step 2**: Translate the solution into Python and Rust. For uniformity of comparison,
  use the same algorithm, with language-specific adaptations as
  needed. :white_check_mark:
* **Step 3**: Develop the scripts to run and plot the solutions. This includes the
  pipeline build script and a script to run locally for convenience. :white_check_mark:
* **Step 4**: Share the first version of solutions and results
  publicly. :white_check_mark:
* **Step 5**: *To be revealed shortly!*
* **Step 6**: Optimize the solutions and the build scripts.
* ...
* **Step N**: *To be decided.*

Live Results
------------

**Plot of average execution time** (log scale)

|plot_log_scale|

**Plot of average execution time** (linear scale)

|plot_linear_scale|

.. _`Queen problem`: https://en.wikipedia.org/wiki/Eight_queens_puzzle
.. _`6.1 N Queens Problem using Backtracking`: https://www.youtube.com/watch?v=xFv_Hl4B83A
.. _`ideone`: https://ideone.com
.. _`my solution`: https://ideone.com/YU11ym
.. _`Conventional commits`: https://gist.github.com/qoomon/5dfcdf8eec66a051ecd85625518cfd13

.. |plot_log_scale| image:: https://github.com/dragondive/queen/blob/artifacts/artifacts/queen_log_scale_plot.svg
.. |plot_linear_scale| image:: https://github.com/dragondive/queen/blob/artifacts/artifacts/queen_linear_scale_plot.svg
