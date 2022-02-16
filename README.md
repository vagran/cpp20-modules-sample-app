Sample application for [ADK gradle plugin](https://github.com/vagran/adk-cpp-gradle-plugin) and
[ADK library](https://github.com/vagran/adk-cpp) demonstrating use of C++20 modules.

Before building create `gradle.properties` file with the following content:
```
adkCxx=/path/to/bin/clang++
```

Update Git submodules:
```bash
git submodule update --init --recursive
```

Build the application:
```bash
./gradlew build
```

Compilation database can be generated by:
```bash
./gradlew generateCompileDb
```

Build artifacts can be found in `src/build/debug`.

Only most recent Clang versions are supported. There are still bugs in the Clang related to proper
implementation of C++20 modules 
(e.g. [lambda functions showstopper](https://bugs.llvm.org/show_bug.cgi?id=51607)).