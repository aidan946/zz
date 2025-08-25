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

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_cmd.step);

    const debug_exe = b.addExecutable(.{
        .name = "zz-debug",
        .root_module = b.createModule(.{
            .root_source_file = null,
            .target = target,
            .optimize = .Debug,
        }),
    });

    debug_exe.root_module.addCSourceFiles(.{
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
            "-g",
        },
    });

    debug_exe.linkLibC();
    debug_exe.linkLibCpp();
    debug_exe.linkSystemLibrary("pthread");

    const debug_cmd = b.addRunArtifact(debug_exe);
    if (b.args) |args| {
        debug_cmd.addArgs(args);
    }
    const debug_step = b.step("debug", "Build and run in debug mode");
    debug_step.dependOn(&debug_cmd.step);
}
