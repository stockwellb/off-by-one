-- off-by-one: a growing pile of tiny C programs, one per directory.
--
-- Every folder that contains a `main.c` becomes its own build target,
-- named after the folder. To add a new exercise, just create a new
-- directory with a main.c in it -- no edits to this file required.
--
--   xmake                     build everything
--   xmake build 03-write      build just one exercise
--   xmake run 03-write        build + run it (cwd is that folder)
--   xmake run                 run every target
--   xmake -r / --rebuild      force a rebuild
--   xmake f -m debug          switch mode (debug is the default below)

set_project("off-by-one")

-- Learning C: turn the compiler into a strict teacher.
set_languages("c11")
set_warnings("all", "extra")
set_defaultmode("debug")

if is_mode("debug") then
    add_defines("DEBUG")
    set_symbols("debug")
    set_optimize("none")
    -- Catch the footguns from IDEAS.md at runtime.
    add_cflags("-fsanitize=address,undefined", {force = true})
    add_ldflags("-fsanitize=address,undefined", {force = true})
end

-- Auto-discover one target per `*/main.c`.
for _, mainfile in ipairs(os.files("*/main.c")) do
    local dir = path.directory(mainfile)
    target(dir)
        set_kind("binary")
        add_files(dir .. "/*.c")
        -- Run inside the exercise's own folder so scratch files
        -- (test.bin, test.txt, ...) land there, not at the repo root.
        set_rundir("$(projectdir)/" .. dir)
        -- Silence macOS's harmless "nano zone abandoned" warning that
        -- AddressSanitizer triggers by replacing the system allocator.
        set_runenv("MallocNanoZone", "0")
    target_end()
end
