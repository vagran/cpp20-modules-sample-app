plugins {
    id("io.github.vagran.adk.gradle")
}

adk {
    buildType = "debug"
    modules("valve_controller", "modules/adk/src/adk", "modules/asio")
    binName = "valve_controller"
    cflags("-pthread")
    linkflags("-pthread")
    cppModuleIfaceExt = listOf("cppm")
}
