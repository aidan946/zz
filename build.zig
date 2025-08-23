const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "zz",
        .root_module = b.createModule(.{
            .root_source_file = null,
            .target = target,
            .optimize = optimize,
        }),
    });

    exe.root_module.addCSourceFiles(.{
        .files = &.{
            "src/main.cpp",
            "src/parsing.cpp",
            "src/printer.cpp",
        },
        .flags = &.{
            "-std=c++23",
            "-Wall",
            "-Wextra",
            "-Wpedantic",
        },
    });

    exe.linkLibC();
    exe.linkLibCpp();
    exe.linkSystemLibrary("pthread");

    b.installArtifact(exe);
}
