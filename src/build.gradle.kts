plugins {
    id("io.github.vagran.adk.gradle") version "1.0.1"
    // For local plugin (with adkGradlePluginPath specified):
    // id("io.github.vagran.adk.gradle")
}

adk {
    buildType = "debug"
    modules("sample_app", "modules/adk/src/adk", "modules/asio")
    binName = "sample_app"
    // "-fretain-comments-from-system-headers" required for clangd to work with PCMs but currently
    // causes clang 12 to crash during compilation, works with clang 13
    cflags("-pthread", "-fretain-comments-from-system-headers")
    if (buildType == "debug") {
        cflags("-gfull", "-gdwarf-4", "-gdwarf64", "-O0", "-fno-omit-frame-pointer")
        define("__DEBUG")
    } else {
        cflags("-O3")
    }
    linkflags("-pthread")
    cppModuleIfaceExt = listOf("cppm")
}
