<div align="center">

  [![Pikafish][pikafish-logo]][website-link]


  <h3>Pikafish</h3>

  A free and strong UCI xiangqi engine.
  <br>
  <strong>[Explore Pikafish docs »][wiki-link]</strong>
  <br>
  <br>
  [Report bug][issue-link]
  ·
  [Open a discussion][discussions-link]
  ·
  [Discord][discord-link]
  ·
  [Blog][website-blog-link]

  [![Build][build-badge]][build-link]
  [![License][license-badge]][license-link]
  <br>
  [![Release][release-badge]][release-link]
  [![Commits][commits-badge]][commits-link]
  <br>
  [![Website][website-badge]][website-link]
  [![Fishtest][fishtest-badge]][fishtest-link]
  [![Discord][discord-badge]][discord-link]

</div>

## Overview

[Pikafish][website-link] is a **free and strong UCI xiangqi engine** derived from
Stockfish that analyzes xiangqi positions and computes the optimal moves.

Pikafish **does not include a graphical user interface** (GUI) that is required
to display a chessboard and to make it easy to input moves. These GUIs are
developed independently from Pikafish and are available online. **Read the
documentation for your GUI** of choice for information about how to use
Pikafish with it.

See also the Pikafish [documentation][wiki-usage-link] for further usage help.

## Files

This distribution of Pikafish consists of the following files:

  * [README.md][readme-link], the file you are currently reading.

  * [Copying.txt][license-link], a text file containing the GNU General Public
    License version 3.

  * [AUTHORS][authors-link], a text file with the list of authors for the official Pikafish project.

  * [src][src-link], a subdirectory containing the full source code, including a
    Makefile that can be used to compile Pikafish on Unix-like systems.

  * a file with the .nnue extension, storing the neural network for the NNUE
    evaluation.

## The UCI protocol

The [Universal Chess Interface][uci-link] (UCI) is a standard text-based protocol
used to communicate with a chess engine and is the recommended way to do so for
typical graphical user interfaces (GUI) or chess tools. Pikafish implements the
majority of its options.

Developers can see the default values for the UCI options available in Pikafish
by typing `./pikafish uci` in a terminal, but most users should typically use a
xiangqi GUI to interact with Pikafish.

For more information on UCI or debug commands, see our [documentation][wiki-commands-link].

## Compiling Pikafish

Pikafish has support for 32 or 64-bit CPUs, certain hardware instructions,
big-endian machines such as Power PC, and other platforms.

On Unix-like systems, it should be easy to compile Pikafish directly from the
source code with the included Makefile in the folder `src`. In general, it is
recommended to run `make help` to see a list of make targets with corresponding
descriptions.

```
cd src
make -j build ARCH=x86-64-modern
```

Detailed compilation instructions for all platforms can be found in our
[documentation][wiki-compile-link].

## Contributing

### Donating hardware

Improving Pikafish requires a massive amount of testing. You can donate your
hardware resources by installing the [Fishtest Worker][worker-link] and viewing
the current tests on [Fishtest][fishtest-link].

### Improving the code

In the [chessprogramming wiki][programming-link], many techniques used in
Pikafish are explained with a lot of background information.
The [section on Stockfish][programmingsf-link] describes many features
and techniques used by Stockfish. However, it is generic rather than
focused on Stockfish's precise implementation.

The engine testing is done on [Fishtest][fishtest-link].
If you want to help improve Pikafish, please read this [guideline][guideline-link]
first, where the basics of Pikafish development are explained.

Discussions about Pikafish take place these days mainly in the Pikafish
[Discord server][discord-link]. This is also the best place to ask questions
about the codebase and how to improve it.

## Terms of use

### GNU General Public License version 3

Pikafish is free and distributed under the
[**GNU General Public License version 3**][license-link] (GPL v3). Essentially,
this means you are free to do almost exactly what you want with the program,
including distributing it among your friends, making it available for download
from your website, selling it (either by itself or as part of some bigger
software package), or using it as the starting point for a software project of
your own.

The only real limitation is that whenever you distribute Pikafish in some way,
you MUST always include the license and the full source code (or a pointer to
where the source code can be found) to generate the exact binary you are
distributing. If you make any changes to the source code, these changes must
also be made available under GPL v3.

