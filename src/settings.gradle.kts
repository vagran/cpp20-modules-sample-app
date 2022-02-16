rootProject.name = "sample_app"
// Take directly for development purposes
if (extra.has("adkGradlePluginPath")) {
    includeBuild(extra["adkGradlePluginPath"]!!)
}
