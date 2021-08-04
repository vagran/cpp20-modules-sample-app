plugins {
    id("io.github.vagran.adk.gradle")
}

greeting {
    who = "Bob"
    AddModule("qqqq")
}

greeting {
    who = "Alice"
    AddModule("wwwww")
}

adk {
    buildType = "debug"
    define("S1", "S2")
    println(define)
    define("S3", "S4")
    println(define)
    include("aaa")
    println(include)
}

println(adk.binName)

apply(from = "valve_controller/tmp/module.gradle")
