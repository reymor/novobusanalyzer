# Novo Bus Analyzer

<p align="center">
  <img src="resources/logo.png">
</p>

1. For setting up the development environment, please refer to the document `development_environment.pdf` occuring under the [BUSMASTER documentation](https://reymor.github.io/documentation/2023/12/06/busmaster-docs.html).

2. This BUSMASTER application is entirely compilable and it is possible to run it in simulation mode by following the instruction set provided in the aforementioned document.

3. In order to build an installation application, please follow the instruction set in the developer's environment document. The install script and the related artifacts occur under `Installation Setup` folder.

# Dependencies

`NBA` has migrated the build system and now it uses `cmake`. However, right now for compilation you shall use `Visual Studio 2019 or 2022`. Qt code has been migrated to `Qt6`.

- cmake >= 3.27
- Visual Studio 2019 or 2022
- Qt6 tested on v6.8.1
- You shall configure the compilation for `Win32`
