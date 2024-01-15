# Novo Bus Analyzer

<p align="center">
  <img src="resources/logo.png">
</p>

1. For setting up the development environment, please refer to the document `development_environment.pdf` occuring under the [BUSMASTER documentation](https://reymor.github.io/documentation/2023/12/06/busmaster-docs.html).

2. This BUSMASTER application is entirely compilable and it is possible to run it in simulation mode by following the instruction set provided in the aforementioned document.

3. In order to build an installation application, please follow the instruction set in the developer's environment document. The install script and the related artifacts occur under `Installation Setup` folder.

# Dependencies

`NBA` inherits from `Busmaster` the build system and all dependencies. However, right now for compilation is possible to use `cmake` instead of `*.sln` which is mainly based on `Visual Studio 2013` and `Qt5.5.1`. I have compile with `Visual Studio 2019` using `Qt5.15.2`
