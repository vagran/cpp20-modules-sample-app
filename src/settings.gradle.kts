rootProject.name = "water_valve"
// Take directly for development purposes
if (extra.has("adkGradlePluginPath")) {
    includeBuild(extra["adkGradlePluginPath"]!!)
}