### NNUE-License

Any usage of the Pikafish weights constitutes agreement to this License.

The weight file (pikafish.nnue) released with the pikafish and the weight file further derived from the weight are:
1. Only for legal use, any consequences caused by any use beyond the legal scope (e.g. online cheating) shall be borne by the user.
2. No commercial use without permission.

The use of the nnue weights file for commercial purposes by the following individuals and organizations is permitted, in appreciation of their support:
1. [![Just Xiangqi][justxq-logo]][justxq-link]

The following individuals and organizations are prohibited from using the nnue weights file
derived from this program due to their unfriendly actions, activities, and license violations:
1. 鹏飞象棋
2. 国圣象棋
3. 飞风追云
4. 枯叶
5. 静香
6. 老步
7. 刀霸刘涛

[authors-link]:			https://github.com/official-pikafish/Pikafish/blob/master/AUTHORS
[build-badge]:			https://img.shields.io/github/actions/workflow/status/official-pikafish/Pikafish/pikafish.yml?branch=master&style=for-the-badge&label=pikafish&logo=github
[build-link]:				https://github.com/official-pikafish/Pikafish/actions/workflows/pikafish.yml
[commits-badge]:		https://img.shields.io/github/commits-since/official-pikafish/Pikafish/latest?style=for-the-badge
[commits-link]:			https://github.com/official-pikafish/Pikafish/commits/master
[discord-badge]:			https://img.shields.io/discord/1013130558089478144?style=for-the-badge&label=discord&logo=Discord
[discord-link]:			https://discord.com/invite/uSb3RXb7cY
[discussions-link]:   https://github.com/official-pikafish/Pikafish/discussions/new
[fishtest-badge]:			https://img.shields.io/website?style=for-the-badge&down_color=red&down_message=Offline&label=Fishtest&up_color=success&up_message=Online&url=https://test.pikafish.org
[fishtest-link]:			https://test.pikafish.org
[guideline-link]:			https://github.com/glinscott/fishtest/wiki/Creating-my-first-test
[issue-link]:         https://github.com/official-pikafish/Pikafish/issues/new?assignees=&labels=&template=BUG-REPORT.yml
[justxq-link]:			https://store.steampowered.com/app/2248180/_/
[justxq-logo]:      https://user-images.githubusercontent.com/73384062/217706511-55497939-4a95-4614-98ef-d153083d8a83.png
[license-badge]:			https://img.shields.io/github/license/official-pikafish/Pikafish?style=for-the-badge&label=license&color=success
[license-link]:			https://github.com/official-pikafish/Pikafish/blob/master/Copying.txt
[pikafish-logo]:			https://pikafish.org/assets/logo_256.png
[programming-link]:		https://www.chessprogramming.org/Main_Page
[programmingsf-link]:	https://www.chessprogramming.org/Stockfish
[qqgroup-link]:			https://jq.qq.com/?_wv=1027&k=FORWUh4W
[readme-link]:			https://github.com/official-pikafish/Pikafish/blob/master/README.md
[release-badge]:			https://img.shields.io/github/v/release/official-pikafish/Pikafish?style=for-the-badge&label=official%20release
[release-link]:			https://github.com/official-pikafish/Pikafish/releases/latest
[src-link]:				https://github.com/official-pikafish/Pikafish/tree/master/src
[uci-link]:				https://backscattering.de/chess/uci/
[website-badge]:		https://img.shields.io/website?style=for-the-badge&down_color=red&down_message=Offline&label=website&up_color=success&up_message=Online&url=https://pikafish.org
[website-link]:			https://pikafish.org
[website-blog-link]:  https://pikafish.org/
[wiki-link]:          https://github.com/official-pikafish/Pikafish/wiki
[wiki-usage-link]:    https://github.com/official-pikafish/Pikafish/wiki/Download-and-usage
[wiki-compile-link]:  https://github.com/official-pikafish/Pikafish/wiki/Compiling-from-source
[wiki-commands-link]: https://github.com/official-pikafish/Pikafish/wiki/Commands
[worker-link]:			https://github.com/xyztnecniV/yolo/
