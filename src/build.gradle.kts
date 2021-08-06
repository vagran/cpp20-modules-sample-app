plugins {
    id("io.github.vagran.adk.gradle")
}

adk {
    buildType = "debug"
    define("S1", "S2")
    println(define)
    define("S3", "S4")
    println(define)
    include("aaa", "/bbb", "ccc/ddd")
    println(include)
//    modules("valve_controller", "modules/adk/src/adk", "modules/asio")
    modules("modules/adk/src/adk")
    println(modules)
}

println(adk.binName)
