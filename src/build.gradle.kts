plugins {
    id("io.github.vagran.adk.gradle") version "1.0.1"
    // For local plugin (with adkGradlePluginPath specified):
    // id("io.github.vagran.adk.gradle")
}

adk {
    buildType = "debug"
    modules("sample_app", "modules/adk/src/adk", "modules/asio")
    binName = "sample_app"
    cflags("-pthread")
    linkflags("-pthread")
    cppModuleIfaceExt = listOf("cppm")
}
