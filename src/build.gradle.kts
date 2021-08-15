plugins {
    id("io.github.vagran.adk.gradle")
}

adk {
    buildType = "debug"
    modules("valve_controller", "modules/adk/src/adk", "modules/asio")
    cflags("-pthread")
    linkflags("-pthread")
}
